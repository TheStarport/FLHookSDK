#pragma once
#include "../../FLCoreDefs.hpp"

namespace Universe
{
    struct IBase
    {
        void* vftable;
        BaseId baseId;
        char* nickname;
        uint baseIdS;
        char* filepath;
        SystemId systemId;
        st6::string baseRunBy;
        ulong spaceObjId;
        bool dunno1;
		uint shipSmall01;
		uint shipSmall02;
		uint shipSmall03;
		uint shipMedium01;
		uint shipMedium02;
		uint shipMedium03;
		uint shipLarge01;
		uint shipLarge02;
		uint shipLarge03;
		uint terrainTiny;
		uint terrainSmall;
		uint terrainMedium;
		uint terrainLarge;
		uint terrainDynamic1;
		uint terrainDynamic2;
		bool autosaveForbidden;
    };
}