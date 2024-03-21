#pragma once

#include <FLCore/Common/PhySys/Controller.hpp>
#include "../../../FLCoreDefs.hpp"

class CPhysControllerEquip : public PhySys::Controller
{
    public:
    IMPORT virtual ~CPhysControllerEquip();
    IMPORT virtual bool EnableController();
    IMPORT virtual bool DisableController();
    IMPORT virtual bool IsControllerEnabled() const;
    IMPORT virtual bool ControlObject(CObject*);

    IMPORT CPhysControllerEquip(const CPhysControllerEquip&);
    IMPORT CPhysControllerEquip();
    IMPORT CPhysControllerEquip& operator=(const CPhysControllerEquip&);

    public:
    bool isEnabled;
};