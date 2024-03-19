#pragma once
#include "../FLCoreDefs.hpp"

namespace BaseGroupMessage
{
    enum Type;
};

class CPlayerGroup
{
    public:
    IMPORT CPlayerGroup(const CPlayerGroup&);
    IMPORT CPlayerGroup();
    IMPORT virtual ~CPlayerGroup();
    IMPORT CPlayerGroup& operator=(const CPlayerGroup&);
    IMPORT bool AddInvite(unsigned int);
    IMPORT bool AddMember(unsigned int);
    IMPORT bool DelInvite(unsigned int);
    IMPORT bool DelMember(unsigned int);
    IMPORT void DeliverChat(unsigned long, const void*);
    IMPORT static CPlayerGroup* FromGroupID(unsigned int);
    IMPORT unsigned int GetID();
    IMPORT unsigned int GetInviteCount();
    IMPORT unsigned int GetMember(int) const;
    IMPORT unsigned int GetMemberCount();
    IMPORT unsigned int GetMissionID();
    IMPORT unsigned int GetMissionSetBy();
    IMPORT void HandleClientLogout(unsigned int);
    IMPORT bool IsFull();
    IMPORT bool IsInvited(unsigned int);
    IMPORT bool IsMember(unsigned int);
    IMPORT void RewardMembers(int);
    IMPORT void SendChat(int, const unsigned short*, ...);
    IMPORT void SendGroup(BaseGroupMessage::Type, unsigned int);
    IMPORT void SetMissionID(unsigned int, unsigned int);
    IMPORT void SetMissionMessage(struct CSetMissionMessage&);
    IMPORT void SetMissionObjectives(struct CMissionObjectives&);
    IMPORT void StoreMemberList(st6::vector<unsigned int>&);

    protected:
    IMPORT static st6::map<const unsigned int, CPlayerGroup*, st6::less<const unsigned int>, st6::allocator<CPlayerGroup*>> groupIdToGroupPtrMap;
    IMPORT static unsigned int groupId;

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};