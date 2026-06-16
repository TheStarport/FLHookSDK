#pragma once

#include "../FLCoreDefs.hpp"

#include "../Dacom/IdaComponent.hpp"

class Vector;
class Matrix;

// NOTE: Due to the macro nature of MAKE_IID, you cannot use another macro in place of the version
// number. Keep the second parameter in sync with the value of the explicit version macro, and increment
// both when the interface changes.
#define ISOUNDLISTENER_VERSION 1
#define IID_ISoundListener     MAKE_IID("ISoundListener", 1)
struct ISoundListener : public IDAComponent
{
    virtual GENRESULT __stdcall get_ear_orientation(Vector* back, Vector* up) = 0;
    virtual GENRESULT __stdcall get_ear_position(Vector* position) = 0;
    virtual GENRESULT __stdcall get_ear_velocity(Vector* velocity) = 0;
    virtual GENRESULT __stdcall get_ear_distance_factor(f32* distance) = 0;
    virtual GENRESULT __stdcall get_ear_doppler_factor(f32* doppler) = 0;
    virtual GENRESULT __stdcall get_ear_rolloff_factor(f32* rolloff) = 0;
};
