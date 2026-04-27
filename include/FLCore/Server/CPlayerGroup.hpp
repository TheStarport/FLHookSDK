#pragma once
#include "../FLCoreDefs.hpp"

namespace BaseGroupMessage
{
    enum Type
    {
    };
}; // namespace BaseGroupMessage

class CPlayerGroup
{
    public:
        IMPORT CPlayerGroup(const CPlayerGroup&);
        IMPORT CPlayerGroup();
        IMPORT virtual ~CPlayerGroup();
        IMPORT CPlayerGroup& operator=(const CPlayerGroup&);
        IMPORT bool AddInvite(u32);
        IMPORT bool AddMember(u32);
        IMPORT bool DelInvite(u32);
        IMPORT bool DelMember(u32);
        IMPORT void DeliverChat(ulong, const void*);
        IMPORT static CPlayerGroup* FromGroupID(u32);
        IMPORT u32 GetID();
        IMPORT u32 GetInviteCount();
        IMPORT u32 GetMember(int) const;
        IMPORT u32 GetMemberCount();
        IMPORT u32 GetMissionID();
        IMPORT u32 GetMissionSetBy();
        IMPORT void HandleClientLogout(u32);
        IMPORT bool IsFull();
        IMPORT bool IsInvited(u32);
        IMPORT bool IsMember(u32);
        IMPORT void RewardMembers(int);
        IMPORT void SendChat(int, const u16*, ...);
        IMPORT void SendGroup(BaseGroupMessage::Type, u32);
        IMPORT void SetMissionID(u32, u32);
        IMPORT void SetMissionMessage(struct CSetMissionMessage&);
        IMPORT void SetMissionObjectives(struct CMissionObjectives&);
        IMPORT void StoreMemberList(st6::vector<u32>&);

    protected:
        IMPORT static st6::map<const u32, CPlayerGroup*, st6::less<const u32>, st6::allocator<CPlayerGroup*>> groupIdToGroupPtrMap;
        IMPORT static u32 groupId;

    public:
        byte unk[0x14];
        unsigned memberCount;
};
