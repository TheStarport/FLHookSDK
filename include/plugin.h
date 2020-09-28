#pragma once

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

enum class HookedCall {
    HkCb_AddDmgEntry,
    HkCb_Dock_Call,
    HkCb_Elapse_Time,
    HkCb_GeneralDmg,
    HkCB_MissileTorpHit,
    HkCb_SendChat,
    HkCb_Update_Time,

    HkIClientImpl_Send_FLPACKET_COMMON_ACTIVATECRUISE,
    HkIClientImpl_Send_FLPACKET_COMMON_ACTIVATEEQUIP,
    HkIClientImpl_Send_FLPACKET_COMMON_ACTIVATETHRUSTERS,
    HkIClientImpl_Send_FLPACKET_COMMON_FIREWEAPON,
    HkIClientImpl_Send_FLPACKET_COMMON_UPDATEOBJECT,
    HkIClientImpl_Send_FLPACKET_SERVER_ACTIVATEOBJECT,
    HkIClientImpl_Send_FLPACKET_SERVER_CREATELOOT,
    HkIClientImpl_Send_FLPACKET_SERVER_CREATESHIP,
    HkIClientImpl_Send_FLPACKET_SERVER_CREATESOLAR,
    HkIClientImpl_Send_FLPACKET_SERVER_DESTROYOBJECT,
    HkIClientImpl_Send_FLPACKET_SERVER_LAUNCH,
    HkIClientImpl_Send_FLPACKET_SERVER_MISCOBJUPDATE_3,
    HkIClientImpl_Send_FLPACKET_SERVER_MISCOBJUPDATE_5,
    HkIClientImpl_Send_FLPACKET_SERVER_REQUESTCREATESHIPRESP,
    HkIClientImpl_SendPacket,

    HkIEngine_CShip_destroy,
    HkIEngine_CShip_init,

    HkIServerImpl_AbortMission,
    HkIServerImpl_AcceptTrade,
    HkIServerImpl_ActivateCruise,
    HkIServerImpl_ActivateEquip,
    HkIServerImpl_ActivateThrusters,
    HkIServerImpl_AddTradeEquip,
    HkIServerImpl_BaseEnter,
    HkIServerImpl_BaseExit,
    HkIServerImpl_BaseInfoRequest,
    HkIServerImpl_CharacterInfoReq,
    HkIServerImpl_CharacterSelect,
    HkIServerImpl_CreateNewCharacter,
    HkIServerImpl_DelTradeEquip,
    HkIServerImpl_DestroyCharacter,
    HkIServerImpl_DisConnect,
    HkIServerImpl_FireWeapon,
    HkIServerImpl_GFGoodBuy,
    HkIServerImpl_GFGoodSell,
    HkIServerImpl_GFGoodVaporized,
    HkIServerImpl_GFObjSelect,
    HkIServerImpl_GoTradelane,
    HkIServerImpl_Hail,
    HkIServerImpl_InitiateTrade,
    HkIServerImpl_InterfaceItemUsed,
    HkIServerImpl_JettisonCargo,
    HkIServerImpl_JumpInComplete,
    HkIServerImpl_LaunchComplete,
    HkIServerImpl_LocationEnter,
    HkIServerImpl_LocationExit,
    HkIServerImpl_LocationInfoRequest,
    HkIServerImpl_Login,
    HkIServerImpl_MineAsteroid,
    HkIServerImpl_MissionResponse,
    HkIServerImpl_OnConnect,
    HkIServerImpl_ReqAddItem,
    HkIServerImpl_ReqChangeCash,
    HkIServerImpl_ReqCollisionGroups,
    HkIServerImpl_ReqEquipment,
    HkIServerImpl_ReqHullStatus,
    HkIServerImpl_ReqModifyItem,
    HkIServerImpl_ReqRemoveItem,
    HkIServerImpl_ReqSetCash,
    HkIServerImpl_ReqShipArch,
    HkIServerImpl_RequestBestPath,
    HkIServerImpl_RequestCancel,
    HkIServerImpl_RequestCreateShip,
    HkIServerImpl_RequestEvent,
    HkIServerImpl_RequestGroupPositions,
    HkIServerImpl_RequestPlayerStats,
    HkIServerImpl_RequestRankLevel,
    HkIServerImpl_RequestTrade,
    HkIServerImpl_SetInterfaceState,
    HkIServerImpl_SetManeuver,
    HkIServerImpl_SetTarget,
    HkIServerImpl_SetTradeMoney,
    HkIServerImpl_SetVisitedState,
    HkIServerImpl_SetWeaponGroup,
    HkIServerImpl_Shutdown,
    HkIServerImpl_SPMunitionCollision,
    HkIServerImpl_SPObjCollision,
    HkIServerImpl_SPObjUpdate,
    HkIServerImpl_SPRequestInvincibility,
    HkIServerImpl_SPRequestUseItem,
    HkIServerImpl_SPScanCargo,
    HkIServerImpl_Startup,
    HkIServerImpl_StopTradelane,
    HkIServerImpl_StopTradeRequest,
    HkIServerImpl_SystemSwitchOutComplete,
    HkIServerImpl_TerminateTrade,
    HkIServerImpl_TractorObjects,
    HkIServerImpl_TradeResponse,

    HkTimerCheckKick,
    HkTimerNPCAndF1Check,

    AllowPlayerDamage,
    BaseDestroyed,
    ClearClientInfo,
    CmdHelp,
    LaunchPosHook,
    LoadUserCharSettings,
    SendDeathMsg,
    ShipDestroyed,

    UserCmd_Help,
    UserCmd_Process,
    
    ExecuteCommandString,
    LoadSettings,
    PluginCommunication,
    ProcessEvent,

    Count
};

enum class HookStep {
    Before,
    After
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
        : targetFunction_(targetFunction), hookFunction_(hookFunction), step_(step), priority_(priority) {}

    friend class PluginManager;
};

#ifndef FLHOOK
struct PluginInfo {
    IMPORT void version(int version = PLUGIN_API_VERSION);
    IMPORT void name(const char* name);
    IMPORT void shortName(const char* shortName);
    IMPORT void mayPause(bool pause);
    IMPORT void mayUnload(bool unload);
    IMPORT void returnCode(ReturnCode* returnCode);
    IMPORT void addHook(const PluginHook& hook);
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
