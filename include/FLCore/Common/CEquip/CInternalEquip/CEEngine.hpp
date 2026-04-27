#pragma once

#include "../../../FLCoreDefs.hpp"
#include "../CInternalEquip.hpp"
#include "../../PhySys/Controller/CPhysControllerEquip.hpp"
#include "../../../X86Math/Transform.hpp"
#include "../../Strings.hpp"

namespace Archetype
{
    struct Engine;
}

struct IMPORT ExhaustNozzleInfo
{
        ExhaustNozzleInfo();
        ExhaustNozzleInfo& operator=(const ExhaustNozzleInfo&);
        bool GetHardpointOffset_NS(Transform&) const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

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
    IMPORT virtual void NotifyArchGroupDestroyed(u16);
    IMPORT virtual bool Update(f32, u32);
    IMPORT virtual bool Activate(bool);

    IMPORT static void BuildNozzleHPName(int, CacheString&);
    IMPORT static CEEngine* cast(CEquip*);
    IMPORT static const CEEngine* cast(const CEquip*);

    IMPORT CEEngine(const CEEngine&);
    IMPORT CEEngine(CShip*, u16, const Archetype::Engine*, bool);
    IMPORT bool EngageCruise(bool, bool);
    IMPORT const Archetype::Engine* EngineArch() const;
    IMPORT const st6::vector<ExhaustNozzleInfo>& NozzleInfos() const;
    IMPORT f32 GetCruiseChargeTime() const;
    IMPORT f32 GetCruiseChargeTimeElapsed() const;
    IMPORT f32 GetCruiseDrag() const;
    IMPORT f32 GetCruisePowerDraw() const;
    IMPORT f32 GetCruiseThrust(f32) const;
    IMPORT f32 GetLinearDrag() const;
    IMPORT f32 GetPowerDraw(f32) const;
    IMPORT f32 GetThrust(f32) const;
    IMPORT bool IsCruiseEngaged() const;

    
    /* 10 */ u32 dunno[4];
    /* 14 */ st6::vector<ExhaustNozzleInfo> nozzleInfo;
    /* 18 */ u32 dunno2;
    /* 19 */ f32 targetSpeed;
    /* 20 */ f32 cruiseChargeTimeElapsed;
    /* 21 */ bool isCruiseEngaged;
};