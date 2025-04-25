// ReSharper disable CppClangTidyClangDiagnosticReturnStackAddress
#pragma once

template <typename T>
struct first_template_type;

template <template <typename T, typename...> class t, typename T, typename... Args>
struct first_template_type<t<T, Args...>>
{
        typedef T Type;
};

template <typename T>
using FirstTemplateType = typename first_template_type<T>::Type;

template <typename T>
struct MemberFunctionPointerClassType;

template <typename M, typename T>
struct MemberFunctionPointerClassType<M T::*>
{
        using type = T;
};
