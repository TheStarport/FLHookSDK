#pragma once

#include "../../FLCoreDefs.hpp"

namespace CmnAsteroid
{
    IMPORT CAsteroidField* CreateAsteroidField(u32);
    IMPORT CAsteroidSystem* Find(u32);
    IMPORT int Load(u32);
    IMPORT int Unload(u32);
    IMPORT void Update(struct IObjDB*, f32);
    IMPORT int closest_cube_coord(int, int, int);
    IMPORT ulong compute_cube_id(const Vector&);
    IMPORT bool compute_cube_orientation(ulong, Matrix*, const struct AxisRotations&, f32);
}