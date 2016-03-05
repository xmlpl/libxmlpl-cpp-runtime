#include "Element.h"
#include "Attribute.h"

#include <BasicUtils/BasicException.h>

using namespace xmlpl;

Node *Element::clone() const {
  Element *newElem = new Element(name);

  // Clone Attributes
  Node *attr = getFirstAttribute();
	union {
		Attribute **a;
		Node **n;
	} newAttr;

	newAttr.a = &newElem->firstAttribute;

  while (attr) {
    *newAttr.n = attr->clone();
    newAttr.n = &(*newAttr.n)->next;

    attr = attr->getNext();
  }

  // Clone Children
  Node *child = getFirstChild();
  Node **newChild = &newElem->firstChild;

  while (child) {
    *newChild = child->clone();
    if ((*newChild)->getType() == ELEMENT_TYPE)
      (*newChild)->setParent(newElem);
    (*newChild)->incRef();
    newChild = &(*newChild)->next;

    child = child->getNext();
  }

  return newElem;
}

Attribute *Element::getAttribute(const QName *name) const {
  Attribute *attr = getFirstAttribute();

  while (attr) {
    if (*attr->getName() == *name) return attr;
    attr = (Attribute *)attr->getNext();
  }

  return 0;
}

void Element::setAttribute(Attribute *attr) {
  Attribute *a = getFirstAttribute();
  Attribute *last = 0;

  while (a) {
    if (*a->getName() == *attr->getName()) {
      attr->setNext(a->getNext());

      if (last) last->setNext(attr);
      else setFirstAttribute(attr);

      return;
    }
    
    last = a;
    a = (Attribute *)a->getNext();
  }

  if (last) last->setNext(attr);
  else setFirstAttribute(attr);
}

void Element::release() {
  // This allows attributes to be garbage collected
  // even when one of them is referenced
  // *** May not be a good trade off of time for space. ***
  if (!getRefCount()) {
    Node *attr = getFirstAttribute();
    setFirstAttribute(0);

    while (attr) {
      Node *next = attr->getNextRaw();
      attr->setNext(0);
      attr = next;
    }

    Node *child = getFirstChildRaw();
    firstChild = 0;
    Node *next;

    while (child) {
      next = child->getNextRaw();
      if (child->getType() == ELEMENT_TYPE || child->getType() == PROXY_TYPE)
        child->setParent(0);
      child->setNext(0);
      child->decRef();
      child = next;
    }

    delete this;
  }
}

void Element::serialize(XMLStream &stream) {
  stream.startElement(getName());

  for (Node *attr = getFirstAttribute(); attr; attr = attr->getNextRaw())
    attr->serialize(stream);

  if (getRefCount()) {
    for (Node *child = getFirstChild(); child; child = child->getNext())
      child->serialize(stream);

  } else {
    Node *child = getFirstChildRaw();
    delete this;
    // NOTE: Cannot access object members after this point

    while (child) {
      Node *next = child->getNextRaw();
      if (child->getType() == ELEMENT_TYPE || child->getType() == PROXY_TYPE)
	child->setParent(0);

      child->decRef();
      child->serialize(stream);
      child = next;
    }
  }

  stream.endElement();
}
