// ReSharper disable CppCStyleCast
#pragma once

#include "EqObj.hpp"

#include <Utils/TemplateHelpers.hpp>
#include <Concepts.hpp>

template <auto FuncPtr>
struct IObjVTableIndex;

#define MAP_MEMBER(fn, val)               \
    template <>                           \
    struct IObjVTableIndex<fn>            \
    {                                     \
        static constexpr u32 value = val; \
    }
#define M_CAST(fn, type, val) MAP_MEMBER(type fn, val)

template <auto FuncPtr>
inline constexpr unsigned IObjVTableIndex_v = IObjVTableIndex<FuncPtr>::value;

MAP_MEMBER(&IObjInspectImpl::get_position, 0x06D5FEF4);
MAP_MEMBER(&IObjInspectImpl::get_velocity, 0x06D5FEE);
MAP_MEMBER(&IObjInspectImpl::get_angular_velocity, 0x06D5FEE8);
MAP_MEMBER(&IObjInspectImpl::get_orientation, 0x06D5FEE2);
MAP_MEMBER(&IObjInspectImpl::get_transform, 0x06D5FEDC);
MAP_MEMBER(&IObjInspectImpl::get_center_of_mass, 0x06D5FED6);
MAP_MEMBER(&IObjInspectImpl::get_sub_obj_center_of_mass, 0x06D5FED0);
MAP_MEMBER(&IObjInspectImpl::get_index, 0x06D5FECA);
MAP_MEMBER(&IObjInspectImpl::get_good_id, 0x06D5FEC4);
MAP_MEMBER(&IObjInspectImpl::get_archetype_extents, 0x06D5FEBE);
MAP_MEMBER(&IObjInspectImpl::get_physical_radius, 0x06D5FEB8);
MAP_MEMBER(&IObjInspectImpl::get_mass, 0x06D5FEB2);
MAP_MEMBER(&IObjInspectImpl::is_targetable, 0x06D5FEAC);
MAP_MEMBER(&IObjInspectImpl::is_dying, 0x06D5FEA6);
M_CAST(&IObjInspectImpl::get_status, (int (IObjInspectImpl::*)(f32&) const), 0x06D5FEA0);
M_CAST(&IObjInspectImpl::get_status, (int (IObjInspectImpl::*)(f32&, f32&) const), 0x06D5FE9A);
M_CAST(&IObjInspectImpl::get_shield_status, (int (IObjInspectImpl::*)(f32&, f32&, bool&) const), 0x06D5FE94);
M_CAST(&IObjInspectImpl::get_shield_status, (int (IObjInspectImpl::*)(f32&, bool&) const), 0x06D5FE8E);
MAP_MEMBER(&IObjInspectImpl::get_throttle, 0x06D5FE88);
MAP_MEMBER(&IObjInspectImpl::get_axis_throttle, 0x06D5FE82);
MAP_MEMBER(&IObjInspectImpl::get_nudge_vec, 0x06D5FE7C);
MAP_MEMBER(&IObjInspectImpl::get_strafe_dir, 0x06D5FE76);
M_CAST(&IObjInspectImpl::is_cruise_active, (int (IObjInspectImpl::*)(bool&) const), 0x06D5FE6A);
M_CAST(&IObjInspectImpl::is_cruise_active, (int (IObjInspectImpl::*)(bool&, bool&) const), 0x06D5FE70);
MAP_MEMBER(&IObjInspectImpl::are_thrusters_active, 0x06D5FE64);
MAP_MEMBER(&IObjInspectImpl::get_attitude_towards, 0x06D5FE5E);
MAP_MEMBER(&IObjInspectImpl::get_attitude_towards_symmetrical, 0x06D5FE58);
MAP_MEMBER(&IObjInspectImpl::get_reputation, 0x06D5FE52);
MAP_MEMBER(&IObjInspectImpl::get_target, 0x06D5FE4C);
MAP_MEMBER(&IObjInspectImpl::get_subtarget, 0x06D5FE46);
MAP_MEMBER(&IObjInspectImpl::get_subtarget_center_of_mass, 0x06D5FE40);
MAP_MEMBER(&IObjInspectImpl::get_rank, 0x06D5FE3A);
MAP_MEMBER(&IObjInspectImpl::get_affiliation, 0x06D5FE34);
MAP_MEMBER(&IObjInspectImpl::get_type, 0x06D5FE2E);
MAP_MEMBER(&IObjInspectImpl::get_base, 0x06D5FE28);
MAP_MEMBER(&IObjInspectImpl::get_dock_target, 0x06D5FE22);
MAP_MEMBER(&IObjInspectImpl::get_power, 0x06D5FE1C);
MAP_MEMBER(&IObjInspectImpl::get_zone_props, 0x06D5FE16);
MAP_MEMBER(&IObjInspectImpl::get_scanner_interference, 0x06D5FE10);
MAP_MEMBER(&IObjInspectImpl::get_hold_left, 0x06D5FE0A);
MAP_MEMBER(&IObjInspectImpl::enumerate_cargo, 0x06D5FE04);
MAP_MEMBER(&IObjInspectImpl::get_data, 0x06D5FDFE);
MAP_MEMBER(&IObjInspectImpl::get_formation_offset, 0x06D5FDF8);
MAP_MEMBER(&IObjInspectImpl::get_formation_leader, 0x06D5FDF2);
MAP_MEMBER(&IObjInspectImpl::get_follow_offset, 0x06D5FDEC);
MAP_MEMBER(&IObjInspectImpl::get_follow_leader, 0x06D5FDE6);
MAP_MEMBER(&IObjInspectImpl::is_player, 0x06D5FDE0);
MAP_MEMBER(&IObjInspectImpl::get_hardpoint, 0x06D5FDDA);
MAP_MEMBER(&IObjInspectImpl::has_dock_hardpoints, 0x06D5FDD4);
MAP_MEMBER(&IObjInspectImpl::get_dock_hardpoints, 0x06D5FDCE);
MAP_MEMBER(&IObjInspectImpl::get_time_to_accelerate, 0x06D5FDC8);
MAP_MEMBER(&IObjInspectImpl::get_distance_travelled, 0x06D5FDC2);
MAP_MEMBER(&IObjInspectImpl::get_projected_throttle, 0x06D5FDBC);
MAP_MEMBER(&IObjInspectImpl::get_speed, 0x06D5FDB6);
MAP_MEMBER(&IObjInspectImpl::get_initial_speed_to_coast_distance, 0x06D5FDB0);
M_CAST(&IObjInspectImpl::get_time_to_accelerate_angularly, (f32 (IObjInspectImpl::*)(f32, f32, f32) const), 0x06D5FDAA);
M_CAST(&IObjInspectImpl::get_time_to_accelerate_angularly, (f32 (IObjInspectImpl::*)(f32, f32, f32, f32) const), 0x06D5FDA4);
M_CAST(&IObjInspectImpl::get_angular_distance_travelled, (f32 (IObjInspectImpl::*)(f32, f32, f32) const), 0x06D5FD9E);
M_CAST(&IObjInspectImpl::get_angular_distance_travelled, (f32 (IObjInspectImpl::*)(f32, f32, f32, f32) const), 0x06D5FD98);
MAP_MEMBER(&IObjInspectImpl::get_angular_speed_XY, 0x06D5FD92);
MAP_MEMBER(&IObjInspectImpl::get_angular_speed_Z, 0x06D5FD8C);
MAP_MEMBER(&IObjInspectImpl::get_projected_axis_throttle_XY, 0x06D5FD86);
MAP_MEMBER(&IObjInspectImpl::get_projected_axis_throttle_Z, 0x06D5FD80);
MAP_MEMBER(&IObjInspectImpl::get_max_bank_angle, 0x06D5FD7A);
MAP_MEMBER(&IObjInspectImpl::get_scanlist, 0x06D5FD74);
MAP_MEMBER(&IObjInspectImpl::get_tgt_lead_fire_pos, 0x06D5FD6E);
MAP_MEMBER(&IObjInspectImpl::is_pointing_at, 0x06D5FD68);
MAP_MEMBER(&IObjInspectImpl::can_point_at, 0x06D5FD62);
MAP_MEMBER(&IObjInspectImpl::find_equipment, 0x06D5FD5C);
MAP_MEMBER(&IObjInspectImpl::get_equipment_status, 0x06D5FD56);
MAP_MEMBER(&IObjInspectImpl::get_equipment_val, 0x06D5FD50);
MAP_MEMBER(&IObjInspectImpl::scan_cargo, 0x06D5FD4A);
MAP_MEMBER(&IObjInspectImpl::enumerate_subtargets, 0x06D5FD44);
MAP_MEMBER(&IObjInspectImpl::get_lane_direction, 0x06D5FD3E);
MAP_MEMBER(&IObjInspectImpl::get_ring_side, 0x06D5FD38);
MAP_MEMBER(&IObjInspectImpl::traverse_rings, 0x06D5FD32);
MAP_MEMBER(&IObjInspectImpl::is_using_tradelane, 0x06D5FD2C);
MAP_MEMBER(&IObjInspectImpl::get_lane_start, 0x06D5FD26);
MAP_MEMBER(&IObjInspectImpl::generate_follow_offset, 0x06D5FD20);
MAP_MEMBER(&IObjInspectImpl::get_atmosphere_range, 0x06D5FD1A);
MAP_MEMBER(&IObjInspectImpl::get_toughness, 0x06D5FD14);
MAP_MEMBER(&IObjInspectImpl::get_behavior_id, 0x06D5FD0E);
MAP_MEMBER(&IObjInspectImpl::get_formation_followers, 0x06D5FD08);
MAP_MEMBER(&IObjInspectImpl::cobject, 0x06D5FD02);

