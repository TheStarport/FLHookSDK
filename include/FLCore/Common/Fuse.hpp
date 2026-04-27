#pragma once
#include "../FLCoreDefs.hpp"

class INI_Reader;

class Fuse
{
    public:
        IMPORT Fuse(const ID_String&, f32);
        IMPORT Fuse(const Fuse&);
        IMPORT virtual ~Fuse();
        IMPORT Fuse& operator=(const Fuse&);
        IMPORT int ActionCount() const;
        IMPORT void Burn(f32);
        IMPORT virtual void FreeActions();
        IMPORT bool IgniteAt(u32, u16, f32);
        IMPORT bool IsBurning() const;
        IMPORT bool IsDeathFuse() const;
        IMPORT bool IsSpent() const;
        IMPORT bool IsSpentAt(f32) const;
        IMPORT f32 Lifetime() const;
        IMPORT void Load() const;
        IMPORT const ID_String& Name() const;
        IMPORT bool OverrideLifetime(f32);
        IMPORT void RandomizeActions();
        IMPORT bool UnBurn(u16, f32);
        IMPORT void UnLoad() const;

    protected:
        IMPORT bool ReadFuseValues(INI_Reader&);

    public:
        /* 1  */ unsigned archId;
        /* 2  */ f32 defaultLifetime;
        /* 3  */ bool deathFuse;
        bool align[3];
        /* 4  */ bool dunno2;
        bool dunno3;
        /* 5  */ void* dunno4; // 0x18 size struct
        /* 6  */ void* dunno5; // 0x18 size struct
        /* 7  */ unsigned dunno6;
        /* 8  */ unsigned actionCount;
        /* 9  */ bool dunno8;
        bool align2[3];
        /* 10 */ bool dunno9;
        /* 11 */ void* dunno10; // 0x1C size struct, used in isSpentAt
        /* 12 */ unsigned dunno11;  // isBurning
};

class FuseAction
{
    public:
        IMPORT FuseAction(const FuseAction&);
        IMPORT FuseAction();
        IMPORT FuseAction& operator=(const FuseAction&);
        IMPORT f32 GetTriggerTime() const;
        IMPORT bool ReadFuseActionValue(INI_Reader&);

        virtual ~FuseAction();
        virtual FuseAction ResetAndCopyArch();
        virtual int Load();
        virtual int UnLoad();
        virtual bool IsTriggered(u16) const;
        virtual bool IsTriggered() const;
        virtual void Trigger(u32, u16);
        virtual void UnTrigger(u16);
        virtual bool ShouldRandomize() const;
        virtual f32 Randomize();
        virtual void CopyArchProperties(const FuseAction&);

        /* 1 */ f32 triggerTime;
        /* 2 */ f32 triggerUntil;
        /* 3 */ Archetype::FuseIgnitionList* arch;
        /* 4 */ bool isTriggered;
        st6::vector<u16> sIdVector;
};
struct FuseHardpointPositionOffset
{
        char* hardpoint;
        Transform offset;
};

class StartEffectAction : public FuseAction
{
        /* 9 */ void* clientIObj;
        /* 10 */ ID_String hash;
        /* 11 */ bool attached;
        /* 12 */ unsigned unknown; // possibly unused
        /* 13 */ st6::vector<FuseHardpointPositionOffset> posOffsets;
        /* 17-20 */ unsigned dunno2[4]; // possibly unused
};

class FuseDB
{
    public:
        IMPORT FuseDB& operator=(const FuseDB&);
        IMPORT static void AddFuseINIFile(const char*);
        IMPORT static void Shutdown();

    protected:
        typedef TString<260> TString260;
        IMPORT static st6::list<TString260> m_FuseINIFiles;

    public:
        u8 data[OBJECT_DATA_SIZE];
};

struct AleEffect
{
    struct AlchemyEmitter
    {
            virtual void* __stdcall dunno0();
            virtual void* __stdcall dunno4();
            virtual void* __stdcall dunno8();
            virtual void* __stdcall dunnoC();
            virtual void* __stdcall dunno10();
            virtual void* __stdcall dunno14();
            virtual void* __stdcall dunno18();
            virtual void* __stdcall dunno1C();
            virtual void* __stdcall dunno20();
            virtual void* __stdcall dunno24();
            virtual void* __stdcall dunno28();
            virtual void* __stdcall dunno2C();
            virtual void* __stdcall dunno30();
            virtual void* __stdcall dunno34();
            virtual void* __stdcall dunno38();
            virtual void* __stdcall dunno3C();
            virtual void* __stdcall dunno40();
            virtual void* __stdcall dunno44();
            virtual void* __stdcall dunno48();
            virtual void* __stdcall dunno4C();
            virtual void* __stdcall dunno50();
            virtual void* __stdcall dunno54();
            virtual void* __stdcall dunno58();
            virtual void* __stdcall SetKeyframe(f32);
    };

    struct AlchemyEffect
    {
            virtual void* __stdcall dunno0();
            virtual void* __stdcall dunno4();
            virtual void* __stdcall dunno8();
            virtual void* __stdcall dunnoC();
            virtual void* __stdcall dunno10();
            virtual void* __stdcall dunno14();
            virtual int __stdcall   SetKeyframe(f32);

            int dunno;
            st6::vector<AlchemyEmitter> emitters;
            unsigned dunno2[3];
    };

        virtual void Initialize(void* effectData);
        virtual void Cleanup();
        virtual void fdunno2();
        virtual void SetKeyframe(f32);
        virtual bool nulloptTrue();
        virtual void fdunno5();
        virtual void LoadAlchemy(f32, void*);
        virtual void fdunno7();
        virtual void* Deallocate();
        virtual int SetIntensity2(f32);

        void* ptrdunno;
        unsigned dunno;
        f32 fDunno1;
        Transform offset;
        long index;
        unsigned dunno2[8];
        void* unkMapIter;
        void* effectInfo;
        AlchemyEffect* alchemy;
        void* alchemy2dunno;
        f32 fDunno2;
        f32 lifetime;
        unsigned dunno3;
        f32 fDunno3;
};