//****************************************************************************
//*                                                                          *
//*  ENGINE.H: DA COM game engine component                                  *
//*                                                                          *
//*  Source compatible with 32-bit 80386 C/C++                               *
//*                                                                          *
//*  $Header: /Conquest/Libs/Include/ENGINE.H 6     4/28/00 11:57p Rmarr $
//*                                                                          *
//****************************************************************************
//*                                                                          *
//*  Copyright (C) 1997 Digital Anvil, Inc.                                  *
//*                                                                          *
//****************************************************************************

#pragma once

#include "../FLCoreDefs.hpp"

#include "../Dacom/Dacom.hpp"
#include "DAVariant.hpp"
#include "VisState.hpp"

typedef i32 ARCHETYPE_INDEX;        // ARCHETYPE_INDEX = index to created archetype
typedef i32 INSTANCE_INDEX;         // INSTANCE_INDEX  = index to created instance
typedef INSTANCE_INDEX JOINT_INDEX; // JOINT_INDEX  = index to created instance

#define INVALID_ARCHETYPE_INDEX ((ARCHETYPE_INDEX) - 1)
#define INVALID_INSTANCE_INDEX  ((INSTANCE_INDEX) - 1)
#define INVALID_JOINT_INDEX     ((JOINT_INDEX)(INVALID_INSTANCE_INDEX))

#include "JointInfo.hpp"

// Render Flags
//
// Pass a combination of these flags to render_instance().
//
typedef u32 RenderFlags;
const RenderFlags RF_RELATIVE_LOD = 0x0008; // interpret lod_fraction as a scale for switching distances
const RenderFlags RF_TRANSLATE_FIRST =
    0x0010; // apply Transform translation before it's rotation (default is rotation first)
const RenderFlags RF_TRANSFORM_LOCAL =
    0x0020; // apply Transform in local (object) coord system (default is in world)
const RenderFlags RF_DONT_RECURSE_TRANSFORM = 0x0040; // used internally by render manager
const RenderFlags RF_SAME_LOD = 0x0080;               // don't recompute lod
const RenderFlags RF_DONT_CULL_FRUSTUM = 0x0100;      // don't perform frustum culling
const RenderFlags RF_DONT_CULL_FACES = 0x0200;        // don't perform backface culling
const RenderFlags RF_DONT_RELIGHT = 0x0400;           // don't recalculate lighting (use cache)
const RenderFlags RF_CLAMP_COLOR =
    0x0800; // lighting clamps color preserving intensity (the default is to clamp intensity and preserve color)
const RenderFlags RF_DONT_CLIP =
    0x1000; // don't perform polygon clipping; also use RF_DONT_CULL_FRUSTUM w/ this

// Engine Flags
//
// These are passed to a number of IEngine methods to control
// tree recursion and other common behavior.
//

typedef u32 EngineFlags;
const EngineFlags EN_DONT_RECURSE =
    0x0001; // don't recurse down the compound hierarchy (default is to recurse)
const EngineFlags EN_UPDATE_WO_COMPONENTS = 0x0002;  // don't reflect the update call to the components
const EngineFlags EN_UPDATE_WO_DERIVATIVES = 0x0004; // don't update linear and angular velocities of children

// Joint State Type
//
// Used in calls to get/set_joint_state() to select which state to get.
//
typedef enum
{
    IE_JST_BASIC,
    IE_JST_FIRST_DERIVATIVE
} IE_JOINTSTATETYPE;

// -------------------------------------------------------------------------
//
// IEngineInstance
//
// Clients of IEngine can create components that implement this interface
// to optionally control the implementation of a given engine instance.
//
struct DACOM_NO_VTABLE IEngineInstance
{
    virtual void __stdcall initialize_instance(INSTANCE_INDEX index) = 0;
    virtual void __stdcall create_instance(INSTANCE_INDEX index) = 0;
    virtual void __stdcall destroy_instance(INSTANCE_INDEX index) = 0;

