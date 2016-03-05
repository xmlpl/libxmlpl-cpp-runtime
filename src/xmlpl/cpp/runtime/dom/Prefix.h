#ifndef PREFIX_H
#define PREFIX_H

#include <xmlpl/cpp/runtime/Memory.h>

#include "String.h"

namespace xmlpl {
  class Prefix : public Memory {
    const String name;
    const String uri;

  public:
    Prefix(const String &name, const String &uri) : name(name), uri(uri) {}

    const String &getName() const {return name;}
    const String &getURI() const {return uri;}

    bool operator==(const Prefix &o) const
		{return name == o.name && uri == o.uri;}

    bool operator<(const Prefix &o) const {      
      if (uri < o.uri) return true;
      if (uri == o.uri) return name < o.name;
      return false;
    }

    inline String toString() const {
      if (!name.empty()) return String::concat(3, name.get(), ":", uri.get());
      return uri;
    }

    static Prefix EMPTY;
    static Prefix ANY;
  };

  struct ltPrefix {
    bool operator()(const Prefix *n1, const Prefix *n2) const
		{return *n1 < *n2;}
  };
};
#endif