MAP_MEMBER(&IObjRW::get_object_type, 0x6CE61F0);
MAP_MEMBER(&IObjRW::ObjectDestroyed, 0x6CE63F0);
MAP_MEMBER(&IObjRW::Disconnect, 0x6CEE670);
MAP_MEMBER(&IObjRW::get_dunno_0x40, 0x6CEE6D0);
MAP_MEMBER(&IObjRW::InstantiateCobject, 0x6CE6200);
MAP_MEMBER(&IObjRW::SetCObjectById, 0x6D02CB0);
MAP_MEMBER(&IObjRW::Update, 0x6CE6280);
MAP_MEMBER(&IObjRW::sub_6D01A60, 0x6CEE6E0);
MAP_MEMBER(&IObjRW::sub_6CEE810, 0x6CEE810);
MAP_MEMBER(&IObjRW::sub_6CEE980, 0x6CEE980);
MAP_MEMBER(&IObjRW::sub_6CE9250, 0x6CF4230);
MAP_MEMBER(&IObjRW::process_munition_impact, 0x6CF4230);
MAP_MEMBER(&IObjRW::process_all_explosion_damage, 0x6CEEB80);
MAP_MEMBER(&IObjRW::apply_damage_list, 0x6CEEE70);
MAP_MEMBER(&IObjRW::get_dunno_0x41, 0x6CE6190);
MAP_MEMBER(&IObjRW::sub_6CEEFA0, 0x6CEEFA0);
MAP_MEMBER(&IObjRW::sub_6CEF0F0, 0x6CEF0F0);
MAP_MEMBER(&IObjRW::is_player_vulnerable, 0x06CE61A0);
MAP_MEMBER(&IObjRW::is_invulnerable, 0x6CE61B0);
MAP_MEMBER(&IObjRW::get_max_hp_loss, 0x6CE61C0);
MAP_MEMBER(&IObjRW::process_collision_unk, 0x6CEE9F0);
MAP_MEMBER(&IObjRW::sethp_unk, 0x6CEEE20);
MAP_MEMBER(&IObjRW::set_relative_health, 0x6CEF1E0);
MAP_MEMBER(&IObjRW::damage_hull, 0x6CEEC90);
MAP_MEMBER(&IObjRW::apply_damage_entry, 0x6CEEF70);
MAP_MEMBER(&IObjRW::can_deal_damage, 0x6CEF0B0);

