//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1
//--------------------------
//
//	File:			FLCoreDACom.h
//	Module:			FLCoreDACom.lib
//	Description:	Interface to dacom.dll
//
//	Web: www.skif.be/flcoresdk.php
//
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCOREDACOM_H_
#define _FLCOREDACOM_H_

#include "FLCoreDefs.hpp"

#pragma comment(lib, "FLCoreDACom.lib")

namespace DACOM_CRC
{
    IMPORT int CompareStringsI(const char*, const char*);
    IMPORT unsigned long GetCRC32(const char*, const char*);
    IMPORT unsigned long GetCRC32(const char*);
    IMPORT unsigned long GetContinuedCRC32(unsigned long, char);
    IMPORT unsigned long GetContinuedCRC32(unsigned long, const char*);
}; // namespace DACOM_CRC

namespace LogStream
{
    IMPORT void FlushToDisk();
    IMPORT void LogEvent(const char*, float, unsigned long);
    IMPORT void LogNamedEvent(const char*, const char*, unsigned long);
    IMPORT bool Startup(const char*);
    IMPORT void Update(float);
}; // namespace LogStream

IMPORT void DACOM_Acquire();
IMPORT void DACOM_GetDllVersion();
IMPORT void DACOM_GetVersion();
IMPORT void FDUMP();

#endif // _FLCOREDACOM_H_
