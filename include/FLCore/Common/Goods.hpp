#pragma once
#include "FLCore/FLCoreDefs.hpp"

struct GoodDesc
{
        IMPORT GoodDesc();
        IMPORT GoodDesc& operator=(const GoodDesc&);

        IMPORT static void* operator new(unsigned int);
        IMPORT static void operator delete(void*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct GoodDescList
{
        IMPORT GoodDescList(const GoodDescList&);
        IMPORT GoodDescList();
        IMPORT virtual ~GoodDescList();
        IMPORT const GoodDescList& operator=(const GoodDescList&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct GoodInfo
{
    public:
        enum class Type
        {
            Commodity,
            Equipment,
            Hull,
            Ship
        };

        uint i1;
        uint len;
        uint dunno1[16];
        /* 72 */ uint goodId;
        /* 76 */ Type type; // 0=commodity, 2=hull, 3=ship
        /* 80 */ uint equipmentId;
        /* 84 */ uint shipGoodId; // if type = GOODINFO_TYPE_HULL
        /* 88 */ float price;
        /* 92 */ float goodSellPrice;
        /* 96 */ float badBuyPrice;
        /* 100 */ float badSellPrice;
        /* 104 */ float goodBuyPrice;
        /* 108 */ uint jumpDist;
        /* 112 */ bool multiCount;
        /* 116 */ char* shopArchetype;
        /* 120 */ char* itemIcon;
        /* 124 */ char* materialLibrary;
        /* 128 */ char* hardpointChild;
        /* 132 */ char* attachmentArchetype;
        /* 136 */ uint idsName;
        /* 140 */ uint idsInfo;
        /* 144 */ uint hullGoodId; // if type = GOODINFO_TYPE_SHIP
        /* 148 */ EquipDescList edlLow;
        /* 160 */ EquipDescList edlMid;
        /* 172 */ EquipDescList edlHigh;
        /* 184 */ uint freeAmmoArchId;
        /* 188 */ uint freeAmmoCount;
};

class GoodInfoList
{
    public:
        IMPORT GoodInfoList(const GoodInfoList&);
        IMPORT GoodInfoList();
        IMPORT ~GoodInfoList();
        IMPORT GoodInfoList& operator=(const GoodInfoList&);
        IMPORT void destroy();
        IMPORT const GoodInfo* find_by_archetype(unsigned int) const;
        IMPORT const GoodInfo* find_by_id(unsigned int) const;
        IMPORT const GoodInfo* find_by_name(const char*) const;
        IMPORT const GoodInfo* find_by_ship_arch(unsigned int) const;
        IMPORT const st6::list<GoodInfo*, st6::allocator<GoodInfo*>>* get_list() const;
        IMPORT void load(const char*);

    private:
        IMPORT void read_Good_block(INI_Reader*, GoodInfo*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace GoodList
{
    IMPORT const GoodInfo* find_by_archetype(unsigned int);
    IMPORT const GoodInfo* find_by_id(unsigned int);
    IMPORT const GoodInfo* find_by_nickname(const char*);
}; // namespace GoodList