#undef MAP_MEMBER
#undef M_CAST

template <auto FuncPtr>
u32 FetchIObjVTableAddress(u32 serverDllAddr)
{
    return serverDllAddr + (IObjVTableIndex_v<FuncPtr> - 0x6CE0000);
}

template <auto FuncPtr, typename CurIObjType, typename FuncPtrT = decltype(FuncPtr), typename ClsType = member_fn_ct<FuncPtrT>,
          typename Ret = member_fn_rt<FuncPtrT>, typename... Args>
    requires std::is_base_of_v<ClsType, CurIObjType> && (std::is_same_v<IObjInspectImpl, ClsType> || std::is_same_v<IObjRW, ClsType>) &&
             PackMatchesTuple<member_fn_pt<FuncPtrT>, Args...>
Ret CallSpecificVTable(const u32 serverDllAddr, CurIObjType* obj, Args... args)
{
    // Convert to a free function to get around forbidden ptr casts
    using FreeFuncType = Ret(__thiscall*)(ClsType*, Args...);

    auto addr = FetchIObjVTableAddress<FuncPtr>(serverDllAddr);
    auto target = reinterpret_cast<FreeFuncType>(addr);

    if constexpr (std::is_same_v<Ret, void>)
    {
        target(obj, args...);
        return void();
    }
    else
    {
        return target(obj, args...);
    }
}

#define CALL_IOBJ_VTABLE(func, serverAddr, obj, ...) CallSpecificVTable<&func>(serverAddr, obj, ##__VA_ARGS__)
