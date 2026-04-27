#pragma once
#include "../../FLCoreDefs.hpp"

#include "../Enums.hpp"

class CExternalEquip;
class CEquip;
class CEquipManager;
struct CacheString;
struct CEqObj;
class CEquipTraverser
{
    public:
        IMPORT CEquipTraverser(int);
        IMPORT CEquipTraverser(int, bool);
        IMPORT CEquipTraverser();
        IMPORT CEquipTraverser& operator=(const CEquipTraverser&);
        IMPORT void Restart();

        CEquipTraverser& operator++();

        enum class IteratorState
        {
            End1,
            Iterating1,
            End2,
            Iterating2,
        };

        friend bool operator==(const CEquipTraverser& a, const CEquipTraverser& b)
        { return a.iteratorState == b.iteratorState && a.equipClass == b.equipClass; }

        friend bool operator!=(const CEquipTraverser& a, const CEquipTraverser& b)
        { return a.iteratorState != b.iteratorState || a.equipClass != b.equipClass; }

        EquipmentClass equipClass;
        bool skipDestroyed;
        IteratorState iteratorState;
        unsigned unk3;
};

class CEquipManager
{
        IMPORT int CleanUp(st6::list<CEquip*, st6::allocator<CEquip*>>&);
        IMPORT static void Clear(st6::list<CEquip*, st6::allocator<CEquip*>>&);

    public:
        IMPORT CEquipManager(const CEquipManager&);
        IMPORT CEquipManager();
        IMPORT ~CEquipManager();
        IMPORT CEquipManager& operator=(const CEquipManager&);
        IMPORT bool AddNewEquipment(CEquip*);
        IMPORT int CleanUp();
        IMPORT void Clear();
        IMPORT CExternalEquip* FindByHardpoint(const CacheString&);
        IMPORT const CExternalEquip* FindByHardpoint(const CacheString&) const;
        IMPORT CEquip* FindByID(u16);
        IMPORT const CEquip* FindByID(u16) const;
        IMPORT CEquip* FindFirst(u32);
        IMPORT const CEquip* FindFirst(u32) const;
        IMPORT bool HasDecayingCargo() const;
        IMPORT bool Init(CEqObj*);
        IMPORT u16 InstToSubObjID(long) const;
        IMPORT CEquip* ReverseTraverse(CEquipTraverser&);
        IMPORT const CEquip* ReverseTraverse(CEquipTraverser&) const;
        IMPORT int Size() const;
        IMPORT CEquip* Traverse(CEquipTraverser&);
        IMPORT const CEquip* Traverse(CEquipTraverser&) const;
        IMPORT bool VerifyListSync(const class EquipDescList&) const;

        /* 0 */ unsigned iDunno0;
        /* 1 */ bool bDunno4;
        /* 2 */ unsigned unkPtr1;
        /* 3 */ int size1;
        /* 4 */ bool bDunno10;
        /* 5 */ unsigned unkPtr2;
        /* 6 */ int size2;
        /* 7 */ unsigned decayingCargo;
};
