#ifndef GINSENG_GINSENG_HPP
#define GINSENG_GINSENG_HPP

#include <algorithm>
#include <bitset>
#include <memory>
#include <type_traits>
#include <vector>

#include <cstddef>

namespace Ginseng {

namespace _detail {

    using namespace std;

// TypeGuid

    using TypeGuid = size_t;

    inline TypeGuid nextTypeGuid() noexcept {
        static TypeGuid x = 0;
        return ++x;
    }

    template <typename T>
    struct TypeGuidHolder {
        static const TypeGuid value;
    };

    template <typename T>
    const TypeGuid TypeGuidHolder<T>::value = nextTypeGuid();

    template <typename T>
    TypeGuid getTypeGuid() {
        return TypeGuidHolder<T>::value;
    }

// DynamicBitset

    class DynamicBitset {
    public:
        using size_type = size_t;

        static constexpr size_type N_BITS = 64;

        DynamicBitset() : sdo(0), numbits(N_BITS) {}
        
        DynamicBitset(const DynamicBitset&) = delete;
        DynamicBitset& operator=(const DynamicBitset&) = delete;

        DynamicBitset(DynamicBitset&& other) : sdo(0), numbits(N_BITS) {
            if (other.numbits == N_BITS) {
                sdo = other.sdo;
            } else {
                new (&dyna) unique_ptr<bitset<N_BITS>[]>(move(other.dyna));
                other.dyna.~unique_ptr<bitset<N_BITS>[]>();
                numbits = other.numbits;
                other.numbits = N_BITS;
                other.sdo = 0;
            }
        }

        DynamicBitset& operator=(DynamicBitset&& other) {
            if (numbits != N_BITS) {
                dyna.~unique_ptr<bitset<N_BITS>[]>();
            }
            if (other.numbits == N_BITS) {
                sdo = other.sdo;
            } else {
                new (&dyna) unique_ptr<bitset<N_BITS>[]>(move(other.dyna));
                other.dyna.~unique_ptr<bitset<N_BITS>[]>();
            }
            numbits = other.numbits;
            other.sdo = 0;
            other.numbits = N_BITS;
            return *this;
        }

        ~DynamicBitset() {
            if (numbits != N_BITS) {
                dyna.~unique_ptr<bitset<N_BITS>[]>();
            }
        }

        size_type size() const { return numbits; }

        void resize(size_type ns) {
            if (ns > numbits) {
                auto count = (ns+N_BITS-1u)/N_BITS;
                auto newlen = count * N_BITS;
                auto newptr = make_unique<bitset<N_BITS>[]>(count);
                if (numbits == N_BITS) {
                    newptr[0] = sdo;
                } else {
                    copy(dyna.get(), dyna.get()+(numbits/N_BITS), newptr.get());
                    fill(newptr.get()+(numbits/N_BITS), newptr.get()+(newlen/N_BITS), 0);
                }
                dyna = move(newptr);
                numbits = newlen;
            }
        }

        bool get(size_type i) const {
            if (__builtin_expect(numbits==N_BITS,1)) return sdo[i];
            else return dyna[i/64][i%64];
        }

        void set(size_type i) {
            resize(i+1);
            if (__builtin_expect(numbits==N_BITS,1)) sdo[i] = true;
            else dyna[i/64][i%64] = true;
        }

        void unset(size_type i) {
            resize(i+1);
            if (__builtin_expect(numbits==N_BITS,1)) sdo[i] = false;
            else dyna[i/64][i%64] = false;
        }

        void zero() {
            if (__builtin_expect(numbits==N_BITS,1)) {
                sdo = 0;
            } else {
                fill(dyna.get(), dyna.get()+numbits/N_BITS, 0);
            }
        }

    private:
        union {
            bitset<N_BITS> sdo;
            unique_ptr<bitset<N_BITS>[]> dyna;
        };
        size_type numbits;
    };

// Entity

    struct Entity
    {
        DynamicBitset components = {};
    };

// Queries

    /*! Has component
     *
     * When used as a visitor parameter, applies the matching logic for the parameter, but does not load the component.
     */
    template <typename T>
    struct Has
    {};

    /*! Visitor parameter inverter
     *
     * When used as a visitor parameter, inverts the matching logic for that parameter.
     */
    template <typename T>
    struct Not
    {};

