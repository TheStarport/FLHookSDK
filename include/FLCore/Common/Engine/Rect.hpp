#pragma once

#include "../../FLCoreDefs.hpp"

struct IMPORT Rect
{
    Rect(int, int, int, int);
    Rect();
    Rect& operator=(const Rect&);
    int area() const;
    int bottommost() const;
    void clear();
    void get_center(int*, int*) const;
    int height() const;
    void init(int, int, int, int);
    void init_from_ltrb(int, int, int, int);
    int leftmost() const;
    bool nonnull() const;
    bool null() const;
    bool point_is_inside(int, int) const;
    int rightmost() const;
    int topmost() const;
    int width() const;

  public:
    int left;
    int top;
    int right;
    int bottom;
};

IMPORT bool operator!=(const Rect&, const Rect&);
IMPORT Rect RECT_to_Rect(const tagRECT&);
IMPORT tagRECT Rect_to_RECT(const Rect&);
IMPORT struct ViewRect Rect_to_ViewRect(const Rect&);
IMPORT Rect ViewRect_to_Rect(const ViewRect&);
IMPORT Rect rect_intersect(const Rect&, const Rect&);
IMPORT Rect rect_union(const Rect&, const Rect&);
