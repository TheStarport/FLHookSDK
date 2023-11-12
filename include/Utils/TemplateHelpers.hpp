// ReSharper disable CppClangTidyClangDiagnosticReturnStackAddress
#pragma once

template <typename... Args>
auto CreateTuple(std::vector<std::wstring>& arguments)
{
    return CreateTupleImpl<Args...>(std::index_sequence_for<Args...>{}, arguments);
}

template <typename F, F f>
class ClassFunctionWrapper;

template <class Ret, class Cl, class... Args, Ret (Cl::*func)(Args...)>
class ClassFunctionWrapper<Ret (Cl::*)(Args...), func>
{
    public:
        static Ret ProcessParam(Cl* cl, std::vector<std::wstring>& params)
        {
            auto arg = CreateTuple<Args...>(params);
            auto lambda = std::function<Ret(Args...)>{ [=](Args... args) mutable { return (cl->*func)(args...); } };
            return std::apply(lambda, arg);
        }
};

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
