#pragma once

#include "IProfileParser.hpp"
#include "TSmartPtr.hpp"

#include "ICOManager.hpp"

inline u32 opt_get_u32(ICOManager* DACOM, IProfileParser* _IPP, const char* section, const char* key,
                       u32 def_value, u32* out_value)
{
    u32 ret;

    if (out_value == NULL)
    {
        out_value = &ret;
    }

    static char buffer[1024 + 1];
    COMPTR<IProfileParser> IPP;

    if ((IPP = _IPP) || SUCCEEDED(DACOM->QueryInterface(IID_IProfileParser, (void**)&IPP)))
    {
        HANDLE hSection;

        *out_value = def_value;
        if ((hSection = IPP->CreateSection(section)) != 0)
        {
            if (IPP->ReadKeyValue(hSection, key, buffer, 1024))
            {
                // replace the first occurance of any character not in valid_char_set with a NULL to terminate the string
                char valid_char_set[] =
                    "0123456789truefalsynoxTRUEFALSYNOX+-"; // true false yes no or a number
                u32 early_termination = strspn(buffer, valid_char_set);
                if (early_termination)
                {
                    buffer[early_termination] = NULL;
                }
                if (_stricmp(buffer, "true") == 0)
                {
                    *out_value = 1;
                }
                else if (_stricmp(buffer, "yes") == 0)
                {
                    *out_value = 1;
                }
                else if (_stricmp(buffer, "false") == 0)
                {
                    *out_value = 0;
                }
                else if (_stricmp(buffer, "no") == 0)
                {
                    *out_value = 0;
                }
                else if (strchr(buffer, 'x') || strchr(buffer, 'X'))
                {
                    *out_value = strtoul(buffer, NULL, 16);
                }
                else
                {
                    char numbers_only[] = "0123456789+-"; // check again for typos or bad values
                    if (strspn(buffer, numbers_only) < strlen(buffer))
                    {
                        // GENERAL_TRACE_1(TEMPSTR("Invalid u32 key %s in section [%s].\n", buffer, section));
                    }
                    *out_value = atoi(buffer);
                }
            }
            IPP->CloseSection(hSection);
        }
    }

    return *out_value;
}

//

inline float opt_get_float(ICOManager* DACOM, IProfileParser* _IPP, const char* section, const char* key,
                           float def_value, float* out_value)
{
    float ret;

    if (out_value == NULL)
    {
        out_value = &ret;
    }

    static char buffer[1024 + 1];
    COMPTR<IProfileParser> IPP;

    if ((IPP = _IPP) || SUCCEEDED(DACOM->QueryInterface(IID_IProfileParser, (void**)&IPP)))
    {
        HANDLE hSection;

        *out_value = def_value;
        if ((hSection = IPP->CreateSection(section)) != 0)
        {
            if (IPP->ReadKeyValue(hSection, key, buffer, 1024))
            {
                // replace the first occurance of any character not in valid_char_set with a NULL to terminate the string
                char valid_char_set[] = "0123456789eE.+-"; // numbers.numbers
                u32 early_termination = strspn(buffer, valid_char_set);
                if (early_termination)
                {
                    buffer[early_termination] = NULL;
                }
                *out_value = (float)atof(buffer);
            }
            IPP->CloseSection(hSection);
        }
    }

    return *out_value;
}

//

inline char* opt_get_string(ICOManager* DACOM, IProfileParser* _IPP, const char* section, const char* key,
                            const char* def_value, char* out_value, u32 max_len)
{
    static char buffer[1024 + 1];
    COMPTR<IProfileParser> IPP;

    if ((IPP = _IPP) || SUCCEEDED(DACOM->QueryInterface(IID_IProfileParser, (void**)&IPP)))
    {
        HANDLE hSection;

        strncpy(out_value, def_value, max_len);
        if ((hSection = IPP->CreateSection(section)) != 0)
        {
            if (IPP->ReadKeyValue(hSection, key, buffer, 1024))
            {
                strncpy(out_value, buffer, max_len);
            }
            IPP->CloseSection(hSection);
        }
    }

    return out_value;
}

//

inline Vector& opt_get_vector(ICOManager* DACOM, IProfileParser* _IPP, const char* section, const char* key,
                              Vector& def_value, Vector& out_value)
{
    static char buffer[1024 + 1];
    COMPTR<IProfileParser> IPP;

    if ((IPP = _IPP) || SUCCEEDED(DACOM->QueryInterface(IID_IProfileParser, (void**)&IPP)))
    {
        HANDLE hSection;

        out_value = def_value;
        if ((hSection = IPP->CreateSection(section)) != 0)
        {
            if (IPP->ReadKeyValue(hSection, key, buffer, 1024))
            {
                char* tok;
                out_value.x = 0.0;
                if ((tok = strtok(buffer, " ,\t\n")) != NULL)
                {
                    out_value.x = (float)atof(tok);
                }
                out_value.y = 0.0;
                if ((tok = strtok(NULL, " ,\t\n")) != NULL)
                {
                    out_value.y = (float)atof(tok);
                }
                out_value.z = 0.0;
                if ((tok = strtok(NULL, " ,\t\n")) != NULL)
                {
                    out_value.z = (float)atof(tok);
                }
            }
            IPP->CloseSection(hSection);
        }
    }

    return out_value;
}

//

inline GENRESULT opt_has_key(ICOManager* DACOM, IProfileParser* _IPP, const char* section, const char* key)
{
    static char buffer[1024 + 1];
    COMPTR<IProfileParser> IPP;
    GENRESULT ret = GR_GENERIC;

    if ((IPP = _IPP) || SUCCEEDED(DACOM->QueryInterface(IID_IProfileParser, (void**)&IPP)))
    {
        HANDLE hSection;
        if ((hSection = IPP->CreateSection(section)) != 0)
        {
            if (IPP->ReadKeyValue(hSection, key, buffer, 1024))
            {
                ret = GR_OK;
            }
            IPP->CloseSection(hSection);
        }
    }

    return ret;
}