    /*! Tag component
     *
     * When a tag component is stored in an entity, only the fact that it exists is recorded, no data is stored.
     */
    template <typename T>
    struct Tag
    {};

    /*! Optional component
     *
     * When used as a visitor parameter, applies the matching logic for the parameter, but does not cause the visit to fail.
     * 
     * Provides pointer-like access to the parameter.
     */
    template <typename T>
    class Maybe
    {
    public:
        Maybe() : com(nullptr) {}
        Maybe(const Maybe&) = default;
        Maybe(Maybe&&) = default;
        Maybe& operator=(const Maybe&) = default;
        Maybe& operator=(Maybe&&) = default;
        T* operator->() const { return com; }
        T& operator*() const { return *com; }
        explicit operator bool() const { return com; }
        T& get() const { return *com; }
    private:
        template <typename DB, typename EntID, typename... Components>
        friend struct Applier;
        Maybe(T* c) : com(c) {}
        T* com;
    };

    /*! Optional Tag component
     *
     * When used as a visitor parameter, applies the matching logic for the parameter, but does not cause the visit to fail.
     */
    template <typename T>
    class Maybe<Tag<T>>
    {
    public:
        Maybe() : tag(false) {}
        Maybe(const Maybe&) = default;
        Maybe(Maybe&&) = default;
        Maybe& operator=(const Maybe&) = default;
        Maybe& operator=(Maybe&&) = default;
        explicit operator bool() const { return tag; }
    private:
        template <typename DB, typename EntID, typename... Components>
        friend struct Applier;
        Maybe(bool t) : tag(t) {}
        bool tag;
    };

    // ComponentTraits

        struct ComponentTags
        {
            struct positive {};
            struct normal : positive {};
            struct noload : positive {};
            struct tagged : positive {};
            struct meta {};
            struct nofail : meta {};
            struct inverted : meta {};
            struct eid : meta {};
        };

        template <typename DB, typename Component>
        struct ComponentTraits
        {
            using tag = ComponentTags::normal;
            using com = Component;
        };

        template <typename DB, typename Component>
        struct ComponentTraits<DB, Has<Component>>
        {
            using tag = ComponentTags::noload;
            using com = Component;
        };

        template <typename DB, typename Component>
        struct ComponentTraits<DB, Tag<Component>>
        {
            using tag = ComponentTags::tagged;
            using com = Tag<Component>;
        };

        template <typename DB, typename Component>
        struct ComponentTraits<DB, Maybe<Component>>
        {
            using tag = ComponentTags::nofail;
            using com = Component;
        };

        template <typename DB, typename Component>
        struct ComponentTraits<DB, Not<Component>>
        {
            using tag = ComponentTags::inverted;
            using com = Component;
        };

        template <typename DB>
        struct ComponentTraits<DB, typename DB::EntID>
        {
            using tag = ComponentTags::eid;
            using com = void;
        };

    // Applier

        template <typename DB, typename PrimaryComponent, typename... Components>
        struct Applier;

