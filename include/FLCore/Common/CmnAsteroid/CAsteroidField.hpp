#pragma once

#include "../../FLCoreDefs.hpp"

namespace CmnAsteroid
{
    class CAsteroidField
    {
        public:
        IMPORT CAsteroidField(const CAsteroidField&);
        IMPORT CAsteroidField();
        IMPORT ~CAsteroidField();
        IMPORT CAsteroidField& operator=(const CAsteroidField&);
        IMPORT int AddRef();
        IMPORT int Release();
        IMPORT Vector closest_cube_pos(const Vector&);
        IMPORT unsigned long create_cube_id(const Vector&);
        IMPORT CAsteroidCube* find_cube(unsigned long);
        IMPORT void flush_changes();
        IMPORT AxisRotations& get_axis_rotations();
        IMPORT asteroid_marker* get_changes();
        IMPORT int get_cube_size();
        IMPORT Exclusion::AsteroidExclusionZoneMgr* get_exclusion_mgr();
        IMPORT float get_immersion(const Vector&);
        IMPORT const Universe::IZone* get_lootable_zone(const Vector&) const;
        IMPORT void load(INI_Reader&, int);
        IMPORT bool near_field(const Vector&);
        IMPORT float near_field_fraction(const Vector&, float);
        IMPORT void populate_asteroids(const Vector&, const Vector&);
        IMPORT void set_cube_size(int);
        IMPORT void set_empty_freq(float);
        IMPORT void set_fill_dist(int);
        IMPORT void set_system(unsigned int);
        IMPORT void set_zone(const Universe::IZone*);

        private:
        IMPORT void populate_asteroids_internal(const Vector&, const Vector&, float);
        IMPORT void update(float);

        public:
        uint dunno[10];
        /* 10 */ Universe::IZone* zone;
        /* 11 */ uint dunno4;
        /* 12 */ Exclusion::AsteroidExclusionZoneMgr* exclusionZoneMgr;
        /* 13 */ uint dunno1;
        /* 14 */ uint dunno2;
        /* 15 */ uint dunno3;
        /* 16 */ uint systemId;
        /* 17 */ int cubeSize;
        /* 18 */ int fillDist;
        /* 19 */ float emptyFreq;
        // This is probably a Matrix? // TODO: Test the type @Nen
        /* 20 */ float rotX[4];
        /* 24 */ float rotY[4];
        /* 28 */ float rotZ[4];
    };
}