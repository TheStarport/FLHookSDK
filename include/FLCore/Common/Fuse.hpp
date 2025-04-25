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

        unsigned char data[OBJECT_DATA_SIZE];
};

class FuseAction
{
    public:
        IMPORT FuseAction(const FuseAction&);
        IMPORT FuseAction();
        IMPORT virtual ~FuseAction();
        IMPORT FuseAction& operator=(const FuseAction&);
        IMPORT float GetTriggerTime() const;
        IMPORT virtual bool IsTriggered(unsigned short) const;
        IMPORT virtual bool IsTriggered() const;
        IMPORT virtual int Load();
        IMPORT virtual float Randomize();
        IMPORT virtual bool ShouldRandomize() const;
        IMPORT virtual void Trigger(unsigned int, unsigned short);
        IMPORT virtual int UnLoad();
        IMPORT virtual void UnTrigger(unsigned short);

    protected:
        IMPORT virtual void CopyArchProperties(const FuseAction&);
        IMPORT bool ReadFuseActionValue(INI_Reader&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
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