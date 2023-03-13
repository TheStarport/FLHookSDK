﻿//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreDefs.h
//	Module:			
//	Description:	Common declarations
//
//	Web: www.skif.be/flcoresdk.php
//  
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCOREDEFS_H_
#define _FLCOREDEFS_H_

#include "glm/glm.hpp"
#include "st6.h"

#pragma warning(disable: 4251 4002 4099 4302)

#ifndef IMPORT
#define IMPORT __declspec(dllimport)
#endif
#ifndef  EXPORT
#define EXPORT __declspec(dllexport)
#endif

#define OBJECT_DATA_SIZE	2048

template <int size> struct TString
{
	int len;
	char data[size+1];
	
	TString():len(0) { data[0] = 0; }
};

class Vector : public glm::vec3
{
  public:
	Vector() = default;
	Vector(const float a, const float b, const float c) : glm::vec3(a, b, c) {}
};

class Matrix
{
public:
	float data[3][3];
};

class Quaternion
{
public:
	float w,x,y,z;
};

using uint = unsigned int;
using ushort = unsigned short;
using ulong = unsigned long;
using uchar = unsigned char;
using byte = uchar;

#endif // _FLCOREDEFS_H_
