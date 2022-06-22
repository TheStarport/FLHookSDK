#pragma once

//
// WARNING: THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT!
//

enum class HookedCall {
	IEngine__CShip__Init,
	IEngine__CShip__Destroy,
	IEngine__UpdateTime,
	IEngine__ElapseTime,
	IEngine__DockCall,
	IEngine__LaunchPosition,
	IEngine__ShipDestroyed,
	IEngine__BaseDestroyed,
	IEngine__GuidedHit,
	IEngine__AddDamageEntry,
	IEngine__DamageHit,
	IEngine__AllowPlayerDamage,
	IEngine__SendDeathMessage,
	FLHook__TimerCheckKick,
	FLHook__TimerNPCAndF1Check,
	FLHook__UserCommand__Process,
	FLHook__AdminCommand__Help,
	FLHook__AdminCommand__Process,
	FLHook__LoadSettings,
	FLHook__LoadCharacterSettings,
	FLHook__ClearClientInfo,
	FLHook__ProcessEvent,
	IChat__SendChat,
	IClientImpl__Send_FLPACKET_COMMON_FIREWEAPON,
	IClientImpl__Send_FLPACKET_COMMON_ACTIVATEEQUIP,
	IClientImpl__Send_FLPACKET_COMMON_ACTIVATECRUISE,
	IClientImpl__Send_FLPACKET_COMMON_ACTIVATETHRUSTERS,
	IClientImpl__CDPClientProxy__GetLinkSaturation,
	IClientImpl__Send_FLPACKET_SERVER_SETSHIPARCH,
	IClientImpl__Send_FLPACKET_SERVER_SETHULLSTATUS,
	IClientImpl__Send_FLPACKET_SERVER_SETCOLLISIONGROUPS,
	IClientImpl__Send_FLPACKET_SERVER_SETEQUIPMENT,
	IClientImpl__Send_FLPACKET_SERVER_SETADDITEM,
	IClientImpl__Send_FLPACKET_SERVER_SETSTARTROOM,
	IClientImpl__Send_FLPACKET_SERVER_CREATESOLAR,
	IClientImpl__Send_FLPACKET_SERVER_CREATESHIP,
	IClientImpl__Send_FLPACKET_SERVER_CREATELOOT,
	IClientImpl__Send_FLPACKET_SERVER_CREATEMINE,
	IClientImpl__Send_FLPACKET_SERVER_CREATEGUIDED,
	IClientImpl__Send_FLPACKET_SERVER_CREATECOUNTER,
	IClientImpl__Send_FLPACKET_COMMON_UPDATEOBJECT,
	IClientImpl__Send_FLPACKET_SERVER_DESTROYOBJECT,
	IClientImpl__Send_FLPACKET_SERVER_ACTIVATEOBJECT,
	IClientImpl__Send_FLPACKET_SERVER_LAUNCH,
	IClientImpl__Send_FLPACKET_SERVER_REQUESTCREATESHIPRESP,
	IClientImpl__Send_FLPACKET_SERVER_USE_ITEM,
	IClientImpl__Send_FLPACKET_SERVER_SETREPUTATION,
	IClientImpl__Send_FLPACKET_SERVER_SENDCOMM,
	IClientImpl__Send_FLPACKET_SERVER_SET_MISSION_MESSAGE,
	IClientImpl__Send_FLPACKET_SERVER_SETMISSIONOBJECTIVES,
	IClientImpl__Send_FLPACKET_SERVER_SETCASH,
	IClientImpl__Send_FLPACKET_SERVER_BURNFUSE,
	IClientImpl__Send_FLPACKET_SERVER_SCANNOTIFY,
	IClientImpl__Send_FLPACKET_SERVER_PLAYERLIST,
	IClientImpl__Send_FLPACKET_SERVER_PLAYERLIST_2,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE_6,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE_7,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE_2,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE_3,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE_4,
	IClientImpl__Send_FLPACKET_SERVER_MISCOBJUPDATE_5,
	IServerImpl__FireWeapon,
	IServerImpl__ActivateEquip,
	IServerImpl__ActivateCruise,
	IServerImpl__ActivateThrusters,
	IServerImpl__SetTarget,
	IServerImpl__TractorObjects,
	IServerImpl__GoTradelane,
	IServerImpl__StopTradelane,
	IServerImpl__JettisonCargo,
	IServerImpl__Startup,
	IServerImpl__Shutdown,
	IServerImpl__Update,
	IServerImpl__DisConnect,
	IServerImpl__OnConnect,
	IServerImpl__Login,
	IServerImpl__CharacterInfoReq,
	IServerImpl__CharacterSelect,
	IServerImpl__CreateNewCharacter,
	IServerImpl__DestroyCharacter,
	IServerImpl__ReqShipArch,
	IServerImpl__ReqHullStatus,
	IServerImpl__ReqCollisionGroups,
	IServerImpl__ReqEquipment,
	IServerImpl__ReqAddItem,
	IServerImpl__ReqRemoveItem,
	IServerImpl__ReqModifyItem,
	IServerImpl__ReqSetCash,
	IServerImpl__ReqChangeCash,
	IServerImpl__BaseEnter,
	IServerImpl__BaseExit,
	IServerImpl__LocationEnter,
	IServerImpl__LocationExit,
	IServerImpl__BaseInfoRequest,
	IServerImpl__LocationInfoRequest,
	IServerImpl__GFObjSelect,
	IServerImpl__GFGoodVaporized,
	IServerImpl__MissionResponse,
	IServerImpl__TradeResponse,
	IServerImpl__GFGoodBuy,
	IServerImpl__GFGoodSell,
	IServerImpl__SystemSwitchOutComplete,
	IServerImpl__PlayerLaunch,
	IServerImpl__LaunchComplete,
	IServerImpl__JumpInComplete,
	IServerImpl__Hail,
	IServerImpl__SPObjUpdate,
	IServerImpl__SPMunitionCollision,
	IServerImpl__SPObjCollision,
	IServerImpl__SPRequestUseItem,
	IServerImpl__SPRequestInvincibility,
	IServerImpl__RequestEvent,
	IServerImpl__RequestCancel,
	IServerImpl__MineAsteroid,
	IServerImpl__RequestCreateShip,
	IServerImpl__SPScanCargo,
	IServerImpl__SetManeuver,
	IServerImpl__InterfaceItemUsed,
	IServerImpl__AbortMission,
	IServerImpl__SetWeaponGroup,
	IServerImpl__SetVisitedState,
	IServerImpl__RequestBestPath,
	IServerImpl__RequestPlayerStats,
	IServerImpl__PopupDialog,
	IServerImpl__RequestGroupPositions,
	IServerImpl__SetInterfaceState,
	IServerImpl__RequestRankLevel,
	IServerImpl__InitiateTrade,
	IServerImpl__TerminateTrade,
	IServerImpl__AcceptTrade,
	IServerImpl__SetTradeMoney,
	IServerImpl__AddTradeEquip,
	IServerImpl__DelTradeEquip,
	IServerImpl__RequestTrade,
	IServerImpl__StopTradeRequest,
	IServerImpl__SubmitChat,
	Count
};