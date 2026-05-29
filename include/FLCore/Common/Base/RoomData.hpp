#pragma once

#include "../../FLCoreDefs.hpp"
#include "../INI_Reader.hpp"

class HardpointSummary;
class Csys;

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
    void add_set_script_Prop(const char*, const char*, int, const Csys&, bool, bool, bool, bool, u8,
                             signed char, ulong, const char*, ulong, bool);
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
