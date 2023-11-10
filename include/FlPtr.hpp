#pragma once

template <typename P>
class CPtrBase
{
    public:
        CPtrBase(P* ptr, bool increments = true) : _ptr(ptr)
        {
            if (increments)
            {
                increment();
            }
        }

        CPtrBase() : _ptr(nullptr) {}

        virtual ~CPtrBase() { decrement(); }

        CPtrBase(CPtrBase& ptr) : _ptr(ptr.get()) { increment(); }

        CPtrBase(CPtrBase&& ptr) noexcept : _ptr(ptr.get())
        {
            increment();
            ptr.decrement();
            ptr._ptr = nullptr;
        }

        P* operator->() const { return _ptr; }

        const P* get() const { return _ptr; }

        P* get() { return _ptr; }

        template <typename P2>
        explicit operator CPtrBase<P2>() const
        {
            return CPtrBase<P2>(_ptr);
        }

        explicit operator bool() const { return _ptr != nullptr; }

        bool operator!() const { return _ptr == nullptr; }

        CPtrBase<P>& set(P* ptr, bool increments = true) noexcept
        {
            decrement();
            _ptr = ptr;
            if (increments)
            {
                increment();
            }
            return *this;
        }

        CPtrBase<P>& operator=(P* ptr) noexcept { return set(ptr); }

        virtual CPtrBase<P>& operator=(nullptr_t) noexcept { return set(nullptr, false); }

        bool operator==(const CObject* ptr) const { return _ptr == ptr; }

        bool operator!=(const CObject* ptr) const { return _ptr != ptr; }

        template <typename P2>
        bool operator==(const CPtrBase<P2>& ptr) const
        {
            return _ptr == ptr.get();
        }

        template <typename P2>
        bool operator!=(const CPtrBase<P2>& ptr) const
        {
            return _ptr != ptr.get();
        }

        template <typename T>
        T& read(size_t offset)
        {
            return *reinterpret_cast<T*>(reinterpret_cast<char*>(_ptr) + offset);
        }

        template <typename T>
        T* readPtr(size_t offset)
        {
            return reinterpret_cast<T*>(reinterpret_cast<char*>(_ptr) + offset);
        }

        template <typename T>
        const T& read(size_t offset) const
        {
            return *reinterpret_cast<T*>(reinterpret_cast<char*>(_ptr) + offset);
        }

        template <typename T>
        const T* readPtr(size_t offset) const
        {
            return reinterpret_cast<T*>(reinterpret_cast<char*>(_ptr) + offset);
        }

        [[nodiscard]]
        std::pair<Vector, Vector> extents() const
        {
            std::pair<Vector, Vector> p;
            _ptr->get_surface_extents(p.first, p.second);

            return p;
        }

        Vector extents_size() const
        {
            Vector p1, p2;
            _ptr->get_surface_extents(p1, p2);

            return p2 - p1;
        }

        float get_radius()
        {
            Vector dummy;
            return PhySys::GetRadiusR(_ptr, true, dummy);
        }

        void set_internal_position(const Vector& position) { *(Vector*)((char*)_ptr + 0xd0) = position; }

        CObject::Class get_class() { return *(CObject::Class*)(((char*)_ptr) + 0x4C); }

        uint get_system() { return *(CObject::Class*)(((char*)_ptr) + 0x50); }

    protected:
        CPtrBase& operator=(const CPtrBase& other)
        {
            decrement();

            _ptr = other._ptr;

            increment();

            return *this;
        }

        void increment()
        {
            if (_ptr)
            {
                int i = const_cast<std::remove_const_t<P>*>(_ptr)->AddRef();
            }
        }

        void decrement()
        {
            if (_ptr)
            {
                if (const int i = const_cast<std::remove_const_t<P>*>(_ptr)->Release(); i == 0)
                {
                    _ptr = nullptr;
                }
            }
        }

        P* _ptr;
};

template <typename P>
class CPtrConvertBase : public CPtrBase<P>
{
    public:
        CPtrConvertBase() : CPtrBase<P>() {}
        CPtrConvertBase(P* ptr, bool increments = true) : CPtrBase<P>(ptr, increments) {}
        CPtrConvertBase(CObject* ptr, bool increments = true) : CPtrBase<P>(dynamic_cast<P*>(ptr), increments) {}
        CPtrConvertBase(const CObject* ptr, bool increments = true) : CPtrBase<P>(dynamic_cast<P*>(ptr), increments)
        {
            if (!std::is_const_v<P>)
            {
                throw std::invalid_argument("Given pointer is const, but smart pointer class is not.");
            }
        }

        CPtrConvertBase<P>& operator=(nullptr_t) noexcept override
        {
            this->decrement();
            this->_ptr = nullptr;
            return *this;
        }

