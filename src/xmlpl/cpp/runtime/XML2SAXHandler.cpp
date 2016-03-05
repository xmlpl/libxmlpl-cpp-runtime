#include "XML2SAXHandler.h"

#include "XMLEntities.h"

#include <libxml/parser.h>

using namespace xmlpl;

#define C_CATCH catch (const BasicException &e) {\
    handler->setError(e);\
  } catch (...) {\
    if (!handler->hasError())\
      handler->setError(\
        BasicException("Caught Unknown Exception in libxml2 callback!"));\
  }

extern "C" {
  void saxStartDocument(XML2SAXHandler *handler) {
    if (handler->hasError()) return;
    try {
      handler->getStream()->startDocument();
    } C_CATCH
  }

  void saxEndDocument(XML2SAXHandler *handler) {
    if (handler->hasError()) return;
    try {
      handler->getStream()->endDocument();
    } C_CATCH;
  }

  void saxStartElementNs(XML2SAXHandler *handler, const xmlChar *localname,
			 const xmlChar *prefix, const xmlChar *URI,
			 int nb_namespaces, const xmlChar **namespaces,
			 int nb_attributes, int nb_defaulted,
			 const xmlChar **attributes) {

    if (handler->hasError()) return;
    try {
      DOMFactory *factory = handler->getFactory();

      handler->getStream()->
	startElement(factory->createQName(factory->
					  createPrefix(prefix, URI, true),
					  localname, true));
      
      for (int i = 0; i < nb_attributes * 5; i+= 5)
	handler->getStream()->
	  attribute(factory->createQName(factory->
					 createPrefix(attributes[i + 1],
						      attributes[i + 2], true),
					 attributes[i + 0], true),
		    String(attributes[i + 3],
			   (int)(attributes[i + 4] - attributes[i + 3])));
    } C_CATCH
  }
  
  void saxEndElementNs(XML2SAXHandler *handler, const xmlChar *localname,
		       const xmlChar *prefix, const xmlChar *URI) {
    if (handler->hasError()) return;
    try {
      handler->getStream()->endElement();
    } C_CATCH
  }
  
  xmlEntityPtr saxGetEntity(XML2SAXHandler *handler, const xmlChar *name) {
    return lookupEntity(name);
  }

  void saxCharacters(XML2SAXHandler *handler, const xmlChar *ch, int len) {
    if (handler->hasError()) return;
    try {
      handler->getStream()->text(String(ch, len));
    } C_CATCH
  }

  void saxComment(XML2SAXHandler *handler, const xmlChar *value) {
    if (handler->hasError()) return;
    try {
      handler->getStream()->comment(String(value, true));
    } C_CATCH
  }

  void saxProcessingInstruction(XML2SAXHandler *handler,
				const xmlChar *target,
				const xmlChar *data) {
    if (handler->hasError()) return;
    try {
      handler->getStream()->pi(String(target, true), String(data, true));
    } C_CATCH
  }

#define BUF_SIZE 512
  void saxWarning(XML2SAXHandler *handler, const char *msg, ...) {
    if (handler->hasError()) return;

    va_list args;
    char buf[BUF_SIZE];
    
    va_start(args, msg);
    vsnprintf(buf, BUF_SIZE, msg, args);
    va_end(args);

    try {
      handler->getStream()->error(XMLStream::WARNING, buf);
    } C_CATCH;
  }
  
  void saxError(XML2SAXHandler *handler, const char *msg, ...) {
    if (handler->hasError()) return;

    va_list args;
    char buf[BUF_SIZE];
    
    va_start(args, msg);
    vsnprintf(buf, BUF_SIZE, msg, args);
    va_end(args);

    try {
      handler->getStream()->error(XMLStream::ERROR, buf);
    } C_CATCH;
  }
  
  void saxFatalError(XML2SAXHandler *handler, const char *msg, ...) {
    if (handler->hasError()) return;

    va_list args;
    char buf[BUF_SIZE];
    
    va_start(args, msg);
    vsnprintf(buf, BUF_SIZE, msg, args);
    va_end(args);
    
    try {
      handler->getStream()->error(XMLStream::FATAL_ERROR, buf);
    } C_CATCH
  }
}

XML2SAXHandler::XML2SAXHandler(DOMFactory *factory) :
  factory(factory), callBackError(false) {

  saxHandler = (xmlSAXHandler *)calloc(1, sizeof(xmlSAXHandler));
  saxHandler->startDocument = (startDocumentSAXFunc)saxStartDocument;
  saxHandler->endDocument = (endDocumentSAXFunc)saxEndDocument;
  saxHandler->startElementNs = (startElementNsSAX2Func)saxStartElementNs;
  saxHandler->endElementNs = (endElementNsSAX2Func)saxEndElementNs;
  saxHandler->characters = (charactersSAXFunc)saxCharacters;
  saxHandler->comment = (commentSAXFunc)saxComment;
  saxHandler->processingInstruction =
    (processingInstructionSAXFunc)saxProcessingInstruction;
  saxHandler->getEntity = (getEntitySAXFunc)saxGetEntity;
  saxHandler->warning = (warningSAXFunc)saxWarning;
  saxHandler->error = (errorSAXFunc)saxError;
  saxHandler->fatalError = (fatalErrorSAXFunc)saxFatalError;
  saxHandler->initialized = XML_SAX2_MAGIC;
}

XML2SAXHandler::~XML2SAXHandler() {
  free(saxHandler);
}

void XML2SAXHandler::setError(const BasicException &e) {
  if (!callBackError) callBackException = e;
  callBackError = true;
}
