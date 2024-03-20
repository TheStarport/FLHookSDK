#pragma once

#include "../../FLCoreDefs.hpp"
#include "IObjectInspect.hpp"

struct GameObject : public IObjInspectImpl, public IObjAffect, public IObjDestructor
{
        virtual ObjectType get_object_type() const;                                                                     // 340
        virtual bool ObjectDestroyed(bool isKill, uint dunno);     // NakedShipDestroyed                                      //344 sub_6CE8080
        virtual int Disconnect();                                // 348 sub_6CE7C80
        virtual bool get_dunno_0x40();                           // 352 sub_6CEE6D0
        virtual int InstantiateCobject(Archetype::Root* archPtr); // 356 sub_6D01040
        virtual bool SetCObjectById(uint cobjId);                // 360 sub_6D010A0
        virtual void Update(float timeDelta);                    // 364 sub_6D01450
        virtual void sub_6D01A60();                              // 368 sub_6D01A60
        virtual int sub_6CEE810(void* PhySys_unk);               // 372 physics collsion handling?
        virtual void sub_6CEE980(int dunno);                     // 376 Behavior interface update
        virtual void sub_6CE9250(void* unk, DamageList*);        // 380
        virtual void sub_6CE9350(void* unk, DamageList*);        // 384
        virtual void process_all_explosion_damage(ExplosionDamageEvent*, DamageList*); // calls methods 508-520         //388
        virtual void sub_6D01A10();                         // 392 sub_6D01A10
        virtual bool get_dunno_0x41();                      // 396
        virtual void sub_6CEEFA0();                         // 400 sub_6CEEFA0
        virtual void sub_6CEF0F0();                         // 404 sub_6CEF0F0
        virtual bool is_player_vulnerable();                // 408 sub_6CE61A0
        virtual bool is_invulnerable();                     // 412 sub_6CE61B0
        virtual float get_max_hp_loss();                    // 416 sub_6CE61C0
        virtual bool process_collision_unk(void*);          // unknown data type, an object containing a IObjRW as 2nd element?? //420 sub_6CEE9F0
        virtual CArchGroup* sethp_unk(DamageList*, float);  // set relative hp to all eq and colgrps to provided float?  //424 sub_6CEB210
        virtual int set_relative_health(float newHp);       // 428
        virtual bool damage_hull(float, DamageList*);       // NakedDamageHit                                                 //432 sub_6CEA3A0
        virtual void apply_damage_entry(DamageEntry*);      // 436 sub_6CEEF70
        virtual bool can_deal_damage(DamageList*);          // invokes get_dunno_0x39 and 0x38                                   //440 sub_6CEF0B0
        CSimple* csimple(){return reinterpret_cast<CSimple*>(cobject());};
        static GameObject* Cast(IObjInspectImpl* iobj)
        {
            if((iobj->cobject()->objectClass & CObject::CSIMPLE_MASK) == CObject::CSIMPLE_MASK)
            {
                return reinterpret_cast<GameObject*>(iobj);
            }
            return nullptr;
        }

        byte bDunno_0x14;
        void* pDunno_0x18; // struct size: 12 bytes
        int iDunnos_0x1C;  // length of 0x1C
        double timer;
        int iDunnos_0x28; // has something to do with fuses
        byte bDunno_0x2C;
        void* pDunno_0x30;   // struct size: 20 bytes
        int iDunno_0x34;     // length of 0x30
        byte isInvulnerable; // not entirely sure on those two
        byte isPlayerVulnerable;
        float maxHpLoss; // when invulnerable, allow HP to drop down to this percentage
        byte bDunno_0x40;  // is alive? Used when fetching IObjRW via sub_6D00670
        byte bDunno_0x41;
        byte bAlign_0x42; // probably not used
        byte bAlign_0x43; // probably not used
        byte bDunno_0x44;
        void* pDunno_0x48; // struct size: 20 bytes
        int iDunno_0x4C;   // size of 0x48
        byte bDunno_0x50;
        int iDunnos_0x54;
};