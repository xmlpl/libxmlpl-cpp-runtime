#ifndef STREAMTARGET_H
#define STREAMTARGET_H

#include "Target.h"
#include "dom/Node.h"
#include "dom/String.h"

namespace xmlpl {
  class StreamTarget : virtual public Target<NodeRef>,
		       virtual public Target<String> {
  public:
		virtual ~StreamTarget() {}

    // Methods
    virtual void append(const Sequence<NodeRef> &s);
    virtual void append(Iterator <NodeRef> &i)
    {while (i.hasNext()) append(i.next());}
    virtual void append(NodeRef n) {if (n != 0) n->serialize(*this);}

    virtual void append(const Sequence<String> &s);
    virtual void append(Iterator<String> &i)
    {while (i.hasNext()) append(i.next());}
    virtual void append(String s) {text(s);}

    virtual Target<NodeRef> &getChildTarget() {return *this;}
  };
};
#endif // STREAMTARGET_H
