#pragma once
#include "FLCore/FLCoreDefs.hpp"

struct CDynamicAsteroid : public CObject
{
    public:
    IMPORT virtual ~CDynamicAsteroid();
    IMPORT virtual int update(float, unsigned int);
    IMPORT virtual void init_physics(const Vector&, const Vector&, unsigned int);

    struct IMPORT CreateParms
    {
        CreateParms();
        CreateParms& operator=(const CreateParms&);

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

   IMPORT CDynamicAsteroid(const CDynamicAsteroid&);
   IMPORT CDynamicAsteroid();
   IMPORT const Archetype::DynamicAsteroid* dynamicAsteroidArch() const;
   IMPORT void init(const CreateParms&);
};