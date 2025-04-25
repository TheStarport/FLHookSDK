#pragma once

struct CacheString
{
    IMPORT void clear();

    public:
    char* value;
};

struct ID_String
{
    IMPORT bool IsEmpty() const;
    IMPORT void clear();
    IMPORT const char* get_string() const;

    public:
    uint id;
    unsigned char data[128];
};
