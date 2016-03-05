#ifndef TARGETCAST_H
#define TARGETCAST_H

#include "Target.h"
#include "CastingObjs.h"

namespace xmlpl {
  template <class From, class To, class Cast>
  class TargetCast : public Target<From> {
    Target<To> &parent;

  public:
    TargetCast(Target<To> &parent) : parent(parent) {}

    // Methods
    virtual void append(const Sequence<From> &s) {
      for (unsigned int i = 0 ; i < s.size(); i++)
        parent.append(Cast::cast(s[i]));
    }
    virtual void append(Iterator<From> &i) {
      while (i.hasNext()) parent.append(Cast::cast(i.next()));
    }
    virtual void append(From t) {parent.append(Cast::cast(t));}

    virtual Target<NodeRef> &getChildTarget() {return parent.getChildTarget();}
    
    // XMLStream functions
    virtual void startDocument() {parent.startDocument();}
    virtual void endDocument() {parent.endDocument();}
    
    virtual void startElement(const QName *name) {parent.startElement(name);}
    virtual void endElement() {parent.endElement();}
    virtual void attribute(const QName *name, const String &text)
    {parent.attribute(name, text);}
    
    virtual void text(const String &text) {parent.text(text);}
    virtual void comment(const String &text) {parent.comment(text);}
    virtual void pi(const String &target, const String &data) {parent.pi(target, data);}

    virtual void flush() {parent.flush();}
    virtual void error(const typename XMLStream::error_t type, const String &msg)
    {parent.error(type, msg);}    
  };
};
#endif // TARGETCAST_H