    virtual void __stdcall set_position(INSTANCE_INDEX index, const Vector& position) = 0;
    virtual const Vector& __stdcall get_position(INSTANCE_INDEX index) const = 0;

    virtual void __stdcall set_orientation(INSTANCE_INDEX index, const Matrix& orientation) = 0;
    virtual const Matrix& __stdcall get_orientation(INSTANCE_INDEX index) const = 0;

    virtual void __stdcall set_transform(INSTANCE_INDEX index, const Transform& transform) = 0;
    virtual const Transform& __stdcall get_transform(INSTANCE_INDEX index) const = 0;

    virtual const Vector& __stdcall get_velocity(INSTANCE_INDEX object) const = 0;
    virtual const Vector& __stdcall get_angular_velocity(INSTANCE_INDEX object) const = 0;

    virtual void __stdcall set_velocity(INSTANCE_INDEX object, const Vector& vel) = 0;
    virtual void __stdcall set_angular_velocity(INSTANCE_INDEX object, const Vector& ang) = 0;

    virtual void __stdcall get_centered_radius(INSTANCE_INDEX index, f32* r, Vector* center) const = 0;
    virtual void __stdcall set_centered_radius(INSTANCE_INDEX index, const f32 r, const Vector& center) = 0;
};

// NOTE: Due to the macro nature of MAKE_IID, you cannot use another macro in place of the version
// number. Keep the second parameter in sync with the value of the explicit version macro, and increment
// both when the interface changes.
#define IENGINE_VERSION 10
#define IID_IEngine     MAKE_IID("IEngine", 10)

// -------------------------------------------------------------------------
//
// IEngine
//
// The IEngine interface allows clients access to a global database of
// archetypes and instances.
//
// Archetypes, instances and their management:
//
// The internal archetype database maintains a reference count for each active
// archetype.  When an archetype is created explicitly using 'create_archetype'
// the reference count for the created archetype is incremented.  An archetype's
// reference count is decrmented for each call to 'destroy_archetype.'  When
// the count reaches 0, the engine unloads the archetype from memory.
//
// The creation of an instance from an archetype_index causes an archetype's
// reference count to be incremented, and when the instance is deleted, the
// reference count is decremented.  If the reference count ever reaches 0,
// the archetype is unloaded from memory.  An instance that is not created
// using an archetype_index may internally create an archetype that will
// be unloaded at the time of the instance's destruction.
//
// In summary, archetypes that are explicitly loaded must be explicitly
// unloaded in order to free thier associated resources.  Archetypes that are
// created as a byproduct of instance creation need no explicit destruction
// in order to free their resources.  They are freed when the last instance
// that refers to them is destroyed.
//
struct DACOM_NO_VTABLE IEngine : public IDAComponent
{
    // Used in enumeration callbacks
    //
    typedef bool (*EngineComponentCallback)(const char* component_name,
                                            struct IEngineComponent* engine_component);
    typedef bool (*EngineArchetypeCallback)(ARCHETYPE_INDEX parent_arch_index,
                                            ARCHETYPE_INDEX child_arch_index, void* user_data);

    // load_engine_components
    //
    // Creates instances of all the components listed in the [Engine]
    // section of the DACOM profile and aggregates those components into
    // this Engine component container.
    //
    // The components listed in the [Engine] section do not necessarily
    // have to implement IEngineInstance, but only those that do will
    // be available via the get_engine_component() call below.  The other
    // aggregated components (as are engine components) are available via
    // QueryInterface()
    //
    // Returns GR_OK on success.
    //
    virtual GENRESULT __stdcall load_engine_components(struct IDAComponent* system) = 0;

    // enumerate_engine_components
    //
    // Calls the requested callback for each component aggregated into the
    // engine contained that implements IEngineComponent.  If callback returns false
    // subsequent components will NOT get called. If callback
    // is NULL, only the count is returned.
    //
    // Returns the number of components that implement IEngineComponent.
    //
    virtual int __stdcall enumerate_engine_components(EngineComponentCallback callback) = 0;

