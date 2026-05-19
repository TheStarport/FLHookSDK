#pragma once

class CEquip;
class IObjClientEqObj;

struct CliEquip
{
    virtual void Disconnect(int dunno, int dunno2);
    virtual void Destructor(bool deallocate);
    virtual bool IsConnected();

    CEquip* equip;
    IObjClientEqObj* owner;
};