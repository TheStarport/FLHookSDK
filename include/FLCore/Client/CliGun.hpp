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
        reinterpret_cast<int(__thiscall*)(CliGun*, const Vector & pos, void* unused)>(0x52CED0);
    static constexpr auto GetCursorFirePosOrig =
        reinterpret_cast<Vector * (__thiscall*)(void*, Vector & pos)>(0x4F1DA0);

    static Vector* GetCursorFirePos()
    {
        static Vector ret;
        static void** unkObj = (void**)0x674B70;
        return GetCursorFirePosOrig(*unkObj, ret);
    }

    bool FireWithSound(Vector& pos)
    {
        if (!Fire(pos))
        {
            return false;
        }

        auto barrelPos = GetGun()->GetBarrelPosWS(0);
        const auto mult = 1.0f / static_cast<float>(GetGun()->GetProjectilesPerFire());
        pos *= mult;
        PlayFireSound(this, barrelPos, nullptr);

        return true;
    }

    bool FireMuzzleOverride(Vector& pos, f32 muzzleCone)
    {
        auto gun = GetGun();
        auto result = gun->CanFire(pos);
        if (result == FireResult::Success)
        {
            return FireWithSound(pos);
        }

        if (result != FireResult::FailureGunAngle)
        {
            return false;
        }

        Vector barrelPos = gun->GetAvgBarrelPosWS();
        Vector posDiff = pos - barrelPos;

        f32 magnitude = posDiff.magnitude();
        posDiff = posDiff.normalize();

        Vector barrelDir = gun->GetBarrelDirWS(0);

        f32 dot = barrelDir.dot_product(posDiff);
        dot = std::clamp(dot, -1.f, 1.f);
        f32 theta = acos(dot);

        if (theta < 0.0001f)
        {
            return FireWithSound(pos);
        }

        f32 coneAngleRad = muzzleCone / (180.f / PI);
        f32 interpolationParam = std::min(1.f, coneAngleRad / theta);

        Vector slerp1 = barrelDir * (sinf((1.f - interpolationParam) * theta) / sinf(theta));
        Vector slerp2 = posDiff * (sinf(interpolationParam * theta) / sinf(theta));
        slerp1 += slerp2;
        slerp1 *= magnitude;
        slerp1 += barrelPos;

        return FireWithSound(slerp1);
    }
};
