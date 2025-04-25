#pragma once
#include <chrono>
#include <string>

template <typename T>
concept StringRestriction = std::is_same_v<std::string, T> || std::is_same_v<std::wstring, T>;

template <typename T>
concept IsStringView = std::is_same_v<std::string_view, T> || std::is_same_v<std::wstring_view, T>;

template <typename T>
concept IsString = std::is_same_v<std::string_view, T> || std::is_same_v<std::string, T>;

template <typename T>
concept IsWString = std::is_same_v<std::wstring_view, T> || std::is_same_v<std::wstring, T>;

template <typename... T>
concept AtLeastOne = sizeof...(T) > 0;

template <typename T>
concept IsNumeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <typename T>
concept IsSignedIntegral = std::is_integral_v<T> && std::is_signed_v<T>;

template <typename T>
concept IsUnsignedIntegral = std::is_integral_v<T> && !std::is_signed_v<T>;

template <typename Base, typename Derived>
concept IsDerivedFrom = std::derived_from<Derived, Base>;

template <typename Base, typename Derived>
concept IsBaseOf = std::is_base_of_v<Base, Derived>;

template <typename T, typename TT>
concept IsSameAs = std::is_same_v<T, TT>;

template <class T, class InnerType>
concept IsConvertibleRangeOf = requires(T&& t) {
    requires std::convertible_to<std::remove_cvref_t<decltype(*std::ranges::begin(t))>, InnerType>;
    std::ranges::end(t);
};

template <typename T>
concept RequireParamterlessConstructor = std::is_default_constructible_v<T>;

template <class _Tp>
struct IsChronoDuration : std::false_type
{};

template <class _Rep, class _Period>
struct IsChronoDuration<std::chrono::duration<_Rep, _Period>> : std::true_type
{};

template <typename _Tp>
concept IsChronoDurationV = IsChronoDuration<_Tp>::value;