    // update
    //
    // Notify each aggregated engine component to update the simulation for
    // all instances by the delta time specified.
    //
    virtual void __stdcall update(f32 dt) = 0;

    // set_search_path
    //
    // Sets the path to be searched when creating a filesystem via create_file_system()
    //
    virtual void __stdcall set_search_path(const char* path) = 0;

    // get_search_path
    //
    // Retrieves the current path to be searched when creating a filesystem
    // via create_file_system().  If out_path is NULL, only the length of the
    // string is returned.
    //
    // Returns the length of the string [to be] copied into out_path.
    //
    virtual u32 __stdcall get_search_path(char* out_path, u32 max_path_len) const = 0;

    // set_search_path2
    //
    // Sets the component to use as the filesystem factory to be used when
    // creating a filesystem via create_file_system.
    //
    // fileFactory can be one of the following:
    // a) NULL					-- sets the search path to the current directory.
    // b) The DACOM ICOManager	-- sets the search path to the current directory.
    // c) An IFileSystem		-- sets the search path to the current directory of the IFilesystem.
    // d) An ISearchPath		-- sets the search path to the given search path.
    //
    virtual void __stdcall set_search_path2(struct IComponentFactory* fileFactory) = 0;

    // get_search_path2
    //
    // Returns the filesystem factory used when creating a filesystem via
    // create_file_system();
    //
    virtual void __stdcall get_search_path2(struct IComponentFactory** fileFactory) const = 0;

    // create_file_system
    //
    // Creates a filesystem components from the given filename.  If the filename
    // does not exist and cannot be found in the current search path, an error
    // is returned.
    //
    // Returns GR_OK on success.
    //
    virtual GENRESULT __stdcall create_file_system(const char* filename, struct IFileSystem** out_filesystem,
                                                   IComponentFactory* filesystem_factory = 0) = 0;

    // allocate_archetype
    //
    // Allocate an archetype entry and name it arch_name.
    //
    // if arch_name is NULL, an anonymous name will be generated for you.
    //
    // Returns the new archtype index on success, if no archetype can be
    // created, returns INVALID_ARCHETYPE_INDEX
    //
    virtual ARCHETYPE_INDEX __stdcall allocate_archetype(const char* arch_name) = 0;

    // create_archetype
    //
    // Allocate an archetype entry and name it arch_name, then load the
    // archetype from the given filesys.
    //
    // This function may be called to ensure that subsequent create_instance() calls
    // do not involve disk accesses or any other time-consuming operations.  For
    // instance, this function may be called once for all types of objects used
    // in a mission, to help avoid pauses when instances of those objects are
    // created during gameplay.
    //
    // Use of this function is optional.  If the app doesn't call this
    // function, the necessary archetype will be created the first time an
    // instance is requested.
    //
    // If the archetype is created and loaded successfully, the archetype's
    // reference count is incremented and the new archetype index is returned.
    //
    // Both arch_name and filesys must be valid.
    //
    // If none of the aggregated components successfully create archetype
    // data, the archetype is destroyed and INVALID_ARCHETYPE_INDEX is
    // returned.
    //
    virtual ARCHETYPE_INDEX __stdcall create_archetype(const char* arch_name,
                                                       struct IFileSystem* filesys) = 0;

    // duplicate_archetype
    //
    // Duplicates all of the archetype related data for the given archetype
    // and names the new archetype new_arch_name.
    //
    // If the duplication succeeds, the new archetype index is returned.
    // If the duplication fails, INVALID_ARCHETYPE_INDEX is returned.
    //
    virtual ARCHETYPE_INDEX __stdcall duplicate_archetype(ARCHETYPE_INDEX arch_index,
                                                          const char* new_arch_name) = 0;

    // hold_archetype
    //
    // Increments the archetype reference count.
    //
    virtual void __stdcall hold_archetype(ARCHETYPE_INDEX arch_index) = 0;

