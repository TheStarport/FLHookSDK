#pragma once

#include "Typedefs.hpp"
#include "Macros.hpp"
#include "Enums.hpp"
#include "Constexpr.hpp"

// vcpkg
#include "magic_enum.hpp"
#include "fmt/format.h"

// Libs
#include <ext/Singleton.h>
#include <ext/Wildcard.hpp>
#include <ext/jpcre2.hpp>
#include <ext/result.hpp>

using jp = jpcre2::select<char>;
using jpWide = jpcre2::select<wchar_t>;

extern DLL st6_malloc_t st6_malloc;
extern DLL st6_free_t st6_free;
#define ST6_ALLOCATION_DEFINED

#include "FLCoreCommon.h"
#include "FLCoreServer.h"
#include "FLCoreRemoteClient.h"
#include "FLCoreDALib.h"
#include "plugin.h"

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
		 * @see
		 */
		DLL cpp::result<const uint, HkError> HkGetClientIdFromAccount(CAccount* acc);

		/**
		 * Gets the current client id of the character.
		 * @param character Wide string of the character name
		 * @returns On success : current client Id associated with that character name
		 * @returns On fail : [CharacterDoesNotExist] The function could not find a client id associated with this character name.
		 * @see
		 */
		DLL cpp::result<const uint, HkError> HkGetClientIdFromCharname(const std::wstring& character);

		/**
		 * Checks to see if the client Id is valid
		 * @param clientId Client Id
		 * @returns If Valid: true
		 * @returns If Not Valid: false
		 * @see
		 */
		DLL bool HkIsValidClientID(uint clientId);

		/**
		 * Gets the account of the character
		 * @param character Wide string of the character name
		 * @returns On success : the account Id for that character
		 * @returns On fail : [CharacterDoesNotExist] The function could not find the account id associated with this character name.
		 * @see
		 */
		DLL cpp::result<CAccount*, HkError> HkGetAccountByCharName(const std::wstring& character);

		/**
		 * Gets the account id in a wide string
		 * @param acc The account
		 * @returns On success : wide string of account Id
		 * @returns On fail : [CannotGetAccount] The function could not find the account.
		 * @see
		 */
		DLL cpp::result<const std::wstring, HkError> HkGetAccountID(CAccount* acc);


		/**
		 * Gets the account id in a wide string
		 * @param fileName The account
		 * @returns On success : wide string of account Id
		 * @returns On fail : [CannotGetAccount] The function could not find the account.
		 * @see
		 */
		DLL bool HkIsEncoded(const std::string& fileName);

		//TODO: The params of this function make no sense, you would not know who the player is if they're in char select.
		DLL bool HkIsInCharSelectMenu(const std::variant<uint, std::wstring>& player);



		DLL cpp::result<const std::wstring, HkError> HkGetCharacterNameById(const uint& clientId);
		DLL cpp::result<const uint, HkError> HkResolveId(const std::wstring& player, uint& clientId);
		DLL cpp::result<const uint, HkError> HkResolveShortCut(const std::wstring& wscShortcut, uint& clientId);
		DLL cpp::result<const uint, HkError> HkGetClientIDByShip(uint iShip);
		DLL std::wstring HkGetAccountDirName(CAccount* acc, std::wstring& wscDir);
		DLL cpp::result<const std::wstring, HkError> HkGetAccountDirName(const std::variant<uint, std::wstring>& player, std::wstring& wscDir);
		DLL cpp::result<const std::wstring, HkError> HkGetCharFileName(const std::variant<uint, std::wstring>& player, std::wstring& wscFilename);
		DLL cpp::result<const std::wstring, HkError> HkGetBaseNickByID(uint baseId);
		DLL cpp::result<const std::wstring, HkError> HkGetPlayerSystem(uint clientId);
		DLL cpp::result<const std::wstring, HkError> HkGetSystemNickByID(uint systemId);
		DLL cpp::result<void, HkError> HkLockAccountAccess(CAccount* acc, bool bKick);
		DLL cpp::result<void, HkError> HkUnlockAccountAccess(CAccount* acc);
		DLL void HkGetItemsForSale(uint baseId, std::list<uint>& lstItems);
		DLL cpp::result<IObjInspectImpl*, HkError> HkGetInspect(uint clientId);
		DLL cpp::result<const EngineState, HkError> HkGetEngineState(uint clientId);
		DLL cpp::result<const EquipmentType, HkError> HkGetEqType(Archetype::Equipment* eq);
	} // namespace Client

	namespace Math
	{
		/**
		 * Computes the difference between two points in 3d space,
		 * @param v1 3d vector 1
		 * @param v2 3d vector 2
		 * @returns a scalar of the distance between point v2 and v1
		 * @see
		 */
		DLL float HkDistance3D(Vector v1, Vector v2);

		/**
		 * See HkDistance3D for more information
		 * @see HkDistance3D
		 */
		DLL cpp::result<float, HkError> HkDistance3DByShip(uint ship1, uint ship2);

		/**
		 * Converts a 3x3 rotation matrix into an equivalent quaternion.
		 */
		DLL Quaternion HkMatrixToQuaternion(Matrix m);
		template<typename Str>
		Str VectorToSectorCoord(uint systemId, Vector vPos);
		template DLL std::string VectorToSectorCoord(uint systemId, Vector vPos);
		template DLL std::wstring VectorToSectorCoord(uint systemId, Vector vPos);
		DLL float degrees(float rad);
		DLL Vector MatrixToEuler(const Matrix& mat);
		DLL uint RgbToBgr(uint color);
		DLL std::wstring UintToHexString(uint number, uint width, bool addPrefix = false);
	} // namespace Math

	namespace Message
	{
		DLL HkError HkMsg(uint clientId, const std::wstring& wscMessage);
		DLL HkError HkMsg(const std::variant<uint, std::wstring>& player, const std::wstring& wscMessage);
		DLL HkError HkMsgS(const std::wstring& wscSystemname, const std::wstring& wscMessage);
		DLL HkError HkMsgU(const std::wstring& wscMessage);
		DLL HkError HkFMsgEncodeXML(const std::wstring& wscXML, char* szBuf, uint iSize, uint& iRet);
		DLL HkError HkFMsgSendChat(uint clientId, char* szBuf, uint iSize);
		DLL HkError HkFMsg(uint clientId, const std::wstring& wscXML);
		DLL HkError HkFMsg(const std::variant<uint, std::wstring>& player, const std::wstring& wscXML);
		DLL HkError HkFMsgS(const std::wstring& wscSystemname, const std::wstring& wscXML);
		DLL HkError HkFMsgU(const std::wstring& wscXML);
		DLL void HkFormatMessage(uint clientId, MessageColor color, MessageFormat format, std::wstring msg, ...);
		DLL std::wstring HkGetWStringFromIDS(uint iIDS);
		DLL void HkLoadStringDLLs();
		DLL void HkUnloadStringDLLs();
		DLL void FormatSendChat(uint iToClientID, const std::wstring& wscSender, const std::wstring& wscText, const std::wstring& wscTextColor);
		DLL void SendGroupChat(uint iFromClientID, const std::wstring& wscText);
		DLL void SendLocalSystemChat(uint iFromClientID, const std::wstring& wscText);
		DLL void SendPrivateChat(uint iFromClientID, uint iToClientID, const std::wstring& wscText);
		DLL void SendSystemChat(uint iFromClientID, const std::wstring& wscText);
	} // namespace Message
} // namespace Hk