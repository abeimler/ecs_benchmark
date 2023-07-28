///
/// OpenEcs v0.1.101
/// Generated: 2016-02-04 13:54:34.305076
/// ----------------------------------------------------------
/// This file has been generated from multiple files. Do not modify
/// ----------------------------------------------------------
///
#ifndef ECS_SINGLE_INCLUDE_H
#define ECS_SINGLE_INCLUDE_H
/// --------------------------------------------------------------------------
/// Copyright (C) 2015  Robin Gr�nberg
///
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/// This file includes all other parts of the library. This files is
/// included when the single header is generated.
#ifndef ECS_MAIN_INCLUDE
#define ECS_MAIN_INCLUDE

#include <bitset>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// #included from: Defines.h
#ifndef ECS_DEFINES_H
#define ECS_DEFINES_H

/// The cache line size for the processor. Usually 64 bytes
#ifndef ECS_CACHE_LINE_SIZE
#define ECS_CACHE_LINE_SIZE 64
#endif

/// This is how an assertion is done. Can be defined with something else if needed.
#ifndef ECS_ASSERT
#define ECS_ASSERT(Expr, Msg) assert(Expr&& Msg)
#endif

/// The maximum number of component types the EntityManager can handle
#ifndef ECS_MAX_NUM_OF_COMPONENTS
#define ECS_MAX_NUM_OF_COMPONENTS 64
#endif

/// How many components each block of memory should contain
/// By default, this is divided into the same size as cache-line size
#ifndef ECS_DEFAULT_CHUNK_SIZE
#define ECS_DEFAULT_CHUNK_SIZE ECS_CACHE_LINE_SIZE
#endif

#define ECS_ASSERT_IS_CALLABLE(T) \
  static_assert(details::is_callable<T>::value, "Provide a function or lambda expression");

