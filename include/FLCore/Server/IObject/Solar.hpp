#pragma once

#include "../../FLCoreDefs.hpp"
#include "EqObj.hpp"

class CSolar;
struct Solar : public EqObj
{
    CSolar* csolar() { return reinterpret_cast<CSolar*>(this->cobject()); }
    virtual Vector& ChooseSystemArrivalLocation(uint unused, Vector& pos, Matrix& ori);

    static Solar* Cast(IObjInspectImpl* iobj)
    {
        if(iobj->cobject()->objectClass == CObject::CSOLAR_OBJECT)
        {
            return reinterpret_cast<Solar*>(iobj);
        }
        return nullptr;
    }
};