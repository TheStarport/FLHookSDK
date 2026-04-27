#pragma once

namespace SubObjectID
{
    class IMPORT CollGroupIdMaker
    {
        public:
        CollGroupIdMaker();
        CollGroupIdMaker& operator=(const CollGroupIdMaker&);
        u16 CreateGroupID();
        void Reset();

        short currSID;
    };

    class IMPORT EquipIdMaker
    {
        public:
        EquipIdMaker();
        EquipIdMaker& operator=(const EquipIdMaker&);
        u16 CreateEquipID();
        void Reset();

        public:
        short currSID;
    };

    class IMPORT ShieldIdMaker
    {
        public:
        ShieldIdMaker();
        ShieldIdMaker& operator=(const ShieldIdMaker&);
        u16 CreateShieldID();
        void Reset();

        public:
        short currSID;
    };

    IMPORT bool IsArchGroupID(u16);
    IMPORT bool IsEquipID(u16);
    IMPORT bool IsShieldEquipID(u16);
}