#ifndef REFERENCECOUNTER_H
#define REFERENCECOUNTER_H

namespace xmlpl {
  class ReferenceCounter {
    unsigned int refCount;

  public:
    ReferenceCounter() : refCount(0) {}
    virtual ~ReferenceCounter() {}

    void incRef() {refCount++;}
    void decRef() {if (refCount) refCount--;}
    unsigned int getRefCount() {return refCount;}
    void release() {if (!refCount) delete this;}
  };
};
#endif // REFERENCECOUNTER_H
