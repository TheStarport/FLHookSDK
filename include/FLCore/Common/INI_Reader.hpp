#pragma once

#include "CommonMethods.hpp"

#include <Utils/StringUtils.hpp>

class INI_Reader
{
    public:
        IMPORT INI_Reader(const INI_Reader&);
        IMPORT INI_Reader();
        IMPORT ~INI_Reader();
        IMPORT INI_Reader& operator=(const INI_Reader&);
        IMPORT void close();
        IMPORT bool find_header(const char*);
        IMPORT bool get_bool(u32);
        IMPORT const char* get_file_name() const;
        IMPORT const char* get_header_ptr();
        IMPORT const char* get_indexed_value(u32);
        IMPORT int get_line_num() const;
        IMPORT const char* get_line_ptr();
        IMPORT const char* get_name() const;
        IMPORT const char* get_name_ptr();
        IMPORT u32 get_num_parameters() const;
        IMPORT void get_state(struct State&) const;
        IMPORT bool get_value_bool(u32);
        IMPORT f32 get_value_float(u32);
        IMPORT int get_value_int(u32);
        IMPORT const char* get_value_ptr();
        IMPORT const char* get_value_string(u32);
        IMPORT const char* get_value_string();
        IMPORT const u16* get_value_wstring();
        IMPORT Vector get_vector();
        IMPORT bool is_end() const;
        IMPORT bool is_header(const char*);
        IMPORT bool is_number(const char*) const;
        IMPORT bool is_value(const char*);
        IMPORT bool is_value_empty(u32);
        IMPORT void log_link(const char*) const;
        IMPORT bool open(const char*, bool);
        IMPORT bool open_memory(const char*, u32);
        IMPORT bool read_header();
        IMPORT bool read_value();
        IMPORT void reset();
        IMPORT void seek(u32);
        IMPORT void set_state(const State&);
        IMPORT u32 tell() const;
        IMPORT f64 value_num(u32);

        bool GetFloat(const std::string_view key, f32& value, bool& found, const int param = 0)
        {
            if (!is_value(key.data()))
            {
                return false;
            }

            found = true;
            value = get_value_float(param);
            return true;
        }

        bool GetFloat(const std::string_view key, f32& value, const int param = 0)
        {
            bool dummy;
            return GetFloat(key, value, dummy, param);
        }

        bool GetInt(const std::string_view key, int& value, bool& found, const int param = 0)
        {
            if (!is_value(key.data()))
            {
                return false;
            }

            found = true;
            value = get_value_int(param);
            return true;
        }

        bool GetInt(const std::string_view key, int& value, const int param = 0)
        {
            bool dummy;
            return GetInt(key, value, dummy, param);
        }

        bool GetString(const std::string_view key, std::string& value, bool& found, const int param = 0)
        {
            if (!is_value(key.data()))
            {
                return false;
            }

            found = true;
            value = get_value_string(param);
            return true;
        }

        bool GetWString(const std::string_view key, std::string& value, const int param = 0)
        {
            bool dummy;
            return GetString(key, value, dummy, param);
        }

        bool GetWString(const std::string_view key, std::wstring& value, bool& found, const int param = 0)
        {
            if (!is_value(key.data()))
            {
                return false;
            }
            found = true;
            value = StringUtils::stows(get_value_string(param));
            return true;
        }

        bool GetWString(const std::string_view key, std::wstring& value, const int param = 0)
        {
            bool dummy;
            return GetWString(key, value, dummy, param);
        }

        bool GetHash(const std::string_view key, Id& value, bool& found, const int param = 0)
        {
            if (!is_value(key.data()))
            {
                return false;
            }

            found = true;
            value = CreateID(get_value_string(param));
            return true;
        }

        bool GetHash(const std::string_view key, Id& value, const int param = 0)
        {
            bool dummy;
            return GetHash(key, value, dummy, param);
        }

        st6::string fileName;
        ulong dunno[5];
        int lineNumber;
        u8 data[5480];
};
