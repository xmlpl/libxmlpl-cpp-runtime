#ifndef QNAME_H
#define QNAME_H

#include <xmlpl/cpp/runtime/Memory.h>

#include "Prefix.h"
#include "String.h"

namespace xmlpl {
  class QName : public Memory {
    const Prefix *prefix;
    const String name;

  public:
    QName(const String &name) : prefix(&Prefix::EMPTY), name(name) {}
    QName(const Prefix *prefix, const String &name) :
			prefix(prefix), name(name) {}

    const String &getURI() const {return prefix->getURI();}
    const String &getPrefixName() const {return prefix->getName();}
    const Prefix *getPrefix() const {return prefix;}
    const String &getName() const {return name;}

    bool operator==(const QName &o) const {
      return name == o.name && prefix->getURI() == o.prefix->getURI();
    }

    bool operator<(const QName &o) const {
      if (prefix->getURI() < o.prefix->getURI()) return true;
      if (prefix->getURI() == o.prefix->getURI()) return name < o.name;
      return false;
    }

    inline String toString() const {
      if (!prefix->getName().empty())
				return String::concat(3, prefix->getName().get(), ":", name.get());
      return name;
    }
  };

  struct ltQName {
    bool operator()(const QName *n1, const QName *n2) const {return *n1 < *n2;}
  };
};
#endif
