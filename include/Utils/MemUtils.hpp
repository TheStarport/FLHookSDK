#pragma once

#include <Windows.h>

class MemUtils
{
    public:
        MemUtils() = delete;

        static HWND GetFlServerHwnd()
        {
            auto* unkThis = reinterpret_cast<void*>(0x00426C58);
            return *reinterpret_cast<HWND*>(*(static_cast<PDWORD>(unkThis) + 8) + 32);
        }

        static unsigned long Protect(const unsigned long addr, const size_t length, const bool execute = true)
        {
            return Protect(reinterpret_cast<void*>(addr), length, execute);
        }

        static unsigned long Protect(void* addr, const size_t length, const bool execute = true)
        {
            unsigned long oldProtect;
            VirtualProtect(addr, length, execute ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE, &oldProtect);
            return oldProtect;
        }

        static void SwapBytes(void* ptr, const unsigned len)
        {
            if (len % 4)
            {
                return;
            }

            for (unsigned i = 0; i < len; i += 4)
            {
                char* ptr1 = static_cast<char*>(ptr) + i;
                unsigned long temp;
                memcpy(&temp, ptr1, 4);
                const auto ptr2 = (char*)&temp;
                memcpy(ptr1, ptr2 + 3, 1);
                memcpy(ptr1 + 1, ptr2 + 2, 1);
                memcpy(ptr1 + 2, ptr2 + 1, 1);
                memcpy(ptr1 + 3, ptr2, 1);
            }
        }

        static void ReadProcMem(const unsigned long address, void* mem, const unsigned size)
        {
            auto ptr = reinterpret_cast<void*>(address);
            unsigned long dwOldProtection = 0;
            VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            memcpy(mem, ptr, size);
        }

        static void WriteProcMem(const unsigned long address, const void* mem, const unsigned size)
        {
            auto ptr = reinterpret_cast<void*>(address);
            unsigned long dwOldProtection = 0;
            VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            memcpy(ptr, mem, size);
        }

        static FARPROC PatchCallAddr(void* mod, const unsigned long installAddress, void* hookFunction)
        {
            return PatchCallAddr((unsigned long)mod + installAddress, hookFunction);
        }

        static FARPROC PatchCallAddr(const unsigned long mod, const unsigned long installAddress, void* hookFunction)
        {
            return PatchCallAddr(mod + installAddress, hookFunction);
        }

        static FARPROC PatchCallAddr(const unsigned long installAddress, void* hookFunction)
        {
            unsigned long relAddr;
            ReadProcMem(installAddress + 1, &relAddr, 4);

            unsigned long offset = (unsigned long)hookFunction - (unsigned long)(installAddress + 5);
            WriteProcMem(installAddress + 1, &offset, 4);

            return (FARPROC)(relAddr + installAddress + 5);
        }

        /**
         * \brief Overwrite an address with a JMP instruction to the target function
         * \param address The absolute address where the function should be called from
         * \param hookFunction The function to be called at the provided address
         * \param call Replace the JMP instruction with a CALL instruction, which will push the return address onto the stack.
         * \param protect If true, apply needed protections to allow writing. Pass false if protection already removed elsewhere.
         */
        static void PatchAssembly(const unsigned long address, const void* hookFunction, const bool call = false, const bool protect = true)
        {
            unsigned long dwOldProtection = 0;     // Create a unsigned long for VirtualProtect calls to allow us to write.
            BYTE patch[5];                 // We need to change 5 bytes and I'm going to use memcpy so this is the simplest way.
            patch[0] = call ? 0xE8 : 0xE9; // Set the first byte of the byte array to the op code for the JMP instruction.
            if (protect)
            {
                // Allow us to write to the memory we need to change
                VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            }

            const auto relativeAddress = reinterpret_cast<unsigned long>(hookFunction) - address - 5; // Calculate the relative JMP address.
            memcpy(&patch[1], &relativeAddress, 4);             // Copy the relative address to the byte array.
            memcpy(reinterpret_cast<PBYTE>(address), patch, 5); // Change the first 5 bytes to the CALL/JMP instruction.
        }

        static void NopAddress(const unsigned long address, const size_t size)
        {
            unsigned long dwOldProtection = 0;
            VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            memset((void*)address, 0x90, size);
            VirtualProtect((void*)address, size, dwOldProtection, NULL);
        }

        static bool IsRunningOnWine()
        {
            const HMODULE ntDll = GetModuleHandleA("ntdll.dll");
            return ntDll && GetProcAddress(ntDll, "wine_get_version");
        }
};
