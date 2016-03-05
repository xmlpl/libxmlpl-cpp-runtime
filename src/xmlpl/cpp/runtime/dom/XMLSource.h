#ifndef XMLSOURCE_H
#define XMLSOURCE_H

#include "XMLStream.h"

namespace xmlpl {
  class XMLSource {
  public:
		virtual ~XMLSource() {}

    virtual bool pump(XMLStream *stream) = 0;
  };
};
#endif
