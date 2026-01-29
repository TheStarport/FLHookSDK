#pragma once

#include <ranges>
#include <cwctype>

#include "Concepts.hpp"

enum class MessageColor
{
    Default = 0x00FF00,
    SystemBlue = 0x84C6E6,
    DeathMessage = 0x1919BD,
    DeathMessageRed = 0xBF1D1D,
    GroupMessagePink = 0xFF7BFF,
    PrivateGreen = 0x3ABD19,

    AliceBlue = 0xF0F8FF,
    AntiqueWhite = 0xFAEBD7,
    Aqua = 0x00FFFF,
    Aquamarine = 0x7FFFD4,
    Azure = 0xF0FFFF,
    Beige = 0xF5F5DC,
    Bisque = 0xFFE4C4,
    Black = 0x000000,
    BlanchedAlmond = 0xFFEBCD,
    Blue = 0x0000FF,
    BlueViolet = 0x8A2BE2,
    Brown = 0xA52A2A,
    BurlyWood = 0xDEB887,
    CadetBlue = 0x5F9EA0,
    Chartreuse = 0x7FFF00,
    Chocolate = 0xD2691E,
    Coral = 0xFF7F50,
    CornflowerBlue = 0x6495ED,
    Cornsilk = 0xFFF8DC,
    Crimson = 0xDC143C,
    Cyan = 0x00FFFF,
    DarkBlue = 0x00008B,
    DarkCyan = 0x008B8B,
    DarkGoldenrod = 0xB8860B,
    DarkGray = 0xA9A9A9,
    DarkGreen = 0x006400,
    DarkKhaki = 0xBDB76B,
    DarkMagenta = 0x8B008B,
    DarkOliveGreen = 0x556B2F,
    DarkOrange = 0xFF8C00,
    DarkOrchid = 0x9932CC,
    DarkRed = 0x8B0000,
    DarkSalmon = 0xE9967A,
    DarkSeaGreen = 0x8FBC8F,
    DarkSlateBlue = 0x483D8B,
    DarkSlateGray = 0x2F4F4F,
    DarkTurquoise = 0x00CED1,
    DarkViolet = 0x9400D3,
    DeepPink = 0xFF1493,
    DeepSkyBlue = 0x00BFFF,
    DimGray = 0x696969,
    DodgerBlue = 0x1E90FF,
    Firebrick = 0xB22222,
    FloralWhite = 0xFFFAF0,
    ForestGreen = 0x228B22,
    Fuchsia = 0xFF00FF,
    Gainsboro = 0xDCDCDC,
    GhostWhite = 0xF8F8FF,
    Gold = 0xFFD700,
    Goldenrod = 0xDAA520,
    Gray = 0x808080,
    Green = 0x008000,
    GreenYellow = 0xADFF2F,
    Honeydew = 0xF0FFF0,
    HotPink = 0xFF69B4,
    IndianRed = 0xCD5C5C,
    Indigo = 0x4B0082,
    Ivory = 0xFFFFF0,
    Khaki = 0xF0E68C,
    Lavender = 0xE6E6FA,
    LavenderBlush = 0xFFF0F5,
    LawnGreen = 0x7CFC00,
    LemonChiffon = 0xFFFACD,
    LightBlue = 0xADD8E6,
    LightCoral = 0xF08080,
    LightCyan = 0xE0FFFF,
    LightGoldenrodYellow = 0xFAFAD2,
    LightGray = 0xD3D3D3,
    LightGreen = 0x90EE90,
    LightPink = 0xFFB6C1,
    LightSalmon = 0xFFA07A,
    LightSeaGreen = 0x20B2AA,
    LightSkyBlue = 0x87CEFA,
    LightSlateGray = 0x778899,
    LightSteelBlue = 0xB0C4DE,
    LightYellow = 0xFFFFE0,
    Lime = 0x00FF00,
    LimeGreen = 0x32CD32,
    Linen = 0xFAF0E6,
    Magenta = 0xFF00FF,
    Maroon = 0x800000,
    MediumAquamarine = 0x66CDAA,
    MediumBlue = 0x0000CD,
    MediumOrchid = 0xBA55D3,
    MediumPurple = 0x9370DB,
    MediumSeaGreen = 0x3CB371,
    MediumSlateBlue = 0x7B68EE,
    MediumSpringGreen = 0x00FA9A,
    MediumTurquoise = 0x48D1CC,
    MediumVioletRed = 0xC71585,
    MidnightBlue = 0x191970,
    MintCream = 0xF5FFFA,
    MistyRose = 0xFFE4E1,
    Moccasin = 0xFFE4B5,
    NavajoWhite = 0xFFDEAD,
    Navy = 0x000080,
    OldLace = 0xFDF5E6,
    Olive = 0x808000,
    OliveDrab = 0x6B8E23,
    Orange = 0xFFA500,
    OrangeRed = 0xFF4500,
    Orchid = 0xDA70D6,
    PaleGoldenrod = 0xEEE8AA,
    PaleGreen = 0x98FB98,
    PaleTurquoise = 0xAFEEEE,
    PaleVioletRed = 0xDB7093,
    PapayaWhip = 0xFFEFD5,
    PeachPuff = 0xFFDAB9,
    Peru = 0xCD853F,
    Pink = 0xFFC0CB,
    Plum = 0xDDA0DD,
    PowderBlue = 0xB0E0E6,
    Purple = 0x800080,
    Red = 0xFF0000,
    RosyBrown = 0xBC8F8F,
    RoyalBlue = 0x4169E1,
    SaddleBrown = 0x8B4513,
    Salmon = 0xFA8072,
    SandyBrown = 0xF4A460,
    SeaGreen = 0x2E8B57,
    SeaShell = 0xFFF5EE,
    Sienna = 0xA0522D,
    Silver = 0xC0C0C0,
    SkyBlue = 0x87CEEB,
    SlateBlue = 0x6A5ACD,
    SlateGray = 0x708090,
    Snow = 0xFFFAFA,
    SpringGreen = 0x00FF7F,
    SteelBlue = 0x4682B4,
    Tan = 0xD2B48C,
    Teal = 0x008080,
    Thistle = 0xD8BFD8,
    Tomato = 0xFF6347,
    Turquoise = 0x40E0D0,
    Violet = 0xEE82EE,
    Wheat = 0xF5DEB3,
    White = 0xFFFFFF,
    WhiteSmoke = 0xF5F5F5,
    Yellow = 0xFFFF00,
    YellowGreen = 0x9ACD32,
};

