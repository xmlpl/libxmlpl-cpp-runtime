#ifndef TARGET_H
#define TARGET_H

#include "Memory.h"
#include "dom/XMLStream.h"
#include "dom/Node.h"
#include "Iterator.h"

namespace xmlpl {
  template <class T> class Sequence;

  template <class T>
  class Target : virtual public Memory, virtual public XMLStream {
  public:
		virtual ~Target() {}

    virtual void append(const Sequence<T> &s) = 0;
    virtual void append(Iterator<T> &i) = 0;
    virtual void append(T t) = 0;

    virtual Target<NodeRef> &getChildTarget() = 0;
  };
};
#endif // TARGET_H
