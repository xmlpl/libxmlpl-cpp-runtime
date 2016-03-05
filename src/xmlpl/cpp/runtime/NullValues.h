#ifndef NULLVALUES_H
#define NULLVALUES_H

#include "Sequence.h"
#include "dom/DOM.h"

namespace xmlpl {
  inline NodeRef NodeNull() {return NodeRef();}
  inline DocumentRef DocumentNull() {return DocumentRef();}
  inline ElementRef ElementNull() {return ElementRef();}
  inline AttributeRef AttributeNull() {return AttributeRef();}
  inline TextRef TextNull() {return TextRef();}
  inline CommentRef CommentNull() {return CommentRef();}
  inline PIRef PINull() {return PIRef();}
  inline const QName *QNameNull() {return 0;}
  inline const Prefix *PrefixNull() {return &Prefix::EMPTY;}
  inline String StringNull() {return "";}
  inline int IntegerNull() {return 0;}
  inline double RealNull() {return 0;}
  inline bool BooleanNull() {return false;}

  inline NodeRef Null(NodeRef *) {return NodeNull();}
  inline DocumentRef Null(DocumentRef *) {return DocumentNull();}
  inline ElementRef Null(ElementRef *) {return ElementNull();}
  inline AttributeRef Null(AttributeRef *) {return AttributeNull();}
  inline TextRef Null(TextRef *) {return TextNull();}
  inline CommentRef Null(CommentRef *) {return CommentNull();}
  inline PIRef Null(PIRef *) {return PINull();}
  inline const QName *Null(const QName **) {return QNameNull();}
  inline const Prefix *Null(const Prefix **) {return PrefixNull();}
  inline String Null(String *) {return StringNull();}
  inline int Null(int *) {return IntegerNull();}
  inline double Null(double *) {return RealNull();}
  inline bool Null(bool *) {return BooleanNull();}
};
#endif // NULLVALUES_H
