#pragma once

#include "../../FLCoreDefs.hpp"

namespace CmnAsteroid
{
    class CAsteroidSystem
    {
        public:
        IMPORT CAsteroidSystem(const CAsteroidSystem&);
        IMPORT CAsteroidSystem();
        IMPORT ~CAsteroidSystem();
        IMPORT CAsteroidSystem& operator=(const CAsteroidSystem&);
        IMPORT int AddRef();
        IMPORT CAsteroidField* FindFirst();
        IMPORT CAsteroidField* FindNext();
        IMPORT int Release();
        IMPORT CAsteroidField* create_field();
        IMPORT unsigned int get_sys_id();
        IMPORT void set_sys_id(unsigned int);
        IMPORT void update(struct IObjDB*, float);

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };
}