#pragma once

#include "CObjects/CObject.hpp"

struct Costume
{
    uint head = 0;
    uint body = 0;
    uint leftHand = 0;
    uint rightHand = 0;
    uint accessory[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int accessories = 0;

    static Costume Trent()
    {
        return Costume{
            .head = 2223155968, // pi_pirate5_head
            .body = 3144214861,
            .leftHand = 2479975689,
            .rightHand = 2264565644,
        };
    }
};

class IMPORT CEquipmentObj : public CObject
{
    public:
    virtual ~CEquipmentObj();

    CEquipmentObj(const CEquipmentObj&);
    CEquipmentObj(Class);

    unsigned char data[OBJECT_DATA_SIZE];
};