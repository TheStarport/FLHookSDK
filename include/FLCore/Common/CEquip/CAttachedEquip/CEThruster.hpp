#pragma once

#include "../../PhySys/Controller/CPhysControllerEquip.hpp"

class CEThruster : public CAttachedEquip, public CPhysControllerEquip
{
    public:
    IMPORT virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

    IMPORT virtual ~CEThruster();

    IMPORT virtual bool EnableController();
    IMPORT virtual bool DisableController();
    IMPORT virtual bool IsControllerEnabled() const;

    IMPORT virtual bool Activate(bool);

    IMPORT static CEThruster* cast(CEquip*);
    IMPORT static const CEThruster* cast(const CEquip*);

    IMPORT CEThruster(const CEThruster&);
    IMPORT CEThruster(CEqObj*, u16, const Archetype::Thruster*, bool);
    IMPORT const Archetype::Thruster* ThrusterArch() const;
    IMPORT bool CouldThrust() const;
    IMPORT f32 GetPowerDraw() const;
    IMPORT f32 GetThrust() const;
};