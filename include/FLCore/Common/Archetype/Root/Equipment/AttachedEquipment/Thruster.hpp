#pragma once
#include "FLCore/FLCoreDefs.hpp"
#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct Thruster : public AttachedEquipment
    {
        IMPORT Thruster(const Thruster&);
        IMPORT Thruster(IClObj*);
        IMPORT virtual ~Thruster();
        IMPORT Thruster& operator=(const Thruster&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 34 */ float powerUsage;
        /* 35 */ float maxForce;
    };
}