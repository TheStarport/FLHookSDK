#pragma once
#include "../../../FLCoreDefs.hpp"

class CStrafeEngine : public PhySys::Controller
{
    public:
    IMPORT CStrafeEngine(const CStrafeEngine&);
    IMPORT CStrafeEngine();
    IMPORT virtual ~CStrafeEngine();
    IMPORT CStrafeEngine& operator=(const CStrafeEngine&);
    IMPORT virtual bool EnableController();
    IMPORT StrafeDir GetStrafe() const;
    IMPORT void SetOwner(CShip*);
    IMPORT void SetStrafe(StrafeDir);

    protected:
    //@@@ virtual void do_simulation_controller(class IVP_Event_Sim *,class IVP_U_Vector<class IVP_Core> *);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};