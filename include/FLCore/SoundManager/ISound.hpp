#pragma once

#include "../FLCoreDefs.hpp"

#include "../Dacom/IdaComponent.hpp"

constexpr i32 SM_INVALID_ARCHETYPE = -1;

// NOTE: Due to the macro nature of MAKE_IID, you cannot use another macro in place of the version
// number. Keep the second parameter in sync with the value of the explicit version macro, and increment
// both when the interface changes.
#define ISOUNDSOURCE_VERSION 1
#define IID_ISoundSource     MAKE_IID("ISoundSource", 1)
//********************************************************************************************
struct ISoundSource : public IDAComponent
{
    virtual void __stdcall unknown() = 0;

    /**
     * @brief Gets the start time for this sound.
     *
     * The start time should initially be set by calling
     * SoundManager::get_current_time_ms() to ensure that the
     * times are synchronized with SoundManager.
     *
     * @return The start time of this sound.
     */
    virtual u32 __stdcall get_start_time() = 0;

    /**
     * @brief Determines whether this sound is currently on.
     * @return true if the sound should be playing; otherwise false.
     */
    virtual bool __stdcall is_on() = 0;

    /**
     * @brief Determines whether this sound is a 3D sound.
     *
     * SoundManager skips all extra 3D processing for non-3D sounds,
     * applying only pan and attenuation. Sounds that do not require
     * 3D processing should return false. A 3D sound may temporarily
     * return false when its 3D properties should be ignored.
     *
     * @return true if this sound should be treated as a 3D sound.
     */
    virtual bool __stdcall is_3D() = 0;

    /**
     * @brief Determines whether this sound should loop.
     * @return true if the sound should loop; otherwise false.
     */
    virtual bool __stdcall is_looping() = 0;

    /**
     * @brief Gets the archetype associated with this sound instance.
     * @return The archetype identifier for this sound.
     */
    virtual i32 get_archetype() = 0;

    /**
     * @brief Gets the attenuation value for the sound.
     *
     * The attenuation value is expressed in decibels in the range
     * [-100.0, 0.0], where 0.0 represents full volume and -100.0
     * is effectively silent.
     *
     * @param attenuation Receives the attenuation value.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the SoundManager default value (0.0).
     */
    virtual GENRESULT __stdcall get_attenuation(f32* attenuation) = 0;

    /**
     * @brief Gets the playback frequency scale for the sound.
     *
     * This value scales the original sample frequency. A value of
     * 0.5 plays at half speed, 1.0 at normal speed, and 2.0 at
     * double speed.
     *
     * The archetype must be created with the
     * SM_ENABLE_FREQUENCY_CONTROL flag or SoundManager will be
     * unable to control frequency.
     *
     * @param frequency Receives the frequency scale.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the SoundManager default value (1.0).
     */
    virtual GENRESULT __stdcall get_frequency(f32* frequency) = 0;

    /**
     * @brief Gets the pan value for the sound.
     *
     * The pan range is [-100.0, 100.0]:
     * - -100.0 = full left
     * - 0.0    = centered
     * - 100.0  = full right
     * @param pan Receives the pan value.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound default value (0).
     */
    virtual GENRESULT __stdcall get_pan(i32* pan) = 0;

    /**
     * @brief Gets the world-space position of the sound.
     * @param position Receives the sound position.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound default position (0,0,0).
     */
    virtual GENRESULT __stdcall get_position(Vector* position) = 0;

    /**
     * @brief Gets the minimum attenuation distance.
     *
     * The sound plays at full volume at or within this distance.
     * Beyond this point, volume decreases according to distance.
     * At twice the minimum distance, the volume is halved.
     * @param distance Receives the minimum distance.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound default value (1.0).
     */
    virtual GENRESULT __stdcall get_min_distance(f32* distance) = 0;

    /**
     * @brief Gets the maximum attenuation distance.
     *
     * Volume attenuation stops decreasing beyond this distance.
     * If the archetype was created with
     * SM_MUTE_3D_AT_MAX_DISTANCE, the sound should be inaudible
     * beyond this point.
     * @param distance Receives the maximum distance.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound default maximum distance.
     */
    virtual GENRESULT __stdcall get_max_distance(f32* distance) = 0;

    /**
     * @brief Gets the inner and outer cone angles.
     *
     * The sound is at full volume inside the inner cone. Between
     * the inner and outer cones, attenuation is interpolated.
     * Outside the outer cone, additional attenuation from
     * get_cone_outside_attenuation() is applied.
     * @param insideAngle Receives the inner cone angle.
     * @param outsideAngle Receives the outer cone angle.
     *
     * @return GR_OK if values were provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound defaults (360 for both).
     */
    virtual GENRESULT __stdcall get_cone_angles(u32* insideAngle, u32* outsideAngle) = 0;

    /**
     * @brief Gets the cone orientation vector.
     *
     * This vector represents the direction in which the sound
     * cone is pointing.
     *
     * @param orientation Receives the cone orientation.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound default orientation (0,0,0).
     */
    virtual GENRESULT __stdcall get_cone_orientation(Vector* orientation) = 0;

    /**
     * @brief Gets the attenuation applied outside the outer cone.
     *
     * Within the inner cone, normal attenuation applies. Between
     * the inner and outer cones, attenuation is interpolated
     * between the normal attenuation and this value.
     *
     * @param attenuation Receives the outside-cone attenuation.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the DirectSound default value (-100.0).
     */
    virtual GENRESULT __stdcall get_cone_outside_attenuation(f32* attenuation) = 0;

    /**
     * @brief Gets the velocity of the sound source.
     *
     * If velocity is provided, SoundManager can automatically
     * calculate doppler effects when supported.
     * @param velocity Receives the velocity vector.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the SoundManager default value (0,0,0).
     */
    virtual GENRESULT __stdcall get_velocity(Vector* velocity) = 0;

    /**
     * @brief Gets the reverb mix amount.
     *
     * Allows the master reverb set through
     * SoundManager::set_master_reverb() to be adjusted on a
     * per-instance basis.
     * @param reverbMix Receives the reverb mix amount.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the SoundManager default value (0.0).
     */
    virtual GENRESULT __stdcall get_reverb_mix(f32* reverbMix) = 0;

    /**
     * @brief Gets the 3D sound mode.
     *
     * If disabled, SoundManager continues processing 3D properties
     * but DirectSound ignores them. In head-relative mode, the
     * sound position automatically follows listener movement.
     * @param mode Receives the sound mode.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the SoundManager default mode.
     */
    virtual GENRESULT __stdcall get_sound_mode(i32* mode) = 0;

    /**
     * @brief Gets the property application mode.
     *
     * Determines whether changes are applied immediately or
     * deferred. SoundManager currently always uses deferred mode.
     * Immediate mode may cause DirectSound to remix buffers more
     * frequently.
     * @param mode Receives the apply mode.
     * @return GR_OK if a value was provided, or GR_NOT_IMPLEMENTED
     *         to use the SoundManager default mode.
     */
    virtual GENRESULT __stdcall get_apply_mode(i32* mode) = 0;
};
