#pragma once
#include "../../FLCoreDefs.hpp"

class CEquipManager;
class CEquipTraverser
{
    public:
        IMPORT CEquipTraverser(int);
        IMPORT CEquipTraverser(int, bool);
        IMPORT CEquipTraverser();
        IMPORT CEquipTraverser& operator=(const CEquipTraverser&);
        IMPORT void Restart();

        CEquipTraverser(CEquipManager* manager, EquipmentClass equipClass = EquipmentClass::All, bool skipDestroyed = false)
            : CEquipTraverser(static_cast<int>(equipClass), skipDestroyed)
        {
            equipManager = manager;
        }

        CEquipTraverser& operator++();

        CEquip* operator->() const { return currentEquip; }

        enum class IteratorState
        {
            End1,
            Iterating1,
            End2,
            Iterating2,
        };

        friend bool operator==(const CEquipTraverser& a, const CEquipTraverser& b)
        {
            return a.iteratorState == b.iteratorState && a.equipManager == b.equipManager;
        }

        friend bool operator!=(const CEquipTraverser& a, const CEquipTraverser& b)
        {
            return a.iteratorState != b.iteratorState || a.equipManager != b.equipManager;
        }

        EquipmentClass equipClass;
        bool skipDestroyed;
        IteratorState iteratorState;
        uint unk3;
        // Fields below added by us
        CEquip* currentEquip = nullptr;
        CEquipManager* equipManager = nullptr;
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
        IMPORT CEquip* FindByID(unsigned short);
        IMPORT const CEquip* FindByID(unsigned short) const;
        IMPORT CEquip* FindFirst(unsigned int);
        IMPORT const CEquip* FindFirst(unsigned int) const;
        IMPORT bool HasDecayingCargo() const;
        IMPORT bool Init(CEqObj*);
        IMPORT unsigned short InstToSubObjID(long) const;
        IMPORT CEquip* ReverseTraverse(class CEquipTraverser&);
        IMPORT const CEquip* ReverseTraverse(CEquipTraverser&) const;
        IMPORT int Size() const;
        IMPORT CEquip* Traverse(CEquipTraverser&);
        IMPORT const CEquip* Traverse(CEquipTraverser&) const;
        IMPORT bool VerifyListSync(const class EquipDescList&) const;

        CEquipTraverser StartTraverse(EquipmentClass equipmentClass = EquipmentClass::All, bool skipDestroyed = false)
        {
            return CEquipTraverser(this, equipmentClass, skipDestroyed);
        }

        CEquipTraverser begin()
        {
            auto traverser = StartTraverse();
            traverser.operator++();
            return traverser;
        }

        CEquipTraverser end() { return { this, EquipmentClass::All, false }; }

    public:
        /* 0 */ uint iDunno0;
        /* 1 */ bool bDunno4;
        /* 2 */ uint unkPtr1;
        /* 3 */ int size1;
        /* 4 */ bool bDunno10;
        /* 5 */ uint unkPtr2;
        /* 6 */ int size2;
        /* 7 */ uint decayingCargo;
};

inline CEquipTraverser& CEquipTraverser::operator++()
{
    currentEquip = equipManager->Traverse(*this);
    return *this;
}