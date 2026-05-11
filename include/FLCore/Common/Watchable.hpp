#pragma once

#include "../FLCoreDefs.hpp"

struct IObjRW;
struct CObject;

// Basically this forms a linked list between BaseWatchers all pointing to the same Watchable object.
// The Watchable object points to the last BaseWatcher which added it
struct BaseWatcher
{
    IMPORT BaseWatcher();
    IMPORT ~BaseWatcher();
    IMPORT BaseWatcher& operator=(const BaseWatcher&);
    IMPORT void set(const struct Watchable*);

  protected:
    IMPORT void set_pointer(const Watchable*);

  public:
    Watchable* watchable;
    BaseWatcher* nextBaseWatcher;

    IObjRW* GetIObj() { return reinterpret_cast<IObjRW*>(reinterpret_cast<u32>(watchable) - 8); }
    CObject* GetCObject() { return *reinterpret_cast<CObject**>(reinterpret_cast<u32>(watchable) + 8); }
};

// The newestBaseWatcher pointer seems sometimes to be used with the address it points to -8 bytes to get the object
// This indicates it is probably some compiler construct
struct Watchable
{
    IMPORT Watchable();
    IMPORT ~Watchable();
    IMPORT Watchable& operator=(const Watchable&);
    IMPORT u32 unwatch();

  public:
    BaseWatcher* newestBaseWatcher; // The last basewatcher set to watch this
};
