#pragma once

#include "CObjects/CObject.hpp"

struct Costume
{
    uint head = 0;
    uint body = 0;
    uint leftHand = 0;
    uint rightHand = 0;
    UINT accessory[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int accessories = 0;
};

class IMPORT CEquipmentObj : public CObject
{
    public:
    virtual ~CEquipmentObj();

    CEquipmentObj(const CEquipmentObj&);
    CEquipmentObj(Class);

    unsigned char data[OBJECT_DATA_SIZE];
};