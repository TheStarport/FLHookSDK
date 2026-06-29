//  COPYRIGHT (C) 1999 BY DIGITAL ANVIL, INC.

#pragma once
#include "../Dacom/Dacom.hpp"
#include "../Dacom/TComponent.hpp"
#include "../Dacom/TSmartPtr.hpp"

#include <dsound.h>
#include <list>
#include <map>

#include "ISound.hpp"
#include "ISoundListener.hpp"
#include "ISoundManager.hpp"

#pragma warning(disable : 4786 4530)

#include "Engine.hpp"
#include "FLCore/Dacom/IProfileParser.hpp"
#include "wavlib.hpp"

struct SoundArchetype;
struct SoundInstance;

// internal SM_BUFFER_FLAGS
const u32 SMI_BUFFER_IN_HARDWARE = 0x01;      // buffer was created in hardware
const u32 SMI_BUFFER_USE_HW_BUFFER = 0x02;    // try to use HW for this buffer
const u32 SMI_BUFFER_USE_HW_3D_BUFFER = 0x04; // try to use 3D HW for this buffer
const u32 SMI_BUFFER_USING_NOTIFICATION = 0x08;
const u32 SMI_BUFFER_GIVE_UP_ON_HW =
    0x10;                        // creating a hw buffer for this instance failed when it shouldn't have
const u32 SMI_DISABLE_3D = 0x20; // disable 3D control

typedef struct _REVERBINFO
{
    u32 baseEnv;
    f32 vol;
    f32 decay;
    f32 damping;
} REVERBINFO;

struct FLSDK_IMPORT GenericDSoundBuffer
{
    LPDIRECTSOUNDBUFFER pBuffer;
    DSBUFFERDESC desc;

    GenericDSoundBuffer(LPWAVEFORMATEX fmt);
    ~GenericDSoundBuffer();
};

// SoundInstance
struct FLSDK_IMPORT SoundInstance
{
    ISoundSource* soundSource;
    LPDIRECTSOUNDBUFFER m_lpSoundBuffer;

    u32 m_startTime;
    u32 m_submitted_index;

    u32 m_internal_flags;
    unsigned long m_DSOUND_buffer_flags;

    f32 m_cachedDistanceSquared;
    f32 m_cachedMax;
    f32 m_cachedMaxSquared;
    f32 m_cachedMin;
    f32 m_cachedMinSquared;
    Vector m_cachedPositionV;
    Vector m_cachedSoundPanV;

    HANDLE m_loopEventHandle;
    u32 m_loopStartOffset;
    u32 m_loopEndOffset;

    SoundArchetype* m_archetype;

    inline void copy_instance_data(const SoundInstance& rhs);

    SoundInstance();
    SoundInstance(ISoundSource*);
    SoundInstance(const SoundInstance& rhs);
    void operator=(const SoundInstance& rhs);
    ~SoundInstance();
    void free();
};

// SoundArchetype implementation
struct FLSDK_IMPORT SoundArchetype : public ISoundArchetype
{
    SoundFile m_soundFile;
    u32 m_msDuration;
    u32 m_bufferFlags;
    u32 m_numHWBuffers;

    f32 m_baseAttenuation;
    LPDIRECTSOUNDBUFFER m_lpSoundBuffer;
    LPDIRECTSOUNDBUFFER m_lpHardwareBuffer;
    WAVEFORMATEX m_dsWaveFormat;

    BEGIN_DACOM_MAP_INBOUND(SoundArchetype)
    DACOM_INTERFACE_ENTRY(ISoundArchetype)
    DACOM_INTERFACE_ENTRY2(IID_ISoundArchetype, ISoundArchetype)
    END_DACOM_MAP()

    SoundArchetype();
    ~SoundArchetype();

    void __stdcall get_sound_format(SoundFormat*) override;
    u32 __stdcall get_samples(void* samples) override;
    u32 __stdcall get_sample_count() override;
    f32 __stdcall get_base_attenuation() override;
    u32 __stdcall get_num_channels() override;
    u32 __stdcall get_duration() override;
    bool __stdcall is_loopable() override;
    void __stdcall get_loop_params(u32* loop_start, u32* loop_end) override;

