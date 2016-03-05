#include "xmlpl.h"

#include "dom/DOMFactory.h"

#include "stdarg.h"

namespace xmlpl {

  Element *createElement(const QName *qname, ...) {
    Element *e = DOMFactory::getInstance()->createElement(qname);
    va_list ap;

    Attribute *attr = 0;
    Node *child = 0;

    va_start(ap, qname);
    while (true) {
      Node *node = va_arg(ap, Node *);
      if (!node) break;
      
      if (node->getType() == Node::ATTRIBUTE_TYPE) {
	if (attr) attr->setNext(node);
	else e->setFirstAttribute((Attribute *)node);

	attr = (Attribute *)node;

      } else {
	if (child) child->setNext(node);
	else e->setFirstChild(node);

	node->incRef();
	child = node;
      }
    }
    va_end(ap); 
    
    return e;
  }

  Element *createElementWithChildren(const QName *qname, const NodeSequence children) {
    Element *e = DOMFactory::getInstance()->createElement(qname);

    Node *last = 0;
    for (unsigned int i = 0; i < children.size(); i++) {
      Node *child = children[i]->clone();
      child->incRef();

      if (last) last->setNext(child);
      else e->setFirstChild(child);
      last = child;
    }

    return e;
  }
};
