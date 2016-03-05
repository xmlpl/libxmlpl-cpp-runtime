#include "Proxy.h"
#include "DOM.h"
#include "DOMBuilder.h"

#include <BasicUtils/BasicException.h>

using namespace xmlpl;

Proxy::Proxy(DOMBuilder &builder) :
  builder(builder), attr(0), child(0), stream(0) {
}

void Proxy::appendAttr(Attribute *attr) {
  (*this->attr) = attr;
  this->attr = (Attribute **)&attr->next;
}

void Proxy::appendChild(Node *child) {
  child->incRef();

  (*this->child) = child;
  this->child = &child->next;
  child->next = this;

  if (elem && child->getType() == Node::ELEMENT_TYPE)
    child->setParent(elem);
}

void Proxy::attach(Element *elem) {
  this->elem = elem;
  attr = &elem->firstAttribute;
  child = &elem->firstChild;

  (*child) = this;
}

void Proxy::release() {
  if (child) (*child) = 0;

  elem = 0;
  attr = 0;
  child = 0;
  stream = 0;
}

void Proxy::serialize(XMLStream &stream) {
  attr = 0;
  child = 0;

  setStream(&stream);
  while (getStream()) pump();
}


void Proxy::pump() const {
  builder.pump();
}