        template <typename DB, typename PrimaryComponent, typename HeadCom, typename... TailComs>
        struct Applier<DB, PrimaryComponent, HeadCom, TailComs...>
        {
            using EntID = typename DB::EntID;
            using ComID = typename DB::ComID;

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::normal, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                auto& com = db.template getComponent<typename Traits::com>(eid);
                return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., com);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::noload, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid))
                {
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Has<typename Traits::com>{});
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::inverted, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                using InnerTraits = ComponentTraits<DB, typename Traits::com>;
                return inverted_helper<Traits>(typename InnerTraits::tag{}, db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void inverted_helper(ComponentTags::positive, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                if (!db.template hasComponent<typename Traits::com>(eid))
                {
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Not<typename Traits::com>{});
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void inverted_helper(ComponentTags::inverted, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                using InnerTraits = ComponentTraits<DB, typename Traits::com>;
                using NextTraits = ComponentTraits<DB, typename InnerTraits::com>;
                return helper<NextTraits>(typename NextTraits::tag{}, db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::tagged, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid))
                {
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., typename Traits::com{});
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::nofail, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                using InnerTraits = ComponentTraits<DB, typename Traits::com>;
                return nofail_helper<Traits>(typename InnerTraits::tag{}, db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void nofail_helper(ComponentTags::normal, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid)) {
                    auto& com = db.template getComponent<typename Traits::com>(eid);
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(&com));
                } else {
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(nullptr));
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void nofail_helper(ComponentTags::tagged, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid)) {
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(true));
                } else {
                    return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(false));
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::eid, DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., eid);
            }

            template <typename Visitor, typename... Args>
            static void try_apply(DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                using Traits = ComponentTraits<DB,HeadCom>;
                return helper<Traits>(typename Traits::tag{}, db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }
        };

        template <typename DB, typename PrimaryComponent, typename... TailComs>
        struct Applier<DB, PrimaryComponent, PrimaryComponent, TailComs...>
        {
            using EntID = typename DB::EntID;
            using ComID = typename DB::ComID;

            template <typename Visitor, typename... Args>
            static void try_apply(DB& db, EntID eid, ComID primary_cid, Visitor&& visitor, Args&&... args)
            {
                using Traits = ComponentTraits<DB,PrimaryComponent>;
                auto& com = db.template getComponentById<typename Traits::com>(primary_cid);
                return Applier<DB, PrimaryComponent, TailComs...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., com);
            }
        };

        template <typename DB, typename PrimaryComponent>
        struct Applier<DB, PrimaryComponent>
        {
            using EntID = typename DB::EntID;
            using ComID = typename DB::ComID;

            template <typename Visitor, typename... Args>
            static void try_apply(DB&, EntID, ComID, Visitor&& visitor, Args&&... args)
            {
                std::forward<Visitor>(visitor)(std::forward<Args>(args)...);
            }
        };

        template <typename DB, typename HeadCom, typename... TailComs>
        struct Applier<DB, void, HeadCom, TailComs...>
        {
            using EntID = typename DB::EntID;
            using ComID = typename DB::ComID;

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::normal, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                auto& com = db.template getComponent<typename Traits::com>(eid);
                return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., com);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::noload, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid))
                {
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Has<typename Traits::com>{});
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::inverted, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                using InnerTraits = ComponentTraits<DB, typename Traits::com>;
                return inverted_helper<Traits>(typename InnerTraits::tag{}, db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void inverted_helper(ComponentTags::positive, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                if (!db.template hasComponent<typename Traits::com>(eid))
                {
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Not<typename Traits::com>{});
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void inverted_helper(ComponentTags::inverted, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                using InnerTraits = ComponentTraits<DB, typename Traits::com>;
                using NextTraits = ComponentTraits<DB, typename InnerTraits::com>;
                return helper<NextTraits>(typename NextTraits::tag{}, db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::tagged, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid))
                {
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., typename Traits::com{});
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::nofail, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                using InnerTraits = ComponentTraits<DB, typename Traits::com>;
                return nofail_helper<Traits>(typename InnerTraits::tag{}, db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void nofail_helper(ComponentTags::normal, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid)) {
                    auto& com = db.template getComponent<typename Traits::com>(eid);
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(&com));
                } else {
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(nullptr));
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void nofail_helper(ComponentTags::tagged, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                if (db.template hasComponent<typename Traits::com>(eid)) {
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(true));
                } else {
                    return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., Maybe<typename Traits::com>(false));
                }
            }

            template <typename Traits, typename Visitor, typename... Args>
            static void helper(ComponentTags::eid, DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                return Applier<DB, void, TailComs...>::try_apply(db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)..., eid);
            }

            template <typename Visitor, typename... Args>
            static void try_apply(DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                using Traits = ComponentTraits<DB,HeadCom>;
                return helper<Traits>(typename Traits::tag{}, db, eid, std::forward<Visitor>(visitor), std::forward<Args>(args)...);
            }
        };

        template <typename DB>
        struct Applier<DB, void>
        {
            using EntID = typename DB::EntID;
            using ComID = typename DB::ComID;

            template <typename Visitor, typename... Args>
            static void try_apply(DB& db, EntID eid, Visitor&& visitor, Args&&... args)
            {
                std::forward<Visitor>(visitor)(std::forward<Args>(args)...);
            }
        };

    // VisitorKey

        template <typename DB, typename... Components>
        struct VisitorKey;
        
        template <typename DB, typename HeadCom, typename... TailComs>
        struct VisitorKey<DB, HeadCom, TailComs...>
        {
            using EntID = typename DB::EntID;
            using Traits = ComponentTraits<DB, HeadCom>;

            static bool helper(DB& db, EntID eid, ComponentTags::positive)
            {
                return VisitorKey<DB, TailComs...>::check(db, eid) && db.template hasComponent<typename Traits::com>(eid);
            }

            static bool helper(DB& db, EntID eid, ComponentTags::meta)
            {
                return VisitorKey<DB, TailComs...>::check(db, eid);
            }
            
            static bool check(DB& db, EntID eid)
            {
                return helper(db, eid, typename Traits::tag{});
            }
        };

        template <typename DB>
        struct VisitorKey<DB>
        {
            using EntID = typename DB::EntID;
            static bool check(DB&, EntID)
            {
                return true;
            }
        };

    // First

        template <typename T, typename... Ts>
        struct First
        {
            using type = T;
        };

        template <typename... Ts>
        using First_t = typename First<Ts...>::type;
    
    // GetPrimary

        template <typename T>
        struct Primary
        {
            using type = T;
        };
        
        template <typename DB, typename HeadTag, typename... Components>
        struct GetPrimary;
    
        template <typename DB, typename... Components>
        using GetPrimary_t = typename GetPrimary<DB, typename ComponentTraits<DB, First_t<Components...>>::tag, Components...>::type;

        template <typename DB, typename HeadTag, typename HeadCom, typename... Components>
        struct GetPrimary<DB, HeadTag, HeadCom, Components...>
        {
            using type = GetPrimary_t<DB, Components...>;
        };
        
        template <typename DB, typename HeadTag, typename HeadCom>
        struct GetPrimary<DB, HeadTag, HeadCom>
        {
            using type = Primary<void>;
        };
        
        template <typename DB, typename HeadCom, typename... Components>
        struct GetPrimary<DB, ComponentTags::normal, HeadCom, Components...>
        {
            using type = Primary<HeadCom>;
        };

        template <typename DB, typename HeadCom>
        struct GetPrimary<DB, ComponentTags::normal, HeadCom>
        {
            using type = Primary<HeadCom>;
        };
    
    // FindOther

        template <typename DB, typename T, bool Positive, typename... Ts>
        struct FindOther;
        
        template <typename DB, typename T, typename... Ts>
        using FindOther_t = typename FindOther<DB, T, is_base_of<ComponentTags::positive, typename ComponentTraits<DB, First_t<Ts...>>::tag>::value, Ts...>::type;

        template <typename DB, typename T, typename U, typename... Ts>
        struct FindOther<DB, T, true, U, Ts...>
        {
            using type = true_type;
        };
        
        template <typename DB, typename T, typename... Ts>
        struct FindOther<DB, T, true, T, Ts...>
        {
            using type = FindOther_t<DB, T, Ts...>;
        };
        
        template <typename DB, typename T, typename U, typename... Ts>
        struct FindOther<DB, T, false, U, Ts...>
        {
            using type = FindOther_t<DB, T, Ts...>;
        };
        
        template <typename DB, typename T, typename U>
        struct FindOther<DB, T, false, U>
        {
            using type = false_type;
        };
        
        template <typename DB, typename T>
        struct FindOther<DB, T, true, T>
        {
            using type = false_type;
        };

        template <typename DB, typename T>
        struct FindOther<DB, T, false, T>
        {
        };

    // VisitorTraits

        template <typename DB, typename... Components>
        struct VisitorTraitsImpl
        {
            using EntID = typename DB::EntID;
            using ComID = typename DB::ComID;
            using Key = VisitorKey<DB, Components...>;
            using PrimaryComponent = GetPrimary_t<DB, Components...>;
            using HasOtherComponents = FindOther_t<DB, typename PrimaryComponent::type, Components...>;

            template <typename Visitor>
            static void apply(DB& db, EntID eid, Visitor&& visitor)
            {
                Applier<DB, typename PrimaryComponent::type, Components...>::try_apply(db, eid, std::forward<Visitor>(visitor));
            }
            
            template <typename Visitor>
            static void apply(DB& db, EntID eid, ComID primary_cid, Visitor&& visitor)
            {
                Applier<DB, typename PrimaryComponent::type, Components...>::try_apply(db, eid, primary_cid, std::forward<Visitor>(visitor));
            }
        };

        template <typename DB, typename Visitor>
        struct VisitorTraits : VisitorTraits<DB,decltype(&decay_t<Visitor>::operator())>
        {};

        template <typename DB, typename R, typename... Ts>
        struct VisitorTraits<DB, R(&)(Ts...)> : VisitorTraitsImpl<DB,std::decay_t<Ts>...>
        {};

        template <typename DB, typename Visitor, typename R, typename... Ts>
        struct VisitorTraits<DB, R(Visitor::*)(Ts...)> : VisitorTraitsImpl<DB,std::decay_t<Ts>...>
        {};

        template <typename DB, typename Visitor, typename R, typename... Ts>
        struct VisitorTraits<DB, R(Visitor::*)(Ts...)const> : VisitorTraitsImpl<DB,std::decay_t<Ts>...>
        {};

        template <typename DB, typename Visitor, typename R, typename... Ts>
        struct VisitorTraits<DB, R(Visitor::*)(Ts...)&> : VisitorTraitsImpl<DB,std::decay_t<Ts>...>
        {};

        template <typename DB, typename Visitor, typename R, typename... Ts>
        struct VisitorTraits<DB, R(Visitor::*)(Ts...)const&> : VisitorTraitsImpl<DB,std::decay_t<Ts>...>
        {};

        template <typename DB, typename Visitor, typename R, typename... Ts>
        struct VisitorTraits<DB, R(Visitor::*)(Ts...)&&> : VisitorTraitsImpl<DB,std::decay_t<Ts>...>
        {};

