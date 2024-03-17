#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace CmnAsteroid
{
    IMPORT CAsteroidField* CreateAsteroidField(unsigned int);
    IMPORT CAsteroidSystem* Find(unsigned int);
    IMPORT int Load(unsigned int);
    IMPORT int Unload(unsigned int);
    IMPORT void Update(struct IObjDB*, float);
    IMPORT int closest_cube_coord(int, int, int);
    IMPORT unsigned long compute_cube_id(const Vector&);
    IMPORT bool compute_cube_orientation(unsigned long, Matrix*, const struct AxisRotations&, float);
}