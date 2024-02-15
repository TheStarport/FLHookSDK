#pragma once

class Hook MemUtils
{
    public:
        MemUtils() = delete;

        static HWND GetFlServerHwnd()
        {
            auto* unkThis = reinterpret_cast<void*>(0x00426C58);
            return *reinterpret_cast<HWND*>(*(static_cast<PDWORD>(unkThis) + 8) + 32);
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

        static void WriteProcMem(void* address, const void* mem, const uint size)
        {
            const HANDLE hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
            DWORD old;
            VirtualProtectEx(hProc, address, size, PAGE_EXECUTE_READWRITE, &old);
            WriteProcessMemory(hProc, address, mem, size, nullptr);
            CloseHandle(hProc);
        }

        static void ReadProcMem(void* address, void* mem, const uint size)
        {
            const HANDLE hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
            DWORD old;
            VirtualProtectEx(hProc, address, size, PAGE_EXECUTE_READWRITE, &old);
            ReadProcessMemory(hProc, address, mem, size, nullptr);
            CloseHandle(hProc);
        }

        static void ReadProcMem(DWORD address, void* mem, const uint size) { ReadProcMem(PDWORD(address), mem, size); }
        static void WriteProcMem(DWORD address, void* mem, const uint size) { WriteProcMem(PDWORD(address), mem, size); }

        static FARPROC PatchCallAddr(void* mod, const DWORD installAddress, void* hookFunction)
        {
            return PatchCallAddr((DWORD)mod, installAddress, hookFunction);
        }

        static FARPROC PatchCallAddr(DWORD mod, const DWORD installAddress, void* hookFunction)
        {
            DWORD relAddr;
            ReadProcMem(mod + installAddress + 1, &relAddr, 4);

            DWORD offset = (DWORD)hookFunction - (DWORD)(mod + installAddress + 5);
            WriteProcMem(mod + installAddress + 1, &offset, 4);

            return (FARPROC)(mod + relAddr + installAddress + 5);
        }

        /**
         * \brief Overwrite an address with a function call
         * \param address The absolute address where the function should be called from
         * \param hookFunction The function to be called at the provided address
         */
        static void PatchAssembly(DWORD address, const void* hookFunction)
        {
            DWORD dwOldProtection = 0; // Create a DWORD for VirtualProtect calls to allow us to write.
            BYTE bPatch[5];            // We need to change 5 bytes and I'm going to use memcpy so this is the simplest way.
            bPatch[0] = 0xE9;          // Set the first byte of the byte array to the op code for the JMP instruction.
            VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &dwOldProtection); // Allow us to write to the memory we need to change
            DWORD dwRelativeAddress = (DWORD)hookFunction - (DWORD)address - 5;          // Calculate the relative JMP address.
            memcpy(&bPatch[1], &dwRelativeAddress, 4);                                   // Copy the relative address to the byte array.
            memcpy(PBYTE(address), bPatch, 5);                                           // Change the first 5 bytes to the JMP instruction.
            VirtualProtect((void*)address, 5, dwOldProtection, nullptr);                 // Set the protection back to what it was.
        }

        static void NopAddress(DWORD address, size_t size)
        {
            DWORD dwOldProtection = 0;
            VirtualProtect((void*)address, size, PAGE_READWRITE, &dwOldProtection);
            memset((void*)address, 0x90, size);
            VirtualProtect((void*)address, size, dwOldProtection, NULL);
        }
};