    // release_archetype
    //
    // Decrements the archetype reference count.  When the reference count
    // reaches zero (0), the archetype is destroyed.
    //
    virtual void __stdcall release_archetype(ARCHETYPE_INDEX arch_index) = 0;

    // get_archetype_name
    //
    // Returns the name of the given archetype index.  If out_arch_name is
    // NULL, the length of the archetype name is returned.
    //
    virtual const char* __stdcall get_archetype_name(ARCHETYPE_INDEX arch_index) const = 0;

    // get_archetype_by_name
    //
    // Returns the archetype index of the given archetype name.  If the
    // given name is not a valid archetype, INVALID_ARCHETYPE_INDEX is returned.
    //
    virtual ARCHETYPE_INDEX __stdcall get_archetype_by_name(const char* arch_name) = 0;

    // query_archetype_interface
    //
    // Retrieves a particular interface from the given archetype.
    //
    virtual GENRESULT __stdcall query_archetype_interface(ARCHETYPE_INDEX arch_index, const char* iid,
                                                          IDAComponent** out_iif) = 0;

    // is_archetype_compound
    //
    // Determines whether the given archetype is compound or not.
    //
    // If arch_index is invalid, not in the archetypes database, or
    // not a compound archetype this method returns FALSE.
    //
    // Returns TRUE is archetype is a compound archetype
    //
    virtual BOOL __stdcall is_archetype_compound(ARCHETYPE_INDEX arch_index) const = 0;

    // enumerate_archetype_joints
    //
    // enumerate all joints that make up the connectivity of an archetype as long as callback is
    // returning true.
    // The given callback is called for each joint in the archetype.  In the call,
    // parent_arch_index is the archetype index of the joint parent and
    // child_arch_index is the joint child.
    //
    // If arch_index does not exist in the database, this method returns GR_GENERIC.
    //
    // If arch_index references a non-compound archetype, callback will never be
    // called and this method will return GR_OK.
    //
    // user_data is completely opaque and simply passed through during calls to the
    // callback.
    //
    virtual GENRESULT __stdcall enumerate_archetype_joints(ARCHETYPE_INDEX arch_index,
                                                           EngineArchetypeCallback callback,
                                                           void* user_data) const = 0;

    // enumerate_archetype_parts
    //
    // enumerate all of the parts that make up an archetype as long as callback is
    // returning true. The given callback
    // is called for each part in the archetype (including the "root" part).  In
    // the call, parent_arch_index is the archetype index of **compound** archetype
    // and is equal to the value passed in as 'arch_index'. child_arch_index is
    // the index of the archetype referenced by this part.
    //
    // If arch_index does not exist in the database, this method returns GR_GENERIC.
    //
    // If arch_index references a non-compound archetype, callback will never be
    // called and this method will return GR_OK.
    //
    // user_data is completely opaque and simply passed through during calls to the
    // callback.
    //
    virtual GENRESULT __stdcall enumerate_archetype_parts(ARCHETYPE_INDEX arch_index,
                                                          EngineArchetypeCallback callback,
                                                          void* user_data) const = 0;

    // create_instance
    //
    // Create an instance of the given archetype (named arch_name).  If the archetype
    // has not yet been created, the archetype will be created (and named arch_name)
    // and then loaded from the given filesystem.
    //
    // arch_name can not be NULL.
    //
    // If the call succeeds, the new instance index is returned.
    // If the call fails, INVALID_INSTANCE_INDEX is returned.
    //
    virtual INSTANCE_INDEX __stdcall create_instance(const char* arch_name, struct IFileSystem* filesys,
                                                     IEngineInstance* UserInstance) = 0;

    // create_instance2
    //
    // Create an instance of the given archetype and set the instance handler to
    // the given IEngineInstance interface.  If UserInstance is NULL, the internal
    // instance handler is used.
    //
    // arch_index can not be INVALID_ARCHETYPE_INDEX.
    //
    // If the call succeeds, the new instance index is returned.
    // If the call fails, INVALID_INSTANCE_INDEX is returned.
    //
    virtual INSTANCE_INDEX __stdcall create_instance2(ARCHETYPE_INDEX arch_index,
                                                      IEngineInstance* UserInstance) = 0;

