#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Element.h"

namespace xmlpl {
  class Document;
  typedef Reference<Document, Node> DocumentRef;

  class Document : public Element {
    static QName DocumentQName;

  public:
    Document() : Element(&DocumentQName) {}
    virtual ~Document() {}

    virtual const unsigned int getType() const {return DOCUMENT_TYPE;}
    virtual Node *getNext() const;
    virtual Node *getNextRaw() const;
    virtual void setNext(Node *next);

    virtual void serialize(XMLStream &stream);
  };
};
#endif
