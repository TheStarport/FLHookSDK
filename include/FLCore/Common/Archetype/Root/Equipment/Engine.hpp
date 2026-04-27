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
        /* 28 */ f32 maxForce;
        /* 29 */ f32 linearDrag;
        /* 30 */ f32 powerUsage;
        /* 31 */ f32 cruisePowerUsage;
        /* 32 */ f32 cruiseChargeTime;
        /* 33 */ bool indestructible;
        /* 34 */ f32 reverseFraction;
    };
}