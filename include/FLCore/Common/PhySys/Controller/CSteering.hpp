#pragma once
#include "../../../FLCoreDefs.hpp"

class CSteering : public PhySys::Controller
{
  public:
    IMPORT CSteering(const CSteering&);
    IMPORT CSteering();
    IMPORT ~CSteering() override;
    IMPORT CSteering& operator=(const CSteering&);
    IMPORT bool Activate(bool);
    IMPORT virtual bool EnableController();
    IMPORT f32 GetAxisSteeringTorque(u32, f32) const;
    IMPORT const Vector& GetAxisThrottle() const;
    IMPORT bool IsActive() const;
    IMPORT void SetAxisThrottle(const Vector&);
    IMPORT void SetOwner(struct CShip*);

  protected:
    IMPORT static const f32 AXIS_CHANGE_THRESHOLD;
    IMPORT void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*) override;

  public:
    u8 data[OBJECT_DATA_SIZE];
};
