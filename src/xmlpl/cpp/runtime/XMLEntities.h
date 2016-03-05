#ifndef XMLENTITIES_H
#define XMLENTITIES_H

#include <libxml/entities.h>

namespace xmlpl {
  extern xmlEntityPtr lookupEntity(const xmlChar *name);
};

#endif // XMLENTITIES_H
