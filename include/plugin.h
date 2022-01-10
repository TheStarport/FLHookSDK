#pragma once

#include <__generated.h>

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

#ifndef FLHOOK
struct PluginInfo {
    PluginInfo() = delete;

    IMPORT void version(int version = PLUGIN_API_VERSION);
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

enum PLUGIN_MESSAGE {
    DEFAULT_MESSAGE = 0,
    CONDATA_EXCEPTION = 10,
    CONDATA_DATA = 11,
    TEMPBAN_BAN = 20,
    ANTICHEAT_TELEPORT = 30,
    ANTICHEAT_CHEATER = 31,
    DSACE_CHANGE_INFOCARD = 40,
    DSACE_SPEED_EXCEPTION = 41,
    CUSTOM_BASE_BEAM = 42,
    CUSTOM_BASE_IS_DOCKED = 43,
    MAIL = 44
};