#ifndef TEXT_H
#define TEXT_H

#include "Node.h"

namespace xmlpl {
  class Text;
  typedef Reference<Text, Node> TextRef;

  class Text: public Node {
    const String text;

  public:
    Text(const String &text) : text(text) {}
    virtual ~Text() {}

    virtual const unsigned int getType() const {return TEXT_TYPE;}
    Node *clone() const {return new Text(text);}

    virtual const String &getText() const {return text;}

    virtual void serialize(XMLStream &stream) {stream.text(getText());}
  };
};
#endif
