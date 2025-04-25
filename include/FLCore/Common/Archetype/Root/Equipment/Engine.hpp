#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct Engine : Equipment
    {
        IMPORT Engine(const Engine&);
        IMPORT Engine(IClObj*);
        IMPORT virtual ~Engine();
        IMPORT Engine& operator=(const Engine&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float maxForce;
        /* 29 */ float linearDrag;
        /* 30 */ float powerUsage;
        /* 31 */ float cruisePowerUsage;
        /* 32 */ float cruiseChargeTime;
        /* 33 */ bool indestructible;
        /* 34 */ float reverseFraction;
    };
}