enum class MessageFormat
{
    Normal = 0x0,
    Bold = 0x1,
    Italic = 0x2,
    Underline = 0x4,
    Big = 0x8,
    BigAndWide = 0x10,
    VeryBig = 0x20,
    Smoothest = 0x40,
    Smoother = 0x80,
    Small = 0x90,

    BoldAndItalic = Bold | Italic,
    BoldAndItalicAndUnderline = Bold | Italic | Underline,
    BoldAndUnderline = Bold | Underline,
    ItalicAndUnderline = Italic | Underline,
    BigAndBold = Big | Bold,
};

struct StringHash
{
        using hash_type = std::hash<std::string_view>;
        using is_transparent = void;

        std::size_t operator()(const char* str) const { return hash_type{}(str); }
        std::size_t operator()(const std::string_view str) const { return hash_type{}(str); }
        std::size_t operator()(const std::string& str) const { return hash_type{}(str); }
};

struct WStringHash
{
        using hash_type = std::hash<std::wstring_view>;
        using is_transparent = void;

        std::size_t operator()(const wchar_t* str) const { return hash_type{}(str); }
        std::size_t operator()(const std::wstring_view str) const { return hash_type{}(str); }
        std::size_t operator()(const std::wstring& str) const { return hash_type{}(str); }
};

constexpr size_t Hash(const char* str)
{
    long long total = 0;
    long long current_multiplier = 1;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        constexpr long long m = 4294967291;
        constexpr long long p = 131;
        total = (total + current_multiplier * str[i]) % m;
        current_multiplier = current_multiplier * p % m;
    }
    return total;
}

class StringUtils
{
        // ReSharper disable CppExplicitSpecializationInNonNamespaceScope

        template <typename CharT,
                  typename C1 = std::conditional_t<IsStringView<CharT>, std::string_view, std::conditional_t<std::is_same_v<CharT, char>, char, const char*>>,
                  typename C2 =
                      std::conditional_t<IsStringView<CharT>, std::wstring_view, std::conditional_t<std::is_same_v<CharT, wchar_t>, wchar_t, const wchar_t*>>>
        static constexpr CharT NarrowOrWide(C1, C2);

        template <>
        static constexpr const char* NarrowOrWide<const char*>(const char* c, const wchar_t*)
        {
            return c;
        }

        template <>
        static constexpr wchar_t NarrowOrWide<wchar_t>(char, wchar_t w)
        {
            return w;
        }

