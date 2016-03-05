#ifndef NODE_H
#define NODE_H

#include <xmlpl/cpp/runtime/Reference.h>
#include <xmlpl/cpp/runtime/Memory.h>
#include <xmlpl/cpp/runtime/TypeID.h>
#include "XMLStream.h"
#include "QName.h"
#include "String.h"

namespace xmlpl {
  class Proxy;
  class NodeStack;
  class Element;
  class Attribute;

  class Node;
  typedef Reference<Node> NodeRef;

  class Node : public Memory, public TypeID {
    Node *next;

  public:
    Node() : next(0) {}
    virtual ~Node() {}

    virtual const unsigned int getType() const = 0;
    virtual Node *clone() const = 0;

    virtual Node *getNext() const;
    virtual Node *getNextRaw() const {return next;}
    virtual void setNext(Node *next) {this->next = next;}

    virtual const QName *getName() const;
    virtual const String &getTarget() const;
    virtual const String &getText() const;

    virtual Element *getParent() const;
    virtual void setParent(Element *parent);
    virtual Attribute *getFirstAttribute() const;
    virtual void setFirstAttribute(Attribute *attr);
    virtual Attribute *getAttribute(const QName *name) const;
    virtual void setAttribute(Attribute *attr);

    virtual Node *getFirstChild() const;
    virtual Node *getFirstChildRaw() const;
    virtual void setFirstChild(Node *firstChild);

    virtual void setTarget(Node **target);
    virtual void pump() const;

    // Reference counting
    virtual void incRef() {}
    virtual void decRef() {}
    virtual unsigned int getRefCount() {return 1;}
    virtual void release() {}

    virtual void serialize(XMLStream &stream) = 0;

    friend class Proxy;
    friend class NodeStack;
    friend class Element;
  };
};
#endif
