#pragma once

struct FmtStr;
namespace Reputation
{
    struct Relation
    {
            unsigned hash;
            f32 reputation;
    };

    struct ReputationEntry
    {
            unsigned affliation;
            unsigned dunno;
            unsigned clientId;
            unsigned dunno2[14];
            wchar_t name[24];
            unsigned rank;
            st6::vector<Reputation::Relation> reputations;
    };

    struct RepGroup
    {
            unsigned nameLength;
            char name[16];
            unsigned nameIds;
            unsigned infocardIds;
            unsigned shortNameIds;
            st6::map<unsigned, f32> feelingsTowardsMap;
    };

    using RepGroupCB = bool (***)(RepGroup*);
    namespace Vibe
    {
        IMPORT int AdjustAttitude(const int&, const int&, f32);
        IMPORT int Alloc(const int&);
        IMPORT int AttitudeTowards(const int&, const int&, f32&);
        IMPORT int AttitudeTowardsSymmetrical(const int&, const int&, f32&, f32&);
        IMPORT u32 Count();
        IMPORT int EnsureExists(const int&);
        IMPORT int Free(const int&);
        IMPORT void FreeDynamic();
        // ReSharper disable once CppConstParameterInDeclaration
        IMPORT int Get(const int& repId, u32& affiliation, u32& rank, u8& relationCount, Relation* const relations, FmtStr&, FmtStr&, // NOLINT(*-avoid-const-params-in-decls)
                       const u16*& name);
        IMPORT int GetAffiliation(const int&, u32&, bool);
        IMPORT u32 GetClientID(int);
        IMPORT int GetGroupFeelingsTowards(const int&, const u32&, f32&);
        IMPORT int GetInfocard(const int&, u32&);
        IMPORT int GetName(const int&, FmtStr&, FmtStr&, const u16*&);
        IMPORT int GetRank(const int&, u32&);
        IMPORT int Set(const int&, u32, u32, u8, const Relation*, const FmtStr&, const FmtStr&, const u16*);
        IMPORT int SetAffiliation(const int&, u32, bool);
        IMPORT int SetAttitudeTowardsPlayer(int, f32);
        IMPORT int SetClientID(int, u32);
        IMPORT int SetGroupFeelingsTowards(const int&, const u32&, f32);
        IMPORT int SetInfocard(const int&, u32);
        IMPORT int SetName(const int&, const FmtStr&, const FmtStr&, const u16*);
        IMPORT int SetRank(const int&, u32);
        IMPORT bool Verify(int);
    }; // namespace Vibe

    IMPORT void FreeFeelings();
    IMPORT st6::map<u32, u32, st6::less<u32>, st6::allocator<u32>>* GetChangedAffiliationClientMap();
    IMPORT bool IsStoryFaction(u32);
    IMPORT void LoadFeelings(INI_Reader&);
    IMPORT void Save(struct ISave*);
    IMPORT void Shutdown();
    IMPORT bool Startup(const char*);
    IMPORT int affect_relation(const u32&, const u32&, f32);
    IMPORT void enumerate(RepGroupCB*);
    IMPORT int get_feelings_towards(u32, u32, f32&);
    IMPORT u32 get_id(const TString<16>&);
    IMPORT u32 get_info_card(u32);
    IMPORT u32 get_name(u32);
    IMPORT int get_nickname(TString<16>&, const u32&);
    IMPORT u32 get_short_name(u32);
    IMPORT u32 group_count();
    IMPORT void set(const TString<16>&, Relation* const, u32);
}