    // destroy_instance
    //
    // Destroys the given instance and decrements the instance's archetype
    // reference count.
    //
    virtual void __stdcall destroy_instance(INSTANCE_INDEX inst_index) = 0;

    // get_instance_archetype
    //
    // Returns the archetype index of the given instance. If the instance references
    // a valid archetype, the archetype reference is incremented. Call release_archetype()
    // to decrement the reference count when you are finished with the reference.
    //
    virtual ARCHETYPE_INDEX __stdcall get_instance_archetype(INSTANCE_INDEX inst_index) = 0;

    // get_instance_part_name
    //
    // returns the part name of the given instance if the instance is part of a
    // compound instance, or NULL otherwise.
    //
    virtual const char* __stdcall get_instance_part_name(INSTANCE_INDEX inst_index) const = 0;

    // update_instance
    //
    // Notify each aggregated engine component to update the simulation for
    // the given instance by the delta time specified.
    //
    virtual void __stdcall update_instance(INSTANCE_INDEX inst_index, EngineFlags en_f_flags, f32 dt) = 0;

    // render_instance
    //
    // Notify each aggregated engine component to render the given instance using
    // the given camera (which cannot be NULL) at the given level of detail.
    //
    // rf_flags is a combination of the RF_* flags defined above.
    //
    // modifier_transform is applied to the instance before rendering the object
    // according to the rf_flags.
    //
    // lod_fraction is the level of detail to render the instance at.  This must
    // either be a negative number or in the range [0,1].
    //
    // Returns whether the object was visible in the given camera according to the
    // aggregated engine components.
    //
    virtual vis_state __stdcall render_instance(struct ICamera* camera, INSTANCE_INDEX inst_index,
                                                EngineFlags en_f_flags, float lod_fraction, u32 rf_flags,
                                                const Transform* modifier_transform) = 0;

    // set_instance_handler
    //
    // Replaces the current instance handler with the specified instance handler.
    // If newUserInstance is NULL, the current instance handler will be replaced
    // with the default Engine instance handler.
    //
    // If the new instance handler is the same as (equality of pointers) the
    // current instance handler, nothing happens and the function simply returns.
    //
    // When replacing the instance handler, the engine will first initialize the
    // new instance handler with initialize_instance( inst_index ), then it will
    // call the following to finish initializing the new instance handler:
    //
    //	new_instance_handler->set_transform( inst_index, old_instance_handler->get_transform( inst_index ) );
    //	new_instance_handler->set_velocity( inst_index, old_instance_handler->get_velocity( inst_index ) );
    //	new_instance_handler->set_angular_velocity( inst_index, old_instance_handler->get_angular_velocity( inst_index ) );
    //	old_instance_handler->get_centered_radius( inst_index, &radius, &radius_center );
    //	new_instance_handler->set_centered_radius( inst_index, radius, radius_center );
    //
    // Finally, the old instance handler will get a destroy_instance( inst_index );
    //
    virtual void __stdcall set_instance_handler(INSTANCE_INDEX inst_index,
                                                IEngineInstance* newUserInstance) = 0;

    // get_instance_handler
    //
    // Returns the current instance handler for the given instance.  If
    // the inst_index is not a valid instance, out_UserInstance will be
    // NULL;
    //
    virtual void __stdcall get_instance_handler(INSTANCE_INDEX inst_index,
                                                IEngineInstance** out_UserInstance) = 0;

    // query_instance_interface
    //
    // Retrieves a particular interface from the given instance.
    // Note that there is not necessarily any correlation between whether
    // an archetype and an instance of that archetype respond to
    // the same interface requests in the same manner.  i.e. just because
    // an instance implements a particular interface does not mean that
    // the archetype of that instance does.
    //
    virtual GENRESULT __stdcall query_instance_interface(INSTANCE_INDEX inst_index, const char* iid,
                                                         IDAComponent** out_iif) = 0;

