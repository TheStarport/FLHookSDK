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
