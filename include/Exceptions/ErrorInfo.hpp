#pragma once

// TODO: Validate every error code is used and ensure messages are generic
// as the exception handler will now print them by default if an unhandled action occurs.
enum class Error
{
    NicknameNotFound,
    PlayerNotInSpace,
    PlayerNotLoggedIn,
    PlayerNotDocked,
    PlayerNotInGroup,
    CharacterNotSelected,
    CharacterDoesNotExist,
    CannotGetAccount,
    MpNewCharacterFileNotFoundOrInvalid,
    NoTargetSelected,
    TargetIsNotPlayer,
    CouldNotDecodeCharFile,
    CouldNotEncodeCharFile,
    NotAdmin,
    MissingRequiredRole,
    WrongXmlSyntax,
    InvalidClientId,
    InvalidGood,
    InvalidShip,
    InvalidBase,
    InvalidBaseName,
    InvalidIdString,
    InvalidSystem,
    InvalidRepGroup,
    InvalidReputation,
    InvalidGroupId,
    NoAffiliation,
    AlreadyExists,
    InvalidInput,
    CharacterNameTooLong,
    CharacterNameTooShort,
    NoMatchingPlayer,
    InvalidShortcutString,
    PluginCannotBeLoaded,
    PluginNotFound,
    InvalidIdType,
    InvalidSpaceObjId,
    FileNotFound,
    MalformedData,
    UnknownError = 1000,
};

class Hook ErrorInfo
{
        const inline static std::map<Error, std::wstring_view> errors = {
            {
             { Error::NicknameNotFound, L"Provided nickname was not valid" },
             { Error::PlayerNotLoggedIn, L"Player not logged in" },
             { Error::PlayerNotLoggedIn, L"Player is not in a group." },
             { Error::CharacterDoesNotExist, L"Char does not exist" },
             { Error::CouldNotDecodeCharFile, L"Could not decode charfile" },
             { Error::CouldNotEncodeCharFile, L"Could not encode charfile" },
             { Error::NoTargetSelected, L"No target selected" },
             { Error::TargetIsNotPlayer, L"Target is not a player" },
             { Error::PlayerNotDocked, L"Player in space" },
             { Error::UnknownError, L"unknown error" },
             { Error::InvalidClientId, L"Invalid client id" },
             { Error::InvalidIdString, L"Invalid id string" },
             { Error::InvalidSystem, L"Invalid system" },
             { Error::PlayerNotInSpace, L"Player not in space" },
             { Error::NotAdmin, L"Player is not an admin" },
             { Error::MissingRequiredRole, L"Player is missing a required role." },
             { Error::WrongXmlSyntax, L"Wrong XML syntax" },
             { Error::InvalidGood, L"Invalid good" },
             { Error::CharacterNotSelected, L"Player has no char selected" },
             { Error::AlreadyExists, L"Charname already exists" },
             { Error::AlreadyExists, L"Provided reputation has no affiliation." },
             { Error::CharacterNameTooLong, L"Charname is too long" },
             { Error::CharacterNameTooShort, L"Charname is too short" },
             { Error::NoMatchingPlayer, L"No matching player" },
             { Error::InvalidShortcutString, L"Invalid shortcut string" },
             { Error::MpNewCharacterFileNotFoundOrInvalid, L"mpnewcharacter.fl not found or invalid" },
             { Error::InvalidRepGroup, L"Invalid reputation group" },
             { Error::InvalidReputation, L"Provided reputation id was invalid" },
             { Error::InvalidGroupId, L"The provided group id was not valid. The group may no longer exist." },
             { Error::PluginCannotBeLoaded, L"Plugin cannot be unloaded" },
             { Error::PluginNotFound, L"Plugin not found" },
             { Error::InvalidIdType, L"Invalid Id Type provided" },
             { Error::InvalidSpaceObjId, L"Invalid SpaceObj Id provided" },
             { Error::InvalidBase, L"Invalid base provided" },
             { Error::InvalidBaseName, L"Invalid Base name" },
             { Error::InvalidShip, L"Specified ship was invalid" },
             { Error::InvalidInput, L"One of the provided values was invalid" },
             { Error::MalformedData, L"Data being processed was malformed to the point of failure." },
             }
        };

    public:
        [[nodiscard]]
        inline static std::wstring_view GetText(Error err)
        {
            if (const auto errInfo = errors.find(err); errInfo != errors.end())
            {
                return errInfo->second;
            }

            return L"No error text available";
        };
};
