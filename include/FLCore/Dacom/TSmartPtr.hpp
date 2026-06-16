#pragma once

#include "Dacom.hpp"

#include <comip.h>

template <class Type>
class COMPTR
{
  public:
    Type* ptr;

    COMPTR(void) { ptr = 0; }

    COMPTR(Type* _ptr)
    {
        if ((ptr = _ptr) != 0)
        {
            ptr->AddRef();
        }
    }

    COMPTR(const COMPTR<Type>& new_ptr)
    {
        if ((ptr = new_ptr.ptr) != 0)
        {
            ptr->AddRef();
        }
    }

    ~COMPTR(void) { free(); }

    void free(void)
    {
        if (ptr)
        {
            ptr->Release();
            ptr = 0;
        }
    }

    Type* operator=(Type* new_ptr)
    {
        if (ptr != new_ptr)
        {
            free();
            if ((ptr = new_ptr) != 0)
            {
                ptr->AddRef();
            }
        }
        return (Type*)ptr;
    }

    const COMPTR& operator=(const COMPTR<Type>& new_ptr)
    {
        free();
        if ((ptr = new_ptr.ptr) != 0)
        {
            ptr->AddRef();
        }

        return *this;
    }

    operator void**(void)
    {
        free();
        return (void**)&ptr;
    }

    operator Type**(void)
    {
        free();
        return (Type**)&ptr;
    }

    operator Type*(void) const { return (Type*)ptr; }

    Type* operator->(void) const { return (Type*)ptr; }

    // EMAURER:  these seem as though they could be const,
    // but having them const causes existing code elsewhere
    // in the libraries not to compile.

    bool operator==(const int i) // const
    {
        return (ptr == (Type*)i);
    }

    bool operator!=(const int i) // const
    {
        return (ptr != (Type*)i);
    }

    bool operator==(Type* cmp) // const
    {
        return (((Type*)ptr) == cmp);
    }

    bool operator!=(Type* cmp) // const
    {
        return (((Type*)ptr) != cmp);
    }

    operator bool(void) // const
    {
        return (ptr != 0);
    }

    bool operator!(void) const { return (ptr == 0); }

    bool operator==(const int i) const { return (ptr == (Type*)i); }

    bool operator!=(const int i) const { return (ptr != (Type*)i); }
};
