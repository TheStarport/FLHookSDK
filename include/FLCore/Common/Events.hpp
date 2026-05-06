#pragma once

struct INotify
{
    enum Event
    {
        ArchGroupDestroyed = 13, // id of destroyed group payload
        NotEnoughPower = 15, // No payload
        RemoveShieldGeneratorFromShield = 16, // ?, no payload
        SetShieldInternal = 17, // Bool payload
        UpdateShieldHealth = 19 // ?, no payload
    };
};
