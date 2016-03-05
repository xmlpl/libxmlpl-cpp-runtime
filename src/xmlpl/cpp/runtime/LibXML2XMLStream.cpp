#include "LibXML2XMLStream.h"

#include <BasicUtils/BasicException.h>

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlerror.h>

#include <sstream>

using namespace std;
using namespace xmlpl;

extern "C" {
  int iowrite(void *context, const char *buffer, int len) {
    ((ostream *)context)->write(buffer, len);
    return len;
  }
  
  int ioclose(void *context) {
    ((ostream *)context)->flush();
    return 0;
  }
}

LibXML2XMLStream::LibXML2XMLStream(ostream &out, const std::string encoding,
                                   bool disableHeader) :
  out(out), encoding(encoding), disableHeader(disableHeader), writer(0),
  attributeOk(false), depth(0), started(false) {

  xmlOutputBufferPtr outBuf =
    xmlOutputBufferCreateIO(iowrite, ioclose, &out, 0);
  ASSERT_OR_THROW("Creating libxml output buffer", outBuf);
  writer = xmlNewTextWriter(outBuf);
  ASSERT_OR_THROW("Creating libxml text writer", writer);
}

LibXML2XMLStream::~LibXML2XMLStream() {
  if (writer) xmlFreeTextWriter(writer);
}

void LibXML2XMLStream::startDocument() {
  if (!disableHeader)
    if (xmlTextWriterStartDocument(writer, 0, encoding.c_str(), 0) < 0)
      THROW("Error starting libxml document");

  started = true;
}

void LibXML2XMLStream::endDocument() {
  if (!disableHeader)
    if (xmlTextWriterEndDocument(writer) < 0)
      THROW("Error ending libxml document");

  xmlTextWriterFlush(writer);

  started = false;
}

void LibXML2XMLStream::startElement(const QName *name) {
  if (!started) startDocument();

  depth++;

  if (!name->getPrefixName().empty()) {

    const xmlChar *uri = 0;
    if (!isPrefixActive(name->getPrefix())) {
      prefixStack.push_back(prefixPair_t(name->getPrefix(), depth));
      uri = name->getURI();
    }

    if (xmlTextWriterStartElementNS(writer, name->getPrefixName(),
				    name->getName(), uri) < 0)
      THROW("Error starting libxml ns element");

  } else if (xmlTextWriterStartElement(writer, name->getName()) < 0)
    THROW("Error starting libxml ns element");

  attributeOk = true;
}

void LibXML2XMLStream::endElement() {
  if (xmlTextWriterEndElement(writer) < 0)
    THROW("Error ending libxml element");
  xmlTextWriterFlush(writer);

  while (prefixStack.size() && prefixStack.back().second == depth)
    prefixStack.pop_back();

  depth--;
  attributeOk = false;
}

void LibXML2XMLStream::attribute(const QName *name, const String &text) {
  if (attributeOk) {

    // TODO ignore repeated attributes
    if (!name->getPrefixName().empty()) {

      const xmlChar *uri = 0;
      if (!isPrefixActive(name->getPrefix())) {
	prefixStack.push_back(prefixPair_t(name->getPrefix(), depth));
	uri = name->getURI();
      }
      
      if (xmlTextWriterWriteAttributeNS(writer, name->getPrefixName(),
					name->getName(),
					uri, text) < 0)
	THROW(string("Error writing libxml ns attribute ") +
	      name->toString().cpp_str() +
	      "=\"" + text.cpp_str() + "\"");    

    } else if (xmlTextWriterWriteAttribute(writer, name->getName(), text) < 0)
      THROW(string("Error writing libxml ns attribute ") +
	    name->toString().cpp_str() +
	    "=\"" + text.cpp_str() + "\"");    


  } else if (xmlTextWriterWriteString(writer, text) < 0)
      THROW("Error writing libxml attribute as text");
}

void LibXML2XMLStream::text(const String &text) {
  attributeOk = false;

  if (text.empty()) return;

  if (xmlTextWriterWriteString(writer, text) < 0)
    THROW("Error writing libxml text");
}

void LibXML2XMLStream::comment(const String &text) {
  if (!started) startDocument();

  attributeOk = false;

  if (xmlTextWriterWriteComment(writer, text) < 0)
    THROW("Error writing libxml comment");
}

void LibXML2XMLStream::pi(const String &target, const String &data) {
  if (!started) startDocument();

  attributeOk = false;

  if (xmlTextWriterWritePI(writer, target, data) < 0)
    THROW("Error writing libxml processing instruction");
}

void LibXML2XMLStream::flush() {
  xmlTextWriterFlush(writer);
  out.flush();
}

void LibXML2XMLStream::close() {
  flush();
  if (closeFunctor) (*closeFunctor)();
}

bool LibXML2XMLStream::isPrefixActive(const Prefix *prefix) {
  for (unsigned int i = prefixStack.size(); i; i--)
    if (prefixStack[i - 1].first && *prefix == *prefixStack[i - 1].first)
      return true;

  return false;
}
