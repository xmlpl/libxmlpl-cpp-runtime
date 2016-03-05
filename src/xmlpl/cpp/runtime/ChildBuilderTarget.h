#ifndef CHILDBUILDERTARGET_H
#define CHILDBUILDERTARGET_H

#include "BuilderTarget.h"
#include "Sequence.h"

namespace xmlpl {
  class ChildBuilderTarget : public BuilderTarget<NodeRef> {
  public:
    ChildBuilderTarget(NodeStack *nodeStack) :
      BuilderTarget<NodeRef>(nodeStack) {}
    virtual ~ChildBuilderTarget() {}

    // BuilderTarget methods
    virtual void append(NodeRef n) {
      if (n->getType() == Node::ATTRIBUTE_TYPE)
        nodeStack->appendAttr((Attribute *)n->clone());
      else
        nodeStack->appendChild(n->clone());
    }
    virtual void append(const Sequence<NodeRef> &s) {
      for (unsigned int i = 0; i < s.size(); i++)
	append(s[i]);
    }
    virtual void append(Iterator<NodeRef> &i) {
      while (i.hasNext()) append(i.next());
    }
  };
};
#endif // CHILDBUILDERTARGET_H
