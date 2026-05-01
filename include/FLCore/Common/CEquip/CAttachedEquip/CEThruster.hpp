#pragma once

#include "../../PhySys/Controller/CPhysControllerEquip.hpp"

class CEThruster : public CAttachedEquip, public CPhysControllerEquip
{
  public:
    IMPORT void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*) override;

    IMPORT ~CEThruster() override;

    IMPORT bool EnableController() override;
    IMPORT bool DisableController() override;
    IMPORT bool IsControllerEnabled() const override;

    IMPORT bool Activate(bool) override;

    IMPORT static CEThruster* cast(CEquip*);
    IMPORT static const CEThruster* cast(const CEquip*);

    IMPORT CEThruster(const CEThruster&);
    IMPORT CEThruster(CEqObj*, u16, const Archetype::Thruster*, bool);
    IMPORT const Archetype::Thruster* ThrusterArch() const;
    IMPORT bool CouldThrust() const;
    IMPORT f32 GetPowerDraw() const;
    IMPORT f32 GetThrust() const;
};