        template <>
        static constexpr char NarrowOrWide<char>(char c, wchar_t)
        {
            return c;
        }

        template <>
        static constexpr const wchar_t* NarrowOrWide<const wchar_t*>(const char*, const wchar_t* w)
        {
            return w;
        }

        template <>
        static constexpr std::string_view NarrowOrWide<std::string_view>(std::string_view c, std::wstring_view)
        {
            // ReSharper disable once CppDFALocalValueEscapesFunction
            return { c };
        }

        template <>
        static constexpr std::wstring_view NarrowOrWide<std::wstring_view>(std::string_view, std::wstring_view w)
        {
            // ReSharper disable once CppDFALocalValueEscapesFunction
            return { w };
        }

#define TOWSTRING1(x)               L##x
#define TOWSTRING(x)                TOWSTRING1(x)
#define TOWSTRINGVIEW1(x)           L##x##sv
#define TOWSTRINGVIEW(x)            TOWSTRINGVIEW1(x)
#define NARROW_OR_WIDE(C, STR)      NarrowOrWide<C>((STR), TOWSTRING(STR))
#define NARROW_OR_WIDE_VIEW(C, STR) NarrowOrWide<C>((STR##sv), TOWSTRINGVIEW1(STR))

        static bool FuzzySearchRecursive(std::string_view pattern, std::string_view src, int& outScore, std::string_view strBegin, // NOLINT(*-no-recursion)
                                         const std::array<uint8_t, 256>* srcMatches, std::array<uint8_t, 256>& newMatches, int& nextMatch, int& recursionCount,
                                         int recursionLimit)
        {
            // Count recursions
            ++recursionCount;
            if (recursionCount >= recursionLimit)
            {
                return false;
            }

            // Detect end of strings
            if (pattern.empty() || src.empty())
            {
                return false;
            }

            // Recursion params
            bool recursiveMatch = false;
            std::array<uint8_t, 256> bestRecursiveMatches{};
            int bestRecursiveScore = 0;

            // Loop through pattern and str looking for a match
            bool firstMatch = true;
            while (!pattern.empty() && !src.empty())
            {
                // Found match
                if (tolower(pattern[0]) == tolower(src[0]))
                {
                    // Supplied matches buffer was too short
                    if (nextMatch >= newMatches.size())
                    {
                        return false;
                    }

                    // "Copy-on-Write" srcMatches into matches
                    if (firstMatch && srcMatches)
                    {
                        memcpy(newMatches.data(), srcMatches->data(), nextMatch);
                        firstMatch = false;
                    }

                    // Recursive call that "skips" this match
                    std::array<uint8_t, 256> recursiveMatches{};
                    int recursiveScore;
                    int recursiveNextMatch = nextMatch;
                    if (FuzzySearchRecursive(pattern,
                                             src.substr(1),
                                             recursiveScore,
                                             strBegin,
                                             &newMatches,
                                             recursiveMatches,
                                             recursiveNextMatch,
                                             recursionCount,
                                             recursionLimit))
                    {
                        // Pick the best recursive score
                        if (!recursiveMatch || recursiveScore > bestRecursiveScore)
                        {
                            memcpy(bestRecursiveMatches.data(), recursiveMatches.data(), recursiveMatches.size());
                            bestRecursiveScore = recursiveScore;
                        }
                        recursiveMatch = true;
                    }

                    // Advance
                    newMatches[nextMatch++] = static_cast<uint8_t>(strBegin.size() - src.size());
                    pattern = pattern.substr(1);
                }

                src = src.substr(1);
            }

            // Determine if full pattern was matched
            bool matched = pattern.empty();

            // Calculate score
            if (matched)
            {
                constexpr int sequentialBonus = 15;  // bonus for adjacent matches
                constexpr int separatorBonus = 30;   // bonus if match occurs after a separator
                constexpr int camelBonus = 30;       // bonus if match is uppercase and prev is lower
                constexpr int firstLetterBonus = 15; // bonus if the first letter is matched

                constexpr int leadingLetterPenalty = -5;     // penalty applied for every letter in str before the first match
                constexpr int maxLeadingLetterPenalty = -15; // maximum penalty for leading letters
                constexpr int unmatchedLetterPenalty = -1;   // penalty for every letter that doesn't matter

                // Iterate str to end
                while (!src.empty())
                {
                    src = src.substr(1);
                }

                // Initialize score
                outScore = 100;

                // Apply leading letter penalty
                int penalty = leadingLetterPenalty * newMatches[0];
                if (penalty < maxLeadingLetterPenalty)
                {
                    penalty = maxLeadingLetterPenalty;
                }
                outScore += penalty;

                // Apply unmatched penalty
                int unmatched = static_cast<int>(strBegin.size() - src.size()) - nextMatch;
                outScore += unmatchedLetterPenalty * unmatched;

                // Apply ordering bonuses
                for (int i = 0; i < nextMatch; ++i)
                {
                    uint8_t currIdx = newMatches[i];

                    if (i > 0)
                    {
                        uint8_t prevIdx = newMatches[i - 1];

                        // Sequential
                        if (currIdx == (prevIdx + 1))
                        {
                            outScore += sequentialBonus;
                        }
                    }

                    // Check for bonuses based on neighbor character value
                    if (currIdx > 0)
                    {
                        // Camel case
                        char neighbor = strBegin[currIdx - 1];
                        char curr = strBegin[currIdx];
                        if (::islower(neighbor) && ::isupper(curr))
                        {
                            outScore += camelBonus;
                        }

                        // Separator
                        bool neighborSeparator = neighbor == '_' || neighbor == ' ';
                        if (neighborSeparator)
                        {
                            outScore += separatorBonus;
                        }
                    }
                    else
                    {
                        // First letter
                        outScore += firstLetterBonus;
                    }
                }
            }

            // Return best result
            if (recursiveMatch && (!matched || bestRecursiveScore > outScore))
            {
                // Recursive score is better than "this"
                memcpy(newMatches.data(), bestRecursiveMatches.data(), bestRecursiveMatches.size());
                outScore = bestRecursiveScore;
                return true;
            }

            if (matched)
            {
                // "this" score is better than recursive
                return true;
            }

            // no match
            return false;
        }