    // set_user_data
    //
    // Sets the client data associated with inst_index to the value in data.
    // Each instance has 32 bits of *totally opaque* client data.
    //
    virtual void __stdcall set_user_data(INSTANCE_INDEX inst_index, i32 data) = 0;

    // get_user_data
    //
    // Returns the client data associated with the inst_index.  If the inst_index
    // is not a valid reference, zero (0) is returned.
    //
    virtual i32 __stdcall get_user_data(INSTANCE_INDEX inst_index) const = 0;

    // set_instance_bounding_sphere
    //
    // Sets the bounding sphere (centered radius) of the given instance to the
    // given values.
    //
    virtual void __stdcall set_instance_bounding_sphere(INSTANCE_INDEX inst_index, EngineFlags en_f_flags,
                                                        const float radius, const Vector& center) = 0;

    // get_instance_bounding_sphere
    //
    // Gets the bounding sphere (centered radius) of the given instance.
    // If the instance is invalid, the radius will be -1.0f and the center will be (0,0,0)
    //
    virtual void __stdcall get_instance_bounding_sphere(INSTANCE_INDEX inst_index, EngineFlags en_f_flags,
                                                        float* radius, Vector* center) const = 0;

    // set_position
    //
    // Sets the current position of the given instance.
    //
    virtual void __stdcall set_position(INSTANCE_INDEX inst_index, const Vector& position) = 0;

    // get_position
    //
    // Gets the current position of the given instance.
    // If the instance is invalid, the return value is (0,0,0)
    //
    virtual const Vector& __stdcall get_position(INSTANCE_INDEX inst_index) const = 0;

    // set_orientation
    //
    // Sets the current orientation of the given instance.
    //
    virtual void __stdcall set_orientation(INSTANCE_INDEX inst_index, const Matrix& orientation) = 0;

    // get_orientation
    //
    // Gets the current orientation of the given instance.
    // If the instance is invalid, the return value is the identity matrix.
    //
    virtual const Matrix& __stdcall get_orientation(INSTANCE_INDEX inst_index) const = 0;

    // set_transform
    //
    // Set the transform (position and orientation) of the given instance.
    //
    virtual void __stdcall set_transform(INSTANCE_INDEX inst_index, const Transform& transform) = 0;

    // get_transform
    //
    // Get the transform (position and orientation) of the given instance.
    // If the instance is invalid, the identity transform is returned.
    //
    virtual const Transform& __stdcall get_transform(INSTANCE_INDEX inst_index) const = 0;

    // set_velocity
    //
    // Sets the velocity of the given instance.
    //
    virtual void __stdcall set_velocity(INSTANCE_INDEX inst_index, const Vector& vel) = 0;

    // get_velocity
    //
    // Gets the velocity of the given instance.
    // If the instance is invalid, zero (0,0,0) is returned.
    //
    virtual const Vector& __stdcall get_velocity(INSTANCE_INDEX inst_index) const = 0;

    // set_angular_velocity
    //
    // Sets the angular velocity of the given instance.
    //
    virtual void __stdcall set_angular_velocity(INSTANCE_INDEX inst_index, const Vector& ang) = 0;

    // get_angular_velocity
    //
    // Gets the angular velocity of the given instance.
    // If the instance is invalid, zero (0,0,0) is returned.
    //
    virtual const Vector& __stdcall get_angular_velocity(INSTANCE_INDEX inst_index) const = 0;

    // create_joint
    //
    // Create a joint that connects one instance as a child of another instance.
    //
    // parent_inst_index must be a valid instance index.
    // child_inst_index must be a valid instance index.
    // joint_info describes the properties of the joint to create.
    //
    // If child_inst_index is already connected, this method will return FALSE.
    //
    // Returns TRUE if the child is successfully connected to the parent.
    //
    virtual BOOL __stdcall create_joint(INSTANCE_INDEX parent_inst_index, INSTANCE_INDEX child_inst_index,
                                        const JointInfo* joint_info) = 0;

