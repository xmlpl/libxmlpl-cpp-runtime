#include "DOMBuilder.h"

#include <BasicUtils/BasicException.h>

#include <iostream>
using namespace std;
using namespace xmlpl;

DOMBuilder::DOMBuilder(DOMFactory &factory, XMLSource &source) :
  factory(factory), source(source), streamDepth(0) {

  root = factory.createDocument();

  proxyStack.push(*this, root);
}

void DOMBuilder::startDocument() {}

void DOMBuilder::endDocument() {
  ASSERT_OR_THROW("No document!", !proxyStack.empty());
  ASSERT_OR_THROW("Stream depth > 0!", !streamDepth);
  
  proxyStack.pop();
}

void DOMBuilder::startElement(const QName *name) {
  ASSERT_OR_THROW("No parent!", !proxyStack.empty());

  XMLStream *stream = proxyStack.top()->getStream();
  if (stream) {
    stream->startElement(name);
    streamDepth++;

  } else {
    Element *elem = factory.createElement(name);

    proxyStack.top()->appendChild(elem);
    proxyStack.push(*this, elem);
  }
}

void DOMBuilder::endElement() {
  ASSERT_OR_THROW("No element!", !proxyStack.empty());

  if (streamDepth) {
    XMLStream *stream = proxyStack.top()->getStream();
    ASSERT_OR_THROW("Stream depth > 0 but no stream!", stream);
    stream->endElement();
    streamDepth--;

  } else proxyStack.pop();
}

void DOMBuilder::attribute(const QName *name, const String &text) {
  ASSERT_OR_THROW("No parent element!", !proxyStack.empty());
  
  XMLStream *stream = proxyStack.top()->getStream();
  if (stream) stream->attribute(name, text);
  else proxyStack.top()->appendAttr(factory.createAttribute(name, text));
}

void DOMBuilder::text(const String &text) {
  ASSERT_OR_THROW("No parent!", !proxyStack.empty());

  XMLStream *stream = proxyStack.top()->getStream();
  if (stream) stream->text(text);
  else proxyStack.top()->appendChild(factory.createText(text));
}

void DOMBuilder::comment(const String &text) {
  ASSERT_OR_THROW("No parent!", !proxyStack.empty());

  XMLStream *stream = proxyStack.top()->getStream();
  if (stream) stream->comment(text);
  else proxyStack.top()->appendChild(factory.createComment(text));
}

void DOMBuilder::pi(const String &target, const String &data) {
  ASSERT_OR_THROW("No parent!", !proxyStack.empty());

  XMLStream *stream = proxyStack.top()->getStream();
  if (stream) stream->pi(target, data);
  else proxyStack.top()->appendChild(factory.createPI(target, data));
}

void DOMBuilder::error(const error_t type, const String &msg) {
  // TODO should be routed through a global error handler.
  if (type == XMLStream::WARNING)
    cerr << "WARNING: " << msg << endl;
  else THROW((const char *)msg.get());
}