    public:
        StringUtils() = delete;

        template <typename Ret, typename Str>
            requires(IsStringView<Str> || StringRestriction<Str>) && (std::is_integral_v<Ret> || std::is_floating_point_v<Ret> || std::is_same_v<Ret, bool>)
        static Ret Cast(const Str& str)
        {
            constexpr auto IsWide = std::is_same_v<Str, std::wstring> || std::is_same_v<Str, std::wstring_view>;
            if constexpr (std::is_same_v<Ret, bool>)
            {
                if constexpr (IsWide)
                {
                    return str == L"1" || str == L"true";
                }
                else
                {
                    return str == "1" || str == "true";
                }
            }

            Str trimmed = Trim(str);
            if (trimmed.empty() || !IsNumeric(trimmed))
            {
                return Ret();
            }

            if constexpr (std::is_same_v<Ret, int> || std::is_same_v<Ret, uint>)
            {
                if constexpr (IsWide)
                {
                    return _wtoi(trimmed.data());
                }
                else
                {
                    return std::atoi(trimmed.data());
                }
            }
            else if constexpr (std::is_same_v<Ret, long> || std::is_same_v<Ret, ulong>)
            {
                if constexpr (IsWide)
                {
                    return _wtol(trimmed.data());
                }
                else
                {
                    return std::atol(trimmed.data());
                }
            }
            else if constexpr (std::is_same_v<Ret, int64> || std::is_same_v<Ret, uint64>)
            {
                if constexpr (IsWide)
                {
                    return _wtoi64_l(trimmed.data());
                }
                else
                {
                    return std::atoll(trimmed.data());
                }
            }
            else if constexpr (std::is_same_v<Ret, float> || std::is_same_v<Ret, double>)
            {
                if constexpr (IsWide)
                {
                    return static_cast<Ret>(_wtof(trimmed.data()));
                }
                else
                {
                    static_cast<Ret>(std::atof(trimmed.data()));
                }
            }

            return 0;
        }

        static bool IsValidHex(const std::wstring_view input)
        {
            constexpr std::wstring_view characters = L"1234567890ABCDEFabcdf";
            return input.find_first_not_of(characters) == std::wstring::npos;
        }

        //! Converts numeric value with a metric suffix to the full value, eg 10k translates to 10000
        template <typename T>
            requires std::is_integral_v<T> || std::is_floating_point_v<T>
        static T MultiplyBySuffix(const std::wstring_view valueString)
        {
            const T value = Cast<T>(valueString);
            const auto lastChar = valueString.back();

            if (lastChar == *L"k" || lastChar == *L"K")
            {
                return value * 1000;
            }

            if (lastChar == *L"m" || lastChar == *L"M")
            {
                return value * 1000000;
            }

            return value;
        }

