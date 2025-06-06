#pragma once

#include "../../FLCoreDefs.hpp"
#include "GameObject.hpp"

struct EqObj : public GameObject
{

        virtual void sub_6CE7D00();                         // collision groups, sets off fuses?                                                //444
        virtual void sub_6CE8C50();                         // damage dealing method, sets off death animation?                                 //448
        virtual void sub_6CE8D40();                         // same as above, but for collision groups                                          //452
        virtual void sub_6CE8CD0();                         // collision group related                                                          //456
        virtual void sub_6CE8E90();                         // hardpoint eq related                                                             //460
        virtual void sub_6CE8E10();                         // hardpoint eq related                                                             //464
        virtual bool sub_6CE8F50(const char*, DamageList*); // iterate over cargo, dunno                                //468
        virtual bool hit_shield_bubble(DamageList*);        // 472
        virtual void sub_6CE88D0();                         // iterate over all equipped equipment and run an update?                           //476
        virtual void sub_6CE8930();                         // processes values under 0x74 and 0x78 pointers                                    //480
        virtual bool light_fuse(uint dunno, ID_String fuse, ushort sId, float radius, float fuseLifetime);                                    // 484 sub_6D01A90
        virtual bool unlight_fuse_unk(uint fuseId, ushort sid, float lifeTime);                                                               // 488 sub_6CEC7F0
        virtual bool fuse_expiration_check();                                                                                                 // 492 sub_6CEC8D0
        virtual void death_explosion();                                                                                                       // 496 sub_6CE8400
        virtual void sub_6D01C90();                                                                                                           // 500
        virtual void sub_6CE8760();                                                                                                           // 504
        virtual void process_explosion_damage_hull(ExplosionDamageEvent* explosion, DamageList* dmgList);                                     // 508 sub_6CE9550
        virtual const CArchGroup* process_explosion_damage_external_equip_and_col_grps(ExplosionDamageEvent* explosion, DamageList* dmgList); // 512 sub_6CE9690
        virtual bool process_explosion_damage_shield_bubble(ExplosionDamageEvent* explosion, DamageList* dmgList); // NakedGuidedHit   //516 sub_6CE9A90
        virtual void process_explosion_damage_energy(ExplosionDamageEvent* explosion, DamageList* dmgList);        // 520 sub_6CE9940
        virtual void damage_shield(CEShield* shield, Archetype::Munition* munition, DamageList* dmgList);          // 524 sub_6CE94B0
        virtual bool damage_ext_eq(CEquip* eq, float dmgDealt, DamageList* dmgList);                               // 528 sub_6CEA4A0
        virtual bool damage_shield_direct(CEShield* target, float dmg, DamageList* dmgList);                       // NakedDamageHit2        //532 sub_6CEA740
        virtual bool damage_col_grp(CArchGroup*, float, DamageList*);                                              // 536 sub_6CEAA80
        virtual bool damage_energy(float energyDamage, DamageList* dmgList);                       // deal energy damage                      //540 sub_6CEAFC0
        virtual void col_grp_death(CArchGroup*, DamageEntry::SubObjFate, DamageList*);             // 544 sub_6CEA9F0
        virtual void cequip_death(CEquip* eq, DamageEntry::SubObjFate fate, DamageList* dmgList);  // 548 sub_6CE9F70
        virtual void unk_death(void* dunno1, DamageEntry::SubObjFate fate, DamageList* dmgList);   // 552 sub_6CE9C50
        virtual EquipmentClass deal_colgrp_linked_damage(CArchGroup* colGrp, DamageList* dmgList); // 556 sub_6CEADC0
        virtual const CArchGroup* sub_6CEAEA0_unk(CArchGroup* colGrp,
                                                  DamageList* dmgList); // colgrp update method checking for lost equipment? idk. //560 sub_6CEAEA0
        virtual void AI_react_to_hull_dmg(DamageList*, DamageEntry*);   // 564 sub_6CEB550
        virtual void AI_react_to_equip_dmg(DamageList*, DamageEntry*);  // 568 sub_6CEB7B0
        virtual void AI_react_to_energy_dmg(DamageList*, DamageEntry*); // 572 sub_6CEBD40
        virtual void AI_react_to_colgrp_dmg(DamageList*, DamageEntry*); // 576 sub_6CEBA40
        virtual void sub_6CEBE80();                                     // 580 sub_6CEBE80
        virtual bool sub_6CEC260(CAttachedEquip* attachedEq);           // 584 sub_6CEC260
        virtual void process_perishable_cargo(float deltaTime);         // 588 sub_6CEC910
        CEqObj* ceqobj() { return reinterpret_cast<CEqObj*>(cobject()); };

        static CEqObj* Cast(IObjInspectImpl* iobj)
        {
            if ((iobj->cobject()->objectClass & CObject::CEQUIPMENT_OBJECT) == CObject::CEQUIPMENT_OBJECT)
            {
                return reinterpret_cast<CEqObj*>(iobj);
            }
            return nullptr;
        }

        int iDunnos_0x58;
        int iDunnos_0x5C;
        byte bDunno_0x60;
        void* pDunno_0x64; // struct size: 16 bytes
        int iDunnos_0x68;  // 0x64 size
        float fdunno_0x6C;
        byte bDunno_0x70;
        void* pDunno_0x74; // struct size: 12 bytes twodirectional list that loops
        int iDunno_0x78;   // length of 0x74 chain
        byte bDunno_0x7C;
        void* pDunno_0x80; // struct size: 68 bytes list of fuses?
        int iDunno_0x84;   // 0x80 length
        byte bDunno_0x88;  // flagged on Destroyed event
};
