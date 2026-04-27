#pragma once
#include "../FLCoreDefs.hpp"
#include "EquipDesc.hpp"

#include "GoodType.hpp"

class INI_Reader;
struct GoodDesc
{
        IMPORT GoodDesc();
        IMPORT GoodDesc& operator=(const GoodDesc&);

        IMPORT static void* operator new(u32);
        IMPORT static void operator delete(void*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct GoodDescList
{
        IMPORT GoodDescList(const GoodDescList&);
        IMPORT GoodDescList();
        IMPORT virtual ~GoodDescList();
        IMPORT const GoodDescList& operator=(const GoodDescList&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct GoodInfo
{
        unsigned i1;
        unsigned len;
        unsigned dunno1[16];
        /* 72 */ unsigned goodId;
        /* 76 */ GoodType type; // 0=commodity, 2=hull, 3=ship
        /* 80 */ unsigned equipmentId;
        /* 84 */ unsigned shipGoodId; // if type = GOODINFO_TYPE_HULL
        /* 88 */ f32 price;
        /* 92 */ f32 goodSellPrice;
        /* 96 */ f32 badBuyPrice;
        /* 100 */ f32 badSellPrice;
        /* 104 */ f32 goodBuyPrice;
        /* 108 */ unsigned jumpDist;
        /* 112 */ bool multiCount;
        /* 116 */ char* shopArchetype;
        /* 120 */ char* itemIcon;
        /* 124 */ char* materialLibrary;
        /* 128 */ char* hardpointChild;
        /* 132 */ char* attachmentArchetype;
        /* 136 */ unsigned idsName;
        /* 140 */ unsigned idsInfo;
        /* 144 */ unsigned hullGoodId; // if type = GOODINFO_TYPE_SHIP
        /* 148 */ EquipDescList edlLow;
        /* 160 */ EquipDescList edlMid;
        /* 172 */ EquipDescList edlHigh;
        /* 184 */ unsigned freeAmmoArchId;
        /* 188 */ unsigned freeAmmoCount;
};

class GoodInfoList
{
    public:
        IMPORT GoodInfoList(const GoodInfoList&);
        IMPORT GoodInfoList();
        IMPORT ~GoodInfoList();
        IMPORT GoodInfoList& operator=(const GoodInfoList&);
        IMPORT void destroy();
        IMPORT const GoodInfo* find_by_archetype(u32) const;
        IMPORT const GoodInfo* find_by_id(u32) const;
        IMPORT const GoodInfo* find_by_name(const char*) const;
        IMPORT const GoodInfo* find_by_ship_arch(u32) const;
        IMPORT const st6::list<GoodInfo*, st6::allocator<GoodInfo*>>* get_list() const;
        IMPORT void load(const char*);

    private:
        IMPORT void read_Good_block(INI_Reader*, GoodInfo*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace GoodList
{
    IMPORT const GoodInfo* find_by_archetype(u32);
    IMPORT const GoodInfo* find_by_id(u32);
    IMPORT const GoodInfo* find_by_nickname(const char*);
}; // namespace GoodList
