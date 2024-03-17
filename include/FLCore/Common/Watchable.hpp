#pragma once
#include "FLCore/FLCoreDefs.hpp"

// Basically this forms a linked list between BaseWatchers all pointing to the same Watchable object.
// The Watchable object points to the last BaseWatcher which added it
struct IMPORT BaseWatcher
{
    BaseWatcher();
    ~BaseWatcher();
    BaseWatcher& operator=(const BaseWatcher&);
    void set(const struct Watchable*);

    protected:
    void set_pointer(const Watchable*);

    public:
    Watchable* watchable;
    BaseWatcher* nextBaseWatcher;
};

// The newestBaseWatcher pointer seems sometimes to be used with the address it points to -8 bytes to get the object
// This indicates it is probably some compiler construct
struct IMPORT Watchable
{
    Watchable();
    ~Watchable();
    Watchable& operator=(const Watchable&);
    unsigned int unwatch();

    public:
    BaseWatcher* newestBaseWatcher; // The last basewatcher set to watch this
};