        template <typename View, typename Str = std::conditional_t<std::is_same_v<std::string_view, View>, std::string, std::wstring>>
            requires IsStringView<View>
        static Str XmlText(View text)
        {
            Str ret;
            for (uint i = 0; i < text.length(); i++)
            {
                if (text[i] == '<')
                {
                    ret.append(NARROW_OR_WIDE_VIEW(View, "&#60;"));
                }
                else if (text[i] == '>')
                {
                    ret.append(NARROW_OR_WIDE_VIEW(View, "&#62;"));
                }
                else if (text[i] == '&')
                {
                    ret.append(NARROW_OR_WIDE_VIEW(View, "&#38;"));
                }
                else
                {
                    ret.append(1, text[i]);
                }
            }

            return ret;
        }

        template <typename T>
            requires std::convertible_to<T, std::string_view>
        static std::wstring stows(const T& text)
        {
            const std::string_view view = text;

            // Statically allocate buffer to prevent reallocations
            static std::array<wchar_t, 8192> buffer;
            std::memset(buffer.data(), 0, buffer.size());

            const int size = MultiByteToWideChar(CP_UTF8, 0, view.data(), static_cast<int>(view.size()), buffer.data(), buffer.size());

            if (!size)
            {
                return L"";
            }

            // Only copy the byes we need
            auto end = buffer.begin();
            std::advance(end, size);

            return { buffer.begin(), end };
        }

        template <typename T>
            requires std::convertible_to<T, std::wstring_view>
        static std::string wstos(const T& text)
        {
            const std::wstring_view view = text;

            // Statically allocate buffer to prevent reallocations
            static std::array<char, 8192> buffer;
            std::memset(buffer.data(), 0, buffer.size());

            const int size = WideCharToMultiByte(CP_UTF8, 0, view.data(), static_cast<int>(view.size()), buffer.data(), buffer.size(), nullptr, nullptr);

            if (!size)
            {
                return "";
            }
            // Only copy the byes we need
            auto end = buffer.begin();
            std::advance(end, size);

            return { buffer.begin(), end };
        }

        static std::wstring ToHex(const std::wstring_view input)
        {
            std::wostringstream output;

            for (const auto& c : input)
            {
                const auto val = static_cast<long>(c);
                output << std::uppercase << std::setfill(L'0') << std::setw(4) << std::hex << val;
            }
            return output.str();
        }

        template <typename Str>
            requires StringRestriction<Str> || IsStringView<Str>
        static bool IsAscii(Str str)
        {
            return !std::any_of(str.begin(), str.end(), [](auto c) { return static_cast<unsigned char>(c) > 127; });
        }

        template <typename Str>
            requires StringRestriction<Str> || IsStringView<Str>
        static bool IsNumeric(Str str)
        {
            if (str.empty())
            {
                return false;
            }

            constexpr bool isWide = !(std::is_same_v<Str, std::string_view> || std::is_same_v<Str, std::string>);
            constexpr auto minus = isWide ? L'-' : '-';
            using ViewType = std::conditional_t<isWide, std::wstring_view, std::string_view>;

            bool isFirstMinusSign = *str.begin() == minus;
            ViewType view{ isFirstMinusSign ? str.begin() + 1 : str.begin(), str.end() };

            bool hasDot = false;
            if constexpr (!isWide)
            {
                return std::ranges::all_of(view,
                                           [&hasDot](const char c)
                                           {
                                               if (c == '.')
                                               {
                                                   if (hasDot)
                                                   {
                                                       return FALSE;
                                                   }
                                                   hasDot = true;
                                                   return TRUE;
                                               }
                                               return isdigit(c);
                                           });
            }
            else
            {
                return std::ranges::all_of(view,
                                           [&hasDot](const wchar_t c)
                                           {
                                               if (c == L'.')
                                               {
                                                   if (hasDot)
                                                   {
                                                       return FALSE;
                                                   }
                                                   hasDot = true;
                                                   return TRUE;
                                               }
                                               return iswdigit(c);
                                           });
            }
        }

        template <typename Str,
                  typename ReturnStr = std::conditional_t<std::is_same_v<Str, std::string> || std::is_same_v<Str, std::string_view>, std::string, std::wstring>>
            requires IsStringView<Str> || StringRestriction<Str>
        static ReturnStr ToLower(Str str)
        {
            ReturnStr retStr;
            retStr.reserve(str.size());

            // If we are a string view we need to convert it back.
            // String views use an explicit constructor
            auto before = ReturnStr(str);
            std::ranges::copy(before | std::ranges::views::transform([](auto c) { return std::tolower(c); }), std::back_inserter(retStr));
            return retStr;
        }

