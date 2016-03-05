#ifndef PROXY_H
#define PROXY_H

#include "Node.h"

namespace xmlpl {
  class DOMBuilder;
  class Element;
  class Attribute;
  class XMLStream;

  class Proxy : public Node {
    DOMBuilder &builder;

    Element *elem;
    Attribute **attr;
    Node **child;
    XMLStream *stream;

  public:
    Proxy(DOMBuilder &builder);
    virtual ~Proxy() {}

    // Node methods
    virtual const unsigned int getType() const {return PROXY_TYPE;}
    Node *clone() const {THROW("Cannot clone proxy node!");}

    virtual void setParent(Element *parent) {elem = parent;}
    virtual void release();
    virtual void serialize(XMLStream &stream);
    virtual void setTarget(Node **target) {child = target;}
    virtual void pump() const;

    void appendAttr(Attribute *attr);
    void appendChild(Node *child);
    void attach(Element *elem);

    XMLStream *getStream() {return stream;}
    void setStream(XMLStream *stream) {this->stream = stream;}
  };
};
#endif
