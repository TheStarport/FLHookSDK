#pragma once

#include "../FLCoreDefs.hpp"
#include "Strings.hpp"

struct EquipDescVector;
struct EquipDesc
{
        IMPORT EquipDesc(const EquipDesc&);
        IMPORT EquipDesc();
        IMPORT EquipDesc& operator=(const EquipDesc&);
        IMPORT bool operator==(const EquipDesc&) const;
        IMPORT bool operator!=(const EquipDesc&) const;
        IMPORT bool operator<(const EquipDesc&) const;
        IMPORT bool operator>(const EquipDesc&) const;

        IMPORT static const CacheString CARGO_BAY_HP_NAME;
        IMPORT unsigned int get_arch_id() const;
        IMPORT float get_cargo_space_occupied() const;
        IMPORT int get_count() const;
        IMPORT const CacheString& get_hardpoint() const;
        IMPORT unsigned short get_id() const;
        IMPORT int get_owner() const;
        IMPORT float get_status() const;
        IMPORT bool get_temporary() const;
        IMPORT bool is_equipped() const;
        IMPORT bool is_internal() const;
        IMPORT void make_internal();
        IMPORT void set_arch_id(unsigned int);
        IMPORT void set_count(int);
        IMPORT void set_equipped(bool);
        IMPORT void set_hardpoint(const CacheString&);
        IMPORT void set_id(unsigned short);
        IMPORT void set_owner(int);
        IMPORT void set_status(float);
        IMPORT void set_temporary(bool);

    public:
        /* 0 */ ushort dunno;
        ushort id;
        /* 1 */ uint archId;
        /* 2 */ CacheString hardPoint;
        /* 3 */ bool mounted;
        /* 4 */ float health;
        /* 5 */ ushort count;
        /* 6 */ bool mission;
        /* 7 */ uint owner;
};

class EquipDescList
{
    public:
        IMPORT EquipDescList(const EquipDescVector&);
        IMPORT EquipDescList(const EquipDescList&);
        IMPORT EquipDescList();
        IMPORT ~EquipDescList();
        IMPORT EquipDescList& operator=(const EquipDescList&);
        IMPORT int add_equipment_item(const EquipDesc&, bool);
        IMPORT void append(const EquipDescList&);
        IMPORT EquipDesc* find_equipment_item(const CacheString&);
        IMPORT EquipDesc* find_equipment_item(unsigned short);
        IMPORT const EquipDesc* find_equipment_item(const CacheString&) const;
        IMPORT const EquipDesc* find_equipment_item(unsigned short) const;
        IMPORT const EquipDesc* find_matching_cargo(unsigned int, int, float) const;
        IMPORT float get_cargo_space_occupied() const;
        IMPORT int remove_equipment_item(unsigned short, int);
        IMPORT EquipDesc* traverse_equipment_type(unsigned int, const EquipDesc*);
        IMPORT const EquipDesc* traverse_equipment_type(unsigned int, const EquipDesc*) const;

    public:
        st6::list<EquipDesc> equip;
};

struct EquipDescVector
{
        IMPORT EquipDescVector(const EquipDescVector&);
        IMPORT EquipDescVector(const EquipDescList&);
        IMPORT EquipDescVector();
        IMPORT ~EquipDescVector();
        IMPORT EquipDescVector& operator=(const EquipDescVector&);
        IMPORT int add_equipment_item(const EquipDesc&, bool);
        IMPORT void append(const EquipDescVector&);
        IMPORT EquipDesc* traverse_equipment_type(unsigned int, const EquipDesc*);

    public:
        st6::vector<EquipDesc> equip;
};