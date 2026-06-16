#pragma once

#include "../FLCoreDefs.hpp"

#include "../Dacom/IdaComponent.hpp"

// ISoundManager.h
// COPYRIGHT (C) 1999 BY DIGITAL ANVIL, INC.
/*
   This header file describes the SoundListener interface used by the Digital Anvil Sound Manager.
   The Sound Manager provides a simple way to add sounds to an app.  The app implements the ISoundListener interface,
   provides a list of sounds to play, implementing the ISoundSource interface for the sounds, and calls
   update periodically causing Sound Manager to play the sounds.  Sound Manager handles all of the buffer
   creation and management using DirectSound, allows the user to set EAX and A3D properties if desired,
   and supports DirectSound3D.
*/

struct ISoundListener;
struct ISoundSource;
struct SoundFile;
struct IFileSystem;
enum SM_DEVICE_OPTIONS // used when setting the device options and returned by getting available options
{
    SM_USE_2D_HARDWARE = 1, // app wants/device has 2D hw mixing capabilites
    SM_USE_3D_HARDWARE = 2, // app wants/device has 3D hw capabilites
    SM_USE_EAX = 4,         // app wants/device supports EAX
    SM_USE_A3D = 8,         // app wants/device supports A3D
    SM_USE_RIGHT_HANDED_SYSTEM = 16,
    SM_CREATE_ALL_2D_IN_SOFTWARE = 32,
    SM_USE_3D_SOFTWARE_USER_DEFINED =
        64, // *** CURRENT DSOUND IMPLEMENTATION = SM_USE_3D_SOFTWARE_BASIC *** app wants DS3D to use whatever the user's current selection
    SM_USE_3D_SOFTWARE_BASIC =
        128, // app wants DS3D to apply min calculations to 3D software buffers - only pan and volume adjustments to simulate 3D
    SM_USE_3D_SOFTWARE_LIGHT =
        256, // app wants DS3D to apply some calculations to 3D software buffers - decent results, less CPU
    SM_USE_3D_SOFTWARE_FULL =
        512, // app wants DS3D to apply maximum calculations to 3D software buffers - best results, more CPU
    SM_USE_3D_SOFTWARE_NONE = 1024, // app wants no DS3D calcs applied to 3D SW buffers
    SM_USE_NO_HW = 2048,            // disables any hardware help

    SM_DEFAULT_SETTINGS = SM_USE_2D_HARDWARE | SM_USE_3D_HARDWARE | SM_USE_EAX | SM_USE_A3D |
                          SM_USE_RIGHT_HANDED_SYSTEM | SM_USE_3D_SOFTWARE_LIGHT
};

enum SM_ARCHETYPE_OPTIONS
{
    SM_MUTE_3D_AT_MAX_DISTANCE = 1,
    SM_ENABLE_FREQUENCY_CONTROL = 2,
    SM_ENABLE_STICKY_FOCUS = 4,
    SM_DISABLE_STICKY_FOCUS = 8,
    SM_ARCHETYPE_DEFAULT = SM_MUTE_3D_AT_MAX_DISTANCE | SM_DISABLE_STICKY_FOCUS
};

enum SM_3D_PROCESSING_MODES
{
    SM_INGNORE_3D_PROECESSING = 0,      // does no 3D calculations
    SM_NORMAL_3D_PROCESSING,            // paramaters of the sound are absolute
    SM_LISTENER_RELATIVE_3D_PROCESSING, // parameters of the sound are relative to the listener paramaters
    SM_NUM_3D_PROCESSING_MODES
};

enum SM_SPEAKER_CONFIG
{
    SM_SPEAKER_MONO = 0,
    SM_SPEAKER_HEADPHONE,
    SM_SPEAKER_STEREO,
    SM_SPEAKER_STEREO_MIN,    //   5 deg arc
    SM_SPEAKER_STEREO_NARROW, //  10 deg arc
    SM_SPEAKER_STEREO_WIDE,   //  20 deg arc
    SM_SPEAKER_STEREO_MAX,    // 180 deg arc
    SM_SPEAKER_QUAD,          // 4
    SM_SPEAKER_SURROUND,      // 2 w/surround
    SM_SPEAKER_5POINT1,       // 5.1
    SM_SPEAKER_NUM_SETTINGS
};

struct SM_DEVICEINFO
{
    u32 size;
    u32 deviceOptionsUsed;
    u32 numHWChannels;
    u32 numHW3DBuffers;
    u32 numHWChannelsFree;
    u32 numHW3DBuffersFree;
    GUID deviceGUID;
};

