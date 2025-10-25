#pragma once
class INI_Reader
{
    public:
        IMPORT INI_Reader(const INI_Reader&);
        IMPORT INI_Reader();
        IMPORT ~INI_Reader();
        IMPORT INI_Reader& operator=(const INI_Reader&);
        IMPORT void close();
        IMPORT bool find_header(const char*);
        IMPORT bool get_bool(unsigned int);
        IMPORT const char* get_file_name() const;
        IMPORT const char* get_header_ptr();
        IMPORT const char* get_indexed_value(unsigned int);
        IMPORT int get_line_num() const;
        IMPORT const char* get_line_ptr();
        IMPORT const char* get_name() const;
        IMPORT const char* get_name_ptr();
        IMPORT unsigned int get_num_parameters() const;
        IMPORT void get_state(struct State&) const;
        IMPORT bool get_value_bool(unsigned int);
        IMPORT float get_value_float(unsigned int);
        IMPORT int get_value_int(unsigned int);
        IMPORT const char* get_value_ptr();
        IMPORT const char* get_value_string(unsigned int);
        IMPORT const char* get_value_string();
        IMPORT const unsigned short* get_value_wstring();
        IMPORT Vector get_vector();
        IMPORT bool is_end() const;
        IMPORT bool is_header(const char*);
        IMPORT bool is_number(const char*) const;
        IMPORT bool is_value(const char*);
        IMPORT bool is_value_empty(unsigned int);
        IMPORT void log_link(const char*) const;
        IMPORT bool open(const char*, bool);
        IMPORT bool open_memory(const char*, unsigned int);
        IMPORT bool read_header();
        IMPORT bool read_value();
        IMPORT void reset();
        IMPORT void seek(unsigned int);
        IMPORT void set_state(const State&);
        IMPORT unsigned int tell() const;
        IMPORT double value_num(unsigned int);

    public:
        st6::string fileName;
        unsigned long dunno[5];
        int lineNumber;
        unsigned char data[5480];
};
