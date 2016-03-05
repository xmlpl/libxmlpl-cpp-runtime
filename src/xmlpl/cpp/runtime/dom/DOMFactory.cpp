#include "DOMFactory.h"

#include <string.h>

using namespace xmlpl;

DOMFactory *DOMFactory::instance = 0;

DOMFactory::DOMFactory() {
  prefixMap.insert(&Prefix::EMPTY);
}

DOMFactory *DOMFactory::getInstance() {
	if (!instance) instance = new DOMFactory();

	return instance;
}


Document *DOMFactory::createDocument() {
  return new Document();
}

Element *DOMFactory::createElement(const QName *name) {
  return new Element(name);
}

Attribute *DOMFactory::createAttribute(const QName *name, const String &value) {
  return new Attribute(name, value);
}

PI *DOMFactory::createPI(const String &name, const String &data) {
  return new PI(name, data);
}

Comment *DOMFactory::createComment(const String &text) {
  return new Comment(text);
}

Text *DOMFactory::createText(const String &value) {
  return new Text(value);
}

const Prefix *DOMFactory::createPrefix(const String &name,
                                       const String &uri, bool copy) {
  Prefix p(name, uri);

  prefixMap_t::iterator it = prefixMap.find(&p);
  if (it != prefixMap.end()) return *it;

  Prefix *prefix = new Prefix(String(name, copy), String(uri, copy));
  prefixMap.insert(prefix);

  return prefix;
}

const QName *DOMFactory::createQName(const Prefix *prefix,
                                     const String &name, bool copy) {
  QName q(prefix, name);

  qnameMap_t::iterator it = qnameMap.find(&q);
  if (it != qnameMap.end()) return *it;

  QName *qname = new QName(prefix, String(name, copy));
  qnameMap.insert(qname);

  return qname;
}
