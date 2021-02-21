//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreRemoteClient.h
//	Module:			FLCoreRemoteClient.lib
//	Description:	Interface to RemoteClient.dll
//
//	Web: www.skif.be/flcoresdk.php
//  
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCOREREMOTECLIENT_H_
#define _FLCOREREMOTECLIENT_H_

#include "FLCoreDefs.h"
#include "FLCoreCommon.h"

#pragma warning(disable : 5030)
#pragma comment( lib, "FLCoreRemoteClient.lib" )

struct SSPObjUpdateInfo;
struct XJettisonCargo;
struct XGoTradelane;
struct XSetTarget;
struct XActivateEquip;
struct XActivateThrusters;
struct XActivateCruise;
struct XFireWeaponInfo;

class IMPORT IClient
{
public:
	 IClient(class IClient const &);
	 IClient(void);
	 class IClient & operator=(class IClient const &);

public:
	unsigned char data[OBJECT_DATA_SIZE];
};


class CDPServer;

///////////////////////////////
///// FL PACKET STRUCTS ///////
///////////////////////////////

struct FLPACKET_UNKNOWN
{
	uint iDunno[20];
};

struct FLPACKET_SETREPUTATION
{
	uint iSpaceID;
	float fRep;
	uint iRepGroup; // not sure
	// there is more (FMTStr? - object name?)
};

struct FLPACKET_LAUNCH
{
	uint iShip;
	uint iBase;
	uint iState;
	float fRotate[4];
	float fPos[3];
};

struct FLPACKET_BURNFUSE
{
	uint iShipAttacker;
	uint iShip;
	uint iFuseID;
	uint iDunno1;
	uint iDunno2;
	float fDunno;
	bool bActive;
};

struct FLPACKET_DESTROYOBJECT
{
	uint iSpaceID;
	uint iDestroyType;
};

struct FLPACKET_CREATESHIP
{
	char* pAddress; // ??
	uint iSpaceID;
	uint iShipArch;
	uint iDunno1;
	uint iPilot;
	struct {
		uint body;
		uint head;
		uint lefthand;
		uint righthand;
		uint accessory[8];
		int  accessories;
	} costume;
	uint iVoiceID;
	Vector vPos;
	Quaternion qOrientation;
	int iHealth;
	uint iDunno3;
	uint iSize1;
	EquipDesc* equipBegin;
	EquipDesc* equipEnd;
	void* equipPointer3;
	uint iSize2;
	void* cargoPointer1;
	void* cargoPointer2;
	uint iSize3;
	void *dunnoPointer1;
	void *dunnoPointer2;
	uint iDunno4[5];
	uint iClientID;
	uint iDunno5;
	uint iLevel;
};

struct FLPACKET_CREATESOLAR
{
	char* pAddress; // ??
	uint iSpaceID;
	uint iSolarArch;
	uint iDunno;
	uint iPilot;
	struct {
		uint body;
		uint head;
		uint lefthand;
		uint righthand;
		uint accessory[8];
		int  accessories;
	} costume;
	int iVoiceID;
	Vector vPos;
	Quaternion qOrientation;
	float fHealth;

};

struct FLPACKET_LAND
{
	uint iShip;
	uint iLandSpaceID;
	uint iTargetBase;
};

struct [[Hook, ClientCall]] HkIClientImpl
{
public:
	void* unknown[2];
	CDPServer* cdpServer;

