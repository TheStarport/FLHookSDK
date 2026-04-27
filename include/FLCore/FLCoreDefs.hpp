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
#include <cmath>
#include <cctype>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <string>

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

#include "X86Math/Vector.hpp"
#include "X86Math/Quaternion.hpp"
#include "X86Math/Matrix.hpp"
#include "X86Math/Transform.hpp"

template <int size>
struct TString
{
        int len;
        char data[size + 1];

        TString() : len(0) { data[0] = 0; }
};

// We need to specialize the BST insert function for each type and then proxy it to the original function

#define ArchetypeBstInsertError(type, module, insertAddr)                                              \
    template <>                                                                                        \
    inline void BinarySearchTree<type>::Insert(unsigned key, type value)                                   \
    {                                                                                                  \
        static unsigned long mod = unsigned long(GetModuleHandleA(module));                                            \
        using InsertFuncType = int(__thiscall*)(BinarySearchTree * ptr, type, unsigned*, char* errorName); \
        static auto insertFunc = reinterpret_cast<InsertFuncType>(mod + insertAddr);                   \
                                                                                                       \
        insertFunc(this, value, &key, nullptr);                                                        \
    }

#define ArchetypeBstInsert(type, module, insertAddr)                                  \
    template <>                                                                       \
    inline void BinarySearchTree<type>::Insert(unsigned key, type value)                  \
    {                                                                                 \
        static unsigned long mod = unsigned long(GetModuleHandleA(module));                           \
        using InsertFuncType = int(__thiscall*)(BinarySearchTree * ptr, type, unsigned*); \
        static auto insertFunc = reinterpret_cast<InsertFuncType>(mod + insertAddr);  \
                                                                                      \
        insertFunc(this, value, &key);                                                \
    }
