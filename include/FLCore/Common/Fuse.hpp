#pragma once
#include "../FLCoreDefs.hpp"

class INI_Reader;

class Fuse
{
    public:
        IMPORT Fuse(const ID_String&, float);
        IMPORT Fuse(const Fuse&);
        IMPORT virtual ~Fuse();
        IMPORT Fuse& operator=(const Fuse&);
        IMPORT int ActionCount() const;
        IMPORT void Burn(float);
        IMPORT virtual void FreeActions();
        IMPORT bool IgniteAt(unsigned int, unsigned short, float);
        IMPORT bool IsBurning() const;
        IMPORT bool IsDeathFuse() const;
        IMPORT bool IsSpent() const;
        IMPORT bool IsSpentAt(float) const;
        IMPORT float Lifetime() const;
        IMPORT void Load() const;
        IMPORT const ID_String& Name() const;
        IMPORT bool OverrideLifetime(float);
        IMPORT void RandomizeActions();
        IMPORT bool UnBurn(unsigned short, float);
        IMPORT void UnLoad() const;

    protected:
        IMPORT bool ReadFuseValues(INI_Reader&);

    public:
        /* 1  */ uint archId;
        /* 2  */ float defaultLifetime;
        /* 3  */ bool deathFuse;
        bool align[3];
        /* 4  */ bool dunno2;
        bool dunno3;
        /* 5  */ void* dunno4; // 0x18 size struct
        /* 6  */ void* dunno5; // 0x18 size struct
        /* 7  */ uint dunno6;
        /* 8  */ uint actionCount;
        /* 9  */ bool dunno8;
        bool align2[3];
        /* 10 */ bool dunno9;
        /* 11 */ void* dunno10; // 0x1C size struct, used in isSpentAt
        /* 12 */ uint dunno11;  // isBurning
};

class FuseAction
{
    public:
        IMPORT FuseAction(const FuseAction&);
        IMPORT FuseAction();
        IMPORT FuseAction& operator=(const FuseAction&);
        IMPORT float GetTriggerTime() const;
        IMPORT bool ReadFuseActionValue(INI_Reader&);

        virtual ~FuseAction();
        virtual FuseAction ResetAndCopyArch();
        virtual int Load();
        virtual int UnLoad();
        virtual bool IsTriggered(unsigned short) const;
        virtual bool IsTriggered() const;
        virtual void Trigger(unsigned int, unsigned short);
        virtual void UnTrigger(unsigned short);
        virtual bool ShouldRandomize() const;
        virtual float Randomize();
        virtual void CopyArchProperties(const FuseAction&);

        /* 1 */ float triggerTime;
        /* 2 */ float triggerUntil;
        /* 3 */ Archetype::FuseIgnitionList* arch;
        /* 4 */ bool isTriggered;
        st6::vector<ushort> sIdVector;
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
        /* 12 */ uint unknown; // possibly unused
        /* 13 */ st6::vector<FuseHardpointPositionOffset> posOffsets;
        /* 17-20 */ uint dunno2[4]; // possibly unused
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
        unsigned char data[OBJECT_DATA_SIZE];
};