class Vector;
struct IDirectSound;
struct SoundFormat;

#define ISOUNDARCHETYPE_VERSION 1
#define IID_ISoundArchetype     DACOM_MAKE_IID("ISoundArchetype")

struct ISoundArchetype : public IDAComponent
{
    virtual void __stdcall get_sound_format(SoundFormat*) = 0;
    virtual u32 __stdcall get_samples(void* samples) = 0;
    virtual u32 __stdcall get_sample_count() = 0;
    virtual f32 __stdcall get_base_attenuation() = 0;
    virtual u32 __stdcall get_num_channels() = 0;
    virtual u32 __stdcall get_duration() = 0;

    virtual void __stdcall set_samples(void* samples, u32 length) = 0;
    virtual GENRESULT __stdcall set_base_attenuation(f32 attenuation) = 0;
    virtual bool __stdcall is_loopable() = 0;
    virtual void __stdcall get_loop_params(u32* loop_start, u32* loop_end) = 0;
};

struct ISoundManager : public IDAComponent
{
    /**
     * @brief Sets the format of the primary buffer.
     * @param soundFormat ptr to SoundFormat structure (defined in Wavlib.lib).
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall set_sound_format(SoundFormat* soundFormat) = 0;

    /**
     * @brief Fills in soundFormat so that it contains the format of the primary buffer.
     * @param soundFormat ptr to SoundFormat structure (defined in Wavlib.lib).
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall get_sound_format(SoundFormat* soundFormat) = 0;

    /**
    * @brief This value is applied to all instances.  Archetype and instance attenuation can also
            be set independently.
     * @param attenuation Floating point decibal attenuation.  Valid values are between -100.0 and 0.0 .
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall set_master_attenuation(const f32 attenuation) = 0;

    /**
    * @brief This function controls the number of sounds that the sound manager will try to
            play simultaneously.  The number should be determined by the app based on the
            number of channels the card can handle in HW and other performance issues. The
            default value is the number of HW channels available.
     * @param numChannels Unsigned long maximum number of simultaneous sounds to play.
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall set_maximum_channels(const u32 numChannels) = 0;

    /**
    * @brief This value can also be set in the ini file (speakerConfiguration = ) and processed by
            Sound Manager at startup.
    * @param speakerConfiguration DWORD representing the users (or app desired) speaker configuration.
            Valid values are those (SM_SPEAKER_...) values defined in this file.
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall set_speaker_configuration(const u32 speakerConfiguration) = 0;

    /**
     * @return Floating point decibal attenuation between -100.0 and 0.0 .
     */
    virtual f32 __stdcall get_master_attenuation() = 0;

    /**
     * @brief The app should make a decision based on the number of sounds the app needs to play vs the abilities
            of the sound card. Too large a number on a bad card = degraded performance. Too low could = bad
            gameplay.
     * @return Unsigned long maximum number of simultaneous sounds to play.
     */
    virtual u32 __stdcall get_maximum_channels() = 0;

    /**
     * @return representing the current speaker configuration.
     * Valid values are those (SM_SPEAKER_...) values defined in this file.
     */
    virtual u32 __stdcall get_speaker_configuration() = 0;

    /**
    * @brief This function sets the reverb effect for all sounds.  If EAX is supported, and enabled, all parameters are
        passed to EAX.  If A3D (1.2) is supported, and enabled, only the damping factor is passed to A3D.
     * @param baseEnv defined in EAX.h currently
     * @param vol reverb volume
     * @param decay decay rate scale (1.0 is normal)
     * @param damping damping rate scale (1.0 is normal)
     */
    virtual GENRESULT __stdcall set_master_reverb(const u32 baseEnv, const f32 vol, const f32 decay,
                                                  const f32 damping) = 0;

    /**
     * @param baseEnv defined in EAX.h currently
     * @param vol reverb volume
     * @param decay decay rate scale (1.0 is normal)
     * @param damping damping rate scale (1.0 is normal)
     * @return GR_OK if EAX and/or A3D are supported and enabled, GR_GENERIC otherwise.
     */
    virtual void __stdcall get_master_reverb(u32* baseEnv, f32* vol, f32* decay, f32* damping) = 0;

