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
        IMPORT ulong create_cube_id(const Vector&);
        IMPORT CAsteroidCube* find_cube(ulong);
        IMPORT void flush_changes();
        IMPORT AxisRotations& get_axis_rotations();
        IMPORT asteroid_marker* get_changes();
        IMPORT int get_cube_size();
        IMPORT Exclusion::AsteroidExclusionZoneMgr* get_exclusion_mgr();
        IMPORT f32 get_immersion(const Vector&);
        IMPORT const Universe::IZone* get_lootable_zone(const Vector&) const;
        IMPORT void load(INI_Reader&, int);
        IMPORT bool near_field(const Vector&);
        IMPORT f32 near_field_fraction(const Vector&, f32);
        IMPORT void populate_asteroids(const Vector&, const Vector&);
        IMPORT void set_cube_size(int);
        IMPORT void set_empty_freq(f32);
        IMPORT void set_fill_dist(int);
        IMPORT void set_system(u32);
        IMPORT void set_zone(const Universe::IZone*);

        private:
        IMPORT void populate_asteroids_internal(const Vector&, const Vector&, f32);
        IMPORT void update(f32);

        public:
        unsigned dunno[10];
        /* 10 */ Universe::IZone* zone;
        /* 11 */ unsigned dunno4;
        /* 12 */ Exclusion::AsteroidExclusionZoneMgr* exclusionZoneMgr;
        /* 13 */ unsigned dunno1;
        /* 14 */ unsigned dunno2;
        /* 15 */ unsigned dunno3;
        /* 16 */ unsigned systemId;
        /* 17 */ int cubeSize;
        /* 18 */ int fillDist;
        /* 19 */ f32 emptyFreq;
        // This is probably a Matrix? // TODO: Test the type @Nen
        /* 20 */ f32 rotX[4];
        /* 24 */ f32 rotY[4];
        /* 28 */ f32 rotZ[4];
    };
}