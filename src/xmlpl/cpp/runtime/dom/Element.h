#ifndef ELEMENT_H
#define ELEMENT_H

#include "Node.h"

namespace xmlpl {
  class Proxy;
  class NodeStack;

  class Element;
  typedef Reference<Element, Node> ElementRef;

  class Element: public Node, public BasicObjCounter<Element> {
    const QName *name;
    Element *parent;
    Attribute *firstAttribute;
    Node *firstChild;

  protected:
    unsigned int refCount;

  public:
    Element(const QName *name) :
      name(name), parent(0),
      firstAttribute(0), firstChild(0), refCount(0) {}
    virtual ~Element() {}

    virtual const unsigned int getType() const {return ELEMENT_TYPE;}
    virtual Node *clone() const;

    virtual const QName *getName() const {return name;}

    virtual Element *getParent() const {return parent;}
    virtual void setParent(Element *parent) {this->parent = parent;}

    virtual Attribute *getFirstAttribute() const {return firstAttribute;}
    virtual void setFirstAttribute(Attribute *firstAttribute) {
      this->firstAttribute = firstAttribute;
    }
    virtual Attribute *getAttribute(const QName *name) const;
    virtual void setAttribute(Attribute *attr);

    virtual Node *getFirstChildRaw() const {return firstChild;}
    virtual void setFirstChild(Node *firstChild)
    {this->firstChild = firstChild;}

    virtual void incRef() {refCount++;}
    virtual void decRef() {if (refCount) refCount--;}
    virtual unsigned int getRefCount() {return refCount;}
    virtual void release();

    virtual void serialize(XMLStream &stream);

    friend class Proxy;
    friend class NodeStack;
  };
};
#endif
