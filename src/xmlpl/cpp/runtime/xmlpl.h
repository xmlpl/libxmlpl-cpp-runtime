#ifndef XMLPL_H
#define XMLPL_H

#include "Memory.h"
#include "Exception.h"
#include "Sequence.h"
#include "Iterator.h"
#include "TypeClasses.h"
#include "LibraryInfo.h"
#include "dom/DOM.h"
#include "dom/DOMFactory.h"

namespace xmlpl {
  inline const bool nameTest(const QName *qname, const Prefix *prefix, const String name) {
    return (prefix == &Prefix::ANY ||
	    prefix == qname->getPrefix() ||
	    prefix->getURI() == qname->getURI()) &&
      (name == "*" || name == qname->getName());
  }

  Element *createElement(const QName *qname, ...);

  Element *createElementWithChildren(const QName *qname, const NodeSequence children);

  inline Attribute *createAttribute(const QName *qname, const String &value) {
    return DOMFactory::getInstance()->createAttribute(qname, value);
  }

  inline Comment *createComment(const String &text) {
    return DOMFactory::getInstance()->createComment(text);
  }

  inline PI *createPI(const String &target, const String &data) {
    return DOMFactory::getInstance()->createPI(target, data);
  }

  inline Text *createText(const String &value) {
    return DOMFactory::getInstance()->createText(value);
  }

  inline const Prefix *createPrefix(const String &name, const String &uri) {
    return DOMFactory::getInstance()->createPrefix(name, uri);
  }

  inline const QName *createQName(const Prefix *prefix, const String &name) {
    return DOMFactory::getInstance()->createQName(prefix, name);
  }

#define XPL_TCALL(x, y) (x ? Temp##y##Sequence(y##SequenceResult) : Temp##y##Sequence())
};

#include "TargetCast.h"
#include "VoidTarget.h"
#include "NullValues.h"
#include "main.h"
#endif // XMLPL_H
