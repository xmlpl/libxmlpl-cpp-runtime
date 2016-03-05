#ifndef LIBXML2XMLSTREAM_H
#define LIBXML2XMLSTREAM_H

#include "StreamTarget.h"

#include <BasicUtils/BasicFunctor.h>

#include <iostream>
#include <string>
#include <vector>

typedef struct _xmlTextWriter xmlTextWriter;

namespace xmlpl {
  class LibXML2XMLStream : public StreamTarget {
    std::ostream &out;
    BasicFunctorBase *closeFunctor;
    std::string encoding;
    bool disableHeader;
    xmlTextWriter *writer;
    bool attributeOk;

    unsigned int depth;
    typedef std::pair<const Prefix *, unsigned int> prefixPair_t;
    typedef std::vector<prefixPair_t> prefixStack_t;
    prefixStack_t prefixStack;

    bool started;

  public:
    LibXML2XMLStream(std::ostream &out, const std::string encoding = "UTF-8",
                     bool disableHeader = false);
    virtual ~LibXML2XMLStream();

    void setCloseFunctor(BasicFunctorBase *functor) {closeFunctor = functor;}
    BasicFunctorBase *getCloseFunctor() const {return closeFunctor;}

    // XMLStream functions
    virtual void startDocument();
    virtual void endDocument();

    virtual void startElement(const QName *name);
    virtual void endElement();

    virtual void attribute(const QName *name, const String &text);
    virtual void text(const String &text);
    virtual void comment(const String &text);
    virtual void pi(const String &target, const String &data);

    virtual void flush();
    virtual void close();

  protected:
    bool isPrefixActive(const Prefix *prefix);
  };
};
#endif
