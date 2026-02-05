#pragma once

#include "MemUtils.hpp"

class DynPatch
{
    public:
        struct Entry
        {
            friend DynPatch;
            unsigned long address;
            const void* newValue;
            void* oldValue;

            Entry(const unsigned long address, const void* newValue, void* oldValue = nullptr) : address(address), newValue(newValue), oldValue(oldValue) {}

            private:
                std::array<char, 4> originalData{};
        };

    private:
        std::string_view binary;
        std::vector<Entry> patches;
        bool applied = false;

    public:
        DynPatch(const std::string_view binary, const std::initializer_list<Entry>& entries) : binary(binary), patches(entries) {}
        ~DynPatch()
        {
            Revert();
        }

        void Apply()
        {
            if (applied)
            {
                throw std::logic_error("ERROR: Cannot apply patch multiple times.");
            }

            const auto base = reinterpret_cast<DWORD>(GetModuleHandleA(binary.data()));
            if (!base)
            {
                throw std::runtime_error("ERROR: Tried to apply patch to unloaded DLL");
            }

            for (auto& entry : patches)
            {
                if (entry.newValue)
                {
                    continue;
                }

                const auto address = entry.address + base;
                if (!entry.oldValue)
                {
                    entry.oldValue = entry.originalData.data();
                }

                MemUtils::ReadProcMem(address, entry.oldValue, 4);
                MemUtils::WriteProcMem(address, &entry.newValue, 4);
            }

            applied = true;
        }

        void Revert()
        {
            const auto base = reinterpret_cast<DWORD>(GetModuleHandleA(binary.data()));
            if (!base || !applied)
            {
                return;
            }

            for (const auto& entry : patches)
            {
                const DWORD address = entry.address + base;
                MemUtils::WriteProcMem(address, entry.oldValue, 4);
            }

            applied = false;
        }
};