// SparseSet

    class SparseSet
    {
    public:
        using size_type = std::size_t;
        virtual ~SparseSet() = 0;
        virtual void remove(size_type entid) = 0;
    };

    inline SparseSet::~SparseSet() = default;

    template <typename T>
    class SparseSetImpl final : public SparseSet
    {
    public:
        virtual ~SparseSetImpl() = default;

        void assign(size_type entid, T com)
        {
            if(entid >= entid_to_comid.size()) {
                entid_to_comid.resize(entid+1, -1);
            }

            auto comid = comid_to_entid.size();

            entid_to_comid[entid] = comid;
            comid_to_entid.push_back(entid);
            components.push_back(move(com));
        }

        virtual void remove(size_type entid) override final
        {
            auto last = comid_to_entid.size() - 1;
            auto comid = entid_to_comid[entid];

            entid_to_comid[entid] = -1;
            entid_to_comid[comid_to_entid[last]] = comid;

            comid_to_entid[comid] = comid_to_entid[last];
            comid_to_entid.pop_back();

            components[comid] = move(components[last]);
            components.pop_back();
        }

        size_type get_comid(size_type entid) const
        {
            return entid_to_comid[entid];
        }

        T& get_com(size_type comid)
        {
            return components[comid];
        }

        size_type get_entid(size_type comid) const
        {
            return comid_to_entid[comid];
        }

        auto size() const
        {
            return components.size();
        }

    private:
        vector<size_type> entid_to_comid;
        vector<size_type> comid_to_entid;
        vector<T> components;
    };

    template <typename T>
    class SparseSetImpl<Tag<T>> final : public SparseSet
    {
    public:
        virtual ~SparseSetImpl() = default;
        virtual void remove(size_type entid) override final {}
    };

