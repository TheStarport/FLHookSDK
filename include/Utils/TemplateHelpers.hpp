// ReSharper disable CppClangTidyClangDiagnosticReturnStackAddress
#pragma once

#include <type_traits>
#include <optional>
#include <tuple>

template <typename T>
struct first_template_type;

template <template <typename T, typename...> class t, typename T, typename... Args>
struct first_template_type<t<T, Args...>>
{
        typedef T type;
};

template <typename T>
using FirstTemplateType = typename first_template_type<T>::type;

template <std::size_t I, typename... Ts>
using NthType = std::tuple_element_t<I, std::tuple<Ts...>>;

template <typename T, typename Tuple>
struct TupleHasType;

template <typename T>
struct TupleHasType<T, std::tuple<>> : std::false_type
{};

template <typename T, typename U, typename... Ts>
struct TupleHasType<T, std::tuple<U, Ts...>> : TupleHasType<T, std::tuple<Ts...>>
{};

template <typename T, typename... Ts>
struct TupleHasType<T, std::tuple<T, Ts...>> : std::true_type
{};

template <template <typename> class Meta, typename Tuple>
struct tuple_map;

template <template <typename> class Meta, typename... Ts>
struct tuple_map<Meta, std::tuple<Ts...>>
{
        using type = std::tuple<Meta<Ts>...>;
};

template <template <typename> class Meta, typename Tuple>
using tuple_map_t = typename tuple_map<Meta, Tuple>::type;

template <typename Tuple, typename T>
constexpr bool TupleHasTypeV = TupleHasType<T, Tuple>::value;

template <typename>
constexpr bool IsOptional = false;
template <typename T>
constexpr bool IsOptional<std::optional<T>> = true;
template <typename T>
constexpr bool IsOptionalV = IsOptional<std::remove_cvref_t<T>>;

template <typename T>
struct member_fn_traits;

template <typename R, typename C, typename... Params>
struct member_fn_traits<R (C::*)(Params...)>
{
        using return_type = R;
        using class_type = std::remove_const_t<C>;
        using params = std::tuple<Params...>;
};

template <typename R, typename C, typename... Ps>
struct member_fn_traits<R (C::*)(Ps...) const> : member_fn_traits<R (C::*)(Ps...)>
{};

template <typename T>
using member_fn_ct = member_fn_traits<T>::class_type;
template <typename T>
using member_fn_rt = member_fn_traits<T>::return_type;
template <typename T>
using member_fn_pt = member_fn_traits<T>::params;

template <typename... Ts>
using remove_cvref_pack_t = std::tuple<std::remove_cvref_t<Ts>...>;

template <typename Tuple>
struct tuple_tail_impl;

template <typename First, typename... Rest>
struct tuple_tail_impl<std::tuple<First, Rest...>>
{
        using type = std::tuple<Rest...>;
};

template <typename Tuple>
using tuple_tail_t = tuple_tail_impl<std::remove_cvref_t<Tuple>>::type;

template <typename T, typename... Ts>
struct IsAnyOf : std::bool_constant<(std::is_same<T, Ts>{} || ...)>
{};

template <typename Test, template <typename...> class Ref>
struct IsSpecialization : std::false_type
{};

template <template <typename...> class Ref, typename... Args>
struct IsSpecialization<Ref<Args...>, Ref> : std::true_type
{};
