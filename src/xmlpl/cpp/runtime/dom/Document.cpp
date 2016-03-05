#include "Document.h"

#include <BasicUtils/BasicException.h>

using namespace xmlpl;

QName Document::DocumentQName(&Prefix::EMPTY, "*document*");

Node *Document::getNext() const {
  THROW("Document cannot have next!");
}

void Document::setNext(Node *next) {
  THROW("Document cannot have next!");
}

Node *Document::getNextRaw() const {
  THROW("Document cannot have next!");
}

void Document::serialize(XMLStream &stream) {
  stream.startDocument();

  if (getRefCount()) {
    for (Node *child = getFirstChild(); child; child = child->getNext())
      child->serialize(stream);

  } else {
    Node *child = getFirstChildRaw();
    delete this;
    // NOTE: Cannot access object members after this point
    
    while (child) {
      Node *next = child->getNextRaw();
      child->decRef();
      child->serialize(stream);
      child = next;
    }
  }

  stream.endDocument();
}