    void __stdcall set_samples(void* samples, u32 length) override;
    GENRESULT __stdcall set_base_attenuation(f32 attenuation) override;

    GENRESULT set_sound_data(const SoundFormat* sourceData, u32 length, u32 loop_start, u32 loop_end,
                             void* sample_buffer, LPDIRECTSOUND lpds, u32 options);

    // Commented out because wavlib not implemented
    // GENRESULT set_sound_data_from_file(IFileSystem* sourceFile, LPDIRECTSOUND lpds, u32 options);

    void add_instance_hw_buffer();
    void release_instance_hw_buffer();
};

typedef DAComponent<SoundArchetype> SOUND_ARCH;
typedef st6::map<u32, SOUND_ARCH*> ArchetypeMap;
typedef st6::list<SoundInstance> InstanceList;
typedef st6::list<ISoundSource*> SoundSourceList;

// typedef DAComponent<SoundArchetype> SOUND_ARCH;
// typedef AllocLite<SOUND_ARCH *> SOUND_ARCH_ALLOC;
// ALLOCLITE_GLOBAL (SOUND_ARCH_ALLOC);
// typedef map<u32, SOUND_ARCH *, less<u32>, SOUND_ARCH_ALLOC> ArchetypeMap;
//
// typedef AllocLite<SoundInstance> SOUND_INSTANCE_ALLOC;
// ALLOCLITE_GLOBAL (SOUND_INSTANCE_ALLOC)
// typedef list<SoundInstance, SOUND_INSTANCE_ALLOC> InstanceList;
//
// typedef AllocLite<ISoundSource *> SOUND_SOURCE_ALLOC;
// ALLOCLITE_GLOBAL (SOUND_SOURCE_ALLOC)
// typedef list<ISoundSource *, SOUND_SOURCE_ALLOC> SoundSourceList;

#define ISOUNDMANAGER_VERSION 1
#define IID_ISoundManager     DACOM_MAKE_IID("ISoundManager")
struct FLSDK_IMPORT SoundManager : public ISoundManager, ISoundManagerStatus, IAggregateComponent
{
  public:
    HWND m_hWnd;
    ArchetypeMap m_archetypeMap;

    CRITICAL_SECTION m_archetypeLock;

    CRITICAL_SECTION m_loopThreadLock;

    SoundSourceList m_activeSoundList;

    InstanceList m_spliceList;
    static InstanceList m_playList;

    SoundInstance m_tempInstance;

    i32 m_nextAvailableArchetype;

    bool m_Initialized;
    char m_deviceGuidString[40];
    GUID m_deviceGuid;

    u32 m_hw_threshold_multiplier_squared; // scale applied to min distance to determine whether a buffer gets hw
    f32 m_masterAttenuation;               // master attenuation applied to all sound instances
    u32 m_currentTime;                     // current ms soundmanager time
    u32 m_maxHardwareChannels;             // max HW channels reported by the card
    u32 m_maxChannels;                     // max total channels reported by the card
    u32 m_speakerConfiguration;            // current speaker configuration
    REVERBINFO m_reverb;                   // current reverb info
    REVERBINFO m_originalReverb;           // reverb info to be reverted when soundmanager is shutdown
    u32 m_masterReverbMix;                 // master amount of reverb to apply to all sound instances
    f32 m_originalA3DRollofFactor;         // original value to be reverted when soundmanager is shutdown
    GUID m_DS3D_SW_ALG_GUID;               // SW DS3D algorithm to use for 3D SW sounds

    u32 m_hardwareOptionsDesired; // flags indicating the options the app requested
    u32 m_hardwareOptionsUsed;  // flags indicating the options that soundmanager was able to succesfully use
    u32 m_numHardware3DBuffers; // number of HW buffers available
    u32 m_primarySampleRate;
    u32 m_primaryNumChannels;
    u32 m_primaryBitsPerSample;
    i32 m_simpleCoordTransformation;
    Transform m_earTransform;

    LPDIRECTSOUND3DLISTENER m_lpdsListener; // the listener ptr
    Vector m_listenerFront;
    Vector m_listenerUp;
    Vector m_listenerPan;
    Vector m_listenerPosition;
    Vector m_listenerVelocity;
    f32 m_listenerDistanceFactor;
    f32 m_listenerDopplerFactor;
    f32 m_listenerRolloffFactor;

