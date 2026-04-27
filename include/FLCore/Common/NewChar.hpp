#pragma once
#include "../FLCoreDefs.hpp"

namespace NewChar
{
    struct Pilot
    {
        unsigned nickname;
        st6::string body;
        st6::vector<st6::string> bodyAnims;
        st6::string comm;
        st6::vector<st6::string> commAnims;
        st6::string voice;
    };

    struct Package
    {
        unsigned nickname;
        int idsName;
        int idsDescription;
        st6::string ship;
        st6::string loadout;
        int money;
    };

    struct Faction
    {
        unsigned nickname;
        st6::string repGroup;
    };

    struct Base
    {
        unsigned nickname;
        st6::string nicknameStr;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class IDatabase // NOLINT
    {
        public:
        virtual Faction* FindFaction(unsigned faction);
        virtual Package* FindPackage(unsigned package);
        virtual Pilot* FindPilot(unsigned pilot);
        virtual Base* FindBase(unsigned base);
        virtual void UnknownMethod16(ulong arg1);
        virtual void UnknownMethod20(ulong arg1);
        virtual void UnknownMethod24(ulong arg1);
        virtual void UnknownMethod28(ulong arg1);
        virtual void UnknownMethod32(ulong arg1);
        virtual void UnknownMethod36(ulong arg1);
        virtual void UnknownMethod40(ulong arg1);
        virtual void UnknownMethod44(ulong arg1);
        virtual void UnknownMethod48(ulong arg1);
        virtual void LoadNewCharacterIni(const char* fileBuffer);
    };

    IMPORT IDatabase* TheDB;
}