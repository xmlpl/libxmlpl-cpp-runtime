#include "Node.h"
#include "DOM.h"

#include <BasicUtils/BasicException.h>

using namespace std;
using namespace xmlpl;

Node *Node::getNext() const {
  while (next && next->getType() == PROXY_TYPE)
    next->pump();

  return next;
}

const QName *Node::getName() const {
  THROW(string("Function not supported by type!"));
}

const String &Node::getTarget() const {
  THROW(string("Function not supported by type!"));
}

const String &Node::getText() const {
  THROW(string("Function not supported by type!"));
}

Element *Node::getParent() const {
  THROW(string("Function not supported by type!"));
}

void Node::setParent(Element *parent) {
  THROW(string("Function not supported by type!"));
}

Attribute *Node::getFirstAttribute() const {
  THROW(string("Function not supported by type!"));
}

void Node::setFirstAttribute(Attribute *attr) {
  THROW(string("Function not supported by type!"));
}

Attribute *Node::getAttribute(const QName *name) const {
  THROW(string("Function not supported by type!"));
}

void Node::setAttribute(Attribute *attr) {
  THROW(string("Function not supported by type!"));
}

Node *Node::getFirstChild() const {
  while (getFirstChildRaw() && getFirstChildRaw()->getType() == PROXY_TYPE)
    getFirstChildRaw()->pump();

  return getFirstChildRaw();
}

Node *Node::getFirstChildRaw() const {
  THROW(string("Function not supported by type!"));
}

void  Node::setFirstChild(Node *firstChild) {
  THROW(string("Function not supported by type!"));
}

void Node::setTarget(Node **target) {
  THROW(string("Function not supported by type!"));
}

void Node::pump() const {
  THROW(string("Function not supported by type!"));
}
