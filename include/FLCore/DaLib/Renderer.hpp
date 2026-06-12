#pragma once

#include "../FLCoreDefs.hpp"

#include "../Common/Engine/Rect.hpp"

struct IView
{
    virtual void __stdcall u00() = 0;
    virtual void __stdcall u04() = 0;
    virtual void __stdcall u08() = 0;
    virtual Vector* __stdcall GetVector() = 0;
    virtual Matrix* __stdcall GetMatrix1() = 0;
    virtual Rect* __stdcall GetRect() = 0;
    virtual void __stdcall u18() = 0;
    virtual void __stdcall u1C() = 0;
    virtual void __stdcall u20() = 0;
    virtual void __stdcall u24() = 0;
    virtual void __stdcall u28() = 0;
    virtual void __stdcall u2C() = 0;
    virtual void __stdcall u30() = 0;
    virtual void __stdcall u34() = 0;
    virtual void __stdcall ScreenToClient(Vector& Vector, float x, float y) = 0;
    virtual void __stdcall u3C() = 0;
    virtual Matrix* __stdcall GetMatrix2() = 0;
    virtual void __stdcall u44() = 0;
    virtual void __stdcall u48() = 0;
    virtual void __stdcall u4C() = 0;
};

struct Fl3d;
struct IRenderer2
{
    virtual void __stdcall u00() = 0;
    virtual void __stdcall u04() = 0;
    virtual void __stdcall u08() = 0;
    virtual void __stdcall u0C() = 0;
    virtual void __stdcall u10() = 0;
    virtual void __stdcall u14() = 0;
    virtual void __stdcall u18() = 0;
    virtual void __stdcall Draw3d(const IView* View, const Fl3d* _3d, float a1, unsigned int a2, // 0x800
                                  unsigned int a3, unsigned int a4) = 0;
};