        template <typename Str>
            requires IsStringView<Str>
        static bool CompareCaseInsensitive(Str str1, Str str2)
        {
            if (str1.size() != str2.size())
            {
                return false;
            }

            for (int i = 0; i < str1.size(); ++i)
            {
                if (std::tolower(str1[i]) != std::tolower(str2[i]))
                {
                    return false;
                }
            }

            return true;
        }

        template <typename Str>
        static Str Trim(const Str& stringInput)
            requires StringRestriction<Str> || IsStringView<Str>
        {
            if (stringInput.empty())
            {
                return stringInput;
            }

            using Char = typename Str::value_type;

            // Reallocate the str to remove needless null terminators
            Str nullRemoved = stringInput.data();

            constexpr auto trimmable = []() constexpr
            {
                if constexpr (std::is_same_v<Char, char>)
                {
                    return std::string_view(" \t\n\r");
                }
                else if constexpr (std::is_same_v<Char, wchar_t>)
                {
                    return std::wstring_view(L" \t\n\r");
                }
            }();

            auto start = nullRemoved.find_last_not_of(trimmable);
            auto end = nullRemoved.find_last_of(trimmable);

            if (start >= end)
            {
                return nullRemoved;
            }

            return nullRemoved.substr(0, start + 1);
        }

        template <typename View, typename Str = std::conditional_t<std::is_same_v<View, std::string_view>, std::string, std::wstring>>
            requires IsStringView<View>
        static Str ExpandEnvironmentVariables(const View& input)
        {
            std::string accumulator;
            std::string output;
            bool percentFound = false;

            for (uint i = 0; i < input.length(); i++)
            {
                if (const auto ch = input[i]; ch == '%')
                {
                    if (percentFound || input[i + 1] != '%')
                    {
                        percentFound = !percentFound;
                        if (percentFound)
                        {
                            accumulator.clear();
                        }
                        else
                        {
                            auto var = std::getenv(accumulator.c_str());
                            accumulator = var ? var : accumulator;
                            output += accumulator;
                        }
                    }
                    else
                    {
                        i++; // Extra percentage sign, escape it.
                    }
                }
                else
                {
                    if (percentFound)
                    {
                        accumulator += ch;
                    }
                    else
                    {
                        output += ch;
                    }
                }
            }

            if constexpr (std::is_same_v<View, std::string_view>)
            {
                return Trim(output);
            }
            else
            {
                auto ret = Trim(stows(output));
                return ret;
            }
        }

        static std::wstring_view GetParam(IsConvertibleRangeOf<std::wstring_view> auto view, int pos)
        {
            return GetParam<decltype(view), std::wstring_view>(view, pos);
        }

        template <typename TStr, typename TChar>
        static auto GetParams(const TStr& line, TChar splitChar)
            requires(StringRestriction<TStr> || IsStringView<TStr>) && (std::is_same_v<TChar, char> || std::is_same_v<TChar, wchar_t>)
        {
            using ViewType = std::conditional_t<std::is_same_v<TChar, char>, std::string_view, std::wstring_view>;
            std::vector<ViewType> result;

            int indexCommaToLeftOfColumn = 0;
            int indexCommaToRightOfColumn = -1;

            for (int i = 0; i < static_cast<int>(line.size()); i++)
            {
                if (line[i] == splitChar)
                {
                    indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
                    indexCommaToRightOfColumn = i;
                    int index = indexCommaToLeftOfColumn + 1;
                    const int length = indexCommaToRightOfColumn - index;
                    ViewType column(line.data() + index, length);
                    result.push_back(column);
                }
            }

            const ViewType finalColumn(line.data() + indexCommaToRightOfColumn + 1, line.size() - indexCommaToRightOfColumn - 1);
            result.emplace_back(finalColumn);
            return result;
        }

        // TODO: Fix this template error
        template <typename TTransformView, typename TViewType>
        static TViewType GetParamToEnd(TTransformView view, uint pos)
        {
            if (pos == 0)
            {
                return TViewType();
            }

            // If specified pos is over the max amount of items return an empty string
            if (static_cast<int>(pos) >= std::distance(view.begin(), view.end()))
            {
                return TViewType();
            }

            auto offset = view.begin();
            std::advance(offset, pos);

            auto newRange = std::ranges::views::counted(offset, std::distance(offset, view.end()));
            auto finalRange = newRange | std::ranges::views::take(std::distance(offset, view.end())) | std::ranges::views::join;
            return TViewType(&*finalRange.begin(), std::ranges::distance(finalRange) + 1);
        }

