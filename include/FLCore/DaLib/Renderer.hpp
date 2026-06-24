#pragma once

#include "../FLCoreDefs.hpp"

#include "../Common/Engine/Rect.hpp"

struct IView
{
    virtual void __stdcall u00(){};
    virtual void __stdcall u04(){};
    virtual void __stdcall u08(){};
    virtual Vector* __stdcall GetVector() { return nullptr; };
    virtual Matrix* __stdcall GetMatrix1() { return nullptr; };
    virtual Rect* __stdcall GetRect() { return nullptr; };
    virtual void __stdcall u18(){};
    virtual void __stdcall u1C(){};
    virtual void __stdcall u20(){};
    virtual void __stdcall u24(){};
    virtual void __stdcall u28(){};
    virtual void __stdcall u2C(){};
    virtual void __stdcall u30(){};
    virtual void __stdcall u34(){};
    virtual void __stdcall ScreenToClient(Vector& Vector, float x, float y){};
    virtual void __stdcall u3C(){};
    virtual Matrix* __stdcall GetMatrix2() { return nullptr; };
    virtual void __stdcall u44(){};
    virtual void __stdcall u48(){};
    virtual void __stdcall u4C(){};
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