/*! Database
 *
 * An Entity component Database. Uses the given allocator to allocate
 * components, and may also use the same allocator for internal data.
 *
 * @warning
 * This container does not perform any synchronization. Therefore, it is not
 * considered "thread-safe".
 */
class Database
{
public:
// IDs

    /*! Entity ID.
    */
    using EntID = size_t;

    /*! Component ID.
    */
    using ComID = size_t;

// Entity functions

    /*! Creates a new Entity.
    *
    * Creates a new Entity that has no components.
    *
    * @return EntID of the new Entity.
    */
    EntID makeEntity()
    {
        EntID eid;

        if (free_entities.empty())
        {
            eid = entities.size();
            entities.emplace_back();
        }
        else
        {
            eid = free_entities.back();
            free_entities.pop_back();
        }

        entities[eid].components.set(0);

        return eid;
    }

    /*! Destroys an Entity.
    *
    * Destroys the given Entity and all associated components.
    *
    * @param eid EntID of the Entity to erase.
    */
    void eraseEntity(EntID eid)
    {
        for (DynamicBitset::size_type i=1; i<entities[eid].components.size(); ++i) {
            if (entities[eid].components.get(i)) {
                component_sets[i]->remove(eid);
            }
        }

        entities[eid].components.zero();
        free_entities.push_back(eid);
    }

// Component functions