        template <typename TString, typename TChar>
        static TString GetParamToEnd(TString line, TChar splitChar, uint pos)
        {
            if (pos == 0)
            {
                return line;
            }

            auto params = GetParams(line, splitChar);
            using TViewType = decltype(params);
            return GetParamToEnd<TViewType, TString>(params, pos);
        }

        template <typename TString, typename View>
            requires StringRestriction<TString> && IsStringView<View>
        static TString ReplaceStr(const TString& source, View searchForRaw, View replaceWithRaw)
        {
            uint lPos, sPos = 0;

            TString result = source;
            while ((lPos = static_cast<uint>(result.find(searchForRaw, sPos))) != UINT_MAX)
            {
                result.replace(lPos, searchForRaw.length(), replaceWithRaw);
                sPos = lPos + replaceWithRaw.length();

                if (lPos == sPos)
                {
                    break;
                }
            }

            return result;
        }

        template <typename T>
            requires StringRestriction<T>
        static T ToMoneyStr(T cash)
        {
            std::conditional_t<std::is_same_v<T, std::string>, std::stringstream, std::wstringstream> ss;
            ss.imbue(std::locale(""));
            ss << std::fixed << cash;
            return ss.str();
        }

        static uint RgbToBgr(const uint color) { return color & 0xFF000000 | (color & 0xFF0000) >> 16 | color & 0x00FF00 | (color & 0x0000FF) << 16; };

        template <typename T>
            requires StringRestriction<T>
        static T UintToHexString(const uint number, const uint width, const bool addPrefix = false)
        {
            using CharType = std::conditional_t<std::is_same_v<T, std::string>, char, wchar_t>;
            using CharPtrType = std::conditional_t<std::is_same_v<T, std::string>, const char*, const wchar_t*>;
            std::conditional_t<std::is_same_v<T, std::string>, std::stringstream, std::wstringstream> stream;
            if (addPrefix)
            {
                stream << NARROW_OR_WIDE(CharPtrType, "0x");
            }

            stream << std::setfill(NARROW_OR_WIDE(CharType, '0')) << std::setw(width) << std::hex << number;
            return stream.str();
        }

        template <typename T, typename TStr = std::conditional_t<std::is_same_v<T, std::string_view>, std::string_view, std::wstring_view>>
            requires IsStringView<T>
        static TStr FormatMsg(MessageColor color, MessageFormat format, T msg)
        {
            using namespace std::string_view_literals;
            using CharType = std::conditional_t<std::is_same_v<T, std::string_view>, const char*, const wchar_t*>;
            using Str = std::conditional_t<std::is_same_v<T, std::string_view>, std::string, std::wstring>;

            const uint bgrColor = RgbToBgr(static_cast<uint>(color));
            const Str tra = UintToHexString<Str>(bgrColor, 6, true) + UintToHexString<Str>(static_cast<uint>(format), 2);

            return std::format(NARROW_OR_WIDE(CharType, "<TRA data=\"{}\" mask=\"-1\"/><TEXT>{}</TEXT>"),
                               tra,
                               ReplaceStr(XmlText(msg), NARROW_OR_WIDE_VIEW(T, "\n"), NARROW_OR_WIDE_VIEW(T, "</TEXT><PARA/><TEXT>")));
        }

