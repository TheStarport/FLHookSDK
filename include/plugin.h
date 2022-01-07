#pragma once

#include <__generated.h>

#define PLUGIN_API_VERSION 210

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
    CUSTOM_BASE_IS_DOCKED = 43
};

// Almost every plugin will handle user commands in the exact same way.
// Rather than duplicating this code block over and over, lets just macro it.
#define DefaultUserCommandHandling std::wstring wscCmdLower = ToLower(wscCmd); \
    for (uint i = 0; (i < sizeof(UserCmds) / sizeof(USERCMD)); i++) { \
        if (wscCmdLower.find(ToLower(UserCmds[i].wszCmd)) == 0) { \
            std::wstring wscParam = L""; \
            if (wscCmd.length() > wcslen(UserCmds[i].wszCmd)) { \
                if (wscCmd[wcslen(UserCmds[i].wszCmd)] != ' ') \ 
                    continue; \
                wscParam = wscCmd.substr(wcslen(UserCmds[i].wszCmd) + 1); \
            } \
            UserCmds[i].proc(iClientID, wscParam); \
            returncode = ReturnCode::SkipAll; \
            return true; \
        } \
    } \
    return false;