    /*! Create new component.
    *
    * Creates a new component from the given value and associates it with
    * the given Entity.
    * If a component of the same type already exists, it will be
    * overwritten.
    *
    * @param eid Entity to attach new component to.
    * @param com Component value.
    */
    template <typename T>
    void makeComponent(EntID eid, T&& com)
    {
        auto guid = getTypeGuid<T>();

        auto& ent_coms = entities[eid].components;

        auto& com_set = getOrCreateComSet<T>();
        
        if (guid < ent_coms.size() && ent_coms.get(guid))
        {
            auto cid = com_set.get_comid(eid);
            com_set.get_com(cid) = forward<T>(com);
        }
        else
        {
            com_set.assign(eid, forward<T>(com));
            ent_coms.set(guid);
        }
    }

    /*! Create new Tag component.
    *
    * Creates a new Tag component associates it with the given Entity.
    *
    * @param eid Entity to attach new Tag component to.
    * @param com Tag value.
    */
    template <typename T>
    void makeComponent(EntID eid, Tag<T> com)
    {
        auto guid = getTypeGuid<Tag<T>>();
        auto& ent_coms = entities[eid].components;

        getOrCreateComSet<Tag<T>>();

        ent_coms.set(guid);
    }

    /*! Erase a component.
    *
    * Destroys the given component and disassociates it from its Entity.
    *
    * @warning
    * All ComIDs associated with components of the component's Entity will
    * be invalidated.
    *
    * @tparam Com Type of the component to erase.
    * 
    * @param eid EntID of the entity.
    */
    template <typename Com>
    void eraseComponent(EntID eid)
    {
        auto guid = getTypeGuid<Com>();
        auto& com_set = *getComSet<Com>();
        com_set.remove(eid);
        entities[eid].components.unset(guid);
    }
    
    /*! Get a component.
    *
    * Gets a reference to the component of the given type
    * that is associated with the given entity.
    *
    * @warning
    * Behavior is undefined when the entity has no associated
    * component of the given type.
    *
    * @tparam Com Type of the component to get.
    * 
    * @param eid EntID of the entity.
    * @return Reference to the component.
    */
    template <typename Com>
    Com& getComponent(EntID eid)
    {
        auto& com_set = *getComSet<Com>();
        auto cid = com_set.get_comid(eid);
        return com_set.get_com(cid);
    }

    /*! Checks if an entity has a component.
    *
    * Returns whether or not the entity has a component of the
    * associated type.
    *
    * @tparam Com Type of the component to check.
    * 
    * @param eid EntID of the entity.
    * @return True if the component exists.
    */
    template <typename Com>
    bool hasComponent(EntID eid)
    {
        auto guid = getTypeGuid<Com>();
        auto& ent_coms = entities[eid].components;
        return guid < ent_coms.size() && ent_coms.get(guid);
    }

