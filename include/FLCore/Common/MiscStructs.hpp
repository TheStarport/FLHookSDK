#pragma once

#include "CObjects/CObject.hpp"

struct Costume
{
    unsigned head = 0;
    unsigned body = 0;
    unsigned leftHand = 0;
    unsigned rightHand = 0;
    unsigned accessory[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int accessories = 0;

    static Costume Trent()
    {
        return Costume{
            .head = 2'223'155'968, // pi_pirate5_head
            .body = 3'144'214'861,
            .leftHand = 2'479'975'689,
            .rightHand = 2'264'565'644,
        };
    }
};

class IMPORT CEquipmentObj : public CObject
{
  public:
    ~CEquipmentObj() override;

    CEquipmentObj(const CEquipmentObj&);
    CEquipmentObj(Class);

    u8 data[OBJECT_DATA_SIZE];
};

struct ImpactNormalVector
{
    Vector impactPosition;
    Vector impactNormal;
};