#define ECS_ASSERT_IS_ENTITY(T)                                                                   \
  static_assert(std::is_base_of<details::BaseEntity, T>::value || std::is_same<Entity, T>::value, \
                #T " does not inherit EntityAlias.");

#define ECS_ASSERT_ENTITY_CORRECT_SIZE(T)                 \
  static_assert(sizeof(details::BaseEntity) == sizeof(T), \
                #T " should not include new variables, add them as Components instead.");

#define ECS_ASSERT_VALID_ENTITY(E) ECS_ASSERT(is_valid(E), "Entity is no longer valid");

#define ECS_ASSERT_IS_SYSTEM(S) static_assert(std::is_base_of<System, S>::value, "DirivedSystem must inherit System.");

#define ECS_ASSERT_MSG_ONLY_ONE_ARGS_PROPERTY_CONSTRUCTOR       \
  "Creating a property component should only take 1 argument. " \
  "If component should initilize more members, provide a "      \
  "constructor to initilize property component correctly"

namespace ecs {
/// Type used for entity index
using index_t = uint32_t;
/// Type used for entity version
using version_t = uint8_t;

namespace details {

/// ComponentMask is a mask defining what components and entity has.
using ComponentMask = std::bitset<ECS_MAX_NUM_OF_COMPONENTS>;

} // namespace details
} // namespace ecs

#endif // ECS_DEFINES_H
// #included from: Pool.h
#ifndef ECS_POOL_H
#define ECS_POOL_H

// #included from: Utils.h
#ifndef ECS_UTILS_H
#define ECS_UTILS_H

///--------------------------------------------------------------------
/// This file contains useful classes for meta-programming or
/// nice helper functions
///--------------------------------------------------------------------

namespace ecs {

/// Forward declarations
class Entity;

namespace details {

///--------------------------------------------------------------------
/// function_traits is used to determine function properties
/// such as parameter types (arguments) and return type.
///--------------------------------------------------------------------
template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())> {};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
  enum { arg_count = sizeof...(Args) };

  typedef ReturnType return_type;

  template <size_t i>
  struct arg_t {
    typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
  };
  template <size_t i>
  using arg = typename arg_t<i>::type;

  template <size_t i>
  struct arg_remove_ref_t {
    typedef typename std::remove_reference<arg<i>>::type type;
  };
  template <size_t i>
  using arg_remove_ref = typename arg_remove_ref_t<i>::type;

  typedef std::tuple<Args...> args;
};

///---------------------------------------------------------------------
/// Determine if type is part of a list of types
///---------------------------------------------------------------------
template <typename T, typename... Ts>
struct is_type;

template <typename T, typename... Ts>
struct is_type<T, T, Ts...> : std::true_type {};

template <typename T>
struct is_type<T, T> : std::true_type {};

template <typename T, typename Tail>
struct is_type<T, Tail> : std::false_type {};

template <typename T, typename Tail, typename... Ts>
struct is_type<T, Tail, Ts...> : is_type<T, Ts...>::type {};

///---------------------------------------------------------------------
/// Check if a class has implemented operator()
///
/// Mostly used for checking if provided type is a lambda expression
///---------------------------------------------------------------------
///
template <typename T>
struct is_callable {
  template <typename U>
  static char test(decltype(&U::operator()));

  template <typename U>
  static int test(...);

  enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

///---------------------------------------------------------------------
/// Any class that should not be able to copy itself inherit this class
///---------------------------------------------------------------------
///
class forbid_copies {
protected:
  forbid_copies() = default;
  ~forbid_copies() = default;
  forbid_copies(const forbid_copies&) = delete;
  forbid_copies& operator=(const forbid_copies&) = delete;
};

///--------------------------------------------------------------------
/// Helper functions
///--------------------------------------------------------------------

inline size_t& component_counter() {
  static size_t counter = 0;
  return counter;
}

inline size_t inc_component_counter() {
  size_t index = component_counter()++;
  ECS_ASSERT(index < ECS_MAX_NUM_OF_COMPONENTS, "maximum number of components exceeded.");
  return index;
}

template <typename C>
size_t component_index() {
  static size_t index = inc_component_counter();
  return index;
}

inline size_t& system_counter() {
  static size_t counter = 0;
  return counter;
}

template <typename C>
size_t system_index() {
  static size_t index = system_counter()++;
  return index;
}

// C1 should not be Entity
template <typename C>
inline auto component_mask() -> typename std::enable_if<!std::is_same<C, Entity>::value, ComponentMask>::type {
  ComponentMask mask = ComponentMask((1UL << component_index<C>()));
  return mask;
}

// When C1 is Entity, ignore
template <typename C>
inline auto component_mask() -> typename std::enable_if<std::is_same<C, Entity>::value, ComponentMask>::type {
  return ComponentMask(0);
}

// recursive function for component_mask creation
template <typename C1, typename C2, typename... Cs>
inline auto component_mask() -> typename std::enable_if<!std::is_same<C1, Entity>::value, ComponentMask>::type {
  ComponentMask mask = component_mask<C1>() | component_mask<C2, Cs...>();
  return mask;
}

} // namespace details

} // namespace ecs

#endif // ECS_UTILS_H
namespace ecs {

namespace details {

///---------------------------------------------------------------------
/// A Pool is a memory pool.
/// See link for more info: http://en.wikipedia.org/wiki/Memory_pool
///---------------------------------------------------------------------
///
/// The BasePool is used to store void*. Use Pool<T> for a generic
/// Pool allocation class. The standard is to store one cache-line
/// (64 bytes) per chunk.
///
///---------------------------------------------------------------------
class BasePool : forbid_copies {
public:
  inline explicit BasePool(size_t element_size, size_t chunk_size = ECS_DEFAULT_CHUNK_SIZE);
  inline virtual ~BasePool();

  inline index_t size() const { return size_; }
  inline index_t capacity() const { return capacity_; }
  inline size_t chunks() const { return chunks_.size(); }
  inline void ensure_min_size(std::size_t size);
  inline void ensure_min_capacity(size_t min_capacity);

  virtual void destroy(index_t index) = 0;

protected:
  index_t size_;
  index_t capacity_;
  size_t element_size_;
  size_t chunk_size_;
  std::vector<char*> chunks_;
};

///---------------------------------------------------------------------
/// A Pool is a memory pool.
/// See link for more info: http://en.wikipedia.org/wiki/Memory_pool
///---------------------------------------------------------------------
///
/// The Pool is used to store * of any class. Destroying an object calls
/// destructor. The pool doesn't know where there is data allocated.
/// This must be done from outside. The default chunk-size is 64 bytes *
/// the size of each object.
///
///---------------------------------------------------------------------
template <typename T>
class Pool : public BasePool {
public:
  Pool(size_t chunk_size);

  inline virtual void destroy(index_t index) override;

  inline T* get_ptr(index_t index);
  inline const T* get_ptr(index_t index) const;

  inline T& get(index_t index);
  inline const T& get(index_t index) const;

  inline T& operator[](size_t index);
  inline const T& operator[](size_t index) const;
};

} // namespace details

} // namespace ecs

// #included from: Pool.inl
namespace ecs {

namespace details {

BasePool::BasePool(size_t element_size, size_t chunk_size)
    : size_(0), capacity_(0), element_size_(element_size), chunk_size_(chunk_size) {
}

BasePool::~BasePool() {
  for (char* ptr : chunks_) {
    delete[] ptr;
  }
}
void BasePool::ensure_min_size(std::size_t size) {
  if (size >= size_) {
    if (size >= capacity_)
      ensure_min_capacity(size);
    size_ = size;
  }
}
void BasePool::ensure_min_capacity(size_t min_capacity) {
  while (min_capacity >= capacity_) {
    char* chunk = new char[element_size_ * chunk_size_];
    chunks_.push_back(chunk);
    capacity_ += chunk_size_;
  }
}

template <typename T>
Pool<T>::Pool(size_t chunk_size) : BasePool(sizeof(T), chunk_size) {
}

template <typename T>
void Pool<T>::destroy(index_t index) {
  ECS_ASSERT(index < size_, "Pool has not allocated memory for this index.");
  T* ptr = get_ptr(index);
  ptr->~T();
}

template <typename T>
inline T* Pool<T>::get_ptr(index_t index) {
  ECS_ASSERT(index < capacity_, "Pool has not allocated memory for this index.");
  return reinterpret_cast<T*>(chunks_[index / chunk_size_] + (index % chunk_size_) * element_size_);
}

template <typename T>
inline const T* Pool<T>::get_ptr(index_t index) const {
  ECS_ASSERT(index < this->capacity_, "Pool has not allocated memory for this index.");
  return reinterpret_cast<T*>(chunks_[index / chunk_size_] + (index % chunk_size_) * element_size_);
}

template <typename T>
inline T& Pool<T>::get(index_t index) {
  return *get_ptr(index);
}

template <typename T>
inline const T& Pool<T>::get(index_t index) const {
  return *get_ptr(index);
}

template <typename T>
inline T& Pool<T>::operator[](size_t index) {
  return get(index);
}

template <typename T>
inline const T& Pool<T>::operator[](size_t index) const {
  return get(index);
}

} // namespace details

} // namespace ecs
#endif // ECS_POOL_H
// #included from: ComponentManager.h
#ifndef ECS_COMPONENTMANAGER_H
#define ECS_COMPONENTMANAGER_H

namespace ecs {

// Forward declarations
class EntityManager;

namespace details {

// Forward declarations
class BaseProperty;

///-----------------------------------------------------------------------
/// global function for creating a component at a specific location
///-----------------------------------------------------------------------
template <typename C, typename... Args>
auto create_component(void* ptr, Args&&... args) ->
    typename std::enable_if<std::is_constructible<C, Args...>::value, C&>::type;

// Creating a component that doesn't have ctor, and is not a property -> create using uniform initialization
template <typename C, typename... Args>
auto create_component(void* ptr, Args&&... args) -> typename std::enable_if<
    !std::is_constructible<C, Args...>::value && !std::is_base_of<details::BaseProperty, C>::value, C&>::type;

// Creating a component that doesn't have ctor, and is a property -> create using underlying Property ctor
template <typename C, typename... Args>
auto create_component(void* ptr, Args&&... args) -> typename std::enable_if<
    !std::is_constructible<C, Args...>::value && std::is_base_of<details::BaseProperty, C>::value, C&>::type;

///---------------------------------------------------------------------
/// Helper class, all ComponentManager are a BaseManager
///---------------------------------------------------------------------
class BaseManager {
public:
  virtual ~BaseManager(){};
  virtual void remove(index_t index) = 0;
  virtual ComponentMask mask() = 0;
  virtual void* get_void_ptr(index_t index) = 0;
  virtual void const* get_void_ptr(index_t index) const = 0;
  virtual void ensure_min_size(index_t size) = 0;
};

///---------------------------------------------------------------------
/// Helper class, This is the main class for holding many Component of
/// a specified type. It uses a memory pool to store the components
///---------------------------------------------------------------------
template <typename C>
class ComponentManager : public BaseManager, details::forbid_copies {
public:
  ComponentManager(EntityManager& manager, size_t chunk_size = ECS_DEFAULT_CHUNK_SIZE);

  /// Allocate and create at specific index, using constructor
  template <typename... Args>
  C& create(index_t index, Args&&... args);

  /// Remove component at specific index and call destructor
  void remove(index_t index);

  /// Access a component given a specific index
  C& operator[](index_t index);
  C& get(index_t index);
  C const& get(index_t index) const;

  /// Access a ptr to a component given a specific index
  C* get_ptr(index_t index);
  C const* get_ptr(index_t index) const;

  /// Access a raw void ptr to a component given a specific index
  void* get_void_ptr(index_t index);
  void const* get_void_ptr(index_t index) const;

  // Ensures the pool that at it has the size of at least size
  void ensure_min_size(index_t size);

  /// Get the bitmask for the component this ComponentManger handles
  ComponentMask mask();

private:
  EntityManager& manager_;
  details::Pool<C> pool_;
}; // ComponentManager

} // namespace details

} // namespace ecs

// #included from: ComponentManager.inl
// #included from: EntityManager.h
#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER_H

namespace ecs {

/// Forward declareations
template <typename...>
class EntityAlias;
class Entity;
class UnallocatedEntity;
template <typename>
class View;
class Id;

namespace details {

/// Used to iterate through the EntityManager with a lambda-expression,
/// with each argument as a specific component type. Used by with
/// function.
template <size_t N, typename...>
struct with_t;

} // namespace details

///---------------------------------------------------------------------
/// This is the main class for holding all Entities and Components
///---------------------------------------------------------------------
///
/// It uses a vector for holding entity versions and another for component
/// masks. It also uses 1 memory pool for each type of component.
///
/// The index of each data structure is used to identify each entity.
/// The version is used for checking if entity is valid.
/// The component mask is used to check what components an entity has
///
/// The Entity id = {index + version}. When an Entity is removed,
/// the index is added to the free list. A free list knows where spaces are
/// left open for new entities (to ensure no holes).
///
///---------------------------------------------------------------------
class EntityManager : details::forbid_copies {
private:
  // Class for accessing where to put entities with specific components.
  struct IndexAccessor {
    // Used to store next available index there is within each block
    std::vector<index_t> block_index;
    // Used to store all indexes that are free
    std::vector<index_t> free_list;
  };

public:
  inline EntityManager(size_t chunk_size = 8192);
  inline ~EntityManager();

  /// Create a new Entity
  inline UnallocatedEntity create();

  /// Create a specified number of new entities.
  inline std::vector<Entity> create(const size_t num_of_entities);

  /// Create a specified number of new entities, and do something with each entity
  template <typename T>
  inline void create(const size_t num_of_entities, T lambda);

  /// Create, using EntityAlias
  template <typename T, typename... Args>
  inline auto create(Args&&... args) -> typename std::enable_if<!std::is_constructible<T, Args...>::value, T>::type;
  template <typename T, typename... Args>
  inline auto create(Args&&... args) -> typename std::enable_if<std::is_constructible<T, Args...>::value, T>::type;

  /// Create an entity with components assigned
  template <typename... Components, typename... Args>
  inline auto create_with(Args&&... args) ->
      typename std::conditional<(sizeof...(Components) > 0), EntityAlias<Components...>, EntityAlias<Args...>>::type;

  /// Create an entity with components assigned, using default values
  template <typename... Components>
  inline EntityAlias<Components...> create_with();

  // Access a View of all entities with specified components
  template <typename... Components>
  inline View<EntityAlias<Components...>> with();

  // Iterate through all entities with all components, specified as lambda parameters
  // example: entities.with([] (Position& pos) {  });
  template <typename T>
  inline void with(T lambda);

  // Access a View of all entities that has every component as Specified EntityAlias
  template <typename T>
  inline View<T> fetch_every();

  // Access a View of all entities that has every component as Specified EntityAlias specified as lambda parameters
  // example: entities.fetch_every([] (EntityAlias<Position>& entity) {  });
  template <typename T>
  inline void fetch_every(T lambda);

  // Get an Entity at specified index
  inline Entity operator[](index_t index);

  // Get an Entity with a specific Id. Id must be valid
  inline Entity operator[](Id id);

  // Get the Entity count for this EntityManager
  inline size_t count();

private:
  /// Creates an entity and put it close to entities
  /// with similar components
  inline Entity create_with_mask(details::ComponentMask mask);

  /// Creates any number of entities > 0 and put them close to entities
  /// with similar components
  inline std::vector<Entity> create_with_mask(details::ComponentMask mask, const size_t num_of_entities);

  /// Find a proper index for a new entity with components
  inline index_t find_new_entity_index(details::ComponentMask mask);

  /// Create a new block for this entity type.
  inline void create_new_block(IndexAccessor& index_accessor, unsigned long mask_as_ulong, index_t next_free_index);

  /// Creates a ComponentManager. Mainly used by get_component_manager the first time its called
  template <typename C, typename... Args>
  inline details::ComponentManager<C>& create_component_manager(Args&&... args);

  /// Get the ComponentManager. Assumes that the component manager already exists.
  template <typename C>
  inline details::ComponentManager<C>& get_component_manager_fast();
  template <typename C>
  inline details::ComponentManager<C> const& get_component_manager_fast() const;

  /// Get the ComponentManager. Creates a component manager if it
  /// doesn't exists for specified component type.
  template <typename C>
  inline details::ComponentManager<C>& get_component_manager();
  template <typename C>
  inline details::ComponentManager<C> const& get_component_manager() const;

  inline details::BaseManager& get_component_manager(size_t component_index);
  inline details::BaseManager const& get_component_manager(size_t component_index) const;

  /// Get component for a specific entity or index.
  template <typename C>
  inline C& get_component(Entity& entity);
  template <typename C>
  inline C const& get_component(Entity const& entity) const;

  /// Get component for a specific entity or index. Assumes that a
  /// ComponentManager exists for the specific component type.
  template <typename C>
  inline C& get_component_fast(index_t index);
  template <typename C>
  inline C const& get_component_fast(index_t index) const;
  template <typename C>
  inline C& get_component_fast(Entity& entity);
  template <typename C>
  inline C const& get_component_fast(Entity const& entity) const;

  /// Use to create a component tmp that is assignable. Calls the constructor.
  template <typename C, typename... Args>
  inline static auto create_tmp_component(Args&&... args) ->
      typename std::enable_if<std::is_constructible<C, Args...>::value, C>::type {
    return C(std::forward<Args>(args)...);
  }

  /// Use to create a component tmp that is assignable. Uses uniform initialization.
  template <typename C, typename... Args>
  inline static auto create_tmp_component(Args&&... args) -> typename std::enable_if<
      !std::is_constructible<C, Args...>::value && !std::is_base_of<details::BaseProperty, C>::value, C>::type {
    return C{std::forward<Args>(args)...};
  }

  /// Use to create a component tmp that is assignable. Call the right constructor
  /// Called when component is a property, and no constructor inaccessible.
  template <typename C, typename... Args>
  inline static auto create_tmp_component(Args&&... args) -> typename std::enable_if<
      !std::is_constructible<C, Args...>::value && std::is_base_of<details::BaseProperty, C>::value, C>::type {
    static_assert(sizeof...(Args) == 1, ECS_ASSERT_MSG_ONLY_ONE_ARGS_PROPERTY_CONSTRUCTOR);
    // static_assert(sizeof(C) == sizeof(std::tuple < Args... > ),
    //"Cannot initilize component property. Please provide a constructor");
    auto tmp = typename C::ValueType(std::forward<Args>(args)...);
    return *reinterpret_cast<C*>(&tmp);
  }

  /// Creates a component for a specific entity with Args
  template <typename C, typename... Args>
  inline C& create_component(Entity& entity, Args&&... args);

  /// Removes a specific component from an entity.
  template <typename C>
  inline void remove_component(Entity& entity);

  /// Removes a specific component from an entity. Assumes that
  /// a ComponentManager exists for component type
  template <typename C>
  inline void remove_component_fast(Entity& entity);

  /// Removes all components from a single entity
  inline void remove_all_components(Entity& entity);

  /// Clears the component mask without removing any components
  inline void clear_mask(Entity& entity);

  /// Set a component for a specific entity. It uses contructor if
  /// entity does not have component. It uses assignment operator
  /// if component already added
  template <typename C, typename... Args>
  inline C& set_component(Entity& entity, Args&&... args);

  /// Set a component for a specific entity. It assumes that the
  /// entity already has the component and uses the assignment
  /// operator.
  template <typename C, typename... Args>
  inline C& set_component_fast(Entity& entity, Args&&... args);

  /// Check if component has specified component types attached
  inline bool has_component(Entity& entity, details::ComponentMask component_mask);
  inline bool has_component(Entity const& entity, details::ComponentMask const& component_mask) const;
  template <typename... Components>
  inline bool has_component(Entity& entity);
  template <typename... Components>
  inline bool has_component(Entity const& entity) const;

  /// Check if an entity is valid
  inline bool is_valid(Entity& entity);
  inline bool is_valid(Entity const& entity) const;

  /// Destroy an entity. Also removed all added components
  inline void destroy(Entity& entity);

  /// Get the entity mask from a specific entity or index
  inline details::ComponentMask& mask(Entity& entity);
  inline details::ComponentMask const& mask(Entity const& entity) const;
  inline details::ComponentMask& mask(index_t index);
  inline details::ComponentMask const& mask(index_t index) const;

  /// Get an entity given its id or index. When using Id, it must always be valid
  inline Entity get_entity(Id id);
  inline Entity get_entity(index_t index);

  /// Gey how many entities the EntityManager can handle atm
  inline size_t capacity() const;

  std::vector<details::BaseManager*> component_managers_;
  std::vector<details::ComponentMask> component_masks_;
  std::vector<version_t> entity_versions_;
  std::vector<index_t> next_free_indexes_;
  std::vector<size_t> index_to_component_mask;
  std::map<size_t, IndexAccessor> component_mask_to_index_accessor_;

  /// How many blocks of entities there exists. Used when tracking where to put entities in momory
  index_t block_count_ = 0;
  /// How many entities there are atm
  index_t count_ = 0;

  /// The EntityManager want some friends :)
  template <size_t N, typename...>
  friend struct details::with_t;
  template <typename T>
  friend class details::ComponentManager;
  template <typename... Cs>
  friend class EntityAlias;
  template <typename T>
  friend class Iterator;
  friend class Entity;
  friend class UnallocatedEntity;
  friend class BaseComponent;
};

} // namespace ecs

// #included from: EntityManager.inl
// #included from: Entity.h
#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

// #included from: Id.h
#ifndef ECS_ID_H
#define ECS_ID_H

namespace ecs {

///---------------------------------------------------------------------
/// Id is used for Entity to identify entities. It consists of an index
/// and a version. The index describes where the entity is located in
/// memory. The version is used to separate entities if they get the
/// same index.
///---------------------------------------------------------------------
class Id {
public:
  inline Id();
  inline Id(index_t index, version_t version);

  inline index_t index() { return index_; }
  inline index_t index() const { return index_; }

  inline version_t version() { return version_; }
  inline version_t version() const { return version_; }

private:
  index_t index_;
  version_t version_;
  friend class Entity;
  friend class EntityManager;
};

inline bool operator==(const Id& lhs, const Id& rhs);
inline bool operator!=(const Id& lhs, const Id& rhs);

} // namespace ecs

// #included from: Id.inl
namespace ecs {

Id::Id() {
}

Id::Id(index_t index, version_t version) : index_(index), version_(version) {
}

bool operator==(const Id& lhs, const Id& rhs) {
  return lhs.index() == rhs.index() && lhs.version() == rhs.version();
}

bool operator!=(const Id& lhs, const Id& rhs) {
  return lhs.index() != rhs.index() || lhs.version() != rhs.version();
}

} // namespace ecs
#endif // ECS_ID_H
namespace ecs {
///---------------------------------------------------------------------
/// Entity is the identifier of an identity
///---------------------------------------------------------------------
///
/// An entity consists of an id and version. The version is used to
/// ensure that new entities allocated with the same id are separable.
///
/// An entity becomes invalid when destroyed.
///
///---------------------------------------------------------------------
class Entity {
public:
  inline Entity(EntityManager* manager, Id id);
  inline Entity& operator=(const Entity& rhs);

  inline Id& id() { return id_; }
  inline Id const& id() const { return id_; }

  /// Returns the requested component, or error if it doesn't exist
  template <typename C>
  inline C& get();
  template <typename C>
  inline C const& get() const;

  /// Set the requested component, if old component exist,
  /// a new one is created. Otherwise, the assignment operator
  /// is used.
  template <typename C, typename... Args>
  inline C& set(Args&&... args);

  /// Add the requested component, error if component of the same type exist already
  template <typename C, typename... Args>
  inline C& add(Args&&... args);

  /// Access this Entity as an EntityAlias.
  template <typename T>
  inline T& as();
  template <typename T>
  inline T const& as() const;

  /// Assume that this entity has provided Components
  /// Use for faster component access calls
  template <typename... Components>
  inline EntityAlias<Components...>& assume();
  template <typename... Components>
  inline EntityAlias<Components...> const& assume() const;

  /// Removes a component. Error of it doesn't exist
  template <typename C>
  inline void remove();

  /// Removes all components and call destructors
  void inline remove_everything();

  /// Clears the component mask without destroying components (faster than remove_everything)
  void inline clear_mask();

  /// Destroys this entity. Removes all components as well
  void inline destroy();

  /// Return true if entity has all specified components. False otherwise
  template <typename... Components>
  inline bool has();
  template <typename... Components>
  inline bool has() const;

  /// Returns whether an entity is an entity alias or not
  template <typename T>
  inline bool is();
  template <typename T>
  inline bool is() const;

  /// Returns true if entity has not been destroyed. False otherwise
  bool inline is_valid();
  bool inline is_valid() const;

private:
  /// Return true if entity has all specified compoents. False otherwise
  inline bool has(details::ComponentMask& check_mask);
  inline bool has(details::ComponentMask const& check_mask) const;

  inline details::ComponentMask& mask();
  inline details::ComponentMask const& mask() const;

  inline static details::ComponentMask static_mask();

  EntityManager* manager_;
  Id id_;

  friend class EntityManager;
}; // Entity

inline bool operator==(const Entity& lhs, const Entity& rhs);
inline bool operator!=(const Entity& lhs, const Entity& rhs);

} // namespace ecs

// #included from: Entity.inl
// #included from: EntityAlias.h
#ifndef ECS_ENTITYALIAS_H
#define ECS_ENTITYALIAS_H

// #included from: BaseEntity.h
//
// Created by Robin Gr�nberg on 05/12/15.
//

#ifndef OPENECS_BASEENTITY_H
#define OPENECS_BASEENTITY_H

namespace ecs {

namespace details {

class BaseEntity {
public:
  inline BaseEntity(const Entity& entity);

protected:
  inline BaseEntity();
  inline BaseEntity(EntityManager* manager);
  inline BaseEntity(const BaseEntity& other);
  inline BaseEntity& operator=(const BaseEntity& other) {
    entity_ = other.entity_;
    return *this;
  }

  inline EntityManager& entities() { return *manager_; }
  inline Entity& entity() { return entity_; }
  inline EntityManager const& entities() const { return *manager_; }
  inline Entity const& entity() const { return entity_; }

private:
  union {
    EntityManager* manager_;
    Entity entity_;
  };
}; // BaseEntity

} // namespace details

} // namespace ecs

// #included from: BaseEntity.inl

namespace ecs {

namespace details {

BaseEntity::BaseEntity(const Entity& entity) : entity_(entity) {
}
BaseEntity::BaseEntity() {
}
BaseEntity::BaseEntity(EntityManager* manager) : manager_(manager) {
}
BaseEntity::BaseEntity(const BaseEntity& other) : entity_(other.entity_) {
}

} // namespace details

} // namespace ecs
#endif // OPENECS_BASEENTITY_H
namespace ecs {

///---------------------------------------------------------------------
/// EntityAlias is a wrapper around an Entity
///---------------------------------------------------------------------
///
/// An EntityAlias makes modification of the entity and other
/// entities much easier when performing actions. It acts solely as an
/// abstraction layer between the entity and different actions.
///
///---------------------------------------------------------------------
template <typename... Components>
class EntityAlias : public details::BaseEntity {
private:
  /// Underlying EntityAlias. Used for creating Entity alias without
  /// a provided constructor
  using Type = EntityAlias<Components...>;
  template <typename C>
  using is_component = details::is_type<C, Components...>;

public:
  inline EntityAlias(const Entity& entity);

  /// Cast to Entity or EntityAlias
  inline operator Entity&();
  inline operator Entity const &() const;

  inline bool operator==(const Entity& rhs) const;
  inline bool operator!=(const Entity& rhs) const;

  inline Id& id();
  inline Id const& id() const;

  /// Returns the requested component, or error if it doesn't exist
  template <typename C>
  inline auto get() -> typename std::enable_if<is_component<C>::value, C&>::type;
  template <typename C>
  inline auto get() -> typename std::enable_if<!is_component<C>::value, C&>::type;
  template <typename C>
  inline auto get() const -> typename std::enable_if<is_component<C>::value, C const&>::type;
  template <typename C>
  inline auto get() const -> typename std::enable_if<!is_component<C>::value, C const&>::type;

  /// Set the requested component, if old component exist,
  /// a new one is created. Otherwise, the assignment operator
  /// is used.
  template <typename C, typename... Args>
  inline auto set(Args&&... args) -> typename std::enable_if<is_component<C>::value, C&>::type;
  template <typename C, typename... Args>
  inline auto set(Args&&... args) -> typename std::enable_if<!is_component<C>::value, C&>::type;

  /// Add the requested component, error if component of the same type exist already
  template <typename C, typename... Args>
  inline C& add(Args&&... args);

  /// Access this Entity as an EntityAlias.
  template <typename T>
  inline T& as();
  template <typename T>
  inline T const& as() const;

  /// Assume that this entity has provided Components
  /// Use for faster component access calls
  template <typename... Components_>
  inline EntityAlias<Components_...>& assume();

  template <typename... Components_>
  inline EntityAlias<Components_...> const& assume() const;

  /// Removes a component. Error of it doesn't exist. Cannot remove dependent components
  template <typename C>
  inline auto remove() -> typename std::enable_if<is_component<C>::value, void>::type;
  template <typename C>
  inline auto remove() -> typename std::enable_if<!is_component<C>::value, void>::type;

  /// Removes all components and call destructors
  inline void remove_everything();

  /// Clears the component mask without destroying components (faster than remove_everything)
  inline void clear_mask();

  /// Destroys this entity. Removes all components as well
  inline void destroy();
  /// Return true if entity has all specified components. False otherwise
  template <typename... Components_>
  inline bool has();
  template <typename... Components_>
  inline bool has() const;

  /// Returns whether an entity is an entity alias or not
  template <typename T>
  inline bool is();
  template <typename T>
  inline bool is() const;

  /// Returns true if entity has not been destroyed. False otherwise
  inline bool is_valid();
  inline bool is_valid() const;

protected:
  inline EntityAlias();

private:
  // Recursion init components with argument
  template <typename C0, typename Arg>
  inline void init_components(Arg arg) {
    add<C0>(arg);
  }

  template <typename C0, typename C1, typename... Cs, typename Arg0, typename Arg1, typename... Args>
  inline void init_components(Arg0 arg0, Arg1 arg1, Args... args) {
    init_components<C0>(arg0);
    init_components<C1, Cs...>(arg1, args...);
  }
  // Recursion init components without argument
  template <typename C>
  inline void init_components() {
    add<C>();
  }

  template <typename C0, typename C1, typename... Cs>
  inline void init_components() {
    init_components<C0>();
    init_components<C1, Cs...>();
  }

  template <typename... Args>
  inline void init(Args... args) {
    init_components<Components...>(args...);
  }

  inline static details::ComponentMask static_mask();

  friend class EntityManager;
  friend class Entity;
}; // EntityAlias

} // namespace ecs

// #included from: EntityAlias.inl

namespace ecs {

template <typename... Cs>
EntityAlias<Cs...>::EntityAlias() {
}

template <typename... Cs>
EntityAlias<Cs...>::EntityAlias(const Entity& entity) : details::BaseEntity(entity) {
}

template <typename... Cs>
EntityAlias<Cs...>::operator Entity&() {
  return entity();
}

template <typename... Cs>
EntityAlias<Cs...>::operator Entity const &() const {
  return entity();
}

template <typename... Cs>
Id& EntityAlias<Cs...>::id() {
  return entity().id();
}

template <typename... Cs>
Id const& EntityAlias<Cs...>::id() const {
  return entity().id();
}

template <typename... Cs>
template <typename C>
inline auto EntityAlias<Cs...>::get() -> typename std::enable_if<is_component<C>::value, C&>::type {
  return entities().template get_component_fast<C>(entity());
}

template <typename... Cs>
template <typename C>
inline auto EntityAlias<Cs...>::get() const -> typename std::enable_if<is_component<C>::value, C const&>::type {
  return entities().template get_component_fast<C>(entity());
}

template <typename... Cs>
template <typename C>
inline auto EntityAlias<Cs...>::get() -> typename std::enable_if<!is_component<C>::value, C&>::type {
  return entity().template get<C>();
}

template <typename... Cs>
template <typename C>
inline auto EntityAlias<Cs...>::get() const -> typename std::enable_if<!is_component<C>::value, C const&>::type {
  return entity().template get<C>();
}

template <typename... Cs>
template <typename C, typename... Args>
inline auto EntityAlias<Cs...>::set(Args&&... args) -> typename std::enable_if<is_component<C>::value, C&>::type {
  return entities().template set_component_fast<C>(entity(), std::forward<Args>(args)...);
}

template <typename... Cs>
template <typename C, typename... Args>
inline auto EntityAlias<Cs...>::set(Args&&... args) -> typename std::enable_if<!is_component<C>::value, C&>::type {
  return entities().template set_component<C>(entity(), std::forward<Args>(args)...);
}

template <typename... Cs>
template <typename C, typename... Args>
inline C& EntityAlias<Cs...>::add(Args&&... args) {
  return entity().template add<C>(std::forward<Args>(args)...);
}

template <typename... Cs>
template <typename C>
C& EntityAlias<Cs...>::as() {
  return entity().template as<C>();
}

template <typename... Cs>
template <typename C>
C const& EntityAlias<Cs...>::as() const {
  return entity().template as<C>();
}

template <typename... Cs>
template <typename... Components_>
EntityAlias<Components_...>& EntityAlias<Cs...>::assume() {
  return entity().template assume<Components_...>();
}

template <typename... Cs>
template <typename... Components>
EntityAlias<Components...> const& EntityAlias<Cs...>::assume() const {
  return entity().template assume<Components...>();
}

template <typename... Cs>
template <typename C>
inline auto EntityAlias<Cs...>::remove() -> typename std::enable_if<!is_component<C>::value, void>::type {
  entity().template remove<C>();
}

template <typename... Cs>
template <typename C>
inline auto EntityAlias<Cs...>::remove() -> typename std::enable_if<is_component<C>::value, void>::type {
  entities().template remove_component_fast<C>(entity());
}

template <typename... Cs>
void EntityAlias<Cs...>::remove_everything() {
  entity().remove_everything();
}

template <typename... Cs>
void EntityAlias<Cs...>::clear_mask() {
  entity().clear_mask();
}

template <typename... Cs>
void EntityAlias<Cs...>::destroy() {
  entity().destroy();
}

template <typename... Cs>
template <typename... Components>
bool EntityAlias<Cs...>::has() {
  return entity().template has<Components...>();
}

template <typename... Cs>
template <typename... Components>
bool EntityAlias<Cs...>::has() const {
  return entity().template has<Components...>();
}

template <typename... Cs>
template <typename T>
bool EntityAlias<Cs...>::is() {
  return entity().template is<T>();
}
template <typename... Cs>
template <typename T>
bool EntityAlias<Cs...>::is() const {
  return entity().template is<T>();
}

template <typename... Cs>
bool EntityAlias<Cs...>::is_valid() {
  return entity().is_valid();
}

template <typename... Cs>
bool EntityAlias<Cs...>::is_valid() const {
  return entity().is_valid();
}

template <typename... Cs>
details::ComponentMask EntityAlias<Cs...>::static_mask() {
  return details::component_mask<Cs...>();
}

template <typename... Cs>
inline bool EntityAlias<Cs...>::operator==(const Entity& rhs) const {
  return entity() == rhs;
}

template <typename... Cs>
inline bool EntityAlias<Cs...>::operator!=(const Entity& rhs) const {
  return entity() != rhs;
}

} // namespace ecs
#endif // ECS_ENTITYALIAS_H

namespace ecs {

Entity::Entity(EntityManager* manager, Id id) : manager_(manager), id_(id) {
}

Entity& Entity::operator=(const Entity& rhs) {
  manager_ = rhs.manager_;
  id_ = rhs.id_;
  return *this;
}

template <typename C>
C& Entity::get() {
  return manager_->get_component<C>(*this);
}

template <typename C>
C const& Entity::get() const {
  return manager_->get_component<C>(*this);
}

template <typename C, typename... Args>
C& Entity::set(Args&&... args) {
  return manager_->set_component<C>(*this, std::forward<Args>(args)...);
}

template <typename C, typename... Args>
C& Entity::add(Args&&... args) {
  return manager_->create_component<C>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline T& Entity::as() {
  ECS_ASSERT_IS_ENTITY(T);
  ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
  ECS_ASSERT(has(T::static_mask()), "Entity doesn't have required components for this EntityAlias");
  return reinterpret_cast<T&>(*this);
}

template <typename T>
inline T const& Entity::as() const {
  ECS_ASSERT_IS_ENTITY(T);
  ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
  ECS_ASSERT(has(T::static_mask()), "Entity doesn't have required components for this EntityAlias");
  return reinterpret_cast<T const&>(*this);
}

/// Assume that this entity has provided Components
/// Use for faster component access calls
template <typename... Components>
inline EntityAlias<Components...>& Entity::assume() {
  return as<EntityAlias<Components...>>();
}

template <typename... Components>
inline EntityAlias<Components...> const& Entity::assume() const {
  return as<EntityAlias<Components...>>();
}

template <typename C>
void Entity::remove() {
  manager_->remove_component<C>(*this);
}

void Entity::remove_everything() {
  manager_->remove_all_components(*this);
}

void Entity::clear_mask() {
  manager_->clear_mask(*this);
}

void Entity::destroy() {
  manager_->destroy(*this);
}

template <typename... Components>
bool Entity::has() {
  return manager_->has_component<Components...>(*this);
}

template <typename... Components>
bool Entity::has() const {
  return manager_->has_component<Components...>(*this);
}

template <typename T>
bool Entity::is() {
  ECS_ASSERT_IS_ENTITY(T);
  ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
  return has(T::static_mask());
}

template <typename T>
bool Entity::is() const {
  ECS_ASSERT_IS_ENTITY(T);
  ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
  return has(T::static_mask());
}

bool Entity::is_valid() {
  return manager_->is_valid(*this);
}

bool Entity::is_valid() const {
  return manager_->is_valid(*this);
}

bool Entity::has(details::ComponentMask& check_mask) {
  return manager_->has_component(*this, check_mask);
}

bool Entity::has(details::ComponentMask const& check_mask) const {
  return manager_->has_component(*this, check_mask);
}

details::ComponentMask& Entity::mask() {
  return manager_->mask(*this);
}
details::ComponentMask const& Entity::mask() const {
  return manager_->mask(*this);
}

inline bool operator==(const Entity& lhs, const Entity& rhs) {
  return lhs.id() == rhs.id();
}

inline bool operator!=(const Entity& lhs, const Entity& rhs) {
  return lhs.id() != rhs.id();
}

details::ComponentMask Entity::static_mask() {
  return details::ComponentMask(0);
}

} // namespace ecs
#endif // ECS_ENTITY_H
// #included from: UnallocatedEntity.h
//
// Created by Robin Gr�nberg on 05/12/15.
//

#ifndef OPENECS_UNALLOCATEDENTITY_H
#define OPENECS_UNALLOCATEDENTITY_H

#include <vector>

namespace ecs {

///---------------------------------------------------------------------
/// UnallocatedEntity is used when creating an Entity but postponing
/// allocation for memory in the EntityManager
///---------------------------------------------------------------------
///
/// UnallocatedEntity is used when creating an Entity from the
/// EntityManager but does not allocate memory inside the EntityManager
/// until the UnallocatedEntity is assigned, or goes out of scope.
///
/// The purpose of doing this is to postpone the placement of the Entity
/// until components have been attached. Then, the EntityManager knows
/// what components that the entity has, and can place the entity close
/// to similar entities in memory. This leads to better usage of the
/// CPU cache
///
/// An UnallocatedEntity can always be implicitly casted to an Entity.
///
/// Au UnallocatedEntity is assumed unallocated as long as entity_ is
/// a nullptr
///---------------------------------------------------------------------
class UnallocatedEntity {
private:
  struct ComponentHeader {
    unsigned int index, size;
  };

public:
  inline UnallocatedEntity(EntityManager& manager);
  inline UnallocatedEntity& operator=(const UnallocatedEntity& rhs);
  inline ~UnallocatedEntity();

  /// Cast to Entity or EntityAlias
  inline operator Entity&();

  inline bool operator==(const UnallocatedEntity& rhs) const;
  inline bool operator!=(const UnallocatedEntity& rhs) const;
  inline bool operator==(const Entity& rhs) const;
  inline bool operator!=(const Entity& rhs) const;

  inline Id& id();

  /// Returns the requested component, or error if it doesn't exist
  template <typename C>
  inline C& get();
  template <typename C>
  inline C const& get() const;

  /// Set the requested component, if old component exist,
  /// a new one is created. Otherwise, the assignment operator
  /// is used.
  template <typename C, typename... Args>
  inline C& set(Args&&... args);

  /// Add the requested component, error if component of the same type exist already
  template <typename C, typename... Args>
  inline C& add(Args&&... args);

  /// Access this Entity as an EntityAlias.
  template <typename T>
  inline T& as();

  /// Assume that this entity has provided Components
  /// Use for faster component access calls
  template <typename... Components>
  inline EntityAlias<Components...>& assume();

  /// Removes a component. Error of it doesn't exist
  template <typename C>
  inline void remove();

  /// Removes all components and call destructors
  void inline remove_everything();

  /// Clears the component mask without destroying components (faster than remove_everything)
  void inline clear_mask();

  /// Destroys this entity. Removes all components as well
  void inline destroy();

  /// Return true if entity has all specified components. False otherwise
  template <typename... Components>
  inline bool has() const;

  /// Returns whether an entity is an entity alias or not
  template <typename T>
  inline bool is() const;

  /// Returns true if entity has not been destroyed. False otherwise
  bool inline is_valid() const;

  /// Allocates memory for this Entity. Once allocated, the Unallocated Entity function like a
  /// normal Entity
  void inline allocate();

private:
  bool inline is_allocated() const;

  EntityManager* manager_ = nullptr;
  Entity entity_;
  std::vector<char> component_data;
  std::vector<ComponentHeader> component_headers_;
  details::ComponentMask mask_ = details::ComponentMask(0);

}; // UnallocatedEntity

} // namespace ecs

// #included from: UnallocatedEntity.inl
#include <cstring>

namespace ecs {

UnallocatedEntity::UnallocatedEntity(EntityManager& manager)
    : manager_(&manager), entity_(&manager, Id(index_t(-1), 0)) {
}

UnallocatedEntity::~UnallocatedEntity() {
  allocate();
}

UnallocatedEntity& UnallocatedEntity::operator=(const UnallocatedEntity& rhs) {
  allocate();
  manager_ = rhs.manager_;
  entity_ = rhs.entity_;
  component_data = rhs.component_data;
  component_headers_ = rhs.component_headers_;
  return *this;
}

UnallocatedEntity::operator Entity&() {
  allocate();
  return entity_;
}

Id& UnallocatedEntity::id() {
  allocate();
  return entity_.id();
}

template <typename C>
C& UnallocatedEntity::get() {
  ECS_ASSERT(is_valid(), "Unallocated Entity invalid");
  ECS_ASSERT(has<C>(), "UnallocatedEntity does not have Component Attached");
  if (is_allocated()) {
    return entity_.get<C>();
  }
  int index = 0;
  for (auto& componentHeader : component_headers_) {
    if (componentHeader.index == details::component_index<C>()) {
      return *reinterpret_cast<C*>(&component_data[index]);
    }
    index += componentHeader.size;
  }
  // should not happen
  return *static_cast<C*>(nullptr);
}

template <typename C>
C const& UnallocatedEntity::get() const {
  ECS_ASSERT(is_valid(), "Unallocated Entity invalid");
  ECS_ASSERT(has<C>(), "UnallocatedEntity does not have Component Attached");
  if (is_allocated()) {
    return entity_.get<C>();
  } else {
    int index = 0;
    for (auto& componentHeader : component_headers_) {
      if (componentHeader.index == details::component_index<C>()) {
        return *reinterpret_cast<C*>(&component_data[index]);
      }
      index += componentHeader.size;
    }
  }
  // should not happen
  return *static_cast<C*>(nullptr);
}

template <typename C, typename... Args>
C& UnallocatedEntity::set(Args&&... args) {
  if (is_allocated()) {
    return entity_.set<C>(std::forward<Args>(args)...);
  }
  if (has<C>()) {
    return get<C>() = manager_->create_tmp_component<C>(std::forward<Args>(args)...);
  } else {
    return add<C>(std::forward<Args>(args)...);
  }
}

template <typename C, typename... Args>
C& UnallocatedEntity::add(Args&&... args) {
  if (is_allocated()) {
    return entity_.add<C>(std::forward<Args>(args)...);
  }
  ECS_ASSERT(!has<C>(), "Unallocated Entity cannot assign already assigned component with add. Use set instead");
  ECS_ASSERT(is_valid(), "Unallocated Entity invalid");
  int index = 0;
  // Find component location in memory
  for (auto componentHeader : component_headers_) {
    index += componentHeader.size;
  }
  // Ensure that a component manager exists for C
  manager_->get_component_manager<C>();
  // Set component data
  auto component_index = details::component_index<C>();
  mask_.set(component_index);
  component_headers_.push_back(ComponentHeader{static_cast<unsigned int>(component_index), sizeof(C)});
  component_data.resize(index + sizeof(C));
  return details::create_component<C>(&component_data[index], std::forward<Args>(args)...);
}

template <typename C>
C& UnallocatedEntity::as() {
  allocate();
  return entity_.as<C>();
}

template <typename... Components_>
EntityAlias<Components_...>& UnallocatedEntity::assume() {
  allocate();
  return entity_.assume<Components_...>();
}

template <typename C>
void UnallocatedEntity::remove() {
  if (is_allocated()) {
    entity_.remove<C>();
  } else {
    int index = 0;
    auto component_index = details::component_index<C>();
    for (auto& componentHeader : component_headers_) {
      if (componentHeader.index == component_index) {
        C& component = *reinterpret_cast<C*>(&component_data[index]);
        component.~C();
        break;
      }
      index += componentHeader.size;
    }
    mask_.reset(component_index);
  }
}

void UnallocatedEntity::remove_everything() {
  if (is_allocated()) {
    entity_.remove_everything();
  } else {
    // TODO: call dtors on components
    component_headers_.clear();
    mask_.reset();
  }
}

void UnallocatedEntity::clear_mask() {
  if (is_allocated()) {
    entity_.clear_mask();
  } else {
    component_headers_.clear();
    mask_.reset();
  }
}

void UnallocatedEntity::destroy() {
  if (is_allocated()) {
    entity_.destroy();
  } else {
    manager_ = nullptr;
  }
}

template <typename... Components>
bool UnallocatedEntity::has() const {
  if (is_allocated()) {
    return entity_.has<Components...>();
  } else {
    auto component_mask = details::component_mask<Components...>();
    return (component_mask & mask_) == component_mask;
  }
}

template <typename T>
bool UnallocatedEntity::is() const {
  if (is_allocated()) {
    return entity_.is<T>();
  } else {
    ECS_ASSERT_IS_ENTITY(T);
    ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
    auto component_mask = T::static_mask();
    return (component_mask & mask_) == component_mask;
  }
}

bool UnallocatedEntity::is_valid() const {
  if (is_allocated()) {
    return entity_.is_valid();
  } else {
    return manager_ != nullptr;
  }
}

inline bool operator==(const UnallocatedEntity& lhs, const UnallocatedEntity& rhs) {
  return &lhs == &rhs;
}

inline bool operator!=(const UnallocatedEntity& lhs, const UnallocatedEntity& rhs) {
  return &lhs != &rhs;
}

inline bool UnallocatedEntity::operator==(const Entity& rhs) const {
  return &entity_ == &rhs;
}

inline bool UnallocatedEntity::operator!=(const Entity& rhs) const {
  return &entity_ != &rhs;
}

bool UnallocatedEntity::is_allocated() const {
  return manager_ == nullptr;
}

void UnallocatedEntity::allocate() {
  if (!is_allocated()) {
    entity_ = manager_->create_with_mask(mask_);
    if (component_headers_.size() > 0) {
      auto index = entity_.id().index();
      manager_->mask(index) |= mask_;
      unsigned int offset = 0;
      // TODO: set mask
      for (auto componentHeader : component_headers_) {
        details::BaseManager& componentManager = manager_->get_component_manager(componentHeader.index);
        componentManager.ensure_min_size(index);
        // Copy data from tmp location to acctuial location in component manager
        std::memcpy(componentManager.get_void_ptr(index), &component_data[offset], componentHeader.size);
        offset += componentHeader.size;
      }
    }
    manager_ = nullptr;
  }
}

} // namespace ecs
#endif // OPENECS_UNALLOCATEDENTITY_H

namespace ecs {

namespace details {

template <size_t N, typename Lambda, typename... Args>
struct with_t<N, Lambda, Args...>
    : with_t<N - 1, Lambda, typename details::function_traits<Lambda>::template arg_remove_ref<N - 1>, Args...> {};

template <typename Lambda, typename... Args>
struct with_t<0, Lambda, Args...> {
  static inline void for_each(EntityManager& manager, Lambda lambda) {
    typedef details::function_traits<Lambda> function;
    static_assert(function::arg_count > 0, "Lambda or function must have at least 1 argument.");
    auto view = manager.with<Args...>();
    auto it = view.begin();
    auto end = view.end();
    for (; it != end; ++it) {
      lambda(get_arg<Args>(manager, it.index())...);
    }
  }

  // When arg is component, access component
  template <typename C>
  static inline auto get_arg(EntityManager& manager, index_t index) ->
      typename std::enable_if<!std::is_same<C, Entity>::value, C&>::type {
    return manager.get_component_fast<C>(index);
  }

  // When arg is the Entity, access the Entity
  template <typename C>
  static inline auto get_arg(EntityManager& manager, index_t index) ->
      typename std::enable_if<std::is_same<C, Entity>::value, Entity>::type {
    return manager.get_entity(index);
  }
};

template <typename Lambda>
using with_ = with_t<details::function_traits<Lambda>::arg_count, Lambda>;

} // namespace details

EntityManager::EntityManager(size_t chunk_size) {
  entity_versions_.reserve(chunk_size);
  component_masks_.reserve(chunk_size);
}

EntityManager::~EntityManager() {
  for (details::BaseManager* manager : component_managers_) {
    if (manager)
      delete manager;
  }
  component_managers_.clear();
  component_masks_.clear();
  entity_versions_.clear();
  next_free_indexes_.clear();
  component_mask_to_index_accessor_.clear();
  index_to_component_mask.clear();
}

UnallocatedEntity EntityManager::create() {
  return UnallocatedEntity(*this);
}

std::vector<Entity> EntityManager::create(const size_t num_of_entities) {
  return create_with_mask(details::ComponentMask(0), num_of_entities);
}

template <typename T>
inline void EntityManager::create(const size_t num_of_entities, T lambda) {
  ECS_ASSERT_IS_CALLABLE(T);
  using EntityAlias_ = typename details::function_traits<T>::template arg_remove_ref<0>;
  ECS_ASSERT_IS_ENTITY(EntityAlias_);
  for (Entity& entity : create_with_mask(EntityAlias_::static_mask(), num_of_entities)) {
    // We cannot use as<EntityAlias> since we dont have attached any components
    lambda(*reinterpret_cast<EntityAlias_*>(&entity));
    ECS_ASSERT(entity.has(EntityAlias_::static_mask()), "Entity are missing certain components.");
  }
}

/// If EntityAlias is constructable with Args...
template <typename T, typename... Args>
auto EntityManager::create(Args&&... args) ->
    typename std::enable_if<std::is_constructible<T, Args...>::value, T>::type {
  ECS_ASSERT_IS_ENTITY(T);
  ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
  auto mask = T::static_mask();
  Entity entity = create_with_mask(mask);
  T* entity_alias = new (&entity) T(std::forward<Args>(args)...);
  ECS_ASSERT(entity.has(mask), "Every required component must be added when creating an Entity Alias");
  return *entity_alias;
}

/// If EntityAlias is not constructable with Args...
/// Attempt to create with underlying EntityAlias
template <typename T, typename... Args>
auto EntityManager::create(Args&&... args) ->
    typename std::enable_if<!std::is_constructible<T, Args...>::value, T>::type {
  ECS_ASSERT_IS_ENTITY(T);
  ECS_ASSERT_ENTITY_CORRECT_SIZE(T);
  typedef typename T::Type Type;
  auto mask = T::static_mask();
  Entity entity = create_with_mask(mask);
  Type* entity_alias = new (&entity) Type();
  entity_alias->init(std::forward<Args>(args)...);
  ECS_ASSERT(entity.has(mask), "Every required component must be added when creating an Entity Alias");
  return *reinterpret_cast<T*>(entity_alias);
}

template <typename... Components, typename... Args>
auto EntityManager::create_with(Args&&... args) ->
    typename std::conditional<(sizeof...(Components) > 0), EntityAlias<Components...>, EntityAlias<Args...>>::type {
  using Type =
      typename std::conditional<(sizeof...(Components) > 0), EntityAlias<Components...>, EntityAlias<Args...>>::type;
  Entity entity = create_with_mask(Type::static_mask());
  Type* entity_alias = new (&entity) Type();
  entity_alias->init(std::forward<Args>(args)...);
  return *entity_alias;
}

template <typename... Components>
EntityAlias<Components...> EntityManager::create_with() {
  using Type = EntityAlias<Components...>;
  Entity entity = create_with_mask(details::component_mask<Components...>());
  Type* entity_alias = new (&entity) Type();
  entity_alias->init();
  return *entity_alias;
}

Entity EntityManager::create_with_mask(details::ComponentMask mask) {
  ++count_;
  index_t index = find_new_entity_index(mask);
  size_t slots_required = index + 1;
  if (entity_versions_.size() < slots_required) {
    entity_versions_.resize(slots_required);
    component_masks_.resize(slots_required, details::ComponentMask(0));
  }
  return get_entity(index);
}

std::vector<Entity> EntityManager::create_with_mask(details::ComponentMask mask, const size_t num_of_entities) {
  std::vector<Entity> new_entities;
  size_t entities_left = num_of_entities;
  new_entities.reserve(entities_left);
  auto mask_as_ulong = mask.to_ulong();
  IndexAccessor& index_accessor = component_mask_to_index_accessor_[mask_as_ulong];
  // See if we can use old indexes for destroyed entities via free list
  while (!index_accessor.free_list.empty() && entities_left--) {
    new_entities.push_back(get_entity(index_accessor.free_list.back()));
    index_accessor.free_list.pop_back();
  }
  index_t block_index = 0;
  index_t current = ECS_CACHE_LINE_SIZE; // <- if empty, create new block instantly
  size_t slots_required;
  // Are there any unfilled blocks?
  if (!index_accessor.block_index.empty()) {
    block_index = index_accessor.block_index[index_accessor.block_index.size() - 1];
    current = next_free_indexes_[block_index];
    slots_required = block_count_ * ECS_CACHE_LINE_SIZE + current + entities_left;
  } else {
    slots_required = block_count_ * ECS_CACHE_LINE_SIZE + entities_left;
  }
  entity_versions_.resize(slots_required);
  component_masks_.resize(slots_required, details::ComponentMask(0));

  // Insert until no entity is left or no block remain
  while (entities_left) {
    for (; current < ECS_CACHE_LINE_SIZE && entities_left; ++current) {
      new_entities.push_back(get_entity(current + ECS_CACHE_LINE_SIZE * block_index));
      entities_left--;
    }
    // Add more blocks if there are entities left
    if (entities_left) {
      block_index = block_count_;
      create_new_block(index_accessor, mask_as_ulong, 0);
      ++block_count_;
      current = 0;
    }
  }
  count_ += num_of_entities;
  return new_entities;
}

template <typename... Components>
View<EntityAlias<Components...>> EntityManager::with() {
  details::ComponentMask mask = details::component_mask<Components...>();
  return View<EntityAlias<Components...>>(this, mask);
}

template <typename T>
void EntityManager::with(T lambda) {
  ECS_ASSERT_IS_CALLABLE(T);
  details::with_<T>::for_each(*this, lambda);
}

template <typename T>
View<T> EntityManager::fetch_every() {
  ECS_ASSERT_IS_ENTITY(T);
  return View<T>(this, T::static_mask());
}

template <typename T>
void EntityManager::fetch_every(T lambda) {
  ECS_ASSERT_IS_CALLABLE(T);
  typedef details::function_traits<T> function;
  static_assert(function::arg_count == 1, "Lambda or function must only have one argument");
  typedef typename function::template arg_remove_ref<0> entity_interface_t;
  for (entity_interface_t entityInterface : fetch_every<entity_interface_t>()) {
    lambda(entityInterface);
  }
}

Entity EntityManager::operator[](index_t index) {
  return get_entity(index);
}

Entity EntityManager::operator[](Id id) {
  Entity entity = get_entity(id);
  ECS_ASSERT(id == entity.id(), "Id is no longer valid (Entity was destroyed)");
  return entity;
}

size_t EntityManager::count() {
  return count_;
}

index_t EntityManager::find_new_entity_index(details::ComponentMask mask) {
  auto mask_as_ulong = mask.to_ulong();
  IndexAccessor& index_accessor = component_mask_to_index_accessor_[mask_as_ulong];
  // See if we can use old indexes for destroyed entities via free list
  if (!index_accessor.free_list.empty()) {
    auto index = index_accessor.free_list.back();
    index_accessor.free_list.pop_back();
    return index;
  }
  // EntityManager has created similar entities already
  if (!index_accessor.block_index.empty()) {
    // No free_indexes in free list (removed entities), find a new index
    // at last block, if that block has free slots
    auto& block_index = index_accessor.block_index[index_accessor.block_index.size() - 1];
    auto& current = next_free_indexes_[block_index];
    // If block has empty slot, use it
    if (ECS_CACHE_LINE_SIZE > current) {
      return (current++) + ECS_CACHE_LINE_SIZE * block_index;
    }
  }
  create_new_block(index_accessor, mask_as_ulong, 1);
  return (block_count_++) * ECS_CACHE_LINE_SIZE;
}

void EntityManager::create_new_block(EntityManager::IndexAccessor& index_accessor, unsigned long mask_as_ulong,
                                     index_t next_free_index) {
  index_accessor.block_index.push_back(block_count_);
  next_free_indexes_.resize(block_count_ + 1);
  index_to_component_mask.resize(block_count_ + 1);
  next_free_indexes_[block_count_] = next_free_index;
  index_to_component_mask[block_count_] = mask_as_ulong;
}

template <typename C, typename... Args>
details::ComponentManager<C>& EntityManager::create_component_manager(Args&&... args) {
  details::ComponentManager<C>* ptr =
      new details::ComponentManager<C>(std::forward<EntityManager&>(*this), std::forward<Args>(args)...);
  component_managers_[details::component_index<C>()] = ptr;
  return *ptr;
}

template <typename C>
details::ComponentManager<C>& EntityManager::get_component_manager_fast() {
  return *reinterpret_cast<details::ComponentManager<C>*>(component_managers_[details::component_index<C>()]);
}

template <typename C>
details::ComponentManager<C> const& EntityManager::get_component_manager_fast() const {
  return *reinterpret_cast<details::ComponentManager<C>*>(component_managers_[details::component_index<C>()]);
}

template <typename C>
details::ComponentManager<C>& EntityManager::get_component_manager() {
  auto index = details::component_index<C>();
  if (component_managers_.size() <= index) {
    component_managers_.resize(index + 1, nullptr);
    return create_component_manager<C>();
  } else if (component_managers_[index] == nullptr) {
    return create_component_manager<C>();
  }
  return *reinterpret_cast<details::ComponentManager<C>*>(component_managers_[index]);
}

template <typename C>
details::ComponentManager<C> const& EntityManager::get_component_manager() const {
  auto index = details::component_index<C>();
  ECS_ASSERT(component_managers_.size() > index,
             component_managers_[index] == nullptr && "Component manager not created");
  return *reinterpret_cast<details::ComponentManager<C>*>(component_managers_[index]);
}

details::BaseManager& EntityManager::get_component_manager(size_t component_index) {
  ECS_ASSERT(component_managers_.size() > component_index, "ComponentManager not created with that component index.");
  return *component_managers_[component_index];
}
details::BaseManager const& EntityManager::get_component_manager(size_t component_index) const {
  ECS_ASSERT(component_managers_.size() > component_index, "ComponentManager not created with that component index.");
  return *component_managers_[component_index];
}

template <typename C>
C& EntityManager::get_component(Entity& entity) {
  ECS_ASSERT(has_component<C>(entity), "Entity doesn't have this component attached");
  return get_component_manager<C>().get(entity.id_.index_);
}

template <typename C>
C const& EntityManager::get_component(Entity const& entity) const {
  ECS_ASSERT(has_component<C>(entity), "Entity doesn't have this component attached");
  return get_component_manager<C>().get(entity.id_.index_);
}

template <typename C>
C& EntityManager::get_component_fast(index_t index) {
  return get_component_manager_fast<C>().get(index);
}

template <typename C>
C const& EntityManager::get_component_fast(index_t index) const {
  return get_component_manager_fast<C>().get(index);
}

template <typename C>
C& EntityManager::get_component_fast(Entity& entity) {
  return get_component_manager_fast<C>().get(entity.id_.index_);
}

template <typename C>
C const& EntityManager::get_component_fast(Entity const& entity) const {
  return get_component_manager_fast<C>().get(entity.id_.index_);
}

template <typename C, typename... Args>
C& EntityManager::create_component(Entity& entity, Args&&... args) {
  ECS_ASSERT_VALID_ENTITY(entity);
  ECS_ASSERT(!has_component<C>(entity), "Entity already has this component attached");
  C& component = get_component_manager<C>().create(entity.id_.index_, std::forward<Args>(args)...);
  entity.mask().set(details::component_index<C>());
  return component;
}

template <typename C>
void EntityManager::remove_component(Entity& entity) {
  ECS_ASSERT_VALID_ENTITY(entity);
  ECS_ASSERT(has_component<C>(entity), "Entity doesn't have component attached");
  get_component_manager<C>().remove(entity.id_.index_);
}

template <typename C>
void EntityManager::remove_component_fast(Entity& entity) {
  ECS_ASSERT_VALID_ENTITY(entity);
  ECS_ASSERT(has_component<C>(entity), "Entity doesn't have component attached");
  get_component_manager_fast<C>().remove(entity.id_.index_);
}

void EntityManager::remove_all_components(Entity& entity) {
  ECS_ASSERT_VALID_ENTITY(entity);
  for (auto componentManager : component_managers_) {
    if (componentManager && has_component(entity, componentManager->mask())) {
      componentManager->remove(entity.id_.index_);
    }
  }
}

void EntityManager::clear_mask(Entity& entity) {
  ECS_ASSERT_VALID_ENTITY(entity);
  component_masks_[entity.id_.index_].reset();
}

template <typename C, typename... Args>
C& EntityManager::set_component(Entity& entity, Args&&... args) {
  ECS_ASSERT_VALID_ENTITY(entity);
  if (entity.has<C>()) {
    return get_component_fast<C>(entity) = create_tmp_component<C>(std::forward<Args>(args)...);
  } else
    return create_component<C>(entity, std::forward<Args>(args)...);
}

template <typename C, typename... Args>
C& EntityManager::set_component_fast(Entity& entity, Args&&... args) {
  ECS_ASSERT_VALID_ENTITY(entity);
  ECS_ASSERT(entity.has<C>(), "Entity does not have component attached");
  return get_component_fast<C>(entity) = create_tmp_component<C>(std::forward<Args>(args)...);
}

bool EntityManager::has_component(Entity& entity, details::ComponentMask component_mask) {
  ECS_ASSERT_VALID_ENTITY(entity);
  return (mask(entity) & component_mask) == component_mask;
}

bool EntityManager::has_component(Entity const& entity, details::ComponentMask const& component_mask) const {
  ECS_ASSERT_VALID_ENTITY(entity);
  return (mask(entity) & component_mask) == component_mask;
}

template <typename... Components>
bool EntityManager::has_component(Entity& entity) {
  return has_component(entity, details::component_mask<Components...>());
}

template <typename... Components>
bool EntityManager::has_component(Entity const& entity) const {
  return has_component(entity, details::component_mask<Components...>());
}

bool EntityManager::is_valid(Entity& entity) {
  return entity.id_.index_ < entity_versions_.size() && entity.id_.version_ == entity_versions_[entity.id_.index_];
}

bool EntityManager::is_valid(Entity const& entity) const {
  return entity.id_.index_ < entity_versions_.size() && entity.id_.version_ == entity_versions_[entity.id_.index_];
}

void EntityManager::destroy(Entity& entity) {
  index_t index = entity.id().index_;
  remove_all_components(entity);
  ++entity_versions_[index];
  auto& mask_as_ulong = index_to_component_mask[index / ECS_CACHE_LINE_SIZE];
  component_mask_to_index_accessor_[mask_as_ulong].free_list.push_back(index);
  --count_;
}

details::ComponentMask& EntityManager::mask(Entity& entity) {
  return mask(entity.id_.index_);
}

details::ComponentMask const& EntityManager::mask(Entity const& entity) const {
  return mask(entity.id_.index_);
}

details::ComponentMask& EntityManager::mask(index_t index) {
  return component_masks_[index];
}

details::ComponentMask const& EntityManager::mask(index_t index) const {
  return component_masks_[index];
}

Entity EntityManager::get_entity(Id id) {
  return Entity(this, id);
}

Entity EntityManager::get_entity(index_t index) {
  return get_entity(Id(index, entity_versions_[index]));
}

size_t EntityManager::capacity() const {
  return entity_versions_.capacity();
}

} // namespace ecs
#endif // ECS_ENTITYMANAGER_H

namespace ecs {

namespace details {

template <typename C>
ComponentManager<C>::ComponentManager(EntityManager& manager, size_t chunk_size)
    : manager_(manager), pool_(chunk_size) {
}

// Creating a component that has a defined ctor
template <typename C, typename... Args>
auto create_component(void* ptr, Args&&... args) ->
    typename std::enable_if<std::is_constructible<C, Args...>::value, C&>::type {
  return *new (ptr) C(std::forward<Args>(args)...);
}

// Creating a component that doesn't have ctor, and is not a property -> create using uniform initialization
template <typename C, typename... Args>
auto create_component(void* ptr, Args&&... args) -> typename std::enable_if<
    !std::is_constructible<C, Args...>::value && !std::is_base_of<details::BaseProperty, C>::value, C&>::type {
  return *new (ptr) C{std::forward<Args>(args)...};
}

// Creating a component that doesn't have ctor, and is a property -> create using underlying Property ctor
template <typename C, typename... Args>
auto create_component(void* ptr, Args&&... args) -> typename std::enable_if<
    !std::is_constructible<C, Args...>::value && std::is_base_of<details::BaseProperty, C>::value, C&>::type {
  static_assert(sizeof...(Args) <= 1, ECS_ASSERT_MSG_ONLY_ONE_ARGS_PROPERTY_CONSTRUCTOR);
  return *reinterpret_cast<C*>(new (ptr) typename C::ValueType(std::forward<Args>(args)...));
}

template <typename C>
template <typename... Args>
C& ComponentManager<C>::create(index_t index, Args&&... args) {
  pool_.ensure_min_size(index + 1);
  create_component<C>(get_ptr(index), std::forward<Args>(args)...);
  return get(index);
}

template <typename C>
void ComponentManager<C>::remove(index_t index) {
  pool_.destroy(index);
  manager_.mask(index).reset(component_index<C>());
}

template <typename C>
C& ComponentManager<C>::operator[](index_t index) {
  return get(index);
}

template <typename C>
C& ComponentManager<C>::get(index_t index) {
  return *get_ptr(index);
}

template <typename C>
C const& ComponentManager<C>::get(index_t index) const {
  return *get_ptr(index);
}

template <typename C>
C* ComponentManager<C>::get_ptr(index_t index) {
  return pool_.get_ptr(index);
}

template <typename C>
C const* ComponentManager<C>::get_ptr(index_t index) const {
  return pool_.get_ptr(index);
}

template <typename C>
void* ComponentManager<C>::get_void_ptr(index_t index) {
  return pool_.get_ptr(index);
}

template <typename C>
void const* ComponentManager<C>::get_void_ptr(index_t index) const {
  return pool_.get_ptr(index);
}

template <typename C>
void ComponentManager<C>::ensure_min_size(index_t size) {
  pool_.ensure_min_size(size);
}

template <typename C>
ComponentMask ComponentManager<C>::mask() {
  return component_mask<C>();
}

} // namespace details

} // namespace ecs
#endif // ECS_COMPONENTMANAGER_H
// #included from: Property.h
#ifndef ECS_PROPERTY_H
#define ECS_PROPERTY_H

namespace ecs {

namespace details {
///---------------------------------------------------------------------
/// Helper class used for compile-time checks to determine if a
/// component is a propery.
///---------------------------------------------------------------------
class BaseProperty {};

} // namespace details

///---------------------------------------------------------------------
/// A Property is a helper class for Component with only one
/// property of any type
///---------------------------------------------------------------------
///
/// A Property is a helper class for Component with only one
/// property of any type.
///
/// it implements standard constructors, type conversations and
/// operators:
///
///     ==, !=
///     >=, <=, <, >
///     +=, -=, *=, /=, %=
///     &=, |=, ^=
///     +, -, *; /, %
///     &, |, ^, ~
///     >>, <<
///     ++, --
///
/// TODO: Add more operators?
///---------------------------------------------------------------------
template <typename T>
struct Property : details::BaseProperty {
  Property() {}
  Property(const T& value) : value(value) {}

  operator const T&() const { return value; }
  operator T&() { return value; }

  T value;
  using ValueType = T;
};

/// Comparision operators
template <typename T, typename E>
bool operator==(Property<T> const& lhs, const E& rhs);
template <typename T, typename E>
bool operator!=(Property<T> const& lhs, const E& rhs);
template <typename T, typename E>
bool operator>=(Property<T> const& lhs, const E& rhs);
template <typename T, typename E>
bool operator>(Property<T> const& lhs, const E& rhs);
template <typename T, typename E>
bool operator<=(Property<T> const& lhs, const E& rhs);
template <typename T, typename E>
bool operator<(Property<T> const& lhs, const E& rhs);

/// Compound assignment operators
template <typename T, typename E>
T& operator+=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator-=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator*=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator/=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator%=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator&=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator|=(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T& operator^=(Property<T>& lhs, const E& rhs);

/// Arithmetic operators
template <typename T, typename E>
T operator+(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator-(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator*(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator/(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator%(Property<T>& lhs, const E& rhs);
template <typename T>
T& operator++(Property<T>& lhs);
template <typename T>
T operator++(Property<T>& lhs, int);
template <typename T>
T& operator--(Property<T>& lhs);
template <typename T>
T operator--(Property<T>& lhs, int);

/// Bitwise operators
template <typename T, typename E>
T operator&(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator|(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator^(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator~(Property<T>& lhs);
template <typename T, typename E>
T operator>>(Property<T>& lhs, const E& rhs);
template <typename T, typename E>
T operator<<(Property<T>& lhs, const E& rhs);

} // namespace ecs

// #included from: Property.inl
namespace ecs {

template <typename T, typename E>
inline bool operator==(Property<T> const& lhs, const E& rhs) {
  return lhs.value == rhs;
}

template <typename T, typename E>
inline bool operator!=(Property<T> const& lhs, const E& rhs) {
  return lhs.value != rhs;
}

template <typename T, typename E>
inline bool operator>=(Property<T> const& lhs, const E& rhs) {
  return lhs.value >= rhs;
}

template <typename T, typename E>
inline bool operator>(Property<T> const& lhs, const E& rhs) {
  return lhs.value > rhs;
}

template <typename T, typename E>
inline bool operator<=(Property<T> const& lhs, const E& rhs) {
  return lhs.value <= rhs;
}

template <typename T, typename E>
inline bool operator<(Property<T> const& lhs, const E& rhs) {
  return lhs.value < rhs;
}

template <typename T, typename E>
inline T& operator+=(Property<T>& lhs, const E& rhs) {
  return lhs.value += rhs;
}

template <typename T, typename E>
inline T& operator-=(Property<T>& lhs, const E& rhs) {
  return lhs.value -= rhs;
}

template <typename T, typename E>
inline T& operator*=(Property<T>& lhs, const E& rhs) {
  return lhs.value *= rhs;
}

template <typename T, typename E>
inline T& operator/=(Property<T>& lhs, const E& rhs) {
  return lhs.value /= rhs;
}

template <typename T, typename E>
inline T& operator%=(Property<T>& lhs, const E& rhs) {
  return lhs.value %= rhs;
}

template <typename T, typename E>
inline T& operator&=(Property<T>& lhs, const E& rhs) {
  return lhs.value &= rhs;
}

template <typename T, typename E>
inline T& operator|=(Property<T>& lhs, const E& rhs) {
  return lhs.value |= rhs;
}

template <typename T, typename E>
inline T& operator^=(Property<T>& lhs, const E& rhs) {
  return lhs.value ^= rhs;
}

template <typename T, typename E>
inline T operator+(Property<T>& lhs, const E& rhs) {
  return lhs.value + rhs;
}

template <typename T, typename E>
inline T operator-(Property<T>& lhs, const E& rhs) {
  return lhs.value - rhs;
}

template <typename T, typename E>
inline T operator*(Property<T>& lhs, const E& rhs) {
  return lhs.value * rhs;
}

template <typename T, typename E>
inline T operator/(Property<T>& lhs, const E& rhs) {
  return lhs.value / rhs;
}

template <typename T, typename E>
inline T operator%(Property<T>& lhs, const E& rhs) {
  return lhs.value % rhs;
}

template <typename T>
inline T& operator++(Property<T>& lhs) {
  ++lhs.value;
  return lhs.value;
}

template <typename T>
inline T operator++(Property<T>& lhs, int) {
  T copy = lhs;
  ++lhs;
  return copy;
}

template <typename T>
inline T& operator--(Property<T>& lhs) {
  --lhs.value;
  return lhs.value;
}

template <typename T>
inline T operator--(Property<T>& lhs, int) {
  T copy = lhs;
  --lhs;
  return copy;
}

template <typename T, typename E>
inline T operator&(Property<T>& lhs, const E& rhs) {
  return lhs.value & rhs;
}

template <typename T, typename E>
inline T operator|(Property<T>& lhs, const E& rhs) {
  return lhs.value | rhs;
}

template <typename T, typename E>
inline T operator^(Property<T>& lhs, const E& rhs) {
  return lhs.value ^ rhs;
}

template <typename T, typename E>
inline T operator~(Property<T>& lhs) {
  return ~lhs.value;
}

template <typename T, typename E>
inline T operator>>(Property<T>& lhs, const E& rhs) {
  return lhs.value >> rhs;
}

template <typename T, typename E>
inline T operator<<(Property<T>& lhs, const E& rhs) {
  return lhs.value << rhs;
}

} // namespace ecs

///---------------------------------------------------------------------
/// This will allow a property to be streamed into a input and output
/// stream.
///---------------------------------------------------------------------
namespace std {

template <typename T>
ostream& operator<<(ostream& os, const ecs::Property<T>& obj) {
  return os << obj.value;
}

template <typename T>
istream& operator>>(istream& is, ecs::Property<T>& obj) {
  return is >> obj.value;
}

} // namespace std

///---------------------------------------------------------------------
/// This will enable properties to be added to a string
///---------------------------------------------------------------------
template <typename T>
std::string operator+(const std::string& lhs, const ecs::Property<T>& rhs) {
  return lhs + rhs.value;
}

template <typename T>
std::string operator+(std::string&& lhs, ecs::Property<T>&& rhs) {
  return lhs + rhs.value;
}

template <typename T>
std::string operator+(std::string&& lhs, const ecs::Property<T>& rhs) {
  return lhs + rhs.value;
}

template <typename T>
std::string operator+(const std::string& lhs, ecs::Property<T>&& rhs) {
  return lhs + rhs.value;
}
#endif // ECS_PROPERTY_H
// #included from: Iterator.h
#ifndef ECS_ITERATOR_H
#define ECS_ITERATOR_H

namespace ecs {

///---------------------------------------------------------------------
/// Iterator is an iterator for iterating through the entity manager.
/// The iterator should fulfill the c++ standards for an input iterator,
///---------------------------------------------------------------------
template <typename T>
class Iterator : public std::iterator<std::input_iterator_tag, typename std::remove_reference<T>::type> {
  using T_no_ref = typename std::remove_reference<typename std::remove_const<T>::type>::type;

public:
  Iterator(EntityManager* manager, details::ComponentMask mask, bool begin = true);
  Iterator(const Iterator& it);
  Iterator& operator=(const Iterator& rhs) = default;

  // Get the current index (cursor)
  index_t index() const;
  Iterator& operator++();

  // The the current entity
  T entity();
  T const entity() const;

private:
  // find next entity withing the EntityManager which has the correct components
  void find_next();

  EntityManager* manager_;
  details::ComponentMask mask_;
  index_t cursor_;
  size_t size_;
}; // Iterator

template <typename T>
bool operator==(Iterator<T> const& lhs, Iterator<T> const& rhs);
template <typename T>
bool operator!=(Iterator<T> const& lhs, Iterator<T> const& rhs);
template <typename T>
inline T operator*(Iterator<T>& lhs);
template <typename T>
inline T const& operator*(Iterator<T> const& lhs);

} // namespace ecs

// #included from: Iterator.inl
namespace ecs {

template <typename T>
Iterator<T>::Iterator(EntityManager* manager, details::ComponentMask mask, bool begin)
    : manager_(manager), mask_(mask), cursor_(0) {
  // Must be pool size because of potential holes
  size_ = manager_->entity_versions_.size();
  if (!begin)
    cursor_ = size_;
  find_next();
}

template <typename T>
Iterator<T>::Iterator(const Iterator& it) : Iterator(it.manager_, it.cursor_) {
}

template <typename T>
index_t Iterator<T>::index() const {
  return cursor_;
}

template <typename T>
inline void Iterator<T>::find_next() {
  while (cursor_ < size_ && (manager_->component_masks_[cursor_] & mask_) != mask_) {
    ++cursor_;
  }
}

template <typename T>
T Iterator<T>::entity() {
  return manager_->get_entity(index()).template as<typename Iterator<T>::T_no_ref>();
}

template <typename T>
const T Iterator<T>::entity() const {
  return manager_->get_entity(index()).template as<typename Iterator<T>::T_no_ref>();
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
  ++cursor_;
  find_next();
  return *this;
}

template <typename T>
bool operator==(Iterator<T> const& lhs, Iterator<T> const& rhs) {
  return lhs.index() == rhs.index();
}

template <typename T>
bool operator!=(Iterator<T> const& lhs, Iterator<T> const& rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline T operator*(Iterator<T>& lhs) {
  return lhs.entity();
}

template <typename T>
inline T const& operator*(Iterator<T> const& lhs) {
  return lhs.entity();
}

} // namespace ecs
#endif // ECS_ITERATOR_H
// #included from: View.h
#ifndef ECS_VIEW_H
#define ECS_VIEW_H

namespace ecs {

///---------------------------------------------------------------------
/// Helper class that is used to access the iterator
///---------------------------------------------------------------------
/// @usage Calling entities.with<Components>(), returns a view
///        that can be used to access the iterator with begin() and
///        end() that iterates through all entities with specified
///        Components
///---------------------------------------------------------------------
template <typename T>
class View {
  ECS_ASSERT_IS_ENTITY(T)
public:
  using iterator = Iterator<T>;
  using const_iterator = Iterator<T const&>;

  View(EntityManager* manager, details::ComponentMask mask);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  index_t count();
  template <typename... Components>
  View<T>&& with();

private:
  EntityManager* manager_;
  details::ComponentMask mask_;

  friend class EntityManager;
}; // View

} // namespace ecs

// #included from: View.inl

namespace ecs {

template <typename T>
View<T>::View(EntityManager* manager, details::ComponentMask mask) : manager_(manager), mask_(mask) {
}

template <typename T>
typename View<T>::iterator View<T>::begin() {
  return iterator(manager_, mask_, true);
}

template <typename T>
typename View<T>::iterator View<T>::end() {
  return iterator(manager_, mask_, false);
}

template <typename T>
typename View<T>::const_iterator View<T>::begin() const {
  return const_iterator(manager_, mask_, true);
}

template <typename T>
typename View<T>::const_iterator View<T>::end() const {
  return const_iterator(manager_, mask_, false);
}

template <typename T>
inline index_t View<T>::count() {
  index_t count = 0;
  for (auto it = begin(); it != end(); ++it) {
    ++count;
  }
  return count;
}

template <typename T>
template <typename... Components>
View<T>&& View<T>::with() {
  mask_ |= details::component_mask<Components...>();
  return *this;
}

} // namespace ecs
#endif // OPENECS_VIEW_H
// #included from: SystemManager.h
//
// Created by Robin Gr�nberg on 29/11/15.
//

#ifndef OPENECS_SYSTEM_MANAGER_H
#define OPENECS_SYSTEM_MANAGER_H

namespace ecs {

class EntityManager;
class System;

///---------------------------------------------------------------------
/// A SystemManager is responsible for managing Systems.
///---------------------------------------------------------------------
///
/// A SystemManager is associated with an EntityManager and any
/// number of systems. Calling update calls update on every system.
/// Each system can access the EntityManager and perform operations
/// on the entities.
///
///---------------------------------------------------------------------
class SystemManager : details::forbid_copies {
public:
  inline SystemManager(EntityManager& entities) : entities_(&entities) {}

  inline ~SystemManager();

  /// Adds a System to this SystemManager.
  template <typename S, typename... Args>
  inline S& add(Args&&... args);

  /// Removes a System from this System Manager
  template <typename S>
  inline void remove();

  /// Update all attached systems. They are updated in the order they are added
  inline void update(float time);

  /// Check if a system is attached.
  template <typename S>
  inline bool exists();

private:
  std::vector<System*> systems_;
  std::vector<size_t> order_;
  EntityManager* entities_;

  friend class System;
};

} // namespace ecs

// #included from: SystemManager.inl
// #included from: System.h
//
// Created by Robin Gr�nberg on 29/11/15.
//

#ifndef OPENECS_SYSTEM_H
#define OPENECS_SYSTEM_H

namespace ecs {

class EntityManager;
class SystemManager;

///---------------------------------------------------------------------
/// A system is responsible for some kind of behavior for entities
/// with certain components
///---------------------------------------------------------------------
///
/// A system implements behavior of entities with required components
/// The update method is called every frame/update from the
/// SystemManager.
///
///---------------------------------------------------------------------
class System {
public:
  virtual ~System() {}
  virtual void update(float time) = 0;

protected:
  inline EntityManager& entities();

private:
  friend class SystemManager;
  SystemManager* manager_;
};

} // namespace ecs

// #included from: System.inl

namespace ecs {

EntityManager& System::entities() {
  return *manager_->entities_;
}

} // namespace ecs
#endif // OPENECS_SYSTEM_H

namespace ecs {

SystemManager::~SystemManager() {
  for (auto system : systems_) {
    if (system != nullptr)
      delete system;
  }
  systems_.clear();
  order_.clear();
}

template <typename S, typename... Args>
S& SystemManager::add(Args&&... args) {
  ECS_ASSERT_IS_SYSTEM(S);
  ECS_ASSERT(!exists<S>(), "System already exists");
  systems_.resize(details::system_index<S>() + 1);
  S* system = new S(std::forward<Args>(args)...);
  system->manager_ = this;
  systems_[details::system_index<S>()] = system;
  order_.push_back(details::system_index<S>());
  return *system;
}

template <typename S>
void SystemManager::remove() {
  ECS_ASSERT_IS_SYSTEM(S);
  ECS_ASSERT(exists<S>(), "System does not exist");
  delete systems_[details::system_index<S>()];
  systems_[details::system_index<S>()] = nullptr;
  for (auto it = order_.begin(); it != order_.end(); ++it) {
    if (*it == details::system_index<S>()) {
      order_.erase(it);
      break;
    }
  }
}

void SystemManager::update(float time) {
  for (auto index : order_) {
    systems_[index]->update(time);
  }
}

template <typename S>
inline bool SystemManager::exists() {
  ECS_ASSERT_IS_SYSTEM(S);
  return systems_.size() > details::system_index<S>() && systems_[details::system_index<S>()] != nullptr;
}

} // namespace ecs
#endif // OPENECS_SYSTEM_MANAGER_H
#endif // ECS_MAIN_INCLUDE
#endif // ECS_SINGLE_INCLUDE_H
