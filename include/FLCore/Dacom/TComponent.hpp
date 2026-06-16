#pragma once

#include "../FLCoreDefs.hpp"

#include "Dacom.hpp"
#include "IdaComponent.hpp"

// Template class for Base DA Components

#define daoffsetofclass(base, derived) ((u32)(static_cast<base*>((derived*)8)) - 8)
#define daoffsetofmember(base, member) (size_t)((&(((base*)0)->member)) + 0)
#define dasizeofmember(base, member) \
    (size_t)((&(((base*)0)->member)) + 1) - (size_t)((&(((base*)0)->member)) + 0)

struct _DACOM_INTMAP_ENTRY
{
    const char* interface_name;
    u32 offset;
};

#define BEGIN_DACOM_MAP_INBOUND(x)                              \
  public:                                                       \
    const static _DACOM_INTMAP_ENTRY* __stdcall _GetEntriesIn() \
    {                                                           \
        typedef x _DaComMapClass;                               \
        static const _DACOM_INTMAP_ENTRY _entries[] = {

#define BEGIN_DACOM_MAP_OUTBOUND(x)                              \
  public:                                                        \
    const static _DACOM_INTMAP_ENTRY* __stdcall _GetEntriesOut() \
    {                                                            \
        typedef x _DaComMapClass;                                \
        static const _DACOM_INTMAP_ENTRY _entries[] = {

#define DACOM_INTERFACE_ENTRY(x)              { #x, daoffsetofclass(x, _DaComMapClass) },
#define DACOM_INTERFACE_ENTRY2(x, y)          { x, daoffsetofclass(y, _DaComMapClass) },
#define DACOM_INTERFACE_ENTRY_REF(x, y)       { x, daoffsetofmember(_DaComMapClass, y) | 0x80000000 },
#define DACOM_INTERFACE_ENTRY_AGGREGATE(x, y) { x, daoffsetofmember(_DaComMapClass, y) },
#define END_DACOM_MAP()   {0, 0}} \
    ;                             \
    return _entries;              \
    }

template <class Base>
struct DAComponent : public Base
{
    u32 ref_count;

    DAComponent(void) { ref_count = 1; }

    /* IDAComponent methods */

    DACOM_DEFMETHOD(QueryInterface)(const char* interface_name, void** instance);
    DACOM_DEFMETHOD_(u32, AddRef)(void);
    DACOM_DEFMETHOD_(u32, Release)(void);
};

template <class Base>
GENRESULT DAComponent<Base>::QueryInterface(const char* interface_name, void** instance)
{
    int i;
    const _DACOM_INTMAP_ENTRY* interfaces = Base::_GetEntriesIn();

    for (i = 0; interfaces[i].interface_name; i++)
    {
        if (strcmp(interfaces[i].interface_name, interface_name) == 0)
        {
            IDAComponent* result;

            if (interfaces[i].offset & 0x80000000)
            {
                result = *((IDAComponent**)(((char*)this) + (interfaces[i].offset & ~0x80000000)));
            }
            else
            {
                result = (IDAComponent*)(((char*)this) + interfaces[i].offset);
            }

            result->AddRef();
            *instance = result;
            return GR_OK;
        }
    }

    *instance = 0;
    return GR_INTERFACE_UNSUPPORTED;
}

template <class Base>
u32 DAComponent<Base>::AddRef(void)
{
    ref_count++;
    return ref_count;
}

template <class Base>
u32 DAComponent<Base>::Release(void)
{
    if (ref_count > 0)
    {
        ref_count--;
    }

    if (ref_count == 0)
    {
        ref_count++; // artificially add reference to prevent infinite loops
        delete this;
        return 0;
    }

    return ref_count;
}

// Debug version of DAComponent
template <class Base>
struct DADebugComponent : public DAComponent<Base>
{
    DACOM_DEFMETHOD_(u32, AddRef)(void)
    {
        u32 ret = DAComponent<Base>::AddRef();
        return ret;
    }

    //

    DACOM_DEFMETHOD_(u32, Release)(void)
    {
        u32 ret = DAComponent<Base>::Release();
        return ret;
    }
};

//-------------------Component Factory Implementation-----------------------//

template <class ClassType, class DescType>
struct DACOM_NO_VTABLE DAComponentFactoryBase : public IComponentFactory
{
    u32 ref_count;
    const char* className;

    DAComponentFactoryBase(const char* _className)
    {
        ref_count = 1;
        if ((className = _className) == 0)
        {
            className = ClassType::_GetEntriesIn()->interface_name;
        }
    }

    /* IDAComponent methods */
    DACOM_DEFMETHOD(QueryInterface)(const char* interface_name, void** instance);
    DACOM_DEFMETHOD_(u32, AddRef)(void);
    DACOM_DEFMETHOD_(u32, Release)(void);
};

template <class ClassType, class DescType>
GENRESULT DAComponentFactoryBase<ClassType, DescType>::QueryInterface(const char* interface_name,
                                                                      void** instance)
{
    *instance = 0;
    if (strcmp(interface_name, IID_IComponentFactory) != 0)
    {
        return GR_INTERFACE_UNSUPPORTED;
    }

    *instance = this;
    AddRef();
    return GR_OK;
}

template <class ClassType, class DescType>
u32 DAComponentFactoryBase<ClassType, DescType>::AddRef(void)
{
    ref_count++;
    return ref_count;
}

template <class ClassType, class DescType>
u32 DAComponentFactoryBase<ClassType, DescType>::Release(void)
{
    if (ref_count > 0)
    {
        ref_count--;
    }
    if (ref_count == 0)
    {
        ref_count++; // artificially add reference to prevent infinite loops
        delete this;
        return 0;
    }
    return ref_count;
}

template <class ClassType, class DescType>
struct DAComponentFactory : public DAComponentFactoryBase<ClassType, DescType>
{
    DAComponentFactory(const char* _className) : DAComponentFactoryBase<ClassType, DescType>(_className) {}

    /* IComponentFactory methods */

    DACOM_DEFMETHOD(CreateInstance)(DACOMDESC* descriptor, void** instance);
};

template <class ClassType, class DescType>
GENRESULT DAComponentFactory<ClassType, DescType>::CreateInstance(DACOMDESC* descriptor, void** instance)
{
    GENRESULT result = GR_OK;
    ClassType* pNewInstance = 0;
    DescType* lpDesc = (DescType*)descriptor;

    // If unsupported interface requested, fail call

    if ((lpDesc->size != sizeof(*lpDesc)) || strcmp(lpDesc->interface_name, DAComponentFactory::className))
    {
        result = GR_INTERFACE_UNSUPPORTED;
        goto Done;
    }

    // Create an instance of ClassType
    if ((pNewInstance = new ClassType) == 0)
    {
        result = GR_OUT_OF_MEMORY;
        goto Done;
    }

    if ((result = pNewInstance->init(lpDesc)) != GR_OK)
    {
        // initialization failed!
        delete pNewInstance;
        pNewInstance = 0;
    }
Done:
    *instance = pNewInstance;
    return result;
}

//-------------------Component Factory Implementation 2---------------------//

template <class ClassType, class DescType>
struct DAComponentFactory2 : public DAComponentFactoryBase<ClassType, DescType>
{
    DAComponentFactory2(const char* _className) : DAComponentFactoryBase<ClassType, DescType>(_className) {}

    /* IComponentFactory methods */

    DACOM_DEFMETHOD(CreateInstance)(DACOMDESC* descriptor, void** instance);
};

template <class ClassType, class DescType>
GENRESULT DAComponentFactory2<ClassType, DescType>::CreateInstance(DACOMDESC* descriptor, void** instance)
{
    GENRESULT result = GR_OK;
    ClassType* pNewInstance = 0;
    DescType* lpDesc = (DescType*)descriptor;

    //
    // If unsupported interface requested, fail call
    //

    if ((lpDesc->size != sizeof(*lpDesc)) || strcmp(lpDesc->interface_name, this->className))
    {
        result = GR_INTERFACE_UNSUPPORTED;
        goto Done;
    }

    //
    // Create an instance of ClassType
    //

    if ((pNewInstance = new ClassType(lpDesc)) == 0)
    {
        result = GR_OUT_OF_MEMORY;
        goto Done;
    }

    if ((result = pNewInstance->init(lpDesc)) != GR_OK)
    {
        if (lpDesc->inner)
        {
            *(lpDesc->inner) = 0; // reset it to NULL
        }
        //
        // initialization failed!
        delete pNewInstance;
        pNewInstance = 0;
    }
Done:
    *instance = pNewInstance;
    return result;
}

//----------------Inner Component Implementation (for Aggregation)----------//

template <class Type, class Base = IDAComponent>
struct DAComponentInner : public Base
{
    u32 ref_count;
    Type* owner;

    DAComponentInner(Type* _owner)
    {
        ref_count = 1;
        owner = _owner;
    }

    /* IDAComponent methods */

    DACOM_DEFMETHOD(QueryInterface)(const char* interface_name, void** instance);
    DACOM_DEFMETHOD_(u32, AddRef)(void);
    DACOM_DEFMETHOD_(u32, Release)(void);
};

template <class Type, class Base>
GENRESULT DAComponentInner<Type, Base>::QueryInterface(const char* interface_name, void** instance)
{
    int i;
    const _DACOM_INTMAP_ENTRY* interfaces = owner->_GetEntriesIn();

    for (i = 0; interfaces[i].interface_name; i++)
    {
        if (strcmp(interfaces[i].interface_name, interface_name) == 0)
        {
            IDAComponent* result;

            if (interfaces[i].offset & 0x80000000)
            {
                result = *((IDAComponent**)(((char*)owner) + (interfaces[i].offset & ~0x80000000)));
            }
            else
            {
                result = (IDAComponent*)(((char*)owner) + interfaces[i].offset);
            }

            result->AddRef();
            *instance = result;
            return GR_OK;
        }
    }

    *instance = 0;
    return GR_INTERFACE_UNSUPPORTED;
}

template <class Type, class Base>
u32 DAComponentInner<Type, Base>::AddRef(void)
{
    ref_count++;
    return ref_count;
}

template <class Type, class Base>
u32 DAComponentInner<Type, Base>::Release(void)
{
    if (ref_count > 0)
    {
        ref_count--;
    }

    if (ref_count == 0)
    {
        ref_count++; // artificially add reference to prevent infinite loops
        delete owner;
        return 0;
    }

    return ref_count;
}

//--------------------------Aggregate implementation------------------------//

template <class Base>
struct DAComponentAggregate : public Base
{
    IDAComponent* outerComponent;
    DAComponentInner<Base> innerComponent;

    DAComponentAggregate(struct AGGDESC* desc) : innerComponent(this)
    {
        if ((outerComponent = desc->outer) == 0)
        {
            outerComponent = &innerComponent;
        }
        else
        {
            *(desc->inner) = &innerComponent;
        }
    }

    /* IDAComponent methods */

    DACOM_DEFMETHOD(QueryInterface)(const char* interface_name, void** instance);
    DACOM_DEFMETHOD_(u32, AddRef)(void);
    DACOM_DEFMETHOD_(u32, Release)(void);
};

template <class Base>
GENRESULT DAComponentAggregate<Base>::QueryInterface(const char* interface_name, void** instance)
{
    return outerComponent->QueryInterface(interface_name, instance);
}

template <class Base>
u32 DAComponentAggregate<Base>::AddRef(void)
{
    return outerComponent->AddRef();
}

template <class Base>
u32 DAComponentAggregate<Base>::Release(void)
{
    return outerComponent->Release();
}

// Debug version of DAComponentAggregate
template <class Base>
struct DADebugComponentAggregate : public DAComponentAggregate<Base>
{
    DADebugComponentAggregate(struct AGGDESC* desc) : DAComponentAggregate<Base>(desc) {}

    DACOM_DEFMETHOD_(u32, AddRef)(void)
    {
        u32 ret = DAComponentAggregate<Base>::AddRef();
        return ret;
    }

    DACOM_DEFMETHOD_(u32, Release)(void)
    {
        u32 ret = DAComponentAggregate<Base>::Release();
        return ret;
    }
};
