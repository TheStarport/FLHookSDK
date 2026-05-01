#pragma once
#include "../../FLCoreDefs.hpp"

#include "CEquip.hpp"

struct HardpointInfo;
struct CacheString;

class CExternalEquip : public CEquip
{
  public:
    IMPORT ~CExternalEquip() override;
    IMPORT bool IsDestroyed() const override;
    IMPORT bool Update(f32, u32) override;
    IMPORT bool GetEquipDesc(EquipDesc&) const override;
    IMPORT void Destroy() override;
    IMPORT bool GetConnectionPosition(Vector*, Matrix*) const override;
    IMPORT virtual bool IsConnected() const;                    // 88
    IMPORT virtual bool Connect(const char*);                   // 92
    IMPORT virtual CacheString GetParentHPName() const;         // 96
    IMPORT virtual long GetParentConnector(bool) const;         // 100
    IMPORT virtual bool GetHardPointInfo(HardpointInfo&) const; // 104
    IMPORT virtual bool GetVelocity(Vector&) const;             // 108
    IMPORT virtual bool GetCenterOfMass(Vector&) const;         // 112
    IMPORT virtual void Disconnect();                           // 116

    IMPORT static CExternalEquip* cast(CEquip*);
    IMPORT static const CExternalEquip* cast(const CEquip*);

    IMPORT CExternalEquip(const CExternalEquip&);
    IMPORT CExternalEquip(u32, CEqObj*, u16, const Archetype::Equipment*, bool);

    /* 8 */ char* mountedHardpoint;
    /* 9 */ long parentConnector;
};
