#ifndef REFERENCE_H
#define REFERENCE_H

#include "Memory.h"
#include <BasicUtils/BasicException.h>

namespace xmlpl {
  template <class T, class P = T>
  class Reference : public Memory {
    T *ptr;

  public:
    typedef enum {STEAL} steal_t;

    Reference() : ptr(0) {}
    Reference(Reference<T, P> &o, steal_t) : ptr(o.ptr) {o.ptr = 0;}
    Reference(const Reference<T, P> &o) : ptr(o.ptr) {if (ptr) ptr->incRef();}
    Reference(T *ptr) : ptr(ptr) {if (ptr) ptr->incRef();}
    ~Reference() {release();}

    const bool operator==(const T *ptr) const {
      return this->ptr == ptr;
    }

    const bool operator!=(const T *ptr) const {
      return this->ptr != ptr;
    }

    const bool operator==(const Reference<T, P> &ref) const {
      return ptr == ref.ptr;
    }

    const bool operator!=(const Reference<T, P> &ref) const {
      return ptr != ref.ptr;
    }

    const bool operator<(const Reference<T, P> &ref) const {
      return ptr < ref.ptr;
    }

    Reference<T, P> &operator=(const Reference<T, P> &ref) {
      if (*this == ref) return *this;
    
      release();

      ptr = ref.ptr;
      if (ptr) ptr->incRef();

      return *this;
    }

    Reference<T, P> &operator=(T *ptr) {
      if (this->ptr == ptr) return *this;
    
      release();

      this->ptr = ptr;
      if (ptr) ptr->incRef();

      return *this;
    }

    operator Reference<P> &() {
      return *(Reference<P> *)this;
    }

    T *get() const {return ptr;}
    T *operator->() const {checkPtr(); return get();}
    T &operator*() const {checkPtr(); return *get();}
    bool operator!() const {return ptr == 0;}

    T *drop() {
      T *tmp = ptr;
      if (ptr) {
	ptr->decRef();
	ptr = 0;
      }

      return tmp;
    }

    Reference<T, P> adopt() {
      Reference<T, P> tmp(*this, STEAL);
      return tmp;
    }

    Reference<T, P> clone() {return Reference<T, P>(ptr);}

  protected:
    void release() {
      if (ptr) {
	ptr->decRef();
	ptr->release();
	ptr = 0;
      }
    }

    void checkPtr() const {
      ASSERT_OR_THROW("Cannot dereference null pointer!", ptr);
    }
  };
};
#endif
