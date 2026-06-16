#pragma once

#include <string.h>
// A damped spring is not, strictly speaking, a "joint," since it doesn't remove
// any degrees of freedom from the system. But it still fits into the framework
// as a connection between two objects.
typedef enum
{
    JT_NONE = -1,
    JT_FIXED,
    JT_PRISMATIC,
    JT_REVOLUTE,
    JT_DAMPED_SPRING,
    JT_CYLINDRICAL,
    JT_SPHERICAL,     // Joint data is a quaternion.
    JT_TRANSLATIONAL, // Joint daya is a vector.
    JT_LOOSE          // Joint daya is a vector & a quaternion.
} JointType;

//
// Standard names of the different types of joints
//
#define JT_FIXED_NAME         "Fix"
#define JT_PRISMATIC_NAME     "Pris"
#define JT_REVOLUTE_NAME      "Rev"
#define JT_DAMPED_SPRING_NAME "Spr"
#define JT_CYLINDRICAL_NAME   "Cyl"
#define JT_SPHERICAL_NAME     "Sphere"
#define JT_TRANSLATIONAL_NAME "Trans"
#define JT_LOOSE_NAME         "Loose"

//

//
// JointInfo
//
// This structure describes the constraint properties of a
// joint in the system.
//
// min0 and max0:
//	REVOLUTE:		interpreted as radian rotation limits about 'axis'
//	PRISMATIC:		interpreted as engine unit limits along 'axis'
//	CYLINDRICAL:	interpreted as radians.
//	SPHERICAL:		interpreted as radian rotation limits about parent i axis.
//	TRANSLATIONAL:	ignored
//	LOOSE:			ignored
//  FIXED:			ignored
//	DAMPED_SPRING:	ignored
//
// min1 and max1:
//	REVOLUTE:		ignored
//	PRISMATIC:		ignored
//	CYLINDRICAL:	interpreted as engine unit limits along 'axis'.
//	SPHERICAL:		interpreted as radian rotation limits about parent j axis.
//	TRANSLATIONAL:	ignored
//	LOOSE:			ignored
//  FIXED:			ignored
//	DAMPED_SPRING:	ignored
//
// min2 and max2:
//	REVOLUTE:		ignored
//	PRISMATIC:		ignored
//	CYLINDRICAL:	ignored
//	SPHERICAL:		interpreted as radian rotation limits about parent k axis.
//	TRANSLATIONAL:	ignored
//	LOOSE:			ignored
//  FIXED:			ignored
//	DAMPED_SPRING:	ignored
struct JointInfo
{
  public:           // Data
    JointType type; // Type of this joint, determines how the following
                    // properties are interpreted.

    Vector parent_point; // Point of contact on parent, in parent frame.
    Vector child_point;  // Point of contact on child, in child frame.
    Vector rel_position;
    Matrix rel_orientation;
    Vector axis; // Unit axis of rotation or translation in parent frame.
    float min0, max0;
    float min1, max1;
    float min2, max2;
    float spring_constant;
    float damping_constant;
    float rest_length;

  public: // Interface
    //

    JointInfo(JointType _type = JT_NONE) { type = _type; }

    // Returns the number of FLOATS in the state vector
    const i32 get_state_vector_size(void) const { return JointInfo::get_num_state_floats(this); }

    static i32 get_num_state_floats(const JointInfo* joint_info)
    {
        switch (joint_info->type)
        {
            case JT_REVOLUTE: return 1;
            case JT_PRISMATIC: return 1;
            case JT_CYLINDRICAL: return 2;
            case JT_TRANSLATIONAL: return 3;
            case JT_SPHERICAL: return 4;
            case JT_LOOSE: return 7;
            default: return 0;
        }
    }

    static JointType get_type_from_name(const char* jointtypename)
    {
        if (_stricmp(jointtypename, JT_FIXED_NAME) == 0)
        {
            return JT_FIXED;
        }
        else if (_stricmp(jointtypename, JT_PRISMATIC_NAME) == 0)
        {
            return JT_PRISMATIC;
        }
        else if (_stricmp(jointtypename, JT_REVOLUTE_NAME) == 0)
        {
            return JT_REVOLUTE;
        }
        else if (_stricmp(jointtypename, JT_DAMPED_SPRING_NAME) == 0)
        {
            return JT_DAMPED_SPRING;
        }
        else if (_stricmp(jointtypename, JT_CYLINDRICAL_NAME) == 0)
        {
            return JT_CYLINDRICAL;
        }
        else if (_stricmp(jointtypename, JT_SPHERICAL_NAME) == 0)
        {
            return JT_SPHERICAL;
        }
        else if (_stricmp(jointtypename, JT_TRANSLATIONAL_NAME) == 0)
        {
            return JT_TRANSLATIONAL;
        }
        else if (_stricmp(jointtypename, JT_LOOSE_NAME) == 0)
        {
            return JT_LOOSE;
        }

        return JT_NONE;
    }

    //

    static const char* get_name_from_type(JointType _type)
    {
        switch (_type)
        {
            case JT_FIXED: return JT_FIXED_NAME;
            case JT_PRISMATIC: return JT_PRISMATIC_NAME;
            case JT_REVOLUTE: return JT_REVOLUTE_NAME;
            case JT_DAMPED_SPRING: return JT_DAMPED_SPRING_NAME;
            case JT_CYLINDRICAL: return JT_CYLINDRICAL_NAME;
            case JT_SPHERICAL: return JT_SPHERICAL_NAME;
            case JT_TRANSLATIONAL: return JT_TRANSLATIONAL_NAME;
            case JT_LOOSE: return JT_LOOSE_NAME;
            default: return NULL;
        }
    }
};