    LPDIRECTSOUND m_lpds;                    // the dsound ptr
    LPDIRECTSOUNDBUFFER m_lpdsPrimaryBuffer; // the primary buffer ptr

    COMPTR<IProfileParser> profile_parser;

    static HANDLE LoopNotificationThread; // thread created when looping sounds w/ markers are started
    static HANDLE
        ResetNotificationLoopEvent; // dummy event used to reset (and resync) the events the thread is waiting on
    static LONG ExitReq;

    BEGIN_DACOM_MAP_INBOUND(SoundManager)
    DACOM_INTERFACE_ENTRY(ISoundManager)
    DACOM_INTERFACE_ENTRY2(IID_ISoundManager, ISoundManager)
    DACOM_INTERFACE_ENTRY2(IID_ISoundManagerStatus, ISoundManagerStatus)
    END_DACOM_MAP()

  public:
    SoundManager();
    ~SoundManager();

    DA_HEAP_DEFINE_NEW_OPERATOR(SoundManager);

    // ISoundManager methods
    GENRESULT __stdcall set_sound_format(SoundFormat* soundFormat) override;
    GENRESULT __stdcall get_sound_format(SoundFormat* soundFormat) override;

    GENRESULT __stdcall set_master_attenuation(const f32 attenuation) override;
    GENRESULT __stdcall set_maximum_channels(const u32 numChannels) override;
    GENRESULT __stdcall set_speaker_configuration(const u32 speakerConfiguration) override;

    f32 __stdcall get_master_attenuation() override;
    u32 __stdcall get_maximum_channels() override;
    u32 __stdcall get_speaker_configuration() override;

    GENRESULT __stdcall set_master_reverb(const u32 baseEnv, const f32 vol, const f32 decay,
                                          const f32 damping) override
    {
        return GR_OK;
    }

    void __stdcall get_master_reverb(u32* baseEnv, f32* vol, f32* decay, f32* damping) override;

    // These need to be removed as soon as Freelancer implements an ISoundListener begin remove
    GENRESULT __stdcall set_ear_orientation(const Matrix* orientation) override;
    GENRESULT __stdcall set_ear_orientation(const Vector*, const Vector*) override;
    GENRESULT __stdcall set_ear_position(const Vector*) override;
    GENRESULT __stdcall set_ear_velocity(const Vector*) override;
    GENRESULT __stdcall set_ear_distance_factor(const f32) override;
    GENRESULT __stdcall set_ear_doppler_factor(const f32) override;
    GENRESULT __stdcall set_ear_rolloff_factor(const f32) override;

    void __stdcall get_ear_orientation(Matrix* orientation) override;
    void __stdcall get_ear_orientation(Vector*, Vector*) override;
    Vector __stdcall get_ear_position() override;
    Vector __stdcall get_ear_velocity() override;
    f32 __stdcall get_ear_distance_factor() override;
    f32 __stdcall get_ear_doppler_factor() override;
    f32 __stdcall get_ear_rolloff_factor() override;
    // end of remove

    // generic property set extensions to allow getting/setting of new properties not currently supported
    GENRESULT __stdcall get_property(ISoundSource* sound, REFGUID propGUID, const u32 propID, void* propData,
                                     const u32 sizeOfPropData, u32* sizeOfDataWritten) override;
    GENRESULT __stdcall get_global_property(REFGUID propGUID, const u32 propID, void* propData,
                                            const u32 sizeOfPropData, u32* sizeOfDataWritten) override;
    GENRESULT __stdcall set_property(ISoundSource* sound, REFGUID propGUID, const u32 propID, void* propData,
                                     const u32 sizeOfPropData) override;
    GENRESULT __stdcall set_global_property(REFGUID propGUID, const u32 propID, void* propData,
                                            const u32 sizeOfPropData) override;