        virtual IObjRW* iobj() const
        {
            if (!this->_ptr)
            {
                return nullptr;
            }

#ifdef FLHOOK
            IObjInspectImpl* inspect;
            uint iDunno;
            uint id = this->_ptr->get_id();
            if (!FLHook::GetShipInspect(id, inspect, iDunno))
            {
                return nullptr;
            }
            else
            {
                return (IObjRW*)inspect;
            }
#else
// TODO: Setup non-FLHook inspect
#endif
        }
};

template <typename P, CObject::Class C>
class CPtr : public CPtrConvertBase<P>
{
    public:
        CPtr() : CPtrConvertBase<P>() {}
        CPtr(P* ptr, bool increments = true) : CPtrConvertBase<P>(ptr, increments) { check_player(); }
        CPtr(CObject* ptr, bool increments = true) : CPtrConvertBase<P>(ptr, increments) { check_player(); }
        CPtr(const CObject* ptr, bool increments = true) : CPtrConvertBase<P>(ptr, increments) { check_player(); }
        CPtr(uint id) : CPtrConvertBase<P>(reinterpret_cast<P*>(CObject::Find(id, C)), false) { check_player(); }
        CPtr(long lid) : CPtrConvertBase<P>(reinterpret_cast<P*>(CObject::Find(lid, C)), false) { check_player(); }

        static bool empty() { return count() == 0; }

        static size_t count() { return CObject::Count(C); }

        CPtr<P, C>& operator=(nullptr_t) noexcept
        {
            this->decrement();
            this->_ptr = nullptr;
            return *this;
        }

        CPtr<P, C>& operator=(uint id)
        {
            this->decrement();
            this->_ptr = (P*)CObject::Find(id, C);
            return *this;
        }

        class iterator
        {
            public:
                iterator() : _cptr(CObject::FindFirst(C)) {}

                P* operator->() const { return _cptr.operator->(); }

                explicit operator bool() const { return _cptr.operator bool(); }

                bool operator!() const { return !(_cptr.operator bool()); }

                void operator++() { _cptr = CPtr(CObject::FindNext()); }

                void operator++(int) { _cptr = CPtr(CObject::FindNext()); }

                CPtr& get() { return _cptr; }

            protected:
                CPtr _cptr;
        };

    protected:
        void check_player() {}
};

template <typename P, CObject::Class C>
class CPtrMask : public CPtr<P, C>
{
    public:
        CPtrMask() : CPtr<P, C>() {}
        CPtrMask(P* ptr, bool increments = true) : CPtr<P, C>(ptr, increments) {}
        CPtrMask(CObject* ptr, bool increments = true) : CPtr<P, C>(ptr, increments) {}
        CPtrMask(const CObject* ptr, bool increments = true) : CPtr<P, C>(ptr, increments) {}

    protected:
        template <typename T>
        P* find_array(T id, std::initializer_list<CObject::Class> a)
        {
            for (auto c : a)
            {
                auto p = CObject::Find(id, c);
                if (p)
                {
                    return reinterpret_cast<P*>(p);
                }
            }

            return nullptr;
        }
};

class CSimplePtr : public CPtrMask<CSimple, CObject::CSIMPLE_MASK>
{
    public:
        using CPtrMask::CPtrMask;
        CSimplePtr() = default;
        CSimplePtr(uint id) : CPtrMask(find(id), false) {}
        CSimplePtr(long lid) : CPtrMask(find(lid), false) {}

    protected:
        template <typename T>
        CSimple* find(T id)
        {
            return find_array<T>(id,
                                 {
                                     CObject::CSHIP_OBJECT,
                                     CObject::CSOLAR_OBJECT,
                                     CObject::CGUIDED_OBJECT,
                                     CObject::CBEAM_OBJECT,
                                     CObject::CLOOT_OBJECT,
                                     CObject::CCOUNTERMEASURE_OBJECT,
                                     CObject::CASTEROID_OBJECT,
                                     CObject::CMINE_OBJECT,
                                 });
        }
};

class CProjectilePtr : public CPtrMask<CProjectile, CObject::CPROJECTILE_MASK>
{
    public:
        using CPtrMask::CPtrMask;
        CProjectilePtr() = default;
        CProjectilePtr(uint id) : CPtrMask(find(id), false) {}
        CProjectilePtr(long lid) : CPtrMask(find(lid), false) {}

    protected:
        template <typename T>
        CProjectile* find(T id)
        {
            return find_array<T>(id, { CObject::CGUIDED_OBJECT, CObject::CBEAM_OBJECT, CObject::CMINE_OBJECT, CObject::CCOUNTERMEASURE_OBJECT });
        }
};

class CEqObjPtr : public CPtrMask<CEqObj, CObject::CEQOBJ_MASK>
{
    public:
        using CPtrMask::CPtrMask;
        CEqObjPtr() = default;
        CEqObjPtr(uint id) : CPtrMask(find(id), false) {}
        CEqObjPtr(long lid) : CPtrMask(find(lid), false) {}