    // don't use these methods.  implement ISoundListener and use update(ISoundListener *IEar)
    // listener property modifiers
    virtual GENRESULT __stdcall set_ear_orientation(const Matrix* orientation) = 0;
    virtual GENRESULT __stdcall set_ear_orientation(const Vector* front, const Vector* top) = 0;
    virtual GENRESULT __stdcall set_ear_position(const Vector*) = 0;
    virtual GENRESULT __stdcall set_ear_velocity(const Vector*) = 0;
    virtual GENRESULT __stdcall set_ear_distance_factor(const f32) = 0;
    virtual GENRESULT __stdcall set_ear_doppler_factor(const f32) = 0;
    virtual GENRESULT __stdcall set_ear_rolloff_factor(const f32) = 0;
    virtual void __stdcall get_ear_orientation(Matrix* orientation) = 0;
    virtual void __stdcall get_ear_orientation(Vector* front, Vector* top) = 0;
    virtual Vector __stdcall get_ear_position() = 0;
    virtual Vector __stdcall get_ear_velocity() = 0;
    virtual f32 __stdcall get_ear_distance_factor() = 0;
    virtual f32 __stdcall get_ear_doppler_factor() = 0;
    virtual f32 __stdcall get_ear_rolloff_factor() = 0;

    // Expansion mechanism.
    virtual GENRESULT __stdcall get_property(ISoundSource* sound, REFGUID propGUID, const u32 propID,
                                             void* propData, const u32 sizeOfPropData,
                                             u32* sizeOfDataWritten) = 0;
    virtual GENRESULT __stdcall get_global_property(REFGUID propGUID, const u32 propID, void* propData,
                                                    const u32 sizeOfPropData, u32* sizeOfDataWritten) = 0;
    virtual GENRESULT __stdcall set_property(ISoundSource* sound, REFGUID propGUID, const u32 propID,
                                             void* propData, const u32 sizeOfPropData) = 0;
    virtual GENRESULT __stdcall set_global_property(REFGUID propGUID, const u32 propID, void* propData,
                                                    const u32 sizeOfPropData) = 0;

    // Archetype management

    /**
     * @brief This function creates an archetype from a wav file that the app has already loaded. The current
            implementation of SoundManager (and DirectSound) only supports looping entire the sound.
     * @param sformat ptr to SoundFormat structure (WAVLIB.H).
     * @param length unsinged long length of the sample in bytes.
     * @param loop_start unsigned long starting point (byte) of looping sound
     * @param loop_end unsigned long ending point (byte) of looping sound
     * @param sample_buffer ptr to the sample data
     * @param options
     * @return SOUND_ARCH_INDEX of newly created archetype, SM_INVALID_ARCHETYPE if archetype couldn't be created.
     */
    virtual i32 __stdcall create_archetype_from_raw_data(const SoundFormat& sformat, u32 length,
                                                         u32 loop_start, u32 loop_end, void* sample_buffer,
                                                         u32 options) = 0;

    /**
     * @brief This function creates an archetype from a wav file that the app has already loaded
     * in the SoundFile format defined in WAVLIB.H . The current implementation of SoundManager
     * (and DirectSound) only supports looping the entire sound.
     * @param sourceData ptr to SoundFile structure (WAVLIB.H)
     * @param options
     * @return SOUND_ARCH_INDEX of newly created archetype, SM_INVALID_ARCHETYPE if archetype couldn't be created.
     */
    virtual i32 __stdcall create_archetype_from_soundfile(const SoundFile& sourceData, u32 options) = 0;
    virtual i32 __stdcall create_archetype(IFileSystem* sourceFile, u32 options) = 0;

    /**
     * @brief This function destroys an archetype and stops and releases any instances of the archetype.
     * @param archetype SOUND_ARCH_INDEX, previously returned by create_archetype, of the archetype to destroy.
     * @return GR_OK if successful, GR_GENERIC if the archetype was previously deleted or never existed.
     */
    virtual GENRESULT __stdcall destroy_archetype(i32 archetype) = 0;

    /**
     * @brief
     * @param archetype SOUND_ARCH_INDEX, previously returned by create_archetype,
     * whose ISoundArchetype interface is desired.
     * @param archInterface ISoundArchetype * for the archetype if successful,
     * NULL if the archetype is deleted or never existed.
     * @return GR_OK if successful, GR_GENERIC if the archetype is deleted or never existed
     */
    virtual GENRESULT __stdcall get_archetype_interface(i32 archetype, void** archInterface) = 0;