    /*! Visit the Database.
    *
    * Visit the Entities in the Database that match the given function's parameter types.
    *
    * The following parameter categories are accepted:
    *
    * - Component Data: Any `T` except rvalue-references, matches entities that have component `T`.
    * - Component Tag: `Tag<T>` value, matches entities that have component `Tag<T>`.
    * - Component Has: `Has<T>` value, matches entities that have component `T`, but does not load the component.
    * - Component Maybe: `Maybe<T>` value, checks if a component exists, and provides a way to access it, does not fail.
    * - Inverted: `Not<T>` value, matches entities that do *not* match component `T`.
    * - EntID: Matches all entities, provides the `EntID` of the current entity.
    *
    * Component Data and Maybe parameters will refer to the entity's matching component.
    * EntID parameters will contain the entity's EntID.
    * Other parameters will be their default value.
    *
    * Entities that do not match all given parameter conditions will be skipped.
    *
    * @warning Entities are visited in no particular order, so adding and removing entities from the visitor
    *          function could result in non-deterministic behavior.
    *
    * @tparam Visitor Visitor function type.
    * @param visitor Visitor function.
    */
    template <typename Visitor>
    void visit(Visitor&& visitor)
    {
        using Traits = VisitorTraits<Database, Visitor>;
        using PrimaryComponent = typename Traits::PrimaryComponent;

        return visit_helper(forward<Visitor>(visitor), PrimaryComponent{});
    }

// status functions

    /*! Get the number of entities in the Database.
    *
    * @return Number of entities in the Database.
    */
    auto size() const
    {
        return entities.size() - free_entities.size();
    }

private:

    template <typename DB, typename PrimaryComponent, typename... Components>
    friend struct Applier;

    template <typename Com>
    Com& getComponentById(ComID cid)
    {
        auto& com_set = *getComSet<Com>();
        return com_set.get_com(cid);
    }

    template <typename Com>
    SparseSetImpl<Com>* getComSet() {
        auto guid = getTypeGuid<Com>();
        auto& com_set = component_sets[guid];
        auto com_set_impl = static_cast<SparseSetImpl<Com>*>(com_set.get());
        return com_set_impl;
    }

    template <typename Com>
    SparseSetImpl<Com>& getOrCreateComSet() {
        auto guid = getTypeGuid<Com>();
        if (component_sets.size() <= guid) {
            component_sets.resize(guid+1);
        }
        auto& com_set = component_sets[guid];
        if (!com_set) {
            com_set = make_unique<SparseSetImpl<Com>>();
        }
        auto com_set_impl = static_cast<SparseSetImpl<Com>*>(com_set.get());
        return *com_set_impl;
    }

    template <typename Visitor, typename Component>
    void visit_helper(Visitor&& visitor, Primary<Component>)
    {
        using Traits = VisitorTraits<Database, Visitor>;
        using HasOtherComponents = typename Traits::HasOtherComponents;

        return visit_helper_primary(forward<Visitor>(visitor), Primary<Component>{}, HasOtherComponents{});
    }

    template <typename Visitor, typename Component>
    void visit_helper_primary(Visitor&& visitor, Primary<Component>, true_type)
    {
        using Traits = VisitorTraits<Database, Visitor>;
        using Key = typename Traits::Key;

        if (auto com_set_ptr = getComSet<Component>())
        {
            auto& com_set = *com_set_ptr;

            for (ComID cid = 0; cid < com_set.size(); ++cid)
            {
                auto eid = com_set.get_entid(cid);
                if (Key::check(*this, eid))
                {
                    Traits::apply(*this, eid, cid, visitor);
                }
            }
        }
    }

    template <typename Visitor, typename Component>
    void visit_helper_primary(Visitor&& visitor, Primary<Component>, false_type)
    {
        using Traits = VisitorTraits<Database, Visitor>;

        if (auto com_set_ptr = getComSet<Component>())
        {
            auto& com_set = *com_set_ptr;

            for (ComID cid = 0; cid < com_set.size(); ++cid)
            {
                auto eid = com_set.get_entid(cid);
                if (entities[eid].components.get(0))
                {
                    Traits::apply(*this, eid, cid, visitor);
                }
            }
        }
    }

    template <typename Visitor>
    void visit_helper(Visitor&& visitor, Primary<void>)
    {
        using Traits = VisitorTraits<Database, Visitor>;
        using Key = typename Traits::Key;

        for (auto eid = 0; eid < entities.size(); ++eid)
        {
            if (Key::check(*this, eid))
            {
                Traits::apply(*this, eid, visitor);
            }
        }
    }

    vector<Entity> entities;
    vector<EntID> free_entities;
    vector<unique_ptr<SparseSet>> component_sets;
};

} // namespace _detail

using _detail::Database;
using _detail::Has;
using _detail::Not;
using _detail::Tag;
using _detail::Maybe;

} // namespace Ginseng

#endif // GINSENG_GINSENG_HPP
