#pragma once
#include "FLCore/FLCoreDefs.hpp"
#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct Thruster : public AttachedEquipment
    {
        IMPORT Thruster(const Thruster&);
        IMPORT Thruster(IClObj*);
        IMPORT ~Thruster() override;
        IMPORT Thruster& operator=(const Thruster&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 34 */ float powerUsage;
        /* 35 */ float maxForce;
    };
}