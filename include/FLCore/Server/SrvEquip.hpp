#pragma once

class CEquip;
class IObjServerEqObj;

struct SrvEquip
{
    virtual void Disconnect(int dunno, int dunno2);
    virtual void Destructor(bool deallocate);
    virtual bool IsConnected();

    CEquip* equip;
    IObjServerEqObj* owner;
};