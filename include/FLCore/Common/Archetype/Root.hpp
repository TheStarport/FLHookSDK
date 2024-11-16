#pragma once
#include "../../FLCoreDefs.hpp"

#include "ArchetypeMethods.hpp"

struct IEngineInstance;
namespace PhyArch
{
    struct Part;
}

namespace Archetype
{
    struct Root
    {
        IMPORT Root(const Root&);
        IMPORT Root(struct IClObj*);
        IMPORT virtual ~Root();
        IMPORT const Root& operator=(const Root&);
        IMPORT void AddRef();
        IMPORT int GetRef() const;
        IMPORT int Release();
        IMPORT long create_instance(IEngineInstance*) const;
        IMPORT long get_engine_index() const;
        IMPORT unsigned int get_id() const;
        IMPORT const PhyArch::Part* get_phy_part(unsigned int) const;
        IMPORT int get_script_index() const;
        IMPORT bool is_loaded() const;

        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);
        IMPORT virtual bool load();
        IMPORT virtual ClassType get_class_type() const;

        protected:
        void free_physical_representation();
        IMPORT virtual void free_resources();
        bool init_physical_representation();

        public:
        /*  1 */ uint unknown;
        /*  2 */ uint archId;
        /*  3 */ char* name;
        /*  4 */ uint archType;
        /*  5 */ uint idsName;
        /*  6 */ uint idsInfo;
        /*  7 */ float hitPoints;
        /*  8 */ float mass;
        /*  9 */ uint explosionArchId;
        /* 10 */ float explosionResistance;
        /* 11x4 */ Vector rotationInertia;
        /* 14 */ bool hasRotationInertia;
        bool phantomPhysics;
        /* 15 */ uint dunno1;
        /* 16 */ uint dunno2;
        /* 17 */ void* anim;
        /* 18 */ uint array[5]; // not sure about this.
    };
}