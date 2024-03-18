#pragma once
#include "../../../FLCoreDefs.hpp"

class CPhysAttachment
{
    public:
    IMPORT virtual ~CPhysAttachment();
    IMPORT virtual long GetRootIndex() const;
    IMPORT virtual CObject* GetPhysicsOwner() const;
    IMPORT virtual void EnableCollisions(bool);
    IMPORT virtual bool Connect(CAttachedEquip*);
    IMPORT virtual CObject* Disconnect(CAttachedEquip*, bool);

    IMPORT CPhysAttachment(const CPhysAttachment&);
    IMPORT CPhysAttachment();
    IMPORT CPhysAttachment& operator=(const CPhysAttachment&);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};

class CNonPhysAttachment
{
    public:
    IMPORT virtual ~CNonPhysAttachment();
    IMPORT virtual long GetRootIndex() const;
    IMPORT virtual CObject* GetPhysicsOwner() const;
    IMPORT virtual void EnableCollisions(bool);
    IMPORT virtual bool Connect(CAttachedEquip*);
    IMPORT virtual CObject* Disconnect(CAttachedEquip*, bool);

    IMPORT CNonPhysAttachment(const CNonPhysAttachment&);
    IMPORT CNonPhysAttachment();
    IMPORT CNonPhysAttachment& operator=(const CNonPhysAttachment&);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};