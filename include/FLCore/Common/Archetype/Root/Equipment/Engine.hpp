#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct Engine : Equipment
    {
        IMPORT Engine(const Engine&);
        IMPORT Engine(IClObj*);
        IMPORT ~Engine() override;
        IMPORT Engine& operator=(const Engine&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

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