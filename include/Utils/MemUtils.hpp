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

        static FARPROC PatchCallAddr(char* mod, const DWORD installAddress, const char* hookFunction)
        {
            DWORD relAddr;
            ReadProcMem(mod + installAddress + 1, &relAddr, 4);

            const DWORD offset = (DWORD)hookFunction - (DWORD)(mod + installAddress + 5);
            WriteProcMem(mod + installAddress + 1, &offset, 4);

            return (FARPROC)(mod + relAddr + installAddress + 5);
        }
};
