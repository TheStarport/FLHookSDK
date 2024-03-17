#pragma once

namespace Reputation
{
    struct Relation
    {
            uint hash;
            float reptuation;
    };

    struct RepGroup
    {
            uint nameLength;
            char name[16];
            uint nameIds;
            uint infocardIds;
            uint shortNameIds;
    };

    using RepGroupCB = bool (***)(RepGroup*);
    namespace Vibe
    {
        IMPORT int AdjustAttitude(const int&, const int&, float);
        IMPORT int Alloc(const int&);
        IMPORT int AttitudeTowards(const int&, const int&, float&);
        IMPORT int AttitudeTowardsSymmetrical(const int&, const int&, float&, float&);
        IMPORT unsigned int Count();
        IMPORT int EnsureExists(const int&);
        IMPORT int Free(const int&);
        IMPORT void FreeDynamic();
        IMPORT int Get(const int& repId, unsigned int& affiliation, unsigned int& rank, unsigned char& relationCount, Relation* relations, FmtStr&, FmtStr&,
                       const unsigned short*& name);
        IMPORT int GetAffiliation(const int&, unsigned int&, bool);
        IMPORT unsigned int GetClientID(int);
        IMPORT int GetGroupFeelingsTowards(const int&, const unsigned int&, float&);
        IMPORT int GetInfocard(const int&, unsigned int&);
        IMPORT int GetName(const int&, FmtStr&, FmtStr&, const unsigned short*&);
        IMPORT int GetRank(const int&, unsigned int&);
        IMPORT int Set(const int&, unsigned int, unsigned int, unsigned char, const Relation*, const FmtStr&, const FmtStr&, const unsigned short*);
        IMPORT int SetAffiliation(const int&, unsigned int, bool);
        IMPORT int SetAttitudeTowardsPlayer(int, float);
        IMPORT int SetClientID(int, unsigned int);
        IMPORT int SetGroupFeelingsTowards(const int&, const unsigned int&, float);
        IMPORT int SetInfocard(const int&, unsigned int);
        IMPORT int SetName(const int&, const FmtStr&, const FmtStr&, const unsigned short*);
        IMPORT int SetRank(const int&, unsigned int);
        IMPORT bool Verify(int);
    }; // namespace Vibe

    IMPORT void FreeFeelings();
    IMPORT st6::map<unsigned int, unsigned int, st6::less<unsigned int>, st6::allocator<unsigned int>>* GetChangedAffiliationClientMap();
    IMPORT bool IsStoryFaction(unsigned int);
    IMPORT void LoadFeelings(INI_Reader&);
    IMPORT void Save(struct ISave*);
    IMPORT void Shutdown();
    IMPORT bool Startup(const char*);
    IMPORT int affect_relation(const unsigned int&, const unsigned int&, float);
    IMPORT void enumerate(RepGroupCB*);
    IMPORT int get_feelings_towards(unsigned int, unsigned int, float&);
    IMPORT unsigned int get_id(const TString<16>&);
    IMPORT unsigned int get_info_card(unsigned int);
    IMPORT unsigned int get_name(unsigned int);
    IMPORT int get_nickname(TString<16>&, const unsigned int&);
    IMPORT unsigned int get_short_name(unsigned int);
    IMPORT unsigned int group_count();
    IMPORT void set(const TString<16>&, Relation* const, unsigned int);
}