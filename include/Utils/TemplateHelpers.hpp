// ReSharper disable CppClangTidyClangDiagnosticReturnStackAddress
#pragma once

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

template <typename>
constexpr bool IsOptional = false;
template <typename T>
constexpr bool IsOptional<std::optional<T>> = true;
template <typename T>
constexpr bool IsOptionalV = IsOptional<std::remove_cvref_t<T>>;

template <typename T>
struct MemberFunctionClassType;

template <typename M, typename T>
struct MemberFunctionClassType<M T::*>
{
        using type = T;
};

template <typename R, typename... Args>
struct [[maybe_unused]] MemberFunctionReturnType;

template <class Class, typename R, typename... Args>
struct [[maybe_unused]] MemberFunctionReturnType<R (Class::*)(Args...)>
{
        using type = R;
};

template <typename T, typename... Ts>
struct IsAnyOf : std::bool_constant<(std::is_same<T, Ts>{} || ...)>
{};

template<typename Test, template<typename...> class Ref>
struct IsSpecialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct IsSpecialization<Ref<Args...>, Ref>: std::true_type {};