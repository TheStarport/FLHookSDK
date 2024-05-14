#pragma once
#include "../FLCoreDefs.hpp"

struct FmtStr
{
        struct IMPORT Val
        {
                Val(const Val&);
                Val(unsigned short, void*, unsigned char);
                Val(const void*);
                Val(const void*, int&);
                ~Val();
                const Val& operator=(const Val&);
                bool operator==(const Val&) const;
                uint flatten(void*, unsigned int) const;
                uint get_flattened_size() const;

                static void* operator new(unsigned int);
                static void operator delete(void*);

            private:
                int InitFromVoid(const void*);

            public:
                uint dunno;
                uint dunno2;
                wchar_t dunno3;
                uchar dunno4;
        };

        FmtStr() : FmtStr(0, nullptr) {}
        IMPORT FmtStr(const FmtStr&);
        IMPORT FmtStr(unsigned int, const Val*);
        IMPORT ~FmtStr();
        IMPORT const FmtStr& operator=(const FmtStr&);
        IMPORT bool operator==(const FmtStr&) const;
        IMPORT void append(Val*);
        IMPORT void append_base(const unsigned int&);
        IMPORT void append_fmt_str(const FmtStr&);
        IMPORT void append_good(const unsigned int&);
        IMPORT void append_installation(int);
        IMPORT void append_int(unsigned int);
        IMPORT void append_loot(int);
        IMPORT void append_nav_marker(const struct NavMarker&);
        IMPORT void append_rep_group(const unsigned int&);
        IMPORT void append_rep_instance(const int&);
        IMPORT void append_spaceobj_id(const unsigned int&);
        IMPORT void append_string(unsigned int);
        IMPORT void append_system(const unsigned int&);
        IMPORT int append_void(void*);
        IMPORT void append_zone_id(const unsigned int&);
        IMPORT void begin_mad_lib(unsigned int);
        IMPORT void destroy();
        IMPORT void end_mad_lib();
        IMPORT int flatten(void*, unsigned int) const;
        IMPORT int unflatten(void*, unsigned int);

        uint something;
        uint strid;        // resource containing text
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
