#pragma once
#include "../../../FLCoreDefs.hpp"
#include "CPhysControllerEquip.hpp"

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
    IMPORT void SetOwner(struct CShip*);

    protected:
    IMPORT static const float NUDGE_CHANGE_THRESHOLD;
    //@@@

    public:
    DWORD dunno10[3];   // 151
    struct CShip* owner;
    bool isActive;
    Vector nudgeVector; // 157
};