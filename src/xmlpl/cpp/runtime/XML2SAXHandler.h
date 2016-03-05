#ifndef XML2SAXHANDLER_H
#define XML2SAXHANDLER_H

#include <BasicUtils/BasicException.h>
#include "dom/XMLSource.h"
#include "dom/DOMFactory.h"

#include <libxml/xmlstring.h>
typedef struct _xmlSAXHandler xmlSAXHandler;

namespace xmlpl {
  class XML2SAXHandler {
    XMLStream *stream;
    DOMFactory *factory;
    xmlSAXHandler *saxHandler;

    bool callBackError;
    BasicException callBackException;

  public:
    XML2SAXHandler(DOMFactory *factory);
    virtual ~XML2SAXHandler();

    void setStream(XMLStream *stream) {this->stream = stream;}
    XMLStream *getStream() const {return stream;}

    DOMFactory *getFactory() const {return factory;}

    xmlSAXHandler *getSAXHandler() const {return saxHandler;}

    void setError(const BasicException &e);
    const BasicException &getError() const {return callBackException;}
    bool hasError() const {return callBackError;}
    void clearError() {callBackError = false;}
  };

  extern "C" {
    void saxStartDocument(XML2SAXHandler *handler);
    void saxEndDocument(XML2SAXHandler *handler);
    void saxStartElementNs(XML2SAXHandler *handler, const xmlChar *localname,
			   const xmlChar *prefix, const xmlChar *URI,
			   int nb_namespaces, const xmlChar **namespaces,
			   int nb_attributes, int nb_defaulted,
			   const xmlChar **attributes);
    
    void saxEndElementNs(XML2SAXHandler *handler, const xmlChar *localname,
			 const xmlChar *prefix, const xmlChar *URI);
    
    void saxCharacters(XML2SAXHandler *handler, const xmlChar *ch, int len);
    void saxComment(XML2SAXHandler *handler, const xmlChar *value);
    void saxProcessingInstruction(XML2SAXHandler *handler,
				  const xmlChar *target,
				  const xmlChar *data);
    void saxWarning(XML2SAXHandler *handler, const char *msg, ...);
    void saxError(XML2SAXHandler *handler, const char *msg, ...);
    void saxFatalError(XML2SAXHandler *handler, const char *msg, ...);
  }
}
#endif // XML2SAXHANDLER_H
