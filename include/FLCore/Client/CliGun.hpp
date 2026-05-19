#pragma once

#include "CliEquip.hpp"

struct CliGun : public CliEquip
{
    virtual bool Fire(const Vector& pos);
    virtual bool FireForward();

    CEGun* GetGun() { return RC(CEGun*, equip); }
    static CliGun* Cast(CliEquip* cliEquip)
    {
        if (cliEquip->equip->archetype->get_class_type() != Archetype::ClassType::Gun)
        {
            return nullptr;
        }
        return RC(CliGun*, cliEquip);
    }

    static constexpr auto PlayFireSound =
        reinterpret_cast<int(__thiscall*)(CliGun*, const Vector& pos, void* unused)>(0x52CED0);
};