    protected:
        template <typename T>
        CEqObj* find(T id)
        {
            return find_array<T>(id, { CObject::CSHIP_OBJECT, CObject::CSOLAR_OBJECT });
        }
};

typedef CPtr<CObject, CObject::COBJECT_MASK> CObjPtr;

typedef CPtr<CEquipmentObj, CObject::CEQUIPMENT_OBJECT> CEquipmentPtr;
typedef CPtr<CDynamicAsteroid, CObject::CDYNAMICASTEROID_OBJECT> CDynamicAsteroidPtr;

typedef CPtr<CLoot, CObject::CLOOT_OBJECT> CLootPtr;
typedef CPtr<CAsteroid, CObject::CASTEROID_OBJECT> CAsteroidPtr;

typedef CPtr<CMine, CObject::CMINE_OBJECT> CMinePtr;
typedef CPtr<CCounterMeasure, CObject::CCOUNTERMEASURE_OBJECT> CCountermeasurePtr;
typedef CPtr<CBeam, CObject::CBEAM_OBJECT> CBeamPtr;
typedef CPtr<CGuided, CObject::CGUIDED_OBJECT> CGuidedPtr;

typedef CPtr<CShip, CObject::CSHIP_OBJECT> CShipPtr;
typedef CPtr<CSolar, CObject::CSOLAR_OBJECT> CSolarPtr;

class CCSimplePtr : public CPtrMask<const CSimple, CObject::CSIMPLE_MASK>
{
    public:
        using CPtrMask::CPtrMask;
        CCSimplePtr() = default;
        CCSimplePtr(uint id) : CPtrMask(find(id), false) {}
        CCSimplePtr(long lid) : CPtrMask(find(lid), false) {}

    protected:
        template <typename T>
        const CSimple* find(T id)
        {
            return find_array<T>(id,
                                 { CObject::CLOOT_OBJECT,
                                   CObject::CASTEROID_OBJECT,
                                   CObject::CMINE_OBJECT,
                                   CObject::CCOUNTERMEASURE_OBJECT,
                                   CObject::CBEAM_OBJECT,
                                   CObject::CGUIDED_OBJECT,
                                   CObject::CSOLAR_OBJECT,
                                   CObject::CSHIP_OBJECT });
        }
};

class CCProjectilePtr : public CPtrMask<const CProjectile, CObject::CPROJECTILE_MASK>
{
    public:
        using CPtrMask::CPtrMask;
        CCProjectilePtr() = default;
        CCProjectilePtr(uint id) : CPtrMask(find(id), false) {}
        CCProjectilePtr(long lid) : CPtrMask(find(lid), false) {}

    protected:
        template <typename T>
        const CProjectile* find(T id)
        {
            return find_array<T>(id, { CObject::CMINE_OBJECT, CObject::CCOUNTERMEASURE_OBJECT, CObject::CBEAM_OBJECT, CObject::CGUIDED_OBJECT });
        }
};

class CCEqObjPtr : public CPtrMask<const CEqObj, CObject::CEQOBJ_MASK>
{
    public:
        using CPtrMask::CPtrMask;
        CCEqObjPtr() = default;
        CCEqObjPtr(uint id) : CPtrMask(find(id), false) {}
        CCEqObjPtr(long lid) : CPtrMask(find(lid), false) {}

    protected:
        template <typename T>
        const CEqObj* find(T id)
        {
            return find_array<T>(id, { CObject::CSOLAR_OBJECT, CObject::CSHIP_OBJECT });
        }
};

typedef CPtr<const CEquipmentObj, CObject::CEQUIPMENT_OBJECT> CCEquipmentPtr;
typedef CPtr<const CDynamicAsteroid, CObject::CDYNAMICASTEROID_OBJECT> CCDynamicAsteroidPtr;

typedef CPtr<const CLoot, CObject::CLOOT_OBJECT> CCLootPtr;
typedef CPtr<const CAsteroid, CObject::CASTEROID_OBJECT> CCAsteroidPtr;

typedef CPtr<const CMine, CObject::CMINE_OBJECT> CCMinePtr;
typedef CPtr<const CCounterMeasure, CObject::CCOUNTERMEASURE_OBJECT> CCCountermeasurePtr;
typedef CPtr<const CBeam, CObject::CBEAM_OBJECT> CCBeamPtr;
typedef CPtr<const CGuided, CObject::CGUIDED_OBJECT> CCGuidedPtr;

typedef CPtr<const CShip, CObject::CSHIP_OBJECT> CCShipPtr;
typedef CPtr<const CSolar, CObject::CSOLAR_OBJECT> CCSolarPtr;
