#pragma once

#include <Windows.h>
#include <array>
#include <memory>

class MemProtect
{
        void* addr;
        uint size;
        DWORD flags;
        bool released = false;

    public:
        /// <summary>
        /// Creates a protection object with the given arguments
        /// </summary>
        /// <param name="address">The address which should be affected</param>
        /// <param name="size">The size of the memory which should be affected</param>
        MemProtect(LPVOID address, uint size) : addr(address), size(size), flags(0) { VirtualProtect(addr, this->size, PAGE_EXECUTE_READWRITE, &this->flags); }

        /// <summary>
        /// Destroys the protection object and automatically restores old flags
        /// </summary>
        ~MemProtect()
        {
            if (!released)
            {
                VirtualProtect(addr, size, flags, &flags);
            }
        }

        /**
         * @brief
         * Mark this memory protection as released, or otherwise no longer valid.
         * If released, destructing this object will no longer attempt to revert the protection
         */
        void Release() { released = true; }

        [[nodiscard]]
        void* GetAddr() const
        {
            return addr;
        }
};

template <typename CallSig>
class FunctionDetour final
{
        void* originalFunc;
        PBYTE data;
        std::allocator<unsigned char> alloc;
        bool detoured = false;

        MemProtect protection;

    public:
        CallSig GetOriginalFunc() { return reinterpret_cast<CallSig>(originalFunc); }

        explicit FunctionDetour(CallSig origFunc) : originalFunc(reinterpret_cast<void*>(origFunc)), protection(originalFunc, 5) { data = alloc.allocate(5); }
        ~FunctionDetour()
        {
            UnDetour();
            alloc.deallocate(data, 5);
        }

        FunctionDetour(const FunctionDetour&) = delete;
        FunctionDetour& operator=(FunctionDetour) = delete;

        /**
         * @brief
         * Release the underlying memory protection, preventing lockup if the hooked address is no longer valid
         * It will also set the detour state to false, so the destructor will not attempt to remove the detour
         */
        void Release()
        {
            detoured = false;
            protection.Release();
        }

        void Detour(const CallSig hookedFunc)
        {
            if (detoured)
            {
                return;
            }

            detoured = true;

            std::array<byte, 5> patch{}; // We need to change 5 bytes and I'm going to use memcpy so this is the simplest way.
            patch[0] = 0xE9;             // Set the first byte of the byte array to the op code for the JMP instruction.
            DWORD relativeAddress = (DWORD)hookedFunc - (DWORD)originalFunc - 5; // Calculate the relative JMP address.
            memcpy(&patch[1], &relativeAddress, 4);                              // Copy the relative address to the byte array.
            memcpy(data, originalFunc, 5);
            memcpy(originalFunc, patch.data(), 5); // Change the first 5 bytes to the JMP instruction.
        }

        void UnDetour()
        {
            if (!detoured)
            {
                return;
            }

            detoured = false;

            memcpy(originalFunc, data, 5);
        }
};

template <DWORD Start, DWORD End, DWORD Count = (End - Start) / 4 + 1>
class VTableHook final
{
        static constexpr DWORD Size = End - Start + 4;
        const char* dll;

        MemProtect memProtect;

        std::array<void*, Count> originals;

    public:
        explicit VTableHook(const char* dll) : dll(dll), memProtect(reinterpret_cast<void*>(reinterpret_cast<DWORD>(GetModuleHandleA(dll)) + Start), Size)
        {
            memcpy_s(originals.data(), Size, reinterpret_cast<void*>(reinterpret_cast<DWORD>(GetModuleHandleA(dll)) + Start), Size);
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        void Hook(const unsigned short index, const void* replacementFunction) const
        {
            assert(index < Count);
            memcpy_s(reinterpret_cast<void*>(reinterpret_cast<DWORD>(GetModuleHandleA(dll)) + Start + index * 4), 4, replacementFunction, 4);
        }

        /**
         * @brief Gets a pointer to the original function with a given index
         * @param index Index of the function that should be retrieved
         * @returns Returns the function pointer casted into a given function type
         **/
        [[nodiscard]]
        void* GetOriginal(const unsigned short index) const
        {
            assert(index < Count);
            return originals[index];
        }

        /**
         * @brief Unhooks specific index
         * @param index Index of the function that should be unhooked
         **/
        void Unhook(const unsigned short index) const
        {
            assert(index < Count);
            memcpy_s(reinterpret_cast<void*>(reinterpret_cast<DWORD>(GetModuleHandleA(dll)) + Start + index * 4), 4, GetOriginal(index), 4);
        }

        ~VTableHook()
        {
            auto lib = GetModuleHandleA(dll);
            if (!lib)
            {
                return;
            }

            // in case of address mismatch (due to dll being reloaded), omit reapplying the protection and gracefully exit
            if (const auto patchAddr = reinterpret_cast<void*>(reinterpret_cast<DWORD>(lib) + Start); patchAddr == memProtect.GetAddr())
            {
                if (VirtualProtect(patchAddr, Size, PAGE_EXECUTE_READWRITE, nullptr))
                {
                    memcpy_s(patchAddr, Size, originals.data(), Size);
                }
            }
        }
};