    // archetype creation/destruction methods
    i32 __stdcall create_archetype_from_raw_data(const SoundFormat&, u32 length, u32 loop_start, u32 loop_end,
                                                 void* sample_buffer, u32 options) override;
    i32 __stdcall create_archetype_from_soundfile(const SoundFile& sourceData, u32 options) override;
    i32 __stdcall create_archetype(IFileSystem* sourceFile, u32 options) override;
    GENRESULT __stdcall destroy_archetype(i32 archetype) override;

    // sound instance management methods
    GENRESULT __stdcall add_active_sound(ISoundSource* sound, u32 index) override; // add a single
    GENRESULT __stdcall remove_active_sound(
        ISoundSource* sound) override; // remove a sound from the active list
    GENRESULT __stdcall set_active_sounds(ISoundSource* sounds[],
                                          u32 count) override; // this is the list.
    u32 __stdcall get_active_sound_count() override;
    u32 __stdcall get_playing_sound_count() override;

    // SoundManager methods
    GENRESULT init(AGGDESC* desc);
    GENRESULT __stdcall Initialize() override;
    GENRESULT initialize_direct_sound();
    GENRESULT __stdcall startup(HWND hWnd, u32 options) override { return GR_OK; }
    GENRESULT __stdcall shutdown() override;
    GENRESULT __stdcall get_directsound_interface(void**) override;
    u32 get_current_time_ms() override;
    GENRESULT get_device_info(SM_DEVICEINFO*) override;
    // syncs the need_to_play properties to the active sound properties.
    void __stdcall update(ISoundListener* IEar) override {};
    GENRESULT __stdcall unknownA(
        void* value) override; // #TODO unsure what this is (seems to be called when pressing F1 to open menu)
    GENRESULT __stdcall unknownB(void* value)
        override; // #TODO unsure what this is (seems to be called when pressing F1 to close menu)
    static GENRESULT write_data_to_buffer(SoundFile* sourceData, LPDIRECTSOUNDBUFFER lpdsBuffer,
                                          u32 length = 0);

    // SoundArchetype indexed methods
    GENRESULT __stdcall get_archetype_interface(i32 archetype, void** archInterface) override;
    virtual void __stdcall get_sound_format(i32 archetype, SoundFormat*);
    virtual u32 __stdcall get_samples(i32 archetype, void* samples);
    virtual u32 __stdcall get_sample_count(i32 archetype);
    virtual f32 __stdcall get_base_attenuation(i32 archetype);
    virtual u32 __stdcall get_num_channels(i32 archetype);
    virtual void __stdcall set_samples(i32 archetype, void* samples, u32 length);
    virtual bool __stdcall is_loopable(i32 archetype);

    // --- ISoundManagerStatus methods
    GENRESULT __stdcall get_playing_sound_status(int which, SoundStatus& playingStatus) override;

    // internal methods
    void report_audio_options();
    i32 get_next_archetype_index();
    GENRESULT create_instance(SoundInstance& instance, SoundInstance& newInstance);
    GENRESULT delete_instance(ISoundSource* sound, u32 index);
    u32 exists_in_list(const ISoundSource* source, InstanceList& checkList,
                       InstanceList::iterator* returnItr = NULL);
    bool need_to_play(SoundInstance& instance);
    bool finished(const SoundInstance& instance);
    bool in_range(SoundInstance& instance);
    // void update_instance_data(SoundInstance& instance);
    bool update_position(SoundInstance& instance);
    void set_listener_parameters();
    void update_listener_parameters(ISoundListener* IEar);
    GENRESULT create_hardware_buffer(SoundInstance& instance);
    void check_hardware_buffer_status(SoundInstance& instance);
    bool restore_lost_buffer(SoundInstance& instance);
    i32 add_archetype(SOUND_ARCH* nu);

    static DWORD WINAPI loop_notification_thread_loop(LPVOID);
    bool start_looping_sound_with_markers(SoundInstance& instance);

    // EMAURER trashes instances that were referring to 'archetype'
    void clean_archetype_references(u32 archetype);

    // EMAURER zap all of the archetypes in the database.
    void erase_archetypes(void);

    // EMAURER like QueryInterface, if result is true the reference count of 'output'
    // has been increased by 1. call Release () when done.
    bool query_archetype(i32 archetype, SOUND_ARCH*& output);

    static float calculate_frequency_factor(float frequency);
};
