#pragma once
#include "../../../FLCoreDefs.hpp"

class CEScanner : public CInternalEquip
{
    public:
        enum class ScanResult
        {
        };

        IMPORT virtual ~CEScanner();
        // virtual bool add_obj(struct IObjRW*);
        IMPORT virtual bool Update(f32, u32);

        IMPORT static CEScanner* cast(CEquip*);
        IMPORT static const CEScanner* cast(const CEquip*);

        IMPORT CEScanner(const CEScanner&);
        IMPORT CEScanner(CEqObj*, u16, const Archetype::Scanner*, bool);
        IMPORT f32 GetCargoScanRange() const;
        IMPORT f32 GetRadarRange() const;
        IMPORT ScanResult ScanCargo(CEqObj*);
        IMPORT const Archetype::Scanner* ScannerArch() const;
        IMPORT void clear_cache();
        IMPORT void scan_for_types(u32);

        ScanList scanList;
};
