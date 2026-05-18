#pragma once

#include "EqObj.hpp"

struct IObjClientSolar : IObjClientEqObj
{};

struct CSolar;
struct IObjServerSolar : public IObjServerEqObj
{
    CSolar* csolar() { return reinterpret_cast<CSolar*>(this->cobject()); }
    virtual Vector& ChooseSystemArrivalLocation(unsigned unused, Vector& pos, Matrix& ori);

    static IObjServerSolar* Cast(IObjInspectImpl* iobj)
    {
        if (iobj->cobject()->objectClass == CObject::CSOLAR_OBJECT)
        {
            return reinterpret_cast<IObjServerSolar*>(iobj);
        }
        return nullptr;
    }
};