    // destroy_joint
    //
    // Destroy the joint connecting two instances.
    //
    // Returns TRUE if the two instances were immediately connected and are
    // no longer connected.
    //
    // Returns FALSE if the two instances were not immediately connected.
    //
    virtual BOOL __stdcall destroy_joint(INSTANCE_INDEX parent_inst_index,
                                         INSTANCE_INDEX child_inst_index) = 0;

    // get_joint_info
    //
    // Retrieve information about the type of joint between the given
    // instance and its parent instance.
    //
    // Returns non-NULL if the child instance is valid and is connected to a parent instance.
    //
    // Returns NULL if the given instance index is invalid or not connected to a parent.
    //
    virtual const JointInfo* __stdcall get_joint_info(INSTANCE_INDEX child_inst_index) const = 0;

    // set_joint_state
    //
    // Set information about the current state of the joint connecting
    // the given instance to its parent.
    //
    // Returns TRUE if the information is copied and the joint has been updated
    // correctly.
    //
    // Returns FALSE if the given instance index is not connected to a parent.
    //
    virtual BOOL __stdcall set_joint_state(INSTANCE_INDEX child_inst_index, IE_JOINTSTATETYPE state_type,
                                           const float* state_vector) const = 0;

    // get_joint_state
    //
    // Get information about the current state of the joint connecting
    // the given instance to its parent.
    //
    // Returns TRUE if the information is retrieved successfully.
    //
    // Returns FALSE if the given instance index is not connected to a parent.
    //
    virtual BOOL __stdcall get_joint_state(INSTANCE_INDEX child_inst_index, IE_JOINTSTATETYPE state_type,
                                           float* out_state_vector) const = 0;

    // get_root_instance_next
    //
    // Return the next root instance after the given previous root instance.
    //
    // If prev_root_inst_index is INVALID_INSTANCE_INDEX, the first root is returned.
    //
    // If no more roots exist after prev_root_inst_index, INVALID_INSTANCE_INDEX
    // is returned.
    //
    // NOTE: The instance indices returned DO NOT includ simple (non-compound) roots.
    //
    // This replaces 'traverse_roots'
    //
    virtual INSTANCE_INDEX __stdcall get_root_instance_next(
        INSTANCE_INDEX prev_root_inst_index = INVALID_INSTANCE_INDEX) const = 0;

    // get_instance_parent
    //
    // Find the immediate parent of the given instance index.
    //
    // If the specified instance does not exist or does not have a parent,
    // this method returns INVALID_INSTANCE_INDEX.
    //
    // child_inst_index must be a valid instance index.
    //
    virtual INSTANCE_INDEX __stdcall get_instance_parent(INSTANCE_INDEX child_inst_index) const = 0;

    // get_instance_child_next
    //
    // Find the next child of the given instance index "after" prev_child_inst_index.
    //
    // If parent_inst_index is not in the instances database or is INVALID_INSTANCE_INDEX,
    // this method returns INVALID_INSTANCE_INDEX.
    //
    // If prev_child_inst_index is INVALID_INSTANCE_INDEX, the first child is returned.
    //
    // If the specified instance does not have any children or if the instance
    // referred to by prev_child_inst_index is the last child of the parent,
    // this method returns INVALID_INSTANCE_INDEX.
    //
    virtual INSTANCE_INDEX __stdcall get_instance_child_next(INSTANCE_INDEX parent_inst_index,
                                                             EngineFlags en_f_flags,
                                                             INSTANCE_INDEX prev_child_inst_index) const = 0;

    // get_instance_root
    //
    // Find the instance that is the root of the tree of the given instance.
    //
    // If inst_index is invalid, this method returns INVALID_INSTANCE_INDEX.
    //
    // Otherwise, the instance index of the root instance is returned.  If
    // inst_index *is* a root (or non-compound), then inst_index is returned.
    //
    virtual INSTANCE_INDEX __stdcall get_instance_root(INSTANCE_INDEX inst_index) const = 0;
};
