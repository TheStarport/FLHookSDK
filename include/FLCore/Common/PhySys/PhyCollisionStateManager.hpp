#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace PhySys
{
    class PhyCollisionStateManager
    {
        public:
        IMPORT PhyCollisionStateManager(const PhyCollisionStateManager&);
        IMPORT PhyCollisionStateManager(CObject*);
        IMPORT ~PhyCollisionStateManager();
        IMPORT PhyCollisionStateManager& operator=(const PhyCollisionStateManager&);
        IMPORT void enable_collisions(bool, bool);
        IMPORT bool get_actual_collision_state() const;
        IMPORT bool get_desired_collision_state() const;
        IMPORT //@@@ int get_intruding_cobjs(bool,struct CheapSet<struct CObject *,struct st6::less<struct CObject *>> &);
        IMPORT virtual void mindist_entered_volume(class IVP_Controller_Phantom*, class IVP_Mindist_Base*);
        IMPORT virtual void mindist_left_volume(IVP_Controller_Phantom*, IVP_Mindist_Base*);
        IMPORT virtual void phantom_is_going_to_be_deleted_event(IVP_Controller_Phantom*);
        IMPORT void update(float);

        protected:
        IMPORT class IVP_Real_Object* get_other_object(IVP_Mindist_Base*);
        IMPORT CObject* mindist_to_cobject(IVP_Mindist_Base*);

        public:
        CObject* cobject;
        unsigned char data[OBJECT_DATA_SIZE];
    };
}