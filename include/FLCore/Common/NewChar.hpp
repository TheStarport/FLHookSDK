#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace NewChar
{
    struct Pilot
    {
        uint nickname;
        st6::string body;
        st6::vector<st6::string> bodyAnims;
        st6::string comm;
        st6::vector<st6::string> commAnims;
        st6::string voice;
    };

    struct Package
    {
        uint nickname;
        int idsName;
        int idsDescription;
        st6::string ship;
        st6::string loadout;
        int money;
    };

    struct Faction
    {
        uint nickname;
        st6::string repGroup;
    };

    struct Base
    {
        uint nickname;
        st6::string nicknameStr;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class IDatabase // NOLINT
    {
        public:
        virtual Faction* FindFaction(uint faction);
        virtual Package* FindPackage(uint package);
        virtual Pilot* FindPilot(uint pilot);
        virtual Base* FindBase(uint base);
        virtual void UnknownMethod16(DWORD arg1);
        virtual void UnknownMethod20(DWORD arg1);
        virtual void UnknownMethod24(DWORD arg1);
        virtual void UnknownMethod28(DWORD arg1);
        virtual void UnknownMethod32(DWORD arg1);
        virtual void UnknownMethod36(DWORD arg1);
        virtual void UnknownMethod40(DWORD arg1);
        virtual void UnknownMethod44(DWORD arg1);
        virtual void UnknownMethod48(DWORD arg1);
        virtual void LoadNewCharacterIni(const char* fileBuffer);
    };

    IMPORT IDatabase* TheDB;
}