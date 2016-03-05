#ifndef TYPECLASSES_H
#define TYPECLASSES_H

#include "Sequence.h"
#include "Iterator.h"

namespace xmlpl {
#define TYPDEF_CLASS(x, y) \
  typedef x y##_t;\
  typedef Sequence<y##_t> y##Sequence;\
  typedef TemporarySequence<y##_t> Temp##y##Sequence;\
  typedef Target<y##_t> y##Target;\
  typedef Iterator<y##_t> y##Iterator;\
  typedef Target<y##_t> * y##OStream;

  TYPDEF_CLASS(NodeRef,        Node);
  TYPDEF_CLASS(DocumentRef,    Document);
  TYPDEF_CLASS(ElementRef,     Element);
  TYPDEF_CLASS(AttributeRef,   Attribute);
  TYPDEF_CLASS(TextRef,        Text);
  TYPDEF_CLASS(CommentRef,     Comment);
  TYPDEF_CLASS(PIRef,          PI);
  TYPDEF_CLASS(const QName *,  QName);
  TYPDEF_CLASS(const Prefix *, Prefix);
  TYPDEF_CLASS(String,         String);
  TYPDEF_CLASS(int,            Integer);
  TYPDEF_CLASS(double,         Real);
  TYPDEF_CLASS(bool,           Boolean);

  typedef void Void_t;
};
#endif // TYPECLASSES_H
