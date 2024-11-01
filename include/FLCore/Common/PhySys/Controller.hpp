#pragma once
#include "../../FLCoreDefs.hpp"

#include "../Unknown.hpp"

namespace PhySys
{
    struct Controller
    {
        public:
            IMPORT virtual ~Controller();

            IMPORT static void Register(Controller*, CObject*);
            IMPORT static void UnRegister(Controller*);

            IMPORT Controller(const Controller&);
            IMPORT Controller();
            IMPORT Controller& operator=(const Controller&);
            IMPORT void push(const Vector&, float);
            IMPORT void rotate(const Vector&, float);
            IMPORT void wakeup();

        protected:
            IMPORT virtual void core_is_going_to_be_deleted_event(IVP_Core*);
            // virtual float dunno_retn_1f(); //??
            IMPORT virtual IVP_U_Vector<IVP_Core>* get_associated_controlled_cores();
            // virtual void create_instance(long); //??
            IMPORT virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);
            IMPORT virtual IVP_CONTROLLER_PRIORITY get_controller_priority();

            uint PhySysDunno[3];
    };
} // namespace PhySys
