#pragma once

#include <FLHook.h>
#include <plugin.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// message structs

struct ANTICHEAT_TELEPORT_STRUCT // in
{
	uint iClientID; 
	Vector vNewPos; 
	Matrix mNewOrient; 
};

enum ANTICHEAT_CHEAT_CODE
{
	AC_CODE_POWER,
	AC_CODE_TIMER,
	AC_CODE_SPEED,
	AC_CODE_MINING,
};

struct ANTICHEAT_CHEATER_STRUCT
{
	uint iClientID; 
	std::wstring wscCharname;
	ANTICHEAT_CHEAT_CODE CheatCode;
	std::wstring wscLog;
	bool bKilled;
};

struct CONDATA_DATA_STRUCT
{
	uint		iClientID; // in
	uint		iAveragePing; // out
	uint		iAverageLoss; // out
	uint		iPingFluctuation; // out
	uint		iLags; // out
};

struct	CONDATA_EXCEPTION_STRUCT // in
{
	uint iClientID;
	bool bException;
    std::string sReason;
};

struct	TEMPBAN_BAN_STRUCT // in
{
	uint iClientID;
    uint iDuration;
};

struct DSACE_CHANGE_INFOCARD_STRUCT
{
	uint iClientID;
	uint ids;
	std::wstring text;
};

struct DSACE_SPEED_EXCEPTION_STRUCT
{
	uint iClientID;
};

struct CUSTOM_BASE_BEAM_STRUCT
{
	uint iClientID;
	uint iTargetBaseID;
	bool bBeamed;
};

struct CUSTOM_BASE_IS_DOCKED_STRUCT
{
	uint iClientID;
	uint iDockedBaseID;
};

struct CUSTOM_MAIL_STRUCT {
    std::wstring wscTargetCharname;
    std::wstring wscMsg;
};

/** Send a temp ban request to the tempban plugin */
inline void HkTempBan(uint iClientID, uint iDuration)
{
	// call tempban plugin
	TEMPBAN_BAN_STRUCT tempban;
	tempban.iClientID = iClientID;
	tempban.iDuration = iDuration;
	PluginCommunication(TEMPBAN_BAN,&tempban);
}

/** Instructs DSAce to change an IDS std::string */
inline void HkChangeIDSString(uint iClientID, uint ids, const std::wstring &text)
{
	DSACE_CHANGE_INFOCARD_STRUCT info;
	info.iClientID = iClientID;
	info.ids = ids;
	info.text = text;
	PluginCommunication(DSACE_CHANGE_INFOCARD, &info);
}

/** Used to send mail to the mail plugin */
inline void HkSendMail(std::wstring wscTargetCharname, std::wstring wscCharname, std::wstring wscMsg) {
    CUSTOM_MAIL_STRUCT info;
    info.wscTargetCharname = wscTargetCharname;
    info.wscMsg = wscCharname + L": " + wscMsg;
    PluginCommunication(MAIL, &info);
}