        /**
         * @brief Match a string against a wildcard pattern, where an '*' matches one or more characters and '?' matches any one character
         * @tparam Str A type that is convertible to an std::string_view or std::wstring_view
         * @param input The input string that will be compared against
         * @param pattern The wildcard pattern, e.g. Kin*Jam?S = King James
         * @param partialString If true only checks that any part of the string matches (as if placing an asterix at the start and end)
         * @param caseSensitive if true strings must match case to return a successful match
         * @code{.cpp}
         *    MatchStr("Dave The Brave"sv, "Dave*Brave"sv, false) == true;
         *    MatchStr("Dave The Brave"sv, "The"sv) == true;
         *    MatchStr("Dave The Brave"sv, "*Dave"sv, false) == false;
         *    MatchStr("Jeff"sv, "Dave"sv) == false;
         *    MatchStr("Jeff The Brave"sv, "Jeff"sv, false) == false;
         *    MatchStr("Jeff The Brave"sv, "jeff"sv, true, true) == false;
         * @endcode
         * @return True if the string matches
         */
        template <typename Str>
            requires std::convertible_to<Str, std::string_view> || std::convertible_to<Str, std::wstring_view>
        static bool WildcardMatch(const Str& input, const Str& pattern, const bool partialString = true, const bool caseSensitive = false)
        {
            if (input.empty() || pattern.empty())
            {
                return false;
            }

            using ViewType = std::conditional_t<std::convertible_to<Str, std::string_view>, std::string_view, std::wstring_view>;
            using CharType = std::conditional_t<std::convertible_to<Str, std::string_view>, char, wchar_t>;
            constexpr auto multiWildcardCharacter = static_cast<CharType>('*');
            constexpr auto singularWildcardCharacter = static_cast<CharType>('?');

            ViewType inputView = input;
            ViewType patternView = pattern;

            static const auto compareChar = [caseSensitive](const CharType a, const CharType b)
            {
                if constexpr (std::is_same_v<char, CharType>)
                {
                    return caseSensitive ? a == b : std::tolower(a) == std::tolower(b);
                }
                else
                {
                    return caseSensitive ? a == b : std::towlower(a) == std::towlower(b);
                }
            };

            bool matched = !partialString;
            int wildCardCharactersMatched = 0;

            // If the first character is an asterix, it's effectively a partial string match
            if (pattern.front() == multiWildcardCharacter)
            {
                matched = true;
                wildCardCharactersMatched++;
            }

            int patternIndex = 0;
            for (int inputIndex = 0; inputIndex < inputView.size(); inputIndex++)
            {
                if (patternIndex >= pattern.size())
                {
                    // If we are trying to match a full string and the pattern ran out, ensure that it ends with a asterix or it's not a match
                    if (!partialString && patternView.back() != multiWildcardCharacter)
                    {
                        matched = false;
                    }

                    break;
                }

                CharType currentChar = inputView[inputIndex];
                CharType patternChar = patternView[patternIndex];

                // If we encounter a '?', skip the character
                if (patternChar == singularWildcardCharacter)
                {
                    matched = true;
                    patternIndex++;
                    continue;
                }

                // We have encountered our asterix
                if (patternChar == multiWildcardCharacter)
                {
                    matched = true;

                    if (patternIndex + 1 == patternView.size())
                    {
                        break;
                    }

                    if (CharType nextPatternChar = patternView[patternIndex + 1]; wildCardCharactersMatched++ > 0 && compareChar(currentChar, nextPatternChar))
                    {
                        patternIndex++;
                        // The asterix will 'eat' the character we are trying to match
                        inputIndex--;
                    }

                    continue;
                }

                wildCardCharactersMatched = 0;

                // If we haven't started matching, go until we find a character that matches
                if (!matched)
                {
                    if (compareChar(currentChar, patternChar))
                    {
                        matched = true;
                        patternIndex++;
                    }

                    continue;
                }

                // If we have matched, ensure that we still match
                matched = compareChar(currentChar, patternChar);
                patternIndex++;

                if (!matched)
                {
                    break;
                }
            }

            if (patternIndex != patternView.size() && (patternIndex != patternView.size() - 1 && patternView.back() != multiWildcardCharacter))
            {
                matched = false;
            }

            return matched;
        }

        template <typename T>
            requires IsStringView<T>
        static bool FuzzySearch(T pattern, T haystack, int& outScore, std::array<uint8_t, 256>& matches, int& outMatches)
        {
            int recursionCount = 0;
            int recursionLimit = 10;
            int newMatches = 0;
            if constexpr (std::is_same_v<T, std::string_view>)
            {
                bool result = FuzzySearchRecursive(pattern, haystack, outScore, haystack, nullptr, matches, newMatches, recursionCount, recursionLimit);
                outMatches = newMatches;
                return result;
            }
            else
            {
                auto strPattern = wstos(pattern);
                auto strHaystack = wstos(haystack);
                bool result =
                    FuzzySearchRecursive(strPattern, strHaystack, outScore, strHaystack, nullptr, matches, newMatches, recursionCount, recursionLimit);
                outMatches = newMatches;
                return result;
            }
        }

        template <typename T>
            requires IsStringView<T>
        static bool FuzzySearch(T pattern, T input, int& outScore)
        {
            static std::array<uint8_t, 256> matches{};
            std::ranges::fill(matches, 0);

            int matchCount = 0;
            return FuzzySearch(pattern, input, outScore, matches, matchCount);
        }
};

#undef TOWSTRING
#undef TOWSTRING1
#undef TOWSTRINGVIEW
#undef TOWSTRINGVIEW1
#undef NARROW_OR_WIDE
