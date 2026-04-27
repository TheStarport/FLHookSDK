#pragma once

#include "../../FLCoreDefs.hpp"

namespace CmnAsteroid
{
    class CAsteroidCube
    {
        public:
        enum CubeState
        {
        };
        IMPORT CAsteroidCube(const CAsteroidCube&);
        IMPORT CAsteroidCube(class CAsteroidField*);
        IMPORT ~CAsteroidCube();
        IMPORT CAsteroidCube& operator=(const CAsteroidCube&);
        IMPORT struct asteroid_marker* get_changes();
        IMPORT ulong get_id();
        IMPORT Matrix get_orient();
        IMPORT Vector get_pos();
        IMPORT CubeState get_state();
        IMPORT void init(const Vector&, ulong, struct AsteroidCubeArch*, const struct AxisRotations&, f32);
        IMPORT void set_size(int);
        IMPORT void set_state(CubeState);
        IMPORT void set_system(u32);

        private:
        IMPORT bool compute_asteroid_id(const Vector&, ulong&);

        public:
        u8 data[OBJECT_DATA_SIZE];
    };
}