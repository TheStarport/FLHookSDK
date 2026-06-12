#pragma once

#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
#endif

#include <Windows.h>
#include <mmsystem.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <winuser.h>
#undef SendMessage
#undef PlaySound

// Required includes for FreelancersSDK
#include <cctype>
#include <cmath>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "../Typedefs.hpp"
#include "st6.h"

#pragma warning(disable : 4251 4002 4099 4302)

#ifndef IMPORT
    #define IMPORT __declspec(dllimport)
#endif
#ifndef EXPORT
    #define EXPORT __declspec(dllexport)
#endif

#define OBJECT_DATA_SIZE 2048

class Matrix;
class Vector;
Matrix EulerMatrix(const Vector&);

#include "X86Math/Matrix.hpp"
#include "X86Math/Quaternion.hpp"
#include "X86Math/Transform.hpp"
#include "X86Math/Vector.hpp"

template <int size>
struct TString
{
    int len;
    char data[size + 1];

    TString() : len(0) { data[0] = 0; }
};

// Simple helper for debugging data we do not yet understand
union UnkData {
    u32 u32;
    i32 i32;
    f32 f32;
    u16 u16;
    i16 i16;
    u8 u8;
};

struct UnkDataBlock
{
    UnkData data[1000];
};
