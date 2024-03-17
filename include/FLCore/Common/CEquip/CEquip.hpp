#pragma once
#include "FLCore/FLCoreDefs.hpp"

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
        IMPORT virtual void NotifyArchGroupDestroyed(unsigned short);      // 28
        IMPORT virtual bool IsLootable() const;                            // 32
        IMPORT virtual bool Update(float, unsigned int);                   // 36
        IMPORT virtual bool GetEquipDesc(struct EquipDesc&) const;         // 40
        IMPORT virtual void GetStatus(struct EquipStatus&) const;          // 44
        IMPORT virtual bool Activate(bool);                                // 48
        IMPORT virtual void Destroy();                                     // 52
        IMPORT virtual float GetMaxHitPoints() const;                      // 56
        IMPORT virtual float GetHitPoints() const;                         // 60
        IMPORT virtual void SetHitPoints(float);                           // 64
        IMPORT virtual float GetRelativeHealth() const;                    // 68
        IMPORT virtual bool GetConnectionPosition(Vector*, Matrix*) const; // 72
        IMPORT virtual bool IsControllerEnabled();                         // 76
        IMPORT virtual bool EnableController();                            // 80
        IMPORT virtual bool DisableController();                           // 84

        IMPORT static void* operator new(unsigned int);
        IMPORT static void operator delete(void*);

        IMPORT CEquip();
        IMPORT CEquip(const CEquip&);
        IMPORT CEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);

        IMPORT void ConnectClientEquip(INotify*);
        IMPORT void ConnectServerEquip(INotify*);
        IMPORT const Archetype::Equipment* EquipArch() const;
        IMPORT unsigned short GetID() const;
        IMPORT CEqObj* GetOwner() const;
        IMPORT unsigned int GetType() const;
        IMPORT const char* IdentifyEquipment() const;
        IMPORT void Notify(INotify::Event, void*);
        IMPORT void NotifyDisconnecting(INotify*);

        /* 1 */ CEqObj* owner;
        /* 2 */ ushort SubObjId;
        /* 3 */ Archetype::Equipment* archetype;
        /* 4 */ bool isActive;
        bool isDestroyed;
        bool isTemporary;
        /* 5 */ EquipmentClass CEquipType;
        /* 6 */ void* customWrapperClass2;
        /* 7 */ char* dunno;
};