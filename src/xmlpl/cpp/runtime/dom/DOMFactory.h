#ifndef DOMFACTORY_H
#define DOMFACTORY_H

#include <xmlpl/cpp/runtime/Memory.h>

#include "DOM.h"

#include <set>

namespace xmlpl {
  class DOMFactory : public virtual Memory {
    typedef std::set<const Prefix *, ltPrefix,
                     xmlpl_alloc<const Prefix *> > prefixMap_t;
    prefixMap_t prefixMap;

    typedef std::set<const QName *, ltQName,
                     xmlpl_alloc<const QName *> > qnameMap_t;
    qnameMap_t qnameMap;

    static DOMFactory *instance;

  public:
    static DOMFactory *getInstance();

    DOMFactory();

    Document *createDocument();
    Element *createElement(const QName *name);
    Attribute *createAttribute(const QName *name, const String &value);
    PI *createPI(const String &name, const String &data);
    Comment *createComment(const String &text);
    Text *createText(const String &value);

    const Prefix *createPrefix(const String &name,
                               const String &uri, bool copy = false);
    const QName *createQName(const Prefix *prefix, const String &name,
                             bool copy = false);
    inline const QName *createQName(const String &name, bool copy = false) {
      return createQName(&Prefix::EMPTY, name, copy);
    }
  };
};
#endif
