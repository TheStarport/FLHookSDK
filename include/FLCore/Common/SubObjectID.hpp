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

        short currSID;
    };

    class IMPORT EquipIdMaker
    {
        public:
        EquipIdMaker();
        EquipIdMaker& operator=(const EquipIdMaker&);
        unsigned short CreateEquipID();
        void Reset();

        public:
        short currSID;
    };

    class IMPORT ShieldIdMaker
    {
        public:
        ShieldIdMaker();
        ShieldIdMaker& operator=(const ShieldIdMaker&);
        unsigned short CreateShieldID();
        void Reset();

        public:
        short currSID;
    };

    IMPORT bool IsArchGroupID(unsigned short);
    IMPORT bool IsEquipID(unsigned short);
    IMPORT bool IsShieldEquipID(unsigned short);
}