	// N.B. Do not modify order, vtable ordering is fixed by RemoteClient.dll
	virtual bool Send_FLPACKET_COMMON_FIREWEAPON(uint clientID, XFireWeaponInfo& fwi);
	virtual bool Send_FLPACKET_COMMON_ACTIVATEEQUIP(uint clientID, XActivateEquip& aq);
	virtual bool Send_FLPACKET_COMMON_ACTIVATECRUISE(uint clientID, XActivateCruise& aq);
	virtual bool Send_FLPACKET_COMMON_ACTIVATETHRUSTERS(uint clientID, XActivateThrusters& aq);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_SETTARGET(uint clientID, XSetTarget& st);
	[[NoPlugins]] virtual void unknown_6(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_GOTRADELANE(uint clientID, XGoTradelane& tl);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_STOPTRADELANE(uint clientID, uint shipID, uint archTradelane1, uint archTradelane2);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_JETTISONCARGO(uint clientID, XJettisonCargo& jc);
	[[NoPlugins, NoLog]] virtual bool SendPacket(uint clientID, void*);
	[[CallInner, NoLog, NoPlugins]] virtual bool Startup(uint, uint);
	[[NoPlugins]] virtual void nullsub(uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_LOGINRESPONSE(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_CHARACTERINFO(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_CHARSELECTVERIFIED(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins, NoLog]] virtual void Shutdown();
	[[NoHook]] virtual bool DispatchMsgs();
	[[NoPlugins]] virtual bool CDPClientProxy__Disconnect(uint clientID);
	[[NoPlugins]] virtual uint CDPClientProxy__GetSendQSize(uint clientID);
	[[NoPlugins]] virtual uint CDPClientProxy__GetSendQBytes(uint clientID);
	virtual double CDPClientProxy__GetLinkSaturation(uint clientID);
	virtual bool Send_FLPACKET_SERVER_SETSHIPARCH(uint clientID, uint shipArch);
	virtual bool Send_FLPACKET_SERVER_SETHULLSTATUS(uint clientID, float status);
	virtual bool Send_FLPACKET_SERVER_SETCOLLISIONGROUPS(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_SETEQUIPMENT(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_26(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_SETADDITEM(uint clientID, FLPACKET_UNKNOWN&, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_28(uint clientID, uint, uint, uint);
	virtual bool Send_FLPACKET_SERVER_SETSTARTROOM(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFDESTROYCHARACTER(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFUPDATECHAR(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFCOMPLETECHARLIST(uint clientID, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFSCRIPTBEHAVIOR(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFDESTROYSCRIPTBEHAVIOR(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFCOMPLETESCRIPTBEHAVIORLIST(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_36(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_37(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFCOMPLETEAMBIENTSCRIPTLIST(uint clientID, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFDESTROYMISSIONCOMPUTER(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFUPDATEMISSIONCOMPUTER(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFCOMPLETEMISSIONCOMPUTERLIST(uint clientID, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFMISSIONVENDORACCEPTANCE(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFMISSIONVENDORWHYEMPTY(uint clientID, uint reason);
	[[NoPlugins]] virtual void unknown_44(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFUPDATENEWSBROADCAST(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_GFCOMPLETENEWSBROADCASTLIST(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_CREATESOLAR(uint clientID, FLPACKET_CREATESOLAR& solar);
	virtual bool Send_FLPACKET_SERVER_CREATESHIP(uint clientID, FLPACKET_CREATESHIP& ship);
	virtual bool Send_FLPACKET_SERVER_CREATELOOT(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_CREATEMINE(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_CREATEGUIDED(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_CREATECOUNTER(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_53(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_54(uint clientID, uint, uint, uint);
	[[NoLog]] virtual bool Send_FLPACKET_COMMON_UPDATEOBJECT(uint clientID, SSPObjUpdateInfo& update);
	virtual bool Send_FLPACKET_SERVER_DESTROYOBJECT(uint clientID, FLPACKET_DESTROYOBJECT& destroy);
	virtual bool Send_FLPACKET_SERVER_ACTIVATEOBJECT(uint clientID, XActivateEquip& aq);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_SYSTEM_SWITCH_OUT(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_SYSTEM_SWITCH_IN(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_LAND(uint clientID, FLPACKET_LAND& land);
	virtual bool Send_FLPACKET_SERVER_LAUNCH(uint clientID, FLPACKET_LAUNCH& launch);
	virtual bool Send_FLPACKET_SERVER_REQUESTCREATESHIPRESP(uint clientID, bool response, uint shipID);
	[[NoPlugins]] virtual void unknown_63(uint clientID, FLPACKET_UNKNOWN&);
	[[NoLog, NoPlugins]] virtual bool Send_FLPACKET_SERVER_DAMAGEOBJECT(uint clientID, uint objID, DamageList& dmgList);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_ITEMTRACTORED(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_USE_ITEM(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_SETREPUTATION(uint clientID, FLPACKET_SETREPUTATION& rep);
	[[NoPlugins]] virtual void unknown_68(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_SENDCOMM(uint clientID, uint, uint, uint, uint, uint, 
		uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint);
	[[NoPlugins]] virtual void unknown_70(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_SET_MISSION_MESSAGE(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_72(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_SETMISSIONOBJECTIVES(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_74(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_75(uint clientID, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_MARKOBJ(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_77(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_SETCASH(uint clientID, uint cash);
	[[NoPlugins]] virtual void unknown_79(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_80(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_81(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_82(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_83(uint clientID, char*);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_REQUEST_RETURNED(uint clientID, uint shipID, uint flag, uint, uint);
	[[NoPlugins]] virtual void unknown_85(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_86(uint clientID, uint, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_OBJECTCARGOUPDATE(uint clientID, uint, uint);
	virtual bool Send_FLPACKET_SERVER_BURNFUSE(uint clientID, FLPACKET_BURNFUSE& burnFuse);
	[[NoPlugins]] virtual void unknown_89(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_90(uint clientID);
	[[NoPlugins]] virtual void unknown_91(uint clientID, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_SET_WEAPON_GROUP(uint clientID, uchar*, int);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_SET_VISITED_STATE(uint clientID, uchar*, int);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_REQUEST_BEST_PATH(uint clientID, uchar*, int);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_REQUEST_PLAYER_STATS(uint clientID, uchar*, int);
	[[NoPlugins]] virtual void unknown_96(uint clientID, uint, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_REQUEST_GROUP_POSITIONS(uint clientID, uchar*, int);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_SET_MISSION_LOG(uint clientID, uchar*, int);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_SET_INTERFACE_STATE(uint clientID, uchar*, int);
	[[NoPlugins]] virtual void unknown_100(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_101(uint clientID, FLPACKET_UNKNOWN&);
	[[NoPlugins]] virtual void unknown_102(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_103(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_104(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_105(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_106(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_107(uint clientID, uint, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_COMMON_PLAYER_TRADE(uint clientID, uint);
	[[NoPlugins]] virtual void unknown_109(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_SCANNOTIFY(uint clientID, uint, uint);
	virtual bool Send_FLPACKET_SERVER_PLAYERLIST(uint clientID, wchar_t*, uint, char);
	[[NoPlugins]] virtual void unknown_112(uint clientID, uint);
	virtual bool Send_FLPACKET_SERVER_PLAYERLIST_2(uint clientID);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_6(uint clientID, uint, uint);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_7(uint clientID, uint, uint);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE(uint clientID, FLPACKET_UNKNOWN&);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_2(uint clientID, uint, uint);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_3(uint clientID, uint targetID, uint rank);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_4(uint clientID, uint, uint);
	virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_5(uint clientID, uint, uint);
	[[NoPlugins]] virtual void unknown_121(uint clientID, uint);
	[[NoPlugins]] virtual bool Send_FLPACKET_SERVER_FORMATION_UPDATE(uint clientID, uint shipID, Vector& formationOffset);
	[[NoPlugins]] virtual void unknown_123(uint clientID, uint, uint, uint, uint, uint, uint);
	[[NoPlugins]] virtual void unknown_124(uint clientID);
	[[NoPlugins]] virtual void unknown_125(uint clientID, uint);
	[[NoPlugins]] virtual int unknown_126(char*);
};

IMPORT  void  ForceClientLogout(unsigned int);
IMPORT  int  GetClientStats(struct client_stats_t *,int *);
IMPORT  int  GetNumClients(void);
IMPORT  void  GetRemoteClientPort( st6::vector<unsigned long> & );
IMPORT  void  SetRemoteClientPassword(unsigned short const *);
IMPORT  void  SetRemoteClientResponseData(bool,bool,int,unsigned short const *,unsigned int,char const *);
IMPORT  void  SetRemoteClientSessionName(unsigned short const *);
IMPORT  void  SetServerLogFunction(int (*)(struct ErrorCode,char const *,...));

extern "C" IMPORT HkIClientImpl Client;
extern "C" IMPORT HkIClientImpl * GetClientInterface();

#endif // _FLCOREREMOTECLIENT_H_
