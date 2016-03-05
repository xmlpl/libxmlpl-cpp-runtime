#ifndef LIBXML2XMLSOURCE_H
#define LIBXML2XMLSOURCE_H

#include "dom/XMLSource.h"
#include "dom/DOMFactory.h"
#include "XML2SAXHandler.h"
#include "DataSource.h"
#include "Memory.h"

#include <iostream>

typedef struct _xmlParserCtxt xmlParserCtxt;
typedef struct _xmlSAXHandler xmlSAXHandler;

namespace xmlpl {
  class LibXML2XMLSource : public XMLSource {
    DataSource *in;

    DOMFactory *factory;
    xmlParserCtxt *parser;
    XML2SAXHandler saxHandler;

  public:
    LibXML2XMLSource(DataSource *in, DOMFactory *factory);
    virtual ~LibXML2XMLSource();

    virtual bool pump(XMLStream *stream);

    DOMFactory *getFactory() {return factory;}
    xmlParserCtxt *getParser() {return parser;}
  };
};
#endif
