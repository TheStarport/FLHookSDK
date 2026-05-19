#pragma once

#include "Base.hpp"

struct CBeam;

// Freelancer EXE ship VTable, 0x5DD67C
struct IObjClientBeam : ClientGameObject
{
    CBeam* cbeam() { return reinterpret_cast<CBeam*>(cobject()); };
    // TODO: Fields
};

struct IObjServerBeam : ServerGameObject
{
    CBeam* cbeam() { return reinterpret_cast<CBeam*>(cobject()); };
    
    // TODO: Fields and methods
    // lots of fields but not much use filling it in
};
