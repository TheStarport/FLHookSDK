#pragma once

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

class StringUtils
{
    public:
        StringUtils() = delete;

        template <typename Ret, typename Str>
            requires(IsStringView<Str> || StringRestriction<Str>) && (std::is_integral_v<Ret> || std::is_floating_point_v<Ret>)
        static Ret Cast(Str str)
        {
            if (str.empty() || !IsAscii(str))
            {
                return Ret();
            }

            Ret ret;
            std::conditional_t<std::is_same_v<std::wstring, Str> || std::is_same_v<std::wstring_view, Str>, std::wstring_view, std::string_view> input = str;
            std::from_chars(reinterpret_cast<const char*>(str.data()), reinterpret_cast<const char*>(str.data() + str.size()), ret);
            return ret; // TODO: Add trace log for failure to convert
        }

        static Hook bool IsValidHex(const std::wstring_view input)
        {
            constexpr std::wstring_view characters = L"1234567890ABCDEFabcdf";
            return input.find_first_not_of(characters) == std::wstring::npos;
        }

        //! Converts numeric value with a metric suffix to the full value, eg 10k translates to 10000
        static Hook uint MultiplyUIntBySuffix(const std::wstring_view valueString)
        {
            const uint value = Cast<uint>(valueString);
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

        static Hook std::wstring XmlText(const std::wstring_view text)
        {
            std::wstring ret;
            for (uint i = 0; i < text.length(); i++)
            {
                if (text[i] == '<')
                {
                    ret.append(L"&#60;");
                }
                else if (text[i] == '>')
                {
                    ret.append(L"&#62;");
                }
                else if (text[i] == '&')
                {
                    ret.append(L"&#38;");
                }
                else
                {
                    ret.append(1, text[i]);
                }
            }

            return ret;
        }

        template<typename T>
            requires std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view> || std::is_same_v<std::add_pointer_t<std::remove_cv_t<std::remove_pointer_t<T>>>, char*>
        static Hook std::wstring stows(const T& text)
        {
            const char* data;
            if constexpr (std::is_same_v<std::add_pointer_t<std::remove_cv_t<std::remove_pointer_t<T>>>, char*>)
            {
                data = text;
            }
            else
            {
                data = text.data();
            }

            // Statically allocate buffer to prevent reallocations
            static std::array<wchar_t, 4096> buffer;
            std::memset(buffer.data(), 0, buffer.size());

            const int size = MultiByteToWideChar(CP_UTF8, 0, data, -1, buffer.data(), 4096);

            // Only copy the byes we need
            auto end = buffer.begin();
            std::advance(end, size);

            return { buffer.begin(), end };
        }

        template<typename T>
            requires std::is_same_v<T, std::wstring> || std::is_same_v<T, std::wstring_view> || std::is_same_v<std::add_pointer_t<std::remove_cv_t<std::remove_pointer_t<T>>>, wchar_t*>
        static Hook std::string wstos(const T& text)
        {
            const wchar_t* data;
            if constexpr (std::is_same_v<std::add_pointer_t<std::remove_cv_t<std::remove_pointer_t<T>>>, wchar_t*>)
            {
                data = text;
            }
            else
            {
                data = text.data();
            }

            // Statically allocate buffer to prevent reallocations
            static std::array<char, 4096> buffer;
            std::memset(buffer.data(), 0, buffer.size());

            const int size = WideCharToMultiByte(CP_UTF8, 0, data, -1, buffer.data(), 4096, nullptr, nullptr);

            // Only copy the byes we need
            auto end = buffer.begin();
            std::advance(end, size);

            return { buffer.begin(), end };
        }

        static Hook std::wstring ToHex(const std::wstring_view input)
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
                    return std::wstring_view(L" \t\n\r");
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

        static Hook std::wstring ExpandEnvironmentVariables(const std::wstring& input)
        {
            std::string accumulator;
            std::string output;
            bool percentFound = false;

            for (uint i = 0; i < input.length(); i++)
            {
                const auto ch = input[i];
                if (ch == '%')
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

            auto ret = Trim(stows(output));
            return ret;
        }

    private:
        template <typename TTransformView, typename ViewType>
        static ViewType GetParam(TTransformView view, int pos)
        {
            if (pos >= 0)
            {
                throw std::invalid_argument("GetParam pos must be positive");
            }

            if (pos >= std::distance(view.begin(), view.end()))
            {
                return ViewType();
            }

            return *std::ranges::get<0>(std::ranges::subrange{ std::next(view.begin(), pos), view.end() });
        }

    public:
        static std::wstring_view GetParam(IsConvertibleRangeOf<std::wstring_view> auto view, int pos)
        {
            return GetParam<decltype(view), std::wstring_view>(view, pos);
        }

        template <typename TStr, typename TChar>
        static auto GetParams(const TStr& line, TChar splitChar)
            requires(StringRestriction<TStr> || IsStringView<TStr>) && (std::is_same_v<TChar, char> || std::is_same_v<TChar, wchar_t>)
        {
            if constexpr (StringRestriction<TStr>)
            {
                using T = std::conditional<std::is_same_v<TStr, std::string>, std::string_view, std::wstring_view>::type;
                return line | std::ranges::views::split(splitChar) |
                       std::ranges::views::transform(
                           [](auto&& rng)
                           {
                               if (!std::ranges::distance(rng))
                               {
                                   return T();
                               }

                               return T(&*rng.begin(), std::ranges::distance(rng));
                           }) |
                       std::ranges::views::filter([](auto&& rng) { return std::ranges::distance(rng) != 0; });
            }
            else
            {
                return line | std::ranges::views::split(splitChar) |
                       std::ranges::views::transform([](auto&& rng) { return TStr(&*rng.begin(), std::ranges::distance(rng)); });
            }
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
                         requires StringRestriction<TString>
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
        static std::wstring ToMoneyStr(T cash)
        {
            std::wstringstream ss;
            ss.imbue(std::locale(""));
            ss << std::fixed << cash;
            return ss.str();
        }

        static uint RgbToBgr(const uint color) { return color & 0xFF000000 | (color & 0xFF0000) >> 16 | color & 0x00FF00 | (color & 0x0000FF) << 16; };

        static std::wstring UintToHexString(const uint number, const uint width, const bool addPrefix = false)
        {
            std::wstringstream stream;
            if (addPrefix)
            {
                stream << L"0x";
            }
            stream << std::setfill(L'0') << std::setw(width) << std::hex << number;
            return stream.str();
        }

        static std::wstring FormatMsg(MessageColor color, MessageFormat format, const std::wstring& msg)
        {
            const uint bgrColor = RgbToBgr(static_cast<uint>(color));
            const std::wstring tra = UintToHexString(bgrColor, 6, true) + UintToHexString(static_cast<uint>(format), 2);

            return std::format(L"<TRA data=\"{}\" mask=\"-1\"/><TEXT>{}</TEXT>", tra, XmlText(msg));
        }
};
