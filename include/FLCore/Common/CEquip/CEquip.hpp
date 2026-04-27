#pragma once
#include "../../FLCoreDefs.hpp"

#include "../Unknown.hpp"

namespace Archetype
{
    struct Equipment;
}

struct CEqObj;
class CEquip;
struct EquipDesc;
struct EquipStatus;

class CEquip
{
    public:
        IMPORT virtual ~CEquip();                                          // 0
        IMPORT virtual bool IsActive() const;                              // 4
        IMPORT virtual bool IsDestroyed() const;                           // 8
        IMPORT virtual bool IsFunctioning() const;                         // 12
        IMPORT virtual bool IsDisabled() const;                            // 16
        IMPORT virtual bool IsTemporary() const;                           // 20
        IMPORT virtual bool CanDelete() const;                             // 24
        IMPORT virtual void NotifyArchGroupDestroyed(u16);      // 28
        IMPORT virtual bool IsLootable() const;                            // 32
        IMPORT virtual bool Update(f32, u32);                   // 36
        IMPORT virtual bool GetEquipDesc(EquipDesc&) const;         // 40
        IMPORT virtual void GetStatus(EquipStatus&) const;          // 44
        IMPORT virtual bool Activate(bool);                                // 48
        IMPORT virtual void Destroy();                                     // 52
        IMPORT virtual f32 GetMaxHitPoints() const;                      // 56
        IMPORT virtual f32 GetHitPoints() const;                         // 60
        IMPORT virtual void SetHitPoints(f32);                           // 64
        IMPORT virtual f32 GetRelativeHealth() const;                    // 68
        IMPORT virtual bool GetConnectionPosition(Vector*, Matrix*) const; // 72
        IMPORT virtual bool IsControllerEnabled();                         // 76
        IMPORT virtual bool EnableController();                            // 80
        IMPORT virtual bool DisableController();                           // 84

        IMPORT static void* operator new(u32);
        IMPORT static void operator delete(void*);

        IMPORT CEquip();
        IMPORT CEquip(const CEquip&);
        IMPORT CEquip(u32, CEqObj*, u16, const Archetype::Equipment*, bool);

        IMPORT void ConnectClientEquip(INotify*);
        IMPORT void ConnectServerEquip(INotify*);
        IMPORT const Archetype::Equipment* EquipArch() const;
        IMPORT u16 GetID() const;
        IMPORT CEqObj* GetOwner() const;
        IMPORT u32 GetType() const;
        IMPORT const char* IdentifyEquipment() const;
        IMPORT void Notify(INotify::Event, void*);
        IMPORT void NotifyDisconnecting(INotify*);

        /* 1 */ CEqObj* owner;
        /* 2 */ u16 SubObjId;
        /* 3 */ Archetype::Equipment* archetype;
        /* 4 */ bool isActive;
        bool isDestroyed;
        bool isTemporary;
        /* 5 */ EquipmentClass CEquipType;
        /* 6 */ void* customWrapperClass2;
        /* 7 */ char* dunno;
};
