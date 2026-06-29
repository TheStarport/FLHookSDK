#pragma once

#include "Dacom.hpp"
#include "IdaComponent.hpp"

// ICOManager Interface

// Priorities for RegisterComponent
#define DACOM_HIGH_PRIORITY   0xC0000000
#define DACOM_NORMAL_PRIORITY 0x80000000
#define DACOM_LOW_PRIORITY    0x40000000

// callback prototype for EnumerateComponents
typedef int(__cdecl* DACOMENUMCALLBACK)(IComponentFactory* component, const char* interface_name,
                                        u32 priority, void* context);

// flags for SetINIConfig
#define DACOM_INI_WRITABLE 0x00000001
#define DACOM_INI_STRING   0x00000002

#define IID_ICOManager     DACOM_MAKE_IID("ICOManager")
DACOM_INTERFACE(ICOManager, IID_ICOManager);
struct DACOM_NO_VTABLE ICOManager : public IComponentFactory
{
    DACOM_DEFMETHOD(RegisterComponent)(IComponentFactory* component, const char* interface_name,
                                       u32 priority = DACOM_NORMAL_PRIORITY) = 0;
    DACOM_DEFMETHOD(UnregisterComponent)(IComponentFactory* component, const char* interface_name = 0) = 0;
    DACOM_DEFMETHOD(EnumerateComponents)(const char* interface_name, DACOMENUMCALLBACK callback,
                                         void* context = 0) = 0;
    DACOM_DEFMETHOD(AddLibrary)(const char* DLL_filename) = 0;
    DACOM_DEFMETHOD(RemoveLibrary)(const char* DLL_filename) = 0;
    DACOM_DEFMETHOD(ShutDown)(void) = 0;
    DACOM_DEFMETHOD(SetINIConfig)(const char* info, u32 flags = 0) = 0;
};

// Extensions for peeking into the internals of ICOManager
#define IID_ICOManagerLiberty DACOM_MAKE_IID("ICOManagerLiberty")
DACOM_INTERFACE(ICOManagerLiberty, IID_ICOManagerLiberty);
struct DACOM_NO_VTABLE ICOManagerLiberty
{
    DACOM_DEFMETHOD(CreateInstanceEx)(DACOMDESC* descriptor, void** instance, u32 low_priority,
                                      u32 high_priority) = 0;
};
