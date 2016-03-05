#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "BuilderTarget.h"
#include "NullValues.h"
#include "Iterator.h"
#include "Exception.h"

#include <vector>

namespace xmlpl {
  template <class T>
  class RefCountedVector : public std::vector<T> {
    unsigned int refCount;

  public:
    RefCountedVector() : refCount(0) {}

    void incRef() {refCount++;}
    void decRef() {if (refCount) refCount--;}
    unsigned int getRefCount() {return refCount;}
    void release() {if (!refCount) delete this;}
  };

  template <class T>
  class Sequence : public BuilderTarget<T> {
    mutable RefCountedVector<T> *array;

  public:
    Sequence(const Sequence<T> &s) {
      array = s.array;

      if (s.isTemporary()) s.array = 0;
      else if (array) array->incRef();
    }
    Sequence(const Iterator<T> &i) : array(0) {append(i);}
    Sequence(T n) : array(0) {append(n);}
    Sequence() : array(0) {}
    virtual ~Sequence() {release();}

    // Methods
    virtual bool isTemporary() const {return false;}

    T &get(const unsigned int i) const {
      if (size() <= i)
        throw Exception(String("index of ") + String((int)i) + " out of range");

      return (*array)[i];
    }
    bool empty() const {return !array || array->empty();}
    unsigned int size() const {return array ? array->size() : 0;}
    void steal(const Sequence<T> &s) {
      release();

      array = s.array;
      s.array = 0;
    }
    unsigned int getRefCount() const
    {return array ? array->getRefCount() : 0;}
    const T first() const {
      return empty() ? Null((T *)0) : get(0);
    }


    // Operators
    operator bool() const {return !empty();}
    Sequence<T> &operator=(const Sequence<T> &s) {
      release();
      append(s);
      return *this;
    }
    T &operator[](const unsigned int i) const {return get(i);}


    // Target methods
    virtual void append(const Sequence<T> &s) {
      if (s.isTemporary() && s.getRefCount() <= 1 && empty()) steal(s);
      else if (!s.empty()) {
        reserve(s.array->size());

        for (unsigned int i = 0; i < s.array->size(); i++)
          array->push_back((*s.array)[i]);

        if (s.isTemporary()) s.release();
      }
    }
    virtual void append(Iterator<T> &i) {while (i.hasNext()) append(i.next());}
    virtual void append(T t) {
      ensureArray();
      array->push_back(t);
    }


    Sequence<T> &add(const Sequence<T> &s) {append(s); return *this;}
    Sequence<T> &add(T t) {append(t); return *this;}

    void resize(const unsigned int size) {
      if (!size) release();
      else {
        ensureArray();
        array->resize(size, Null((T *)0));
      }
    }

    void reserve(const unsigned int size) {
      ensureArray();
      array->reserve(size);
    }

    void release() const {
      if (array) {
        array->decRef();
        array->release();
        array = 0;
      }
    }

  protected:
    void ensureArray() {
      if (!array) {
        array = new RefCountedVector<T>;
        array->incRef();
      }
    }
  };


  template <class T>
  class TemporarySequence : public Sequence<T> {
  public:
    TemporarySequence(const Sequence<T> &s) : Sequence<T>(s) {}
    TemporarySequence() {}

    virtual bool isTemporary() const {return true;}
  };
};

#include "ChildBuilderTarget.h"

namespace xmlpl {  
  template<class T>
  inline Target<NodeRef> &BuilderTarget<T>::getChildTarget() {
    return *(new ChildBuilderTarget(nodeStack));
  }
};
#endif // SEQUENCE_H
