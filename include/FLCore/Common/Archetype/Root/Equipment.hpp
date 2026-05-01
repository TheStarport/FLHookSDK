#pragma once
#include "../../../FLCoreDefs.hpp"
#include <FLCore/Common/Archetype/ArchetypeMethods.hpp>
#include <FLCore/Common/Archetype/Root.hpp>
#include <FLCore/Common/Enums.hpp>

namespace Archetype
{
    class IMPORT FuseIgnitionList
    {
      public:
        unsigned dunno[4];
    };

    struct Equipment : Root
    {
        IMPORT Equipment(const Equipment&);
        IMPORT Equipment(IClObj*);
        IMPORT ~Equipment() override;
        IMPORT Equipment& operator=(const Equipment&);

        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;
        IMPORT bool load() override;
        IMPORT ClassType get_class_type() const override;
        IMPORT void free_resources() override;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual Equipment* get_loot_appearance();
        IMPORT virtual struct CargoPod* get_pod_appearance();
        IMPORT virtual bool is_attached() const;

        /* 23 */ f32 volume;
        /* 24 */ unsigned useCount;
        /* 25 */ unsigned unitsPerContainer;
        /* 26 */ unsigned tractoredExplosionId;
        /* 27 */ bool lootable;
    };
} // namespace Archetype
