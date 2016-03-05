#ifndef PI_H
#define PI_H

#include "Node.h"

namespace xmlpl {
  class PI;
  typedef Reference<PI, Node> PIRef;

  class PI: public Node {
    const String target;
    const String text;

  public:
    PI(const String &target, const String &text) : target(target), text(text) {}
    virtual ~PI() {}

    virtual const unsigned int getType() const {return PI_TYPE;}
    Node *clone() const {return new PI(target, text);}

    virtual const String &getTarget() const {return target;}
    virtual const String &getText() const {return text;}

    virtual void serialize(XMLStream &stream) {stream.pi(getTarget(), getText());}
  };
};
#endif
