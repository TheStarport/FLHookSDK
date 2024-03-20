#pragma once

#include "../../FLCoreDefs.hpp"
#include "EqObj.hpp"

struct Solar : public EqObj, public IObjAffect, public IObjDestructor
{
    CSolar* csolar(){return reinterpret_cast<CSolar*>(cobject());};
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