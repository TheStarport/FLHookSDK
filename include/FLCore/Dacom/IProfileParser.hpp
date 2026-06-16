#pragma once

#include "../FLCoreDefs.hpp"
#include "IdaComponent.hpp"

#include <Windows.h>

#define IID_IProfileParser DACOM_MAKE_IID("IProfileParser")
struct PROFPARSEDESC : public AGGDESC
{
    PROFPARSEDESC(const char* _interfaceName = IID_IProfileParser) : AGGDESC(_interfaceName)
    {
        size = sizeof(*this);
    };
};

struct DACOM_NO_VTABLE IProfileParser : public IDAComponent
{
    // enumeration callback routine - return TRUE to continue the enumeration

    typedef BOOL(__stdcall* ENUM_PROC)(struct IProfileParser* parser, const char* sectionName, void* context);

    enum ACCESS
    {
        READ_ACCESS = 0,
        WRITE_ACCESS
    };

    enum CREATE_MODE
    {
        PP_CREATENEW = 1,
        PP_CREATEALWAYS = 2,
        PP_OPENEXISTING = 3,
        PP_OPENALWAYS = 4,
        PP_TRUNCATEEXISTING = 5
    };

    DACOM_DEFMETHOD(Initialize)(const char* fileName, ACCESS access = READ_ACCESS) = 0;

    DACOM_DEFMETHOD_(BOOL, EnumerateSections)(ENUM_PROC proc = 0, void* context = 0) = 0;

    DACOM_DEFMETHOD_(HANDLE, CreateSection)(const char* sectionName, CREATE_MODE mode = PP_OPENEXISTING) = 0;

    DACOM_DEFMETHOD_(BOOL, CloseSection)(HANDLE hSection) = 0;

    DACOM_DEFMETHOD_(u32, ReadProfileLine)(HANDLE hSection, u32 lineNumber, char* buffer, u32 bufferSize) = 0;

    DACOM_DEFMETHOD_(u32, ReadKeyValue)(HANDLE hSection, const char* keyName, char* buffer,
                                        u32 bufferSize) = 0;
};

//-----------------------------------------------------------------------------
//---------------------------IProfileParser2 interface-------------------------
//-----------------------------------------------------------------------------

#define IID_IProfileParser2 DACOM_MAKE_IID("IProfileParser2")

struct PROFPARSEDESC2 : public AGGDESC
{
    PROFPARSEDESC2(const char* _interfaceName = IID_IProfileParser2) : AGGDESC(_interfaceName)
    {
        size = sizeof(*this);
    };
};

struct DACOM_NO_VTABLE IProfileCallback
{
    virtual BOOL __stdcall ProfileCallback(struct IProfileParser2* parser, const char* name,
                                           const char* value, void* context) = 0;
};

struct DACOM_NO_VTABLE IProfileParser2 : public IDAComponent
{
    DACOM_DEFMETHOD(Initialize)(const char* fileName,
                                IProfileParser::ACCESS access = IProfileParser::READ_ACCESS) = 0;
    DACOM_DEFMETHOD(Initialize2)(const char* buffer, u32 bufferSize) = 0;
    DACOM_DEFMETHOD_(HANDLE,
                     CreateSection)(const char* sectionName,
                                    IProfileParser::CREATE_MODE mode = IProfileParser::PP_OPENEXISTING) = 0;
    DACOM_DEFMETHOD_(BOOL, CloseSection)(HANDLE hSection) = 0;
    DACOM_DEFMETHOD_(u32, ReadProfileLine)(HANDLE hSection, u32 lineNumber, char* buffer, u32 bufferSize) = 0;
    DACOM_DEFMETHOD_(u32, ReadKeyValue)(HANDLE hSection, const char* keyName, char* buffer,
                                        u32 bufferSize) = 0;
    DACOM_DEFMETHOD_(BOOL, EnumerateSections)(IProfileCallback* callback, void* context = 0) = 0;
    DACOM_DEFMETHOD_(BOOL, EnumerateKeys)(IProfileCallback* callback, HANDLE hSection, void* context = 0) = 0;
};
