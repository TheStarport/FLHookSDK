#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct IMPORT DamageObjInfo
    {
        DamageObjInfo(const DamageObjInfo&);
        DamageObjInfo();
        DamageObjInfo& operator=(const DamageObjInfo&);
        bool operator==(const DamageObjInfo&) const;
        bool operator!=(const DamageObjInfo&) const;
        bool operator<(const DamageObjInfo&) const;
        bool operator>(const DamageObjInfo&) const;

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

    class DamageObjInfoList
    {
        public:
        IMPORT DamageObjInfoList(const DamageObjInfoList&);
        IMPORT DamageObjInfoList();
        IMPORT ~DamageObjInfoList();
        IMPORT DamageObjInfoList& operator=(const DamageObjInfoList&);
        IMPORT bool IsValid();

        public:
        bool dunno1;
        void* dunnoPtr; // 16 byte size
        uint dunno2;
    };
}