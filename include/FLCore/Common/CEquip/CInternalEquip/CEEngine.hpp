#pragma once

#include "FLCore/Common/PhySys/Controller/CPhysControllerEquip.hpp"

struct CShip;
class CEEngine : public CInternalEquip, public CPhysControllerEquip
{
    public:
    IMPORT virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

    IMPORT virtual ~CEEngine();

    IMPORT virtual bool EnableController();
    IMPORT virtual bool DisableController();
    IMPORT virtual bool IsControllerEnabled() const;

    IMPORT virtual bool IsFunctioning() const;
    IMPORT virtual void NotifyArchGroupDestroyed(unsigned short);
    IMPORT virtual bool Update(float, unsigned int);
    IMPORT virtual bool Activate(bool);

    IMPORT static void BuildNozzleHPName(int, CacheString&);
    IMPORT static CEEngine* cast(CEquip*);
    IMPORT static const CEEngine* cast(const CEquip*);

    IMPORT CEEngine(const CEEngine&);
    IMPORT CEEngine(CShip*, unsigned short, const Archetype::Engine*, bool);
    IMPORT bool EngageCruise(bool, bool);
    IMPORT const Archetype::Engine* EngineArch() const;
    IMPORT const st6::vector<struct ExhaustNozzleInfo>& NozzleInfos() const;
    IMPORT float GetCruiseChargeTime() const;
    IMPORT float GetCruiseChargeTimeElapsed() const;
    IMPORT float GetCruiseDrag() const;
    IMPORT float GetCruisePowerDraw() const;
    IMPORT float GetCruiseThrust(float) const;
    IMPORT float GetLinearDrag() const;
    IMPORT float GetPowerDraw(float) const;
    IMPORT float GetThrust(float) const;
    IMPORT bool IsCruiseEngaged() const;
};