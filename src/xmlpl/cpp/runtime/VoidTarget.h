#ifndef VOIDTARGET_H
#define VOIDTARGET_H

#include "Target.h"

namespace xmlpl {
  template <class T>
  class VoidTarget : public Target<T> {
  public:
    virtual void append(const Sequence<T> &s) {}
    virtual void append(T t) {}

    // XMLStream functions
    virtual void startDocument() {}
    virtual void endDocument() {}
    
    virtual void startElement(const QName *name) {}
    virtual void endElement() {}
    virtual void attribute(const QName *name, const String &text) {}
    
    virtual void text(const String &text) {}
    virtual void comment(const String &text) {}
    virtual void pi(const String &target, const String &data) {}

    virtual void flush() {}
    virtual void error(const typename XMLStream::error_t type, const String &msg) {}
  };
};

#endif // VOIDTARGET_H
