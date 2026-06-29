#pragma once

#include "../FLCoreDefs.hpp"

#define DA_XSTR(s) DA_STR(s)
#define DA_STR(s)  #s

enum GENRESULT
{
    GR_OK = 0x00000000,
    GR_GENERIC = -1,
    GR_INVALID_PARMS = -2,
    GR_INTERFACE_UNSUPPORTED = -3,
    GR_OUT_OF_MEMORY = -4,
    GR_OUT_OF_SPACE = -5,
    GR_FILE_ERROR = -6,
    GR_NOT_IMPLEMENTED = -7,
    GR_DATA_NOT_FOUND = -8
};

#ifndef DACOM_DEC
    #define DACOM_DEC __declspec(dllimport)
#endif
#define DACOM_DEFMETHOD(method)        virtual GENRESULT __stdcall method
#define DACOM_DEFMETHOD_(type, method) virtual type __stdcall method
#define DACOM_NO_VTABLE                __declspec(novtable)
// #define DACOM_MAKE_IID(name, ver) name "__" #ver
#define DACOM_MAKE_IID(name)           DA_XSTR(LIB_MAJOR) "." DA_XSTR(LIB_MINOR) "_" name

// NOTE: the clearing behavior of the new operator is necessary
// NOTE: for some components, hence let it in there.

#define DA_HEAP_DEFINE_NEW_OPERATOR(classname) \
    void* operator new(size_t size)            \
    {                                          \
        return ::calloc(size, 1);              \
    }                                          \
    void operator delete(void* ptr)            \
    {                                          \
        ::free(ptr);                           \
    }

#define DA_HEAP_DEFINE_NEW_OPERATOR_DECLARE_HACK(declare, classname, _calloc, _free) \
    declare void* operator new(size_t size);                                         \
    declare void operator delete(void* ptr);

#define DA_HEAP_DEFINE_NEW_OPERATOR_IMPL_HACK(declare, classname, _calloc, _free) \
    void* classname::operator new(size_t size)                                    \
    {                                                                             \
        return reinterpret_cast<decltype(&::calloc)>(_calloc)(size, 1);           \
    }                                                                             \
    void classname::operator delete(void* ptr)                                    \
    {                                                                             \
        reinterpret_cast<decltype(&::free)>(_free)(ptr);                          \
    }

#include "IdaComponent.hpp"

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

struct ICOManager;
extern "C"
{
    IMPORT ICOManager* DACOM_Acquire();
    IMPORT void DACOM_GetDllVersion(const char* dllName, u32& major, u32& minor, u32& patch);
    IMPORT void DACOM_GetVersion(u32& major, u32& minor, u32& patch);
    IMPORT void FDUMP(const char* text, ...);
}
