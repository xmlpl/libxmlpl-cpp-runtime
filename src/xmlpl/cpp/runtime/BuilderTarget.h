#ifndef BUILDERTARGET_H
#define BUILDERTARGET_H

#include "Target.h"
#include "Sequence.h"
#include "dom/DOM.h"
#include "dom/NodeStack.h"
#include "dom/DOMFactory.h"

#include <BasicUtils/BasicException.h>

namespace xmlpl {
  template<class T>
  class BuilderTarget : public Target<T> {
  protected:
    NodeStack *nodeStack;

  public:
    BuilderTarget(NodeStack *nodeStack) : nodeStack(nodeStack) {}
    BuilderTarget() : nodeStack(0) {}
    virtual ~BuilderTarget() {}


    // Target methods (Inherited classes should overide one or none of these.)
    virtual void append(NodeRef n)
    {THROW("Append type not allowed by target!");}
    virtual void append(DocumentRef n) {append(NodeRef(n));}
    virtual void append(ElementRef n) {append(NodeRef(n));}
    virtual void append(AttributeRef n) {append(NodeRef(n));}
    virtual void append(TextRef n) {append(NodeRef(n));}
    virtual void append(CommentRef n) {append(NodeRef(n));}
    virtual void append(PIRef n) {append(NodeRef(n));}

    virtual Target<NodeRef> &getChildTarget();

    // XMLStream methods
    virtual void startDocument() {
      Document *document = DOMFactory::getInstance()->createDocument();
      if (!nodeStack) append(DocumentRef(document));
      else nodeStack->appendChild(document);
      push(document);
    }

    virtual void endDocument() {pop();}

    virtual void startElement(const QName *name) {
      Element *element = DOMFactory::getInstance()->createElement(name);
      if (!nodeStack) append(ElementRef(element));
      else nodeStack->appendChild(element);
      push(element);
    }

    virtual void endElement() {pop();}

    virtual void attribute(const QName *name, const String &text) {
      // TODO should not append attributes after children
      Attribute *attr = DOMFactory::getInstance()->createAttribute(name, text);
      if (!nodeStack) append(AttributeRef(attr));
      else nodeStack->appendAttr(attr);
    }

    virtual void text(const String &text) {
      Text *t = DOMFactory::getInstance()->createText(text);
      if (!nodeStack) append(TextRef(t));
      else nodeStack->appendChild(t);
    }

    virtual void comment(const String &text) {
      Comment *comment = DOMFactory::getInstance()->createComment(text);
      if (!nodeStack) append(CommentRef(comment));
      else nodeStack->appendChild(comment);
    }

    virtual void pi(const String &target, const String &data) {
      PI *pi = DOMFactory::getInstance()->createPI(target, data);
      if (!nodeStack) append(PIRef(pi));
      else nodeStack->appendChild(pi);
    }

    virtual void error(const typename XMLStream::error_t type,
		       const String &msg) {
      // TODO figure out what to do here
      THROW("Not yet implemented!");
    }

  protected:
    inline void push(Element *elem) {
      if (!nodeStack) nodeStack = new NodeStack(elem);
      else nodeStack = nodeStack->push(elem);
    }

    inline void pop() {
      if (nodeStack) nodeStack = nodeStack->pop();
    }
  };
};
#endif // BUILDERTARGET_H
