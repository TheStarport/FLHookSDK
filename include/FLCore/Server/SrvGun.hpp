#pragma once

#include "SrvEquip.hpp"

struct SrvGun : public SrvEquip
{
    virtual bool Fire(const Vector& pos);
    virtual bool FireForward(u32 dunno);

    CEGun* GetGun() { return RC(CEGun*, equip); }

    static SrvGun* Cast(SrvEquip* srvEquip)
    {
        if (srvEquip->equip->archetype->get_class_type() != Archetype::ClassType::Gun)
        {
            return nullptr;
        }
        return RC(SrvGun*, srvEquip);
    }

    bool FireMuzzleOverride(Vector& pos, float muzzleCone)
    {
        auto gun = GetGun();
        auto result = gun->CanFire(pos);
        if (result == FireResult::Success)
        {
            return Fire(pos);
        }

        if (result != FireResult::FailureGunAngle)
        {
            return false;
        }

        Vector barrelPos = gun->GetAvgBarrelPosWS();
        Vector posDiff = pos - barrelPos;

        float magnitude = posDiff.magnitude();
        posDiff = posDiff.normalize();

        Vector barrelDir = gun->GetBarrelDirWS(0);

        auto theta = acos(barrelDir.dot_product(pos.normalize()));
        float interpolationParam = (muzzleCone / (180.f / PI)) / theta;

        Vector slerp1 = barrelDir * (sinf((1.f - interpolationParam) * theta) / sinf(theta));
        Vector slerp2 = posDiff * (sinf(interpolationParam * theta) / sinf(theta));
        slerp1 += slerp2;
        slerp1 *= magnitude;
        slerp1 += barrelPos;

        return Fire(slerp1);
    }
};
