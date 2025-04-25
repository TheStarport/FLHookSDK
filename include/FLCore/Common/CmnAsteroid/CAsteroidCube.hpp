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
        IMPORT unsigned long get_id();
        IMPORT Matrix get_orient();
        IMPORT Vector get_pos();
        IMPORT CubeState get_state();
        IMPORT void init(const Vector&, unsigned long, struct AsteroidCubeArch*, const struct AxisRotations&, float);
        IMPORT void set_size(int);
        IMPORT void set_state(CubeState);
        IMPORT void set_system(unsigned int);

        private:
        IMPORT bool compute_asteroid_id(const Vector&, unsigned long&);

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };
}