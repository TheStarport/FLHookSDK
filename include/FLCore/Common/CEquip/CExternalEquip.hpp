#pragma once
#include "../../FLCoreDefs.hpp"

#include "CEquip.hpp"

class CExternalEquip : public CEquip
{
    public:
        IMPORT virtual ~CExternalEquip();
        IMPORT virtual bool IsDestroyed() const;
        IMPORT virtual bool Update(float, unsigned int);
        IMPORT virtual bool GetEquipDesc(EquipDesc&) const;
        IMPORT virtual void Destroy();
        IMPORT virtual bool GetConnectionPosition(Vector*, Matrix*) const;
        IMPORT virtual bool IsConnected() const;                           // 88
        IMPORT virtual bool Connect(const char*);                          // 92
        IMPORT virtual CacheString GetParentHPName() const;                // 96
        IMPORT virtual long GetParentConnector(bool) const;                // 100
        IMPORT virtual bool GetHardPointInfo(struct HardpointInfo&) const; // 104
        IMPORT virtual bool GetVelocity(Vector&) const;                    // 108
        IMPORT virtual bool GetCenterOfMass(Vector&) const;                // 112
        IMPORT virtual void Disconnect();                                  // 116

        IMPORT static CExternalEquip* cast(CEquip*);
        IMPORT static const CExternalEquip* cast(const CEquip*);

        IMPORT CExternalEquip(const CExternalEquip&);
        IMPORT CExternalEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);

        /* 8 */ char* mountedHardpoint;
        /* 9 */ long parentConnector;
};
