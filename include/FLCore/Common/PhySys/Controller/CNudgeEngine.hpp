#pragma once
#include "../../../FLCoreDefs.hpp"

class CNudgeEngine : public CPhysControllerEquip
{
    public:
    IMPORT virtual ~CNudgeEngine();
    IMPORT virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);
    IMPORT virtual bool EnableController();

    IMPORT CNudgeEngine(const CNudgeEngine&);
    IMPORT CNudgeEngine();
    IMPORT CNudgeEngine& operator=(const CNudgeEngine&);
    IMPORT bool Activate(bool);
    IMPORT Vector GetNudgeVec() const;
    IMPORT bool IsActive() const;
    IMPORT void SetNudgeVec(const Vector&);
    IMPORT void SetOwner(CShip*);

    protected:
    IMPORT static const float NUDGE_CHANGE_THRESHOLD;
    //@@@

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};