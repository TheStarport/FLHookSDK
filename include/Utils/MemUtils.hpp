#pragma once

class MemUtils
{
    public:
        MemUtils() = delete;

        static HWND GetFlServerHwnd()
        {
            auto* unkThis = reinterpret_cast<void*>(0x00426C58);
            return *reinterpret_cast<HWND*>(*(static_cast<PDWORD>(unkThis) + 8) + 32);
        }

        static DWORD Protect(const DWORD addr, const size_t length, const bool execute = true)
        {
            return Protect(reinterpret_cast<void*>(addr), length, execute);
        }

        static DWORD Protect(void* addr, const size_t length, const bool execute = true)
        {
            DWORD oldProtect;
            VirtualProtect(addr, length, execute ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE, &oldProtect);
            return oldProtect;
        }

        static void SwapBytes(void* ptr, const uint len)
        {
            if (len % 4)
            {
                return;
            }

            for (uint i = 0; i < len; i += 4)
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

        static void ReadProcMem(const DWORD address, void* mem, const uint size)
        {
            auto ptr = reinterpret_cast<void*>(address);
            DWORD dwOldProtection = 0;
            VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            memcpy(mem, ptr, size);
        }

        static void WriteProcMem(const DWORD address, const void* mem, const uint size)
        {
            auto ptr = reinterpret_cast<void*>(address);
            DWORD dwOldProtection = 0;
            VirtualProtect(ptr, size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            memcpy(ptr, mem, size);
        }

        static FARPROC PatchCallAddr(void* mod, const DWORD installAddress, void* hookFunction)
        {
            return PatchCallAddr((DWORD)mod, installAddress, hookFunction);
        }

        static FARPROC PatchCallAddr(const DWORD mod, const DWORD installAddress, void* hookFunction)
        {
            DWORD relAddr;
            ReadProcMem(mod + installAddress + 1, &relAddr, 4);

            DWORD offset = (DWORD)hookFunction - (DWORD)(mod + installAddress + 5);
            WriteProcMem(mod + installAddress + 1, &offset, 4);

            return (FARPROC)(mod + relAddr + installAddress + 5);
        }

        /**
         * \brief Overwrite an address with a JMP instruction to the target function
         * \param address The absolute address where the function should be called from
         * \param hookFunction The function to be called at the provided address
         * \param call Replace the JMP instruction with a CALL instruction, which will push the return address onto the stack.
         * \param protect If true, apply needed protections to allow writing. Pass false if protection already removed elsewhere.
         */
        static void PatchAssembly(const DWORD address, const void* hookFunction, const bool call = false, const bool protect = true)
        {
            DWORD dwOldProtection = 0;     // Create a DWORD for VirtualProtect calls to allow us to write.
            BYTE patch[5];                 // We need to change 5 bytes and I'm going to use memcpy so this is the simplest way.
            patch[0] = call ? 0xE8 : 0xE9; // Set the first byte of the byte array to the op code for the JMP instruction.
            if (protect)
            {
                // Allow us to write to the memory we need to change
                VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            }

            const auto relativeAddress = reinterpret_cast<DWORD>(hookFunction) - address - 5; // Calculate the relative JMP address.
            memcpy(&patch[1], &relativeAddress, 4);                                           // Copy the relative address to the byte array.
            memcpy(reinterpret_cast<PBYTE>(address), patch, 5);                               // Change the first 5 bytes to the CALL/JMP instruction.
        }

        static void NopAddress(const DWORD address, const size_t size)
        {
            DWORD dwOldProtection = 0;
            VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            memset((void*)address, 0x90, size);
            VirtualProtect((void*)address, size, dwOldProtection, NULL);
        }
};
