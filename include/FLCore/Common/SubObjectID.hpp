#pragma once

namespace SubObjectID
{
    class IMPORT CollGroupIdMaker
    {
        public:
        CollGroupIdMaker();
        CollGroupIdMaker& operator=(const CollGroupIdMaker&);
        unsigned short CreateGroupID();
        void Reset();

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT EquipIdMaker
    {
        public:
        EquipIdMaker();
        EquipIdMaker& operator=(const EquipIdMaker&);
        unsigned short CreateEquipID();
        void Reset();

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT ShieldIdMaker
    {
        public:
        ShieldIdMaker();
        ShieldIdMaker& operator=(const ShieldIdMaker&);
        unsigned short CreateShieldID();
        void Reset();

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT bool IsArchGroupID(unsigned short);
    IMPORT bool IsEquipID(unsigned short);
    IMPORT bool IsShieldEquipID(unsigned short);
}