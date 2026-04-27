#pragma once

#include "../FLCoreDefs.hpp"
#include "AI/AIEnums.hpp"
#include "AI/ContentCallback.hpp"
#include "AI/Ops.hpp"
#include "AI/Personality.hpp"
#include "Enums.hpp"
#include "FmtStr.hpp"
#include "Goods.hpp"
#include "Watchable.hpp"
#include "XML.hpp"

struct HDC__;

#pragma comment(lib, "FLCoreCommon.lib")

struct CLoot;
struct CObject;
class CETractor;
namespace Archetype
{
    struct Munition;
    struct IClObjFactory;
} // namespace Archetype
class CEShield;
class CEquip;
class CAttachedEquip;
// Forward Declarations
struct IObjRW;
struct HardpointInfo
{
        unsigned dunno;
        Vector position;
        Matrix rotation;
        unsigned dunno2[5];
};
struct EquipStatus;
namespace Universe
{
    struct IZone;
}
class IStateGraph;

enum class TransactionType
{
    Sell = 0,
    Buy = 1
};

enum class ExcludeObjectType
{
};

struct IMPORT ActionDB
{
        ActionDB();
        ~ActionDB();
        ActionDB& operator=(const ActionDB&);
        void add(struct IAction*);
        IAction* find(const char*) const;
        void free();
        int get_action_count() const;
        bool remove(IAction*);
        void update(f32);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT AmbientScriptInfo
{
        AmbientScriptInfo();
        ~AmbientScriptInfo();
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT AmbientScriptProperties
{
    public:
        AmbientScriptProperties();
        ~AmbientScriptProperties();
        AmbientScriptProperties& operator=(const AmbientScriptProperties&);
        void clear();
        void destroy();
        ulong get_key() const;
        void init(const struct AmbientScriptDescription&);
        void marshal(class MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace AnimDB
{
    IMPORT void Add(int);
    IMPORT void Add(struct VChannel*);
    IMPORT u32 Count();
    IMPORT void Rem(int);
    IMPORT void Rem(const VChannel*);
    IMPORT void Shutdown();
    IMPORT void Update(f32);
}; // namespace AnimDB

namespace PhyArch
{
    struct IMPORT Part
    {
            Part(const Part&);
            Part();
            ~Part();
            Part& operator=(const Part&);
            void clear();

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

    IMPORT const Part* GetDefaultPart();
    IMPORT bool LoadSurfaces(const char*, st6::map<u32, Part, st6::less<u32>, st6::allocator<Part>>&);
}; // namespace PhyArch

struct IEngineInstance;

struct DockHardpointInfo
{
        f32 radius;
        const char* hardpoint;
        const char* dockAnimation;
        DockType dockType;
};

struct CHARACTER_ID final
{
        IMPORT CHARACTER_ID();
        IMPORT CHARACTER_ID const& operator=(CHARACTER_ID const&);
        bool operator<(CHARACTER_ID const& a) const { return _stricmp(charFilename, a.charFilename) < 0; }
        bool operator==(CHARACTER_ID const& a) const { return _stricmp(charFilename, a.charFilename) == 0; }
        bool operator!=(CHARACTER_ID const& a) const { return _stricmp(charFilename, a.charFilename) != 0; }
        CHARACTER_ID(const char* input) { strcpy_s(charFilename, input); }
        IMPORT void invalidate();
        IMPORT bool is_valid() const;

        char charFilename[512]; // Only first 16 bytes are ever used
};

namespace Async
{
    struct IMPORT Action
    {
            Action(const Action&);
            Action(bool);
            virtual ~Action();

            static void* operator new(u32);
            static void operator delete(void*);

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

    IMPORT bool AddWork(Action*);
    IMPORT void DumpWorkQueue();
    IMPORT void Shutdown();
    IMPORT void Startup();
    IMPORT int WorkQueueSize();
}; // namespace Async

struct IMPORT BaseHint
{
        BaseHint(const BaseHint&);
        BaseHint();
        virtual ~BaseHint();
        BaseHint& operator=(const BaseHint&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace BehaviorTypes
{
    IMPORT int get_behavior_id(const char*);
    IMPORT const char* get_behavior_name(int);
}; // namespace BehaviorTypes

class IMPORT BinaryRDLReader
{
        char Buf[1024];

    public:
        BinaryRDLReader(const BinaryRDLReader&);
        BinaryRDLReader();
        BinaryRDLReader& operator=(const BinaryRDLReader&);
        virtual bool extract_text_from_buffer(u16*, u32, u32&, const char*, u32);
        virtual bool read_buffer(class RenderDisplayList&, const char*, u32);
        virtual bool read_file(RenderDisplayList&, const char*);
};

class IMPORT BinaryRDLWriter
{
        char Buf[1024];

    public:
        BinaryRDLWriter(const BinaryRDLWriter&);
        BinaryRDLWriter();
        BinaryRDLWriter& operator=(const BinaryRDLWriter&);
        virtual bool write_buffer(const RenderDisplayList&, char*, u32, u32&);
        virtual bool write_file(const RenderDisplayList&, const char*);
};

struct ISpatialPartition;

namespace CmnAsteroid
{
    struct LootableZone;
}

namespace Exclusion
{
    struct IMPORT AsteroidExclusionZone
    {
            AsteroidExclusionZone();
            ~AsteroidExclusionZone();
            AsteroidExclusionZone& operator=(const AsteroidExclusionZone&);
            const Universe::IZone* get_zone();
            bool set_zone(const Universe::IZone*, const Universe::IZone*);
            void update_dist(const Vector&);

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

    class IMPORT AsteroidExclusionZoneMgr
    {
        public:
            AsteroidExclusionZoneMgr(const AsteroidExclusionZoneMgr&);
            AsteroidExclusionZoneMgr();
            ~AsteroidExclusionZoneMgr();
            AsteroidExclusionZoneMgr& operator=(const AsteroidExclusionZoneMgr&);
            AsteroidExclusionZone* back();
            int get_max_billboard_count();
            virtual bool is_excluded(const Vector&, ExcludeObjectType, void*);
            void normalize_billboard_density(int);
            virtual void push_back(const Universe::IZone*, const Universe::IZone*);
            void set_max_cliasteroid_exclusion_distance(f32);
            void set_max_dynamicasteroid_exclusion_distance(f32);
            virtual void sort(void*);

        private:
            bool is_billboard_excluded(const Vector&, f32*);
            bool is_cliasteroid_excluded(const Vector&, f32*);
            bool is_cmnasteroid_excluded(const Vector&, f32*);
            bool is_dynamic_asteroid_excluded(const Vector&);

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

    struct IMPORT NebulaExclusionZone
    {
            NebulaExclusionZone();
            ~NebulaExclusionZone();
            NebulaExclusionZone& operator=(const NebulaExclusionZone&);
            f32 get_fog_far();
            const Universe::IZone* get_zone();
            ID_String get_zone_shell_name();
            void set_fog_far(f32);
            bool set_zone(const Universe::IZone*, const Universe::IZone*);
            void set_zone_shell_name(const char*);
            void update_dist(const Vector&);

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

    class IMPORT NebulaExclusionZoneMgr
    {
        public:
            NebulaExclusionZoneMgr(const NebulaExclusionZoneMgr&);
            NebulaExclusionZoneMgr();
            ~NebulaExclusionZoneMgr();
            NebulaExclusionZoneMgr& operator=(const NebulaExclusionZoneMgr&);
            NebulaExclusionZone* back();
            virtual bool is_excluded(const Vector&, ExcludeObjectType, void*);
            bool is_in_exclusion_zone(const Vector&, NebulaExclusionZone**, f32*, bool);
            virtual void push_back(const Universe::IZone*, const Universe::IZone*);
            void set_max_distance(f32);
            virtual void sort(void*);

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

}; // namespace Exclusion

struct INotify
{
        enum Event
        {
        };
};

class IVP_Core;
class IVP_Event_Sim;

template <class T>
class IVP_U_Vector;

enum IVP_CONTROLLER_PRIORITY
{
};

#undef GetCurrentTime

class IMPORT CAttachmentObj
{
    public:
        virtual ~CAttachmentObj();

        CAttachmentObj(const CAttachmentObj&);
        CAttachmentObj();
        CAttachmentObj& operator=(const CAttachmentObj&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT CBase
{
        virtual ~CBase();

        CBase(const CBase&);
        CBase();
        CBase& operator=(const CBase&);
        void advise(bool);
        void cobject(CObject*);
        CObject* cobject() const;
        long get_index() const;
        void notify_of_destruction(void*);

    public:
        CObject* cobj;
};

class IMPORT CDeadReckonedVector
{
    public:
        CDeadReckonedVector(const CDeadReckonedVector&);
        CDeadReckonedVector();
        virtual ~CDeadReckonedVector();
        CDeadReckonedVector& operator=(const CDeadReckonedVector&);
        void AddSample(const Vector&, f64);
        f64 CalcError(const Vector&);
        f64 ConvergeTime();
        void Doit(f64);
        const Vector& GetProjectedPosition();
        const Vector& GetSample(int);
        void NormalizeProjectedPosition();
        void NormalizeTrackedPosition();
        Vector ProjectVelocity(f64);
        void Reset();
        void SetMaxCorrectiveConvergeTime(f64);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT CFLIDMaker
{
    public:
        CFLIDMaker& operator=(const CFLIDMaker&);
        u32 AllocateObjectID();
        u32 CreateStaticID(const char*);
        static CFLIDMaker* GetInstance();
        int Initialize();
        static void Shutdown();
        static CFLIDMaker* m_pTheMaker;

    protected:
        CFLIDMaker();
        ~CFLIDMaker();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT CPlayerAccount
{
    public:
        CPlayerAccount(const CPlayerAccount&);
        CPlayerAccount();
        virtual ~CPlayerAccount();
        CPlayerAccount& operator=(const CPlayerAccount&);
        void GenerateAccount(const char*);
        static bool GenerateTextKey(char*);
        st6::wstring GetAccountName();
        const char* GetAccountNameChar();
        st6::wstring GetAccountNameSig();
        const char* GetAccountNameSigChar();
        st6::wstring GetServerSignature(const char*);
        static bool GetTextKey(char*);
        bool LoadAccount();
        bool LoadAccountFromStrings(const char*, const char*);
        static void SetAcctIndex(ulong);
        static bool SetTextKey(char*);
        bool VerifyAccount();

    protected:
        void TossHashes();
        static ulong AccountIndex;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT CPlayerTradeOffer
{
    public:
        CPlayerTradeOffer(const CPlayerTradeOffer&);
        CPlayerTradeOffer();
        virtual ~CPlayerTradeOffer();
        CPlayerTradeOffer& operator=(const CPlayerTradeOffer&);
        bool GetAccepted();
        EquipDescList& GetList();
        ulong GetMoneyOffered();
        u32 GetSourcePlayerID();
        CPlayerTradeOffer* GetTargetOffer();
        u32 GetTargetPlayerID();
        void SetAccepted(bool);
        void SetMoneyOffered(ulong);
        void SetSourcePlayerID(u32);
        void SetTargetOffer(CPlayerTradeOffer*);
        void SetTargetPlayerID(u32);

    public:
        unsigned sourceClient;
        unsigned targetClient;
        CPlayerTradeOffer* counterOffer;
        EquipDescList equipOffer;
        int moneyOffered;
        bool isAccepted;
};

class IMPORT CRemotePhysicsSimulation
{
    public:
        CRemotePhysicsSimulation(const CRemotePhysicsSimulation&);
        CRemotePhysicsSimulation();
        virtual ~CRemotePhysicsSimulation();
        CRemotePhysicsSimulation& operator=(const CRemotePhysicsSimulation&);
        f64 CalcPositionError(const Vector&);
        bool CheckForSync(const Vector&, const Vector&, const Quaternion&);
        void Doit(f64);
        Vector GetLatestUpdate();
        Vector GetSample(int);
        ulong GetSampleCount();
        f64 GetSimulationTime();
        virtual void RemoteUpdate(const Vector&, const Quaternion&, f64);
        void Reset();
        void SetLogging(bool);
        void tracef(const char*, ...);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT CharPlaceInfo
{
        CharPlaceInfo();
        ~CharPlaceInfo();
        void clear();
        void destroy();
        bool is_named(const char*) const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT CharacterProperties
{
    public:
        CharacterProperties();
        ~CharacterProperties();
        CharacterProperties& operator=(const CharacterProperties&);
        void destroy();
        ulong get_key() const;
        void init(const struct CharacterDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace Collision
{
    IMPORT f32 CalcCollisionDamage(u32, const Vector&, const Vector&);
    IMPORT f32 CalcCollisionDamage(f32, f32, f32);
    IMPORT void Free();
    IMPORT f32 GetImpactDamageFromType(u32);
    IMPORT bool Load(INI_Reader&);
}; // namespace Collision

struct IMPORT CommReferrable
{
        CommReferrable(const CommReferrable&);
        CommReferrable();
        CommReferrable& operator=(const CommReferrable&);
        virtual const TString<64>& GetMsgIdPrefix() const;
        virtual bool HasVoiceInfo() const;
        virtual bool read_comm_ini_data(INI_Reader&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT CostumeDescriptions
{
    public:
        CostumeDescriptions(const CostumeDescriptions&);
        CostumeDescriptions();
        ~CostumeDescriptions();
        CostumeDescriptions& operator=(const CostumeDescriptions&);
        const struct accessory* find_accessory(ulong) const;
        const accessory* find_accessory(const char*) const;
        ulong find_accessory_id(const char*) const;
        const struct bodypart* find_bodypart(int, ulong) const;
        const bodypart* find_bodypart(int, const char*) const;
        const struct costume* find_costume(ulong) const;
        const costume* find_costume(const char*) const;
        ulong find_costume_id(const char*) const;
        ulong find_part_id(int, const char*) const;
        void get_costume(int, struct Costume&) const;
        void get_costume(const char*, Costume&) const;
        int get_costume_gender(const Costume&) const;
        int get_costume_gender(ulong) const;
        const char* get_part_mesh(int, ulong) const;
        const char* get_part_name(int, ulong) const;
        void load_bodyparts(const char*);
        void load_costumes(const char*);

    private:
        void load_accessory(INI_Reader*);
        void load_bodypart(int, int, class DetailSwitchTable*, INI_Reader*);
        void warn(INI_Reader*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT CostumeHint
{
        CostumeHint(const CostumeHint&);
        CostumeHint();
        virtual ~CostumeHint();
        CostumeHint& operator=(const CostumeHint&);
        virtual void CleanUp(u8*);
        // virtual u32 Serialize(u8**);
        virtual void UnSerialize(u8*, u32);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT Csys
{
    public:
        Csys();
        Csys& operator=(const Csys&);
        Csys get_inverse() const;
        Transform get_transform() const;
        void init(const Vector&, const Matrix&);
        void set_identity();
        void set_transform(const Transform&);
        Csys trans_from_frame(const Csys&) const;
        Matrix trans_from_frame(const Matrix&) const;
        Vector trans_from_frame(const Vector&) const;
        Csys trans_to_frame(const Csys&) const;
        Matrix trans_to_frame(const Matrix&) const;
        Vector trans_to_frame(const Vector&) const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

Csys operator*(const Csys&, const Csys&);

namespace DataConfig
{
    IMPORT void shutdown();
    IMPORT int startup(const char*, Archetype::IClObjFactory*, struct ProgressCB*);
}; // namespace DataConfig

class IMPORT DetailSwitchTable
{
    public:
        DetailSwitchTable(const DetailSwitchTable&);
        DetailSwitchTable();
        ~DetailSwitchTable();
        DetailSwitchTable& operator=(const DetailSwitchTable&);
        f32 adjust_distance(f32, f32, f32) const;
        f32 get_switch_distance(f32) const;
        void read_from_ini(INI_Reader*);

    private:
        void add_table_entry(f32, f32);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT DeviceTRC
{
    public:
        DeviceTRC(const DeviceTRC&);
        DeviceTRC(HDC__*);
        DeviceTRC();
        virtual ~DeviceTRC();
        DeviceTRC& operator=(const DeviceTRC&);
        void bind_to_dc(HDC__*);
        virtual TextRenderContext::Image* create_image(const char* const);
        virtual void destroy_image(TextRenderContext::Image*);
        virtual void execute_image(const TextRenderContext::Image*, bool);
        virtual void execute_text(const u16*, bool, int);
        virtual int get_cell_height() const;
        virtual int get_cell_width() const;
        virtual void get_clip_rect(tagRECT&);
        virtual void get_font_metrics(int&, int&) const;
        virtual void get_text_fit(const u16*, int, int&, int*, VisualSize&, int) const;
        virtual void get_text_visual_size(const u16*, VisualSize&, int) const;
        static void release_font(int);
        virtual void set_clip_rect(const tagRECT&);
        static void set_drop_shadow_offset(int, int);
        static void set_image_root(const char*);
        static void static_set_font(int, const TextRenderContext::FontDesc&, f32);

    private:
        static int dropShadowX;
        static int dropShadowY;
        static class WinFont* font;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace EngineEquipConsts
{
    IMPORT f32 CRUISE_ACCEL_TIME;
    IMPORT f32 CRUISE_ATTEN_MOD_RANGE;
    IMPORT f32 CRUISE_DISRUPT_TIME;
    IMPORT f32 CRUISE_DRAG;
    IMPORT f32 CRUISE_STEADY_TIME;
    IMPORT f32 CRUISING_SPEED;
    IMPORT f32 DELTA_CRUISE_ATTEN_MOD_STEADY;
    IMPORT f32 DELTA_THROTTLE_ATTEN_MOD_CHANGING;
    IMPORT f32 DELTA_THROTTLE_ATTEN_MOD_STEADY;
    IMPORT f32 MAX_DELTA_FX_THROTTLE;
    IMPORT f32 MAX_ENGINE_FX_THROTTLE;
    IMPORT f32 THROTTLE_ATTEN_MOD_RANGE;
    IMPORT f32 THROTTLE_STEADY_TIME;
}; // namespace EngineEquipConsts

#pragma pack(push, 1)
struct SetEquipmentItem
{
        u16 count;
        f32 health;
        Id archId;
        u16 id;
        byte mounted;
        byte mission;
        u16 hardPointLen;
};
#pragma pack(pop)

struct FlPacketSetEquipment
{
        u16 count;
        byte items[1];
};

namespace ErrorHandler
{
    enum SeverityLevel
    {
    };
    IMPORT void activate(const char*, int (*)(const char*, const char*, bool));
    IMPORT void deactivate();
    IMPORT bool is_log_enabled(int);
    IMPORT void log_comment(int, const char*, ...);
    IMPORT void log_disable(int);
    IMPORT void log_enable(int);
    IMPORT void log_last_error(const char*, int, SeverityLevel, char*, ulong);
    IMPORT void* new_log(const char*, int, int, bool, bool);
}; // namespace ErrorHandler

class IMPORT File
{
    public:
        File();
        ~File();
        File& operator=(const File&);
        void close();
        int eof();
        void get_info();
        int get_length();
        const char* get_name() const;
        bool is_open();
        bool open(const char*);
        int read(void*, int);
        int read(void*, int, int);
        int read_line(char*, int);
        int seek(int);
        void set_name(const char*);
        int set_offset(int);
        int tell() const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT FileMap
{
        FileMap(const FileMap&);
        FileMap();
        ~FileMap();
        FileMap& operator=(const FileMap&);
        void close();
        bool eof() const;
        u32 get_file_length() const;
        const char* get_file_name() const;
        void handoff_to(FileMap&);
        bool open(const char*);
        bool open_memory(const void*, u32);
        u32 read(void*, u32);
        bool read_ptr(struct BINI_Block*&);
        bool read_ptr(struct BINI_Header*&);
        bool read_ptr(struct BINI_Value*&);
        void* request_pointer(u32&);
        void seek(u32);
        u32 tell() const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT HardpointSummary
{
    public:
        HardpointSummary(const HardpointSummary&);
        HardpointSummary();
        virtual ~HardpointSummary();
        HardpointSummary& operator=(const HardpointSummary&);
        int analyze_instance(long);
        void clear();
        void destroy();
        void expire_instance();
        int find_name(const char*) const;
        long find_name_instance(const char*) const;
        int get_count() const;
        const HardpointInfo& get_info(int) const;
        const HardpointInfo* get_info_by_name(const char*) const;
        long get_instance(int) const;
        const char* get_name(int) const;

    private:
        void count_hardpoints(long);
        static void count_hardpoints_callback(long, void*);
        void fill_hardpoints(long);
        static void fill_hardpoints_callback(long, void*);
        static void hardpoint_callback1(const char*, void*);
        static void hardpoint_callback2(const char*, void*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT Heap
{
        Heap(u32, int);
        void Free(void*);
        void* Malloc();
        void Shrink();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace Hierarchy
{
    IMPORT int GetDepth(long, long);
};

struct IMPORT IAction
{
        IAction(const IAction&);
        IAction();
        virtual ~IAction();
        IAction& operator=(const IAction&);
        virtual const char* get_id() const;

        static void* operator new(u32);
        static void operator delete(void*);

        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT IDirectiveInfo
{
        bool init; // ? seems to be 1 after first time auto pilot takes over
        void* vUnknown1;
        pub::AI::OpType op;
};

// Size: 460 bytes
// Constructor e.g. sub_62D2220
// Hex numbers behind dunno variables or in a comment indicate hex offset
class IMPORT IBehaviorManager
{
    public:
        enum IBehaviorCameraMode
        {
            A,
            B,
            C,
            D,
            E
        };

        enum class CancelRequestType
        {
        };
        enum class EvaluateResult
        {
        };

        struct Behavior
        {
                virtual void dunno0();
                virtual void dunno4();
                virtual void dunno8();
                virtual void dunnoC();
                virtual void dunno10();
                virtual void dunno14();
                virtual void dunno18();
                virtual void dunno1C();
                virtual void dunno20();
                virtual void dunno24();
                virtual bool SetOp(int op);
                virtual void dunno2C();
                virtual void dunno30();
                virtual void SetThrottle(f32 throttle);
                virtual void SetCruise(bool cruiseState);
                virtual void SetEngine(bool engineState);
                virtual void SetThruster(bool thrusterState);
                virtual void SetSlideStrafeBurst(StrafeDir dir);
                virtual void SetBrakeReverse(bool newState);
                virtual bool GetAllowHeadTracking();
                virtual void dunno50();
                virtual void dunno54();
                virtual void dunno58();
                virtual void dunno5C();
                virtual IObjRW* GetDebuggerTarget();
        };

        bool allow_head_tracking();
        bool cancel_behavior(CancelRequestType);
        bool enable_all_maneuvers();
        bool enable_maneuver(int, bool);
        EvaluateResult external_player_evaluate(int);
        bool get_camera_level_status();
        f32 get_closest_trailing_ship() const;
        const IDirectiveInfo* get_current_directive();
        const IObjRW* get_debugger_target() const;
        bool get_docking_port(const IObjRW*&, int&);
        u32 get_parent_id();
        void get_personality(pub::AI::Personality&);
        pub::AI::ScanResponse get_scan_response(u32);
        const Vector get_ship_up_direction();
        const IStateGraph* get_state_graph();
        class SystemManager* get_sys();
        bool get_user_turning_input_state();
        bool lock_maneuvers(bool);
        void refresh_state_graph();
        void reset_current_behavior_direction();
        void set_camera_mode(IBehaviorCameraMode);
        void set_content_callback(pub::AI::ContentCallback*);
        bool set_current_directive(const IDirectiveInfo&, const pub::AI::BaseOp*);
        void set_directive_callback(pub::AI::DirectiveCallback*);
        pub::AI::OP_RTYPE set_directive_priority(pub::AI::DirectivePriority);
        void set_personality(const pub::AI::Personality&);
        void set_ship_up_direction(const Vector&);
        void set_state_graph(int, bool);
        void set_turn_sensitivity(f32);
        void set_user_turning_input_state(bool);
        void submit_camera_up(const Vector&);
        void update_current_behavior_afterburner(bool);
        void update_current_behavior_auto_avoidance(bool);
        void update_current_behavior_auto_level(bool);
        void update_current_behavior_brake_reverse(bool);
        void update_current_behavior_cruise(bool);
        void update_current_behavior_direction(const Vector&);
        void update_current_behavior_engage_engine(bool);
        void update_current_behavior_slide_strafe_burst(StrafeDir);
        void update_current_behavior_throttle(f32);
        void update_level_camera(bool);

        struct BehaviorSwitchRatios
        {
                f32 percentage;
                pub::AI::OpType type;
        };

    public:
        int* vft;                        // 0x00
        IStateGraph* stateGraphInternal; // 0x04
        void* pDunno_0x08;
        struct PathfindManager* pathfindManager; // 0xC
        BehaviorSwitchRatios switchRatios[21];
        int iEnabledManeuversFlag;     // 0xB8 - 0 = all enabled
        bool bLockManeuvers;           // 0xBC
        pub::AI::OpType iCurrentBehaviourIndex; // 0xC0 - -1 when no behaviour, otherwise index of behaviourArray
        IDirectiveInfo* directiveInfo; // 0xC4
        int iDirectivePriority;        // 0xC8
        int iDirectiveOp;              // 0xCC
        f32 timeSinceLastDirectiveChange; //0xD0
        f32 timeSinceLastDirectiveChangeAttempt; //0xD4
        byte forceDirectiveRefresh; //0xD8
        f32 timeAlive; //0xDC
        f32 fDunno56_0xE0;
        f32 fDunno57_0xE4;
        int iDunnos58_0xE8[2];
        BaseWatcher baseWatcher; // 0xF0
        byte bDunno62_0xF8;
        bool bCameraLevelStatusFlag;                       // 0xF9
        pub::AI::DirectiveCallback* directiveCallbacks[5]; // 0xFC
        pub::AI::ContentCallback* contentCallback;         // 0x110
        int iDunnos_0x114[3];
        pub::AI::OpType queuedBehaviourIndex; // 0x120
        int iDunnos_0x124[3];
        bool bDunno_0x130;
        Vector shipUpDirection;   // 0x134
        Vector cameraUpDirection; // 0x140
        int iDunno_0x14C;
        bool bUserTurningInputState;    // 0x150
        IBehaviorCameraMode cameraMode; // 0x154
        byte bDunno_0x158;
        void* pDunno_0x15C;
        int iDunnos_0x160;
        f32 fTurnSensitivity; // 0x164
        byte bDunno_0x168;
        byte bDunno_0x169;
        int iDunno_0x16C;
        byte disableUpdates;
        struct Behavior* behaviourArray[21]; // 0x174 - index 7 seems to be docking
        byte bDunno_0x1C8;
};

struct IMPORT ICRSplineSegment
{
        ICRSplineSegment();
        ICRSplineSegment& operator=(const ICRSplineSegment&);
        void calculate_arclength();
        Vector calculate_spline_tangent(f32);
        Vector calculate_spline_vector(f32);
        f32 get_spline_length();
        f32 get_t_from_point(const Vector&, f32, f32);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace LaunchActionVars
{
    //@@@TODO	IMPORT  f32 const  launch_coast_time;
    //@@@TODO	IMPORT  f32 const  launch_decel_time;
};

struct IMPORT LineParser32
{
        LineParser32();
        LineParser32& operator=(const LineParser32&);
        void clear();
        u32 fetch_string(char*, u32);
        int find_char(char) const;
        char get_char() const;
        u32 read_string(char*, const char*);
        u32 read_terminator2(char*, char, char);
        u32 read_terminator(char*, char);
        void set(const char*, u32);
        bool skip_char(char);
        void skip_white();
        bool terminate_line(char);
        bool whitespace(char) const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace Loadout
{
    struct IMPORT Map
    {
            Map(const Map&);
            Map();
            ~Map();
            Map& operator=(const Map&);

        public:
            Id id;
            EquipDescVector eqVector;
    };

    IMPORT void Free();
    IMPORT const Map* Get(u32);
    IMPORT u32 GetID(const char*);
    IMPORT int Load(const char*, bool);
    IMPORT bool ReadCargoLine(INI_Reader&, EquipDesc&);
    IMPORT bool ReadEquipLine(INI_Reader&, EquipDesc&);
}; // namespace Loadout

//
// Defined in FLCoreDALib.h
//-------------------------
// class IMPORT MD5Hash
//{
// public:
//	MD5Hash(class MD5Hash const &);
//	class MD5Hash & operator=(class MD5Hash const &);
//	u8 * GetStatePtr();

// public:
//	u8 data[OBJECT_DATA_SIZE];
// };

struct IMPORT MPCritSec
{
        MPCritSec();
        ~MPCritSec();
        MPCritSec& operator=(const MPCritSec&);
        void lock();
        void unlock();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT MarketGoodInfo
{
        MarketGoodInfo();
        MarketGoodInfo& operator=(const MarketGoodInfo&);

    public:
        unsigned goodId;
        f32 price;
        int min;
        int stock;
        TransactionType transType;
        f32 rank;
        f32 rep;
        //int quantity; Those two fields are not actually there? Where'd we get those from?
        //f32 scale;
};

class IMPORT MarshalBuffer
{
    public:
        MarshalBuffer();
        MarshalBuffer& operator=(const MarshalBuffer&);
        void clear();
        Costume get_Costume();
        EquipDescList get_EquipDescList();
        u32 get_FL_ID();
        FmtStr get_FmtStr();
        GoodDescList get_GoodDescList();
        u16 get_U16();
        ulong get_U32();
        u8 get_U8();
        bool get_bool();
        const u8* get_buffer() const;
        int get_buffer_size() const;
        f32 get_float();
        void get_image(u8*);
        void get_image(u16*);
        void get_image(int*);
        void get_image(ulong*);
        void get_image(f32*);
        int get_int();
        int get_num_written() const;
        char* get_string();
        void get_string_to_buffer(char*, int);
        void get_void(void*, int);
        u16* get_wstring();
        bool is_empty() const;
        void put_Costume(const Costume&);
        void put_EquipDescList(const EquipDescList&);
        void put_FL_ID(u32);
        void put_FmtStr(const FmtStr&);
        void put_GoodDescList(const GoodDescList&);
        void put_U16(u16);
        void put_U32(ulong);
        void put_U8(u8);
        void put_bool(bool);
        void put_float(f32);
        void put_image(const u8&);
        void put_image(const u16&);
        void put_image(const int&);
        void put_image(const ulong&);
        void put_image(const f32&);
        void put_int(int);
        void put_string(const char*);
        void put_void(const void*, int);
        void put_wstring(const u16*);
        void skip_over(int);
        void use_default();
        void use_read_buffer(const u8*, int);
        void use_write_buffer(u8*, int);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

/* struct IMPORT MessageHandler
{
    MessageHandler(class IMessageRouter *);
    virtual ~MessageHandler();
    u32 get_id()const ;

protected:
    virtual void send_delayed_message(class StateMachineMessage *,f32,u32);
    virtual void send_delayed_message_to_me(class StateMachineMessage *,f32,int);
    virtual void send_immediate_message(class StateMachineMessage *,u32);

public:
    u8 data[OBJECT_DATA_SIZE];
};*/

class IMPORT MissionVendorAcceptance
{
    public:
        MissionVendorAcceptance(const MissionVendorAcceptance&);
        MissionVendorAcceptance();
        ~MissionVendorAcceptance();
        MissionVendorAcceptance& operator=(const MissionVendorAcceptance&);
        void clear();
        void destroy();
        ulong get_key() const;
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT MissionVendorProperties
{
    public:
        MissionVendorProperties(const MissionVendorProperties&);
        MissionVendorProperties();
        ~MissionVendorProperties();
        MissionVendorProperties& operator=(const MissionVendorProperties&);
        void clear();
        void destroy();
        const char* get_icon_texture() const;
        ulong get_key() const;
        void init(const struct MissionVendorOfferDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT NewsBroadcastProperties
{
    public:
        NewsBroadcastProperties(const NewsBroadcastProperties&);
        NewsBroadcastProperties();
        ~NewsBroadcastProperties();
        NewsBroadcastProperties& operator=(const NewsBroadcastProperties&);
        void clear();
        void destroy();
        ulong get_key() const;
        const char* get_logo_texture() const;
        void init(const struct NewsBroadcastDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

// Size: 1408 bytes
// Constructor e.g. sub_62DB3B0
// Hex numbers behind dunno variables or in a comment indicate hex offset
struct IMPORT PathfindManager
{
        void clear_user_zone();
        bool get_user_zone(struct UserZone&);
        void submit_user_zone(const UserZone&);

    public:
        // size: 64 bytes
        struct UserZone
        {
                int iZoneType;                // 0 = position, 1 = cuboid 2 = spaceobj
                int iDunno_0x04;              // same as iDunno_0x10 from SetZoneBehaviorParams if iDunno_0x10 was 0 or 1
                Vector vPosition;             // only used for iZoneType 0
                f32 fRadius;                // not used for iZoneType 1
                Matrix mDunno_0x18;           // pub::AI::SubmitState sets this to identiy when SetZoneBehaviorParams is used and iZoneType is 1
                Vector vCuboidCenter;         // only used for iZoneType 1
                Vector vCuboidHalfEdgeLength; // only used for iZoneType 1
                int iSpaceObjId;              // only used for iZoneType 2
        };
        int iDunno_0x00;
        int iDunno_0x04;
        bool bHasUserZone; // 0x08
        UserZone userZone; // 0x0C
        int iDunnos_0x64[2];
        int iDunnoStruct_0x6C[8]; // struct size 32 bytes
        File* fileDunno_0x8C;
        int iDunnos_0x90[62];
        File* fileDunno_0x188;
        int iDunnos_0x188[7];
        f32 fDunno_0x1A8;
        int iDunno_0x1AC;
        byte bDunno_0x1B0;
        int iDunnos_0x1B4[3];
        IBehaviorManager* behaviorManager; // 0x1C0 - usually the one this one belongs to
        int iDunno_0x1C4;
        BaseWatcher baseWatcher_0x1C8;
        int iDunnos_0x1D0[4];
        f32 fDunno_0x1E0;
        f32 fDunno_0x1E4;
        f32 fDunno_0x1E8;
        f32 fdunno_0x1EC;
        int iDunno_0x1F0;
        f32 fDunno_0x1F4;
        f32 fDunno_0x1F8;
        f32 fDunno_0x1FC;
        int iDunnos_0x1F8[3];
        f32 fDunno_0x20C;
        f32 fDunno_0x210;
        int iDunno_0x214;
        BaseWatcher baseWatcher_0x218;
        int iDunnos_0x220[6];
        byte bDunno_0x238;
        f32 fDunno_0x23C;
        int iDunno_0x240;
        byte bDunno_0x244;
        byte bDunno_0x245;
        int iDunno_0x248;
        byte bDunno_0x24C;
        int iDunno_0x250;
        byte bDunno_0x254;
        int iDunno_0x258[3];
        byte bDunno_0x260;
        int iDunnos_0x264[198];
};

class IMPORT PetalInterfaceDatabase
{
    public:
        PetalInterfaceDatabase(const PetalInterfaceDatabase&);
        PetalInterfaceDatabase();
        ~PetalInterfaceDatabase();
        PetalInterfaceDatabase& operator=(const PetalInterfaceDatabase&);
        void destroy();
        const struct petal_record* find_record(int, ulong) const;
        static int get_category(const char*);
        void load_from_ini(const char*);

    private:
        void add_record(int, const char*, const char*, char**, int);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT Rect
{
        Rect(int, int, int, int);
        Rect();
        Rect& operator=(const Rect&);
        int area() const;
        int bottommost() const;
        void clear();
        void get_center(int*, int*) const;
        int height() const;
        void init(int, int, int, int);
        void init_from_ltrb(int, int, int, int);
        int leftmost() const;
        bool nonnull() const;
        bool null() const;
        bool point_is_inside(int, int) const;
        int rightmost() const;
        int topmost() const;
        int width() const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

; // namespace Reputation

struct IMPORT RoomButtonInfo
{
        RoomButtonInfo();
        ~RoomButtonInfo();
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomCameraInfo
{
        RoomCameraInfo();
        ~RoomCameraInfo();
        RoomCameraInfo& operator=(const RoomCameraInfo&);
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct Camera
{
        char* vtable; // vftable
        Matrix rotation;
        Vector pos;
        bool bRenderNewCam; // 14
        Matrix rotation2;
        Vector pos2;
        f32 halfRes[2];
        f32 halfRes2[2];
        f32 fovXHud;
        f32 fovYHud;
        f32 cosFovX;
        f32 alwaysZeroFovX;
        f32 sinFovX;
        f32 alwaysZeroFovY;
        f32 cosFovY;
        f32 sinFovY;
        f32 fovX;
        f32 fovY;
        f32 aspect;
        f32 zNear;
        f32 zFar;
        unsigned screenExtents[4];
        unsigned dunno;
        Watchable* watchable; // 49
        unsigned dunno1[6];
        Vector dunno2;
        unsigned dunno3[6];
        Vector cameraOffset;
        unsigned dunno4[40];
        f32 angularPart2;
        f32 dunno5[9];
        f32 angularAcceleration;
        f32 cameraAccelerationPerFrame;
};

class IMPORT RoomData
{
    public:
        RoomData(const RoomData&);
        RoomData();
        ~RoomData();
        RoomData& operator=(const RoomData&);
        void clear();
        void destroy();
        void enumerate_CharacterPlacement_ini(void (*)(int, INI_Reader*, void*), void*) const;
        const RoomCameraInfo* find_camera(const char*, const char*) const;
        const RoomCameraInfo* find_camera_generic(const char*, const char*) const;
        const struct SetpointInfo* find_setpoint(const char*, const char*) const;
        const SetpointInfo* find_setpoint_generic(const char*, const char*) const;
        void fixup(long);
        const RoomCameraInfo* get_camera_info() const;
        void init(u32, u32, const char*, const char*);
        void load();
        void unfixup();
        void unload();

    private:
        void add_set_script_Camera(ulong, const Csys&, const char*, const struct ThornCameraProperties*);
        void add_set_script_Prop(const char*, const char*, int, const Csys&, bool, bool, bool, bool, u8, signed char, ulong, const char*,
                                 ulong, bool);
        void add_set_script_Setpoint(ulong, const Csys&, const char*, const struct ThornEntity*);
        void add_set_script_light(ulong, const Csys&, const struct ThornLightProperties*, u8);
        const SetpointInfo* apply_setpoint(const char*, char**, Csys*, const char*);
        CharPlaceInfo* find_CharacterPlacement(const char*);
        void fixup_FlashLight_list(long, const HardpointSummary*);
        static void make_setpoint_name_generic(const char*, char*);
        void read_Camera_block(INI_Reader*);
        void read_CharacterPlacement_block(INI_Reader*);
        void read_FlashLightLine_block(INI_Reader*);
        void read_FlashLightSet_block(INI_Reader*);
        void read_ForSaleShipPlacement_block(INI_Reader*);
        void read_Hotspot_block(INI_Reader*);
        void read_PlayerShipPlacement_block(INI_Reader*);
        void read_RoomInfo_block(INI_Reader*);
        void read_Sound_block(INI_Reader*);
        void read_ambient_script(INI_Reader*);
        void read_from_ini(const char*);
        void read_set_script(const char*);
        void setup_Camera();
        void unfixup_FlashLight_list();
        void unsetup_Camera();
        void warn(INI_Reader*, bool);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomLightInfo
{
        RoomLightInfo();
        ~RoomLightInfo();
        RoomLightInfo& operator=(const RoomLightInfo&);
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomPropInfo
{
        RoomPropInfo();
        ~RoomPropInfo();
        RoomPropInfo& operator=(const RoomPropInfo&);
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace RtcSlider
{
    IMPORT f32 get_default_fps_cap();
    IMPORT f32 get_fps_cap();
    IMPORT f32 get_slider();
    IMPORT bool is_enabled(ulong);
    IMPORT bool is_enabled(const char*);
    IMPORT void load(const char*);
    IMPORT void set_slider(f32);
    IMPORT bool validate_setting(const char*, const char*);
}; // namespace RtcSlider

struct IMPORT SMControllerEvent
{
        SMControllerEvent(int, const void*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT SMEventData
{
        enum STATE_MACHINE_EVENT_TYPE
        {
        };

        SMEventData(STATE_MACHINE_EVENT_TYPE);
        virtual STATE_MACHINE_EVENT_TYPE get_event_type() const;
        bool is_sm_event() const;
        bool is_user_event() const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT SMMChangeState
{
        SMMChangeState(int);
        virtual class StateMachineMessage* clone() const;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT SMMessage
{
        SMMessage(StateMachineMessage*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT ScanList
{
    public:
        ScanList(const ScanList&);
        ScanList();
        ~ScanList();
        ScanList& operator=(const ScanList&);
        bool add(IObjRW*);
        int add_in_range(const Vector&, f32, struct IObjDB*, u32, struct Filter*);
        void remove(IObjRW*);
        void reset();

    public:
        unsigned vftable;
        BaseWatcher objectArray[256];
        unsigned currSize;
        unsigned maxSize;
};

class IMPORT ScriptBehavior
{
    public:
        ScriptBehavior(const ScriptBehavior&);
        ScriptBehavior();
        ~ScriptBehavior();
        ScriptBehavior& operator=(const ScriptBehavior&);
        void clear();
        void destroy();
        ulong get_key() const;
        void init(const struct CharacterBehaviorDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT SetpointInfo
{
        SetpointInfo(const SetpointInfo&);
        SetpointInfo();
        ~SetpointInfo();
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT SetpointProperties
{
        SetpointProperties(const SetpointProperties&);
        SetpointProperties();
        ~SetpointProperties();
        SetpointProperties& operator=(const SetpointProperties&);
        void clear();
        const char* combine_to_name() const;
        void destroy();
        void extract_from_name(const char*);
        void set_segment(const char*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace ShieldEquipConsts
{
    IMPORT f32 HULL_DAMAGE_FACTOR;
};

struct IMPORT ShipGunStats
{
        ShipGunStats();
        ShipGunStats& operator=(const ShipGunStats&);
        void clear();

    public:
        unsigned activeGunCount;
        f32 avgGunSpeed;
        f32 maxGunRange;
        unsigned dunno1;
        unsigned dunno2;
};

struct IMPORT ShipPlaceInfo
{
        ShipPlaceInfo();
        ~ShipPlaceInfo();
        void clear();
        void destroy();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace SolarReps
{
    IMPORT int FindSolarRep(const ID_String&);
};

class IMPORT SphereIntruderChecker
{
    public:
        SphereIntruderChecker(const SphereIntruderChecker&);
        SphereIntruderChecker();
        ~SphereIntruderChecker();
        SphereIntruderChecker& operator=(const SphereIntruderChecker&);
        void check_sphere(u32, const Vector&, f32, st6::list<CObject*, st6::allocator<CObject*>>&);

    protected:
        virtual void added(CObject*);
        virtual void deleted(CObject*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT StateMachine
{
        StateMachine();
        virtual ~StateMachine();
        int get_state() const;
        virtual void process(const SMEventData*);
        void reset();
        void start();

    protected:
        virtual void handle_state_change();
        void set_state(int);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineGroup
{
    public:
        StateMachineGroup(class IMessageRouter*);
        virtual ~StateMachineGroup();
        virtual void add_state_machine(class StateMachineMessageHandler*);
        virtual void remove_state_machine(u32);
        virtual void remove_state_machine(const StateMachineMessageHandler*);

    protected:
        virtual void process(const SMEventData*);
        void remove_dying_machines();

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineMessage
{
    public:
        StateMachineMessage(const StateMachineMessage&);
        StateMachineMessage(u32);
        StateMachineMessage(f32, u32, u32, u32, int);
        StateMachineMessage();
        virtual ~StateMachineMessage();
        static u32 GenerateUniqueMessageType();
        virtual StateMachineMessage* clone() const;
        int get_delivery_state() const;
        f32 get_delivery_time() const;
        u32 get_message_type() const;
        u32 get_receiver() const;
        u32 get_sender() const;
        bool is_delivered() const;
        void set_delivered(bool);
        void set_delivery_options(f32, u32, u32, int);
        void set_delivery_state(int);
        void set_delivery_time(f32);
        void set_message_type(u32);
        void set_receiver(u32);
        void set_sender(u32);

        static void* operator new(u32);
        static void operator delete(void*);

    private:
        static u32 s_unique_message_type_generator;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineMessageHandler
{
        enum SM_MESSAGE_SCOPE
        {
        };

    public:
        StateMachineMessageHandler(IMessageRouter*);
        virtual void receive_message(StateMachineMessage*);

    protected:
        void send_delayed_message_to_me(StateMachineMessage*, f32, SM_MESSAGE_SCOPE, int);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT StyleCollection
{
        class Style
        {
            public:
                u8 data[OBJECT_DATA_SIZE];
        };

    public:
        StyleCollection& operator=(const StyleCollection&);
        static RenderDisplayList& get_style(u16);
        static void remove_style(u16);
        static void set_style(u16, const TextRenderAttributes&);
        static void set_style(u16, const RenderDisplayList&);

    protected:
        static st6::map<u16, Style, st6::less<u16>, st6::allocator<Style>> mStyles;

    public:
        u8 data[OBJECT_DATA_SIZE];
};
; // namespace SubObjectID

struct IMPORT TargetManager
{
        int remove_forced_target(u32);
        void set_player_enemy_clamp(int, int);
        int submit_forced_target(u32);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT TextFile32
{
        TextFile32(const TextFile32&);
        TextFile32();
        ~TextFile32();
        TextFile32& operator=(const TextFile32&);
        u32 get_line_num() const;
        bool read_line(LineParser32&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT ThrustManager
{
        void engage_cruise(bool);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace ThrusterEquipConsts
{
    IMPORT ID_String EXTERIOR_SOUND_NAME;
    IMPORT f32 INSIDE_CONE_ANGLE;
    IMPORT ID_String INTERIOR_SOUND_NAME;
    IMPORT f32 MAX_VOLUME_FORCE;
    IMPORT f32 MIN_VOLUME_FORCE;
    IMPORT f32 OUTSIDE_CONE_ANGLE;
    IMPORT f32 OUTSIDE_CONE_ATTENUATION;
}; // namespace ThrusterEquipConsts

namespace Timing
{
    struct IMPORT Delta
    {
            Delta();
            Delta& operator=(const Delta&);
            f64 calc_dt();
            void init();
            f64 read_dt();
            void start();
            void stop();
            void swap();

        public:
            u8 data[OBJECT_DATA_SIZE];
    };

    IMPORT f64 GetGlobalTime();
    IMPORT int GetMachineSpeed();
    IMPORT void UpdateGlobalTime(f64);
    IMPORT void init();
    IMPORT f64 read();
    IMPORT int64 read_ticks();
    IMPORT f64 seconds(const int64&);
}; // namespace Timing

enum class TractorFailureCode
{
    Success = 0,
    InvalidLootFailure = 1,
    LootTooFarFailure = 2,
    InsufficientCargoSpaceFailure = 3,
};

class IMPORT TractorArm
{
    public:
        enum class Mode
        {
        };

        TractorArm(const TractorArm&);
        TractorArm(CETractor*);
        ~TractorArm();
        TractorArm& operator=(const TractorArm&);
        TractorFailureCode GetErrorCode() const;
        Mode GetMode() const;
        CLoot* GetTarget() const;
        Vector GetTipPos() const;
        bool IsOn() const;
        void SetTarget(CLoot*);
        void TurnOff();
        void Update(f32);

    protected:
        static const f32 AcquireDelay;
        static const f32 GrabToleranceSquared;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT TradeResponseInfo
{
    public:
        TradeResponseInfo(const TradeResponseInfo&);
        TradeResponseInfo();
        ~TradeResponseInfo();
        TradeResponseInfo& operator=(const TradeResponseInfo&);
        void clear();
        void destroy();
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace TurnHelper
{
    IMPORT Vector get_angular_throttle(const Matrix&, const Matrix&, f32*);
};

struct IMPORT accessory
{
        accessory(const accessory&);
        accessory();
        ~accessory();
        accessory& operator=(const accessory&);
        const char* get_accessory_hardpoint() const;
        const char* get_character_hardpoint() const;
        const st6::list<st6::string>& get_materials() const;
        const char* get_mesh() const;
        const char* get_name() const;
        ulong get_name_crc() const;
        void init(const char*, const char*, const char*, const char*, const st6::list<st6::string>&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT bodypart
{
        bodypart(const bodypart&);
        bodypart();
        ~bodypart();
        bodypart& operator=(const bodypart&);
        int get_gender() const;
        const char* get_mesh() const;
        const char* get_name() const;
        ulong get_name_crc() const;
        st6::list<st6::string>* get_petal_anims() const;
        DetailSwitchTable* get_switch_table() const;
        void init(const char*, const char*, int, st6::list<st6::string>*, DetailSwitchTable*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct IMPORT option_spec
{
        option_spec& operator=(const option_spec&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

namespace Geometry
{
    struct Frustum;
    struct Sphere;
}; // namespace Geometry

struct IMPORT FlashLightSetInfo
{
        FlashLightSetInfo();
        ~FlashLightSetInfo();
        FlashLightSetInfo& operator=(const FlashLightSetInfo&);
        void clear();
        void destroy();
        void fixup(long, const class HardpointSummary*, const RoomData*);
        void unfixup();

    private:
        void add_light_csys(const Csys&);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

class IMPORT BaseData
{
    public:
        BaseData(const BaseData&);
        BaseData();
        ~BaseData();
        BaseData& operator=(const BaseData&);
        u32 get_base_id() const;
        // const st6::list<class RoomData*>* get_const_room_data_list() const;
        // const st6::map<u32, struct MarketGoodInfo, st6::less<u32>, st6::allocator<MarketGoodInfo>>* get_market() const;
        // st6::list<RoomData*>* get_room_data_list();
        //  commented out since they'd fail on the account of them being defined as 'std' in the game binaries. Use the fields below directly instead.
        f32 get_price_variance() const;
        f32 get_ship_repair_cost() const;
        u32 get_start_location() const;
        void read_from_ini(const char*, u32);
        void set_market_good(u32, int, int, TransactionType, f32, f32, f32);

    private:
        void read_Base_block(class INI_Reader*);
        void read_Room_block(INI_Reader*);

    public:
        unsigned dunno;
        f32 startRoom;
        f32 priceVariance;
        f32 shipRepairCost;
        st6::map<Id, MarketGoodInfo> marketMap;
        st6::list<RoomData*> roomData;
};

class IMPORT BaseDataList
{
    public:
        BaseDataList(const BaseDataList&);
        BaseDataList();
        ~BaseDataList();
        BaseDataList& operator=(const BaseDataList&);
        BaseData* get_base_data(u32) const;
        st6::list<BaseData*>* get_base_data_list();
        const st6::list<BaseData*>* get_const_base_data_list() const;
        RoomData* get_room_data(u32) const;
        RoomData* get_unloaded_room_data(u32) const;
        void load();
        void load_market_data(const char*);

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct Pilot
{
        static const unsigned pilotMapOffset = 0x130AA4;
        Id inheritedPilot;
        Id evadeDodge;
        Id evadeBreak;
        Id buzzHeadToward;
        Id buzzPassBy;
        Id trail;
        Id strafe;
        Id engineKill;
        Id repair;
        Id gun;
        Id mine;
        Id missile;
        Id damageReaction;
        Id missileReaction;
        Id countermeasure;
        Id formation;
        Id job;
};