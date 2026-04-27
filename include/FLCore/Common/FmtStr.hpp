#pragma once
#include "../FLCoreDefs.hpp"

struct FmtStr
{
        struct IMPORT Val
        {
                Val(const Val&);
                Val(u16, void*, u8);
                Val(const void*);
                Val(const void*, int&);
                ~Val();
                const Val& operator=(const Val&);
                bool operator==(const Val&) const;
                unsigned flatten(void*, u32) const;
                unsigned get_flattened_size() const;

                static void* operator new(u32);
                static void operator delete(void*);

            private:
                int InitFromVoid(const void*);

            public:
                unsigned dunno;
                unsigned dunno2;
                wchar_t dunno3;
                uchar dunno4;
        };

        FmtStr() : FmtStr(0, nullptr) {}
        IMPORT FmtStr(const FmtStr&);
        IMPORT FmtStr(u32, const Val*);
        IMPORT ~FmtStr();
        IMPORT const FmtStr& operator=(const FmtStr&);
        IMPORT bool operator==(const FmtStr&) const;
        IMPORT void append(Val*);
        IMPORT void append_base(const u32&);
        IMPORT void append_fmt_str(const FmtStr&);
        IMPORT void append_good(const u32&);
        IMPORT void append_installation(int);
        IMPORT void append_int(u32);
        IMPORT void append_loot(int);
        IMPORT void append_nav_marker(const struct NavMarker&);
        IMPORT void append_rep_group(const u32&);
        IMPORT void append_rep_instance(const int&);
        IMPORT void append_spaceobj_id(const u32&);
        IMPORT void append_string(u32);
        IMPORT void append_system(const u32&);
        IMPORT int append_void(void*);
        IMPORT void append_zone_id(const u32&);
        IMPORT void begin_mad_lib(u32);
        IMPORT void destroy();
        IMPORT void end_mad_lib();
        IMPORT int flatten(void*, u32) const;
        IMPORT int unflatten(void*, u32);

        unsigned something;
        unsigned strid;        // resource containing text
        uchar tnav_marker; // counters for each type
        uchar tsystem;
        uchar tbase;
        uchar tstring;
        uchar tgood;
        uchar tunused;
        uchar tint;
        uchar trep_instance;
        uchar trep_group;
        uchar tzone_id;
        uchar tspace_obj_id;
        uchar tfmt_str;
        uchar tinstallation;
        uchar tloot;
};
