#pragma once

#include <__generated.h>

#ifndef FLHOOK
#define DLL __declspec(dllimport)
#else
#define DLL __declspec(dllexport)
#endif

enum class PluginMajorVersion {
    UNDEFINED = -1,
    // We started doing this from 4 onwards
    VERSION_04 = 4,
};

// Define most ahead of time
enum class PluginMinorVersion {
    UNDEFINED = -1,
    VERSION_00 = 0,
    VERSION_01,
    VERSION_02,
    VERSION_03,
    VERSION_04,
    VERSION_05,
    VERSION_06,
    VERSION_07,
    VERSION_08,
    VERSION_09,
};

constexpr PluginMajorVersion CurrentMajorVersion = PluginMajorVersion::VERSION_04;
constexpr PluginMinorVersion CurrentMinorVersion = PluginMinorVersion::VERSION_00;

const std::wstring VersionInformation = std::to_wstring(static_cast<int>(CurrentMajorVersion)) + L"." + std::to_wstring(static_cast<int>(CurrentMinorVersion));

enum class ReturnCode {
    Default = 0,
    SkipPlugins = 1,
    SkipFunctionCall = 2,
    SkipAll = SkipPlugins | SkipFunctionCall,
};

inline ReturnCode operator&(ReturnCode a, ReturnCode b) {
    return ReturnCode(uint(a) & uint(b));
}

enum class HookStep {
    Before,
    After,
    Mid,
    Count
};

class PluginHook {
public:
    using FunctionType = void();
private:
    HookedCall targetFunction_;
    FunctionType *hookFunction_;
    HookStep step_;
    int priority_;
public:
    template <typename Func>
    PluginHook(HookedCall targetFunction, Func *hookFunction, HookStep step = HookStep::Before, int priority = 0)
        : targetFunction_(targetFunction), hookFunction_(reinterpret_cast<FunctionType*>(hookFunction)), step_(step), priority_(priority) {}

    friend class PluginManager;
};

#define PluginCall(name, ...) (__stdcall * (name))(__VA_ARGS__)
// Inherit from this to define a IPC (Inter-Plugin Communication) class.
class DLL PluginCommunicator {
public:
    typedef void(__stdcall *EventSubscription)(int id, void *dataPack);
private:
    std::map<std::string, EventSubscription> listeners;
public:
    void Dispatch(int id, void *dataPack) const;
    void AddListener(std::string plugin, EventSubscription event);

    std::string plugin;
    PluginCommunicator(std::string plugin) : plugin(std::move(plugin)) {}

    static void ExportPluginCommunicator(PluginCommunicator *communicator);
    static PluginCommunicator *ImportPluginCommunicator(std::string plugin, PluginCommunicator::EventSubscription subscription = nullptr);
};

#ifndef FLHOOK
struct PluginInfo {
    PluginInfo() = delete;

    IMPORT void versionMajor(PluginMajorVersion version);
    IMPORT void versionMinor(PluginMinorVersion version);
    IMPORT void name(const char* name);
    IMPORT void shortName(const char* shortName);
    IMPORT void mayPause(bool pause);
    IMPORT void mayUnload(bool unload);
    IMPORT void autoResetCode(bool reset);
    IMPORT void returnCode(ReturnCode* returnCode);
    IMPORT void addHook(const PluginHook& hook);

    template<typename... Args>
    void emplaceHook(Args&&... args) {
        PluginHook ph(std::forward<Args>(args)...);
        addHook(ph);
    }
};
#endif

#undef DLL