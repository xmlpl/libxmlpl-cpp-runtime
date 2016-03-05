#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Node.h"
#include "QName.h"
#include "String.h"

namespace xmlpl {
  class Attribute;
  typedef Reference<Attribute, Node> AttributeRef;

  class Attribute: public Node, public BasicObjCounter<Attribute> {
    const QName *name;
    const String text;

  public:
    Attribute(const QName *name, const String &text) : name(name), text(text) {}
    virtual ~Attribute() {}

    virtual const unsigned int getType() const {return ATTRIBUTE_TYPE;}
    Node *clone() const {return new Attribute(name, text);}

    virtual const QName *getName() const {return name;}
    virtual const String &getText() const {return text;}

    virtual void serialize(XMLStream &stream) {stream.attribute(getName(), getText());}
  };
};
#endif
