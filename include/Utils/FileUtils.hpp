#pragma once

#ifdef SERVER
    #include "API/FLServer/Client.hpp"
    #include "Core/Codec.hpp"
    #include "Defs/CoreGlobals.hpp"
    #include "Defs/FLHookConfig.hpp"
#endif

class Hook FileUtils
{
        FileUtils() = delete;

    public:
        static cpp::result<std::wstring, Error> FileToBuffer(const std::wstring& fileLocation)
        {
            // No file, no processing
            if (!std::filesystem::exists(fileLocation))
            {
                return { cpp::fail(Error::FileNotFound) };
            }

            std::wstring buffer;

            std::wifstream file(fileLocation);
            file.seekg(0, std::ios::end);
            buffer.resize(file.tellg());
            file.seekg(0);
            file.read(buffer.data(), buffer.size());

            return buffer;
        }

        static void BufferToFile(const std::wstring& fileLocation, const std::wstring_view newFileData)
        {
            std::wofstream file(fileLocation);
            file.write(newFileData.data(), newFileData.size());
            file.flush();
            file.close();
        }

#ifdef SERVER
        static cpp::result<std::wstring, Error> ReadCharacterFile(std::wstring_view characterName)
        {
            const auto acc = Hk::Client::GetAccountByCharName(characterName).Raw();
            if (acc.has_error())
            {
                return { cpp::fail(acc.error()) };
            }

            const auto dir = Hk::Client::GetAccountDirName(acc.value());

            auto file = Hk::Client::GetCharFileName(characterName).Raw();
            if (file.has_error())
            {
                return { cpp::fail(file.error()) };
            }

            const std::wstring charFile = std::format(L"{}{}\\{}.fl", CoreGlobals::c()->accPath, dir, file.value());

            auto buffer = FileToBuffer(charFile);
            if (buffer.has_error())
            {
                return { cpp::fail(buffer.error()) };
            }

            const auto str = buffer.value();
            if (!str.starts_with(L"FLS1"))
            {
                return str;
            }

            return FlCodec::Decode(str);
        }

        static Action<void, Error> WriteCharacterFile(std::wstring_view characterName, std::wstring_view newFileData)
        {
            const auto acc = Hk::Client::GetAccountByCharName(characterName).Raw();
            if (acc.has_error())
            {
                return { cpp::fail(acc.error()) };
            }

            const auto dir = Hk::Client::GetAccountDirName(acc.value());

            auto file = Hk::Client::GetCharFileName(characterName).Raw();
            if (file.has_error())
            {
                return { cpp::fail(file.error()) };
            }

            const std::wstring charFile = std::format(L"{}{}\\{}.fl", CoreGlobals::c()->accPath, dir, file.value());

            if (!FLHookConfig::i()->general.disableCharfileEncryption)
            {
                BufferToFile(charFile, FlCodec::Encode(newFileData));
            }
            else
            {
                BufferToFile(charFile, newFileData);
            }

            return { {} };
        }
#endif

        static std::wstring SaveDataPath()
        {
            char dataPath[MAX_PATH];
            GetUserDataPath(dataPath);
            if (!pub::SinglePlayer())
            {
                return StringUtils::stows(std::string(dataPath) + "\\Accts\\MultiPlayer\\");
            }

            return StringUtils::stows(std::string(dataPath) + "\\Accts\\SinglePlayer\\");
        }
};
