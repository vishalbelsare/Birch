/**
 * @file
 */
#pragma once

#include "libbirch/global.hpp"
#include "libbirch/World.hpp"
#include "libbirch/Any.hpp"

namespace bi {
/**
 * Shared pointer with copy-on-write semantics.
 *
 * @ingroup libbirch
 *
 * @tparam T Type.
 */
template<class T>
class SharedPointer: public SharedPointer<typename super_type<T>::type> {
  template<class U> friend class SharedPointer;
  template<class U> friend class WeakPointer;
public:
  using value_type = T;
  using this_type = SharedPointer<T>;
  using super_type = SharedPointer<typename super_type<T>::type>;
  using root_type = typename super_type::root_type;

  /**
   * Default constructor.
   */
  SharedPointer(const std::nullptr_t& object = nullptr) :
      super_type(object) {
    //
  }

  /**
   * Constructor.
   */
  SharedPointer(const std::shared_ptr<T>& object) :
      super_type(object) {
    //
  }

  /**
   * Generic constructor.
   */
  template<class U>
  SharedPointer(const SharedPointer<U>& o) :
      super_type(o) {
    //
  }

  /**
   * Generic constructor.
   */
  template<class U>
  SharedPointer(const WeakPointer<U>& o) :
      super_type(o) {
    //
  }

  /**
   * Value assignment.
   */
  template<class U,
      typename = std::enable_if_t<bi::has_assignment<T,U>::value>>
  SharedPointer<T>& operator=(const U& o) {
    *get() = o;
    return *this;
  }

  /**
   * Value conversion.
   */
  template<class U,
      typename = std::enable_if_t<bi::has_conversion<T,U>::value>>
  operator U() {
    return static_cast<U>(*get());
  }

  /**
   * Get the raw pointer.
   */
  T* get() {
#ifndef NDEBUG
    return dynamic_cast<T*>(root_type::get());
#else
    return static_cast<T*>(root_type::get());
#endif
  }

  /**
   * Dereference.
   */
  T& operator*() {
    return *get();
  }

  /**
   * Member access.
   */
  T* operator->() {
    return get();
  }

  /**
   * Call operator.
   */
  template<class ... Args>
  auto operator()(Args ... args) {
    return (*get())(args...);
  }
};

template<>
class SharedPointer<Any> {
  template<class U> friend class SharedPointer;
  template<class U> friend class WeakPointer;
public:
  using value_type = Any;
  using this_type = SharedPointer<value_type>;
  using root_type = this_type;

  SharedPointer(const std::nullptr_t& object = nullptr) :
      world(fiberWorld) {
    //
  }

  SharedPointer(const std::shared_ptr<Any>& object) :
      object(object),
      world(fiberWorld) {
    //
  }

  SharedPointer(const SharedPointer<Any>& o) :
      object(o.object),
      world(fiberCloning ? fiberWorld : o.world) {
    //
  }

  template<class U>
  SharedPointer(const SharedPointer<U>& o) :
      object(o.object),
      world(o.world) {
    //
  }

  template<class U>
  SharedPointer(const WeakPointer<U>& o) :
      object(o.object.lock()),
      world(o.world) {
    //
  }

  SharedPointer<Any>& operator=(const SharedPointer<Any>& o) {
    assert(world == o.world);
    object = o.object;
    return *this;
  }

  /**
   * Is the pointer not null?
   */
  bool query() const {
    return static_cast<bool>(object);
  }

  Any* get() {
    object = world->get(object);
    return object.get();
  }

  const std::shared_ptr<World>& getWorld() {
    return world;
  }

  Any& operator*() {
    return *get();
  }

  Any* operator->() {
    return get();
  }

  /**
   * Dynamic cast. Returns `nullptr` if the cast if unsuccessful.
   */
  template<class U>
  SharedPointer<U> dynamic_pointer_cast() {
    return SharedPointer<U>(std::dynamic_pointer_cast < U > (object));
  }

  /**
   * Static cast. Undefined if unsuccessful.
   */
  template<class U>
  SharedPointer<U> static_pointer_cast() {
    return SharedPointer<U>(std::static_pointer_cast < U > (object));
  }

protected:
  /**
   * The object.
   */
  std::shared_ptr<Any> object;

  /**
   * The world to which the object should belong (although it may belong to
   * a clone ancestor of this world).
   */
  std::shared_ptr<World> world;
};
}
