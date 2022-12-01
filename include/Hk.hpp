#pragma once

#include "Typedefs.hpp"
#include "Enums.hpp"
#include "Constexpr.hpp"
#include "Macros.hpp"

extern DLL st6_malloc_t st6_malloc;
extern DLL st6_free_t st6_free;
#define ST6_ALLOCATION_DEFINED

#include "FLCoreCommon.h"
#include "FLCoreServer.h"
#include "FLCoreRemoteClient.h"
#include "FLCoreDALib.h"
#include "plugin.h"

#include "Structs.hpp"

// vcpkg
#include "magic_enum.hpp"
#include "fmt/format.h"

// Libs
#include <ext/Singleton.h>
#include <ext/Wildcard.hpp>
#include <ext/jpcre2.hpp>
#include <ext/result.hpp>

struct CARGO_INFO;
using jp = jpcre2::select<char>;
using jpWide = jpcre2::select<wchar_t>;

namespace Hk
{
	namespace Time
	{
		std::chrono::seconds Unix();
		std::chrono::milliseconds UnixMilliseconds();

		template<typename T>
		std::chrono::microseconds ToMicroseconds(T duration)
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(duration);
		}

		template<typename T>
		std::chrono::milliseconds ToMilliseconds(T duration)
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
		}

		template<typename T>
		std::chrono::seconds ToSeconds(T duration)
		{
			return std::chrono::duration_cast<std::chrono::seconds>(duration);
		}

		template<typename T>
		std::chrono::minutes ToMinutes(T duration)
		{
			return std::chrono::duration_cast<std::chrono::minutes>(duration);
		}

		template<typename T>
		std::chrono::hours ToHours(T duration)
		{
			return std::chrono::duration_cast<std::chrono::hours>(duration);
		}

		template<typename T>
		std::chrono::nanoseconds ToNanoseconds(T duration)
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
		}
	} // namespace Time

	namespace Client
	{

		/**
		 * Gets the current client id of the account.
		 * @param acc CAccount
		 * @returns On success : Client id of the active user of the account.
		 * @returns On fail : [PlayerNotLoggedIn] The function could not find a client id associated with the account id.
		 */
		DLL cpp::result<const uint, Error> GetClientIdFromAccount(CAccount* acc);

		DLL std::wstring GetAccountIDByClientID(uint clientId);

		DLL CAccount* GetAccountByClientID(uint clientId);

		/**
		 * Gets the current client id of the character.
		 * @param character Wide string of the character name
		 * @returns On success : current client Id associated with that character name
		 * @returns On fail : [CharacterDoesNotExist] The function could not find a client id associated with this character name.
		 */
		DLL cpp::result<const uint, Error> GetClientIdFromCharName(const std::wstring& character);

		/**
		 * Checks to see if the client Id is valid
		 * @param clientId Client Id
		 * @returns If Valid: true
		 * @returns If Not Valid: false
		 */
		DLL bool IsValidClientID(uint clientId);

		/**
		 * Gets the account of the character
		 * @param character Wide string of the character name
		 * @returns On success : the account Id for that character
		 * @returns On fail : [CharacterDoesNotExist] The function could not find the account id associated with this character name.
		 */
		DLL cpp::result<CAccount*, Error> GetAccountByCharName(const std::wstring& character);

		/**
		 * Gets the account id in a wide string
		 * @param acc The account
		 * @returns On success : wide string of account Id
		 * @returns On fail : [CannotGetAccount] The function could not find the account.
		 */
		DLL cpp::result<const std::wstring, Error> GetAccountID(CAccount* acc);


		/**
		 * Gets the account id in a wide string
		 * @param fileName The account
		 * @returns On success : wide string of account Id
		 * @returns On fail : [CannotGetAccount] The function could not find the account.
		 */
		DLL bool IsEncoded(const std::string& fileName);


		DLL bool IsInCharSelectMenu(const uint& player);

		DLL cpp::result<const std::wstring, Error> GetCharacterNameById(const uint& clientId);
		DLL cpp::result<const uint, Error> ResolveId(const std::wstring& player);
		DLL cpp::result<const uint, Error> ResolveShortCut(const std::wstring& wscShortcut);
		DLL cpp::result<const ClientId, Error> GetClientIDByShip(ShipId iShip);
		DLL std::wstring GetAccountDirName(const CAccount* acc);
		DLL cpp::result<const std::wstring, Error> GetCharFileName(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const std::wstring, Error> GetBaseNickByID(uint baseId);
		DLL cpp::result<const std::wstring, Error> GetPlayerSystem(uint clientId);
		DLL cpp::result<const std::wstring, Error> GetSystemNickByID(uint systemId);
		DLL cpp::result<void, Error> LockAccountAccess(CAccount* acc, bool bKick);
		DLL cpp::result<void, Error> UnlockAccountAccess(CAccount* acc);
		DLL void GetItemsForSale(uint baseId, std::list<uint>& lstItems);
		DLL cpp::result<IObjInspectImpl*, Error> GetInspect(uint clientId);
		DLL EngineState GetEngineState(uint clientId);
		DLL EquipmentType GetEqType(Archetype::Equipment* eq);
	} // namespace Client

	namespace Math
	{
		/**
		 * Computes the difference between two points in 3d space,
		 * @param v1 3d vector 1
		 * @param v2 3d vector 2
		 * @returns a scalar of the distance between point v2 and v1
		 */
		DLL float Distance3D(Vector v1, Vector v2);

		/**
		 * See Distance3D for more information
		 * @see Distance3D
		 */
		DLL cpp::result<float, Error> Distance3DByShip(uint ship1, uint ship2);

		/**
		 * Converts a 3x3 rotation matrix into an equivalent quaternion.
		 */
		DLL Quaternion MatrixToQuaternion(const Matrix& m);
		template<typename Str>
		Str VectorToSectorCoord(uint systemId, Vector vPos);
		template DLL std::string VectorToSectorCoord(uint systemId, Vector vPos);
		template DLL std::wstring VectorToSectorCoord(uint systemId, Vector vPos);
		DLL float Degrees(float rad);
		DLL Vector MatrixToEuler(const Matrix& mat);
		DLL uint RgbToBgr(uint color);
		DLL std::wstring UintToHexString(uint number, uint width, bool addPrefix = false);
	} // namespace Math

	namespace Message
	{
		DLL cpp::result<void, Error> Msg(const std::variant<uint, std::wstring>& player, const std::wstring& wscMessage);
		DLL cpp::result<void, Error> MsgS(const std::wstring& wscSystemname, const std::wstring& wscMessage);
		DLL cpp::result<void, Error> MsgU(const std::wstring& wscMessage);
		DLL cpp::result<void, Error> FMsgEncodeXML(const std::wstring& wscXml, char* szBuf, uint iSize, uint& iRet);
		DLL void FMsgSendChat(uint clientId, char* szBuf, uint iSize);
		DLL cpp::result<void, Error> FMsg(uint clientId, const std::wstring& wscXML);
		DLL cpp::result<void, Error> FMsg(const std::variant<uint, std::wstring>& player, const std::wstring& wscXML);
		DLL cpp::result<void, Error> FMsgS(const std::wstring& wscSystemname, const std::wstring& wscXML);
		DLL cpp::result<void, Error> FMsgU(const std::wstring& wscXML);
		DLL const std::wstring FormatMsg(MessageColor color, MessageFormat format, std::wstring msg, ...);
		DLL std::wstring GetWStringFromIDS(uint iIDS);
		DLL void LoadStringDLLs();
		DLL void UnloadStringDLLs();
		DLL cpp::result<void, Error> FormatSendChat(uint iToClientID, const std::wstring& wscSender, const std::wstring& text,
			const std::wstring& textColor);
		DLL void SendGroupChat(uint iFromClientID, const std::wstring& text);
		DLL void SendLocalSystemChat(uint iFromClientID, const std::wstring& text);
		DLL cpp::result<void, Error> SendPrivateChat(uint iFromClientID, uint iToClientID, const std::wstring& text);
		DLL void SendSystemChat(uint iFromClientID, const std::wstring& text);
	} // namespace Message

	namespace Player
	{
		DLL cpp::result<void, Error> AddToGroup(uint clientId, uint iGroupID);
		DLL cpp::result<const uint, Error> GetGroupID(uint clientId);
		DLL cpp::result<const int, Error> GetCash(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> AddCash(const std::variant<uint, std::wstring>& player, int iAmount);
		DLL cpp::result<void, Error> Kick(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> KickReason(const std::variant<uint, std::wstring>& player, const std::wstring& wscReason);
		DLL cpp::result<void, Error> Ban(const std::variant<uint, std::wstring>& player, bool bBan);
		DLL cpp::result<void, Error> Beam(const std::variant<uint, std::wstring>& player, const std::wstring& wscBasename);
		DLL cpp::result<void, Error> SaveChar(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const std::list<CARGO_INFO>, Error> EnumCargo(const std::variant<uint, std::wstring>& player, int& iRemainingHoldSize);
		DLL cpp::result<void, Error> RemoveCargo(const std::variant<uint, std::wstring>& player, uint iID, int iCount);
		DLL cpp::result<void, Error> AddCargo(const std::variant<uint, std::wstring>& player, uint iGoodID, int iCount, bool bMission);
		DLL cpp::result<void, Error> AddCargo(const std::variant<uint, std::wstring>& player, const std::wstring& wscGood, int iCount, bool bMission);
		DLL cpp::result<void, Error> Rename(const std::variant<uint, std::wstring>& player, const std::wstring& wscNewCharname, bool bOnlyDelete);
		DLL cpp::result<void, Error> MsgAndKick(uint clientId, const std::wstring& wscReason, uint iIntervall);
		DLL cpp::result<void, Error> Kill(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<bool, Error> GetReservedSlot(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> SetReservedSlot(const std::variant<uint, std::wstring>& player, bool bReservedSlot);
		DLL void PlayerAutoBuy(uint clientId, uint baseId);
		DLL cpp::result<void, Error> ResetRep(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<std::vector<GROUP_MEMBER>, Error> GetGroupMembers(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> SetRep(const std::variant<uint, std::wstring>& player, const std::wstring& wscRepGroup, float fValue);
		DLL cpp::result<float, Error> GetRep(const std::variant<uint, std::wstring>& player, const std::wstring& repGroup);
		DLL cpp::result<std::list<std::wstring>, Error> ReadCharFile(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> WriteCharFile(const std::variant<uint, std::wstring>& player, std::wstring wscData);
		DLL cpp::result<void, Error> PlayerRecalculateCRC(uint clientId);
		DLL std::string GetPlayerSystemS(uint clientId);
		DLL bool IsInRange(uint clientId, float fDistance);
		DLL std::wstring GetLocation(unsigned int clientId);
		DLL cpp::result<void, Error> SetEquip(const std::variant<uint, std::wstring>& player, const st6::list<EquipDesc>& equip);
		DLL cpp::result<void, Error> AddEquip(const std::variant<uint, std::wstring>& player, uint iGoodID, const std::string& scHardpoint);
		DLL cpp::result<void, Error> AntiCheat(uint clientId);
		DLL void DelayedKick(uint clientId, uint secs);
		DLL void DeleteCharacter(CAccount* acc, std::wstring& character);
		DLL cpp::result<void, Error> NewCharacter(CAccount* acc, std::wstring& character);
		DLL cpp::result<int, Error> GetOnlineTime(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<int, Error> GetRank(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const float, Error> GetShipValue(const std::variant<uint, std::wstring>& player);
		DLL void RelocateClient(uint clientId, Vector vDestination, Matrix mOrientation);
		DLL void SaveChar(uint clientId);
		DLL cpp::result<const ShipId, Error> GetTarget(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const ClientId, Error> GetTargetClientId(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const BaseId, Error> GetCurrentBase(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const SystemId, Error> GetSystem(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<const ShipId, Error> GetShip(const std::variant<uint, std::wstring>& player);
	}

	namespace Ini
	{
		DLL cpp::result<std::wstring, Error> GetFromPlayerFile(const std::variant<uint, std::wstring>& player, const std::wstring& wscKey);
		DLL cpp::result<void, Error> WriteToPlayerFile(const std::variant<uint, std::wstring>& player, const std::wstring& wscKey, const std::wstring& wscValue);

		DLL void SetCharacterIni(uint client, const std::wstring& name, std::wstring value);
		DLL std::wstring GetCharacterIniString(uint client, const std::wstring& name);
		DLL bool GetCharacterIniBool(uint client, const std::wstring& name);
		DLL int GetCharacterIniInt(uint client, const std::wstring& name);
		DLL uint GetCharacterIniUint(uint client, const std::wstring& name);
		DLL float GetCharacterIniFloat(uint client, const std::wstring& name);
		DLL double GetCharacterIniDouble(uint client, const std::wstring& name);
		DLL int64_t GetCharacterIniInt64(uint client, const std::wstring& name);
	}

	namespace Admin
	{
		DLL std::wstring GetPlayerIP(uint clientId);
		DLL cpp::result<PLAYERINFO, Error> GetPlayerInfo(const std::variant<uint, std::wstring>& player, bool bAlsoCharmenu);
		DLL std::list<PLAYERINFO> GetPlayers();
		DLL cpp::result<DPN_CONNECTION_INFO, Error> GetConnectionStats(uint clientId);
		DLL cpp::result<void, Error> SetAdmin(const std::variant<uint, std::wstring>& player, const std::wstring& wscRights);
		DLL cpp::result<std::wstring, Error> GetAdmin(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> DelAdmin(const std::variant<uint, std::wstring>& player);
		DLL cpp::result<void, Error> ChangeNPCSpawn(bool bDisable);
		DLL cpp::result<BaseHealth, Error> GetBaseStatus(const std::wstring& wscBasename);
		DLL Fuse* GetFuseFromID(uint iFuseID);
		DLL bool LightFuse(IObjRW* ship, uint iFuseID, float fDelay, float fLifetime, float fSkip);
		DLL bool UnLightFuse(IObjRW* ship, uint iFuseID);
		DLL CEqObj* GetEqObjFromObjRW(struct IObjRW* objRW);
	}

	namespace Err
	{
		DLL std::wstring ErrGetText(Error Err);
	}

	namespace Personalities
	{
		DLL cpp::result<pub::AI::Personality, Error> GetPersonality(const std::string& pilotNickname);
	}
} // namespace Hk