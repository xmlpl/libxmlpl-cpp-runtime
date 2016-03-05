#ifndef DOMBUILDER_H
#define DOMBUILDER_H

#include "XMLStream.h"
#include "XMLSource.h"
#include "DOMFactory.h"
#include "Proxy.h"
#include "ProxyStack.h"

#include <xmlpl/cpp/runtime/Memory.h>

namespace xmlpl {
  class DOMBuilder : public virtual Memory, public XMLStream {
    DOMFactory &factory;
    XMLSource &source;

    Document *root;
    ProxyStack proxyStack;
    unsigned int streamDepth;

  public:
    DOMBuilder(DOMFactory &factory, XMLSource &source);
    virtual ~DOMBuilder() {}

    virtual DocumentRef adoptRoot()
		{Document *tmp = root; root = 0; return tmp;}
    virtual bool pump() {return source.pump(this);}

    virtual void startDocument();
    virtual void endDocument();

    virtual void startElement(const QName *name);
    virtual void endElement();
    virtual void attribute(const QName *name, const String &text);

    virtual void text(const String &text);
    virtual void comment(const String &text);
    virtual void pi(const String &target, const String &data);

    virtual void error(const error_t type, const String &msg);
  };
};
#endif