    /**
     * @param sound ptr to the ISoundSource interface of the sound to add.
     * @param index unsigned long position in the list of the sound to add.
     * 0 inserts the sound at the head of the list and get_active_sound_count() adds the sound at the end of the list.
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall add_active_sound(ISoundSource* sound, u32 index) = 0;

    /**
     * @brief This function removes the sound from SoundManager's play list and immediately
     * stops the sound and releases any SSoundManager reference to the sound.
     * (It is safe for an app to delete the sound after calling this function)
     * @param sound ptr to the ISoundSource interface of the sound to remove.
     * @return GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall remove_active_sound(ISoundSource* sound) = 0;

    /**
     * @brief This function sets SoundManager's list of sounds to play. SoundManager's previous
     *  list is not destroyed until the app calls update(). (It is not safe for an app that
     *  does not implement AddRef() and Release() for the sounds to delete the sounds in the
     *  list after calling this function until calling this function with an empty list and
     *  calling update() )
     * @param sounds ptr to the list of ISoundSource interfaces for the sounds.
     * @param count unsigned long number of sounds in the list.
     * @return  GR_OK if successful, or some error code on failure.
     */
    virtual GENRESULT __stdcall set_active_sounds(ISoundSource* sounds[], u32 count) = 0;

    /**
     * @return Unsigned long number of sounds in SoundManager's play list.
     */
    virtual u32 __stdcall get_active_sound_count() = 0;
    virtual u32 __stdcall get_playing_sound_count() = 0;

    /**
     * @brief This function initializes DirectSound and determines the capabilities of the selected
     * audio device.
     * After calling this function the app can get info about the device and start playing sounds.
     * @param hWnd handle to the app's main window.
     * @param options unsigned long mask containing the SoundManager options (define in this file)
     * the app desires.
     * @return GR_OK if successful, GR_GENERIC on failure.
     */
    virtual GENRESULT __stdcall startup(HWND hWnd, u32 options) = 0;
    virtual GENRESULT __stdcall shutdown() = 0;

    /**
     * @brief If successful, this function calls AddRef() for lpds.
     * @param ldps address of the pointer to the direct sound interface. Set to NULL on failure.
     * @return GR_OK if successful, GR_GENERIC if an error occurs.
     */
    virtual GENRESULT __stdcall get_directsound_interface(void** ldps) = 0;

    /**
     * @return Unsigned long current time according to SoundManager in milliseconds.
     */
    virtual u32 get_current_time_ms() = 0;

    /**
     * @param info address of a device info structure. Set to NULL on failure.
     * @return GR_OK if successful, GR_GENERIC if an error occurs.
     */
    virtual GENRESULT get_device_info(SM_DEVICEINFO* info) = 0;

    /**
     * @brief This function synchronizes the playing sounds, starts new sounds, and releases
     * all sound manager references to sounds that are no longer in the play list.
     * If IEar in not NULL, SoundManager updates the listener's parameters before playing
     * any sounds. If IEar is NULL, only the sounds are updated and the listener information
     * is not updated. If the app doesn't implement ISoundListener, the listener will
     * be at the origin with default DSound settings.  The app should call this on a regular
     * basis to make sure that sounds are started at the right time and that their data is
     * updated as needed.
     * @param IEar Ptr to the app's ISoundListener implementation.
     */
    virtual void __stdcall update(ISoundListener* IEar = nullptr) = 0;
    virtual GENRESULT __stdcall unknownA(
        void* value) = 0; // #TODO unsure what this is (seems to be called when pressing F1 to open menu)
    virtual GENRESULT __stdcall unknownB(
        void* value) = 0; // #TODO unsure what this is (seems to be called when pressing F1 to close menu)
};

struct SoundStatus
{
    const ISoundSource* soundSource; // the sound source interface for the sound
    u32 internalFlags;               // the internal sound manager flags for the sound
    DWORD dsoundBufferFlags;         // the DirectSound buffer flags for this sound
};

#define ISOUNDMANAGERSTATUS_VERSION 1
#define IID_ISoundManagerStatus     DACOM_MAKE_IID("ISoundManagerStatus")
struct ISoundManagerStatus
{
    // Returns the ISoundSource pointer for the indicated playing sound.
    // Use get_playing_sound_count() from ISoundManager to get the number of playing sounds.
    // NOTE: The given ISoundSource pointer returned does not have is ref count increased before returning. If you
    // intend to hold on to it, you must ref count it yourself.
    // Returns GR_OK if 0 <= which < get_playing_sound_count().
    // Returns GR_GENERIC otherwise.
    virtual GENRESULT __stdcall get_playing_sound_status(int which, SoundStatus& playingStatus) = 0;
};
