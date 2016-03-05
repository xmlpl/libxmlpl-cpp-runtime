#ifndef NODESTACK_H
#define NODESTACK_H

#include "Node.h"
#include "Element.h"

namespace xmlpl {
  class NodeStack {
    NodeStack *parent;
    Element *elem;
    Node **child;
    Attribute **attr;

  public:
    NodeStack(NodeStack *parent, Element *elem) : parent(parent) {
      this->elem = elem;
      child = &elem->firstChild;
      attr = &elem->firstAttribute;
    }
    NodeStack(Element *elem) : parent(0) {
      child = &elem->firstChild;
      attr = &elem->firstAttribute;
    }

    void appendChild(Node *node) {
      ASSERT_OR_THROW("Cannot append null child!", node); 
      ASSERT_OR_THROW("Cannot append attribute as child!",
		      node->getType() != Node::ATTRIBUTE_TYPE); 

      node->incRef();
      *child = node;
      child = &node->next;
      if (parent && node->getType() == Node::ELEMENT_TYPE)
        node->setParent(parent->elem);
    }

    void appendAttr(Attribute *a) {
      ASSERT_OR_THROW("Cannot append null attribute!", a); 

      *attr = a;
      attr = (Attribute **)&a->next;
    }

    NodeStack *push(Element *elem) {
      return new NodeStack(this, elem);
    }

    NodeStack *pop() {return parent;}
  };
};
#endif // NODESTACK_H
