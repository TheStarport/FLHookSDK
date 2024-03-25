#pragma once
#include "../../../FLCoreDefs.hpp"

class CEScanner : public CInternalEquip
{
    public:
    enum class ScanResult {};

    IMPORT virtual ~CEScanner();
    // virtual bool add_obj(struct IObjRW*);
    IMPORT virtual bool Update(float, unsigned int);

    IMPORT static CEScanner* cast(CEquip*);
    IMPORT static const CEScanner* cast(const CEquip*);

    IMPORT CEScanner(const CEScanner&);
    IMPORT CEScanner(CEqObj*, unsigned short, const Archetype::Scanner*, bool);
    IMPORT float GetCargoScanRange() const;
    IMPORT float GetRadarRange() const;
    IMPORT ScanResult ScanCargo(CEqObj*);
    IMPORT const Archetype::Scanner* ScannerArch() const;
    IMPORT void clear_cache();
    IMPORT void scan_for_types(unsigned int);
};