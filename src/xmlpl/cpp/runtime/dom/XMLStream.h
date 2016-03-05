#ifndef XMLSTREAM_H
#define XMLSTREAM_H

#include "String.h"
#include "QName.h"
#include <xmlpl/cpp/runtime/Memory.h>

namespace xmlpl {
  class XMLStream : public virtual Memory {
  public:
    typedef enum {WARNING = 1, ERROR, FATAL_ERROR} error_t;

		virtual ~XMLStream() {}
    
    virtual void startDocument() = 0;
    virtual void endDocument() = 0;
    
    virtual void startElement(const QName *name) = 0;
    virtual void endElement() = 0;
    virtual void attribute(const QName *name, const String &text) = 0;
    
    virtual void text(const String &text) = 0;
    virtual void comment(const String &text) = 0;
    virtual void pi(const String &target, const String &data) = 0;

    virtual void flush() {}
    virtual void close() {}
    virtual void error(const error_t type, const String &msg) {}
  };
};
#endif
