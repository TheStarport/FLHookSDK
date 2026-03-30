#pragma once
#include "../../FLCoreDefs.hpp"

namespace Universe
{
    struct IBase
    {
        void* vftable;
        BaseId baseId;
        char* nickname;
        unsigned baseIdS;
        char* filepath;
        SystemId systemId;
        st6::string baseRunBy;
        ulong spaceObjId;
        bool dunno1;
		unsigned shipSmall01;
		unsigned shipSmall02;
		unsigned shipSmall03;
		unsigned shipMedium01;
		unsigned shipMedium02;
		unsigned shipMedium03;
		unsigned shipLarge01;
		unsigned shipLarge02;
		unsigned shipLarge03;
		unsigned terrainTiny;
		unsigned terrainSmall;
		unsigned terrainMedium;
		unsigned terrainLarge;
		unsigned terrainDynamic1;
		unsigned terrainDynamic2;
		bool autosaveForbidden;
    };
}