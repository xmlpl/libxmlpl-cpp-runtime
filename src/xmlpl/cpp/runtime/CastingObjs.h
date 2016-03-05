#ifndef CASTINGOBJS_H
#define CASTINGOBJS_H

#include "xmlpl.h"
#include "TypeClasses.h"
#include "dom/DOM.h"

namespace xmlpl {
  struct ToNode {
    inline static Node_t cast(Document_t n) {return n;}
    inline static Node_t cast(Element_t n) {return n;}
    inline static Node_t cast(Attribute_t n) {return n;}
    inline static Node_t cast(Text_t n) {return n;}
    inline static Node_t cast(Comment_t n) {return n;}
    inline static Node_t cast(PI_t n) {return n;}

    inline static Node_t cast(Prefix_t pre);
    inline static Node_t cast(QName_t qname);

    inline static Node_t cast(String_t s);
    inline static Node_t cast(Integer_t x);
    inline static Node_t cast(Real_t x);
    inline static Node_t cast(Boolean_t x);
  };
  
  struct ToText {
    inline static Text_t cast(String_t s) {return createText(s);}

    inline static Text_t cast(Prefix_t pre);
    inline static Text_t cast(QName_t qname);

    inline static Text_t cast(Integer_t x);
    inline static Text_t cast(Real_t x);
    inline static Text_t cast(Boolean_t x);
  };
  
  struct ToString {
    inline static String_t cast(Attribute_t n)
    {return n == 0 ? "" : n->getText();}
    inline static String_t cast(Text_t n)
    {return  n == 0 ? "" : n->getText();}
    inline static String_t cast(Comment_t n)
    {return  n == 0 ? "" : n->getText();}
    inline static String_t cast(PI_t n)
    {return  n == 0 ? "" : n->getText();}

    inline static String_t cast(Prefix_t pre)
    {return pre ? pre->toString() : "";}
    inline static String_t cast(QName_t qname)
    {return qname ? qname->toString() : "";}

    inline static String_t cast(Integer_t x) {return String(x);}
    inline static String_t cast(Real_t x) {return String(x);}
    inline static String_t cast(Boolean_t x) {return x ? "true" : "false";}
  };
  
  struct ToInteger {
    inline static Integer_t cast(Boolean_t x) {return x;}
  };
  
  struct ToReal {
    inline static Real_t cast(Integer_t x) {return x;}
    inline static Real_t cast(Boolean_t x) {return x;}
  };
  
  struct ToBoolean {
    inline static Boolean_t cast(Node_t n) {return n != 0;}
    inline static Boolean_t cast(Document_t n) {return n != 0;}
    inline static Boolean_t cast(Element_t n) {return n != 0;}
    inline static Boolean_t cast(Attribute_t n) {return n != 0;}
    inline static Boolean_t cast(Text_t n) {return n != 0;}
    inline static Boolean_t cast(Comment_t n) {return n != 0;}
    inline static Boolean_t cast(PI_t n) {return n != 0;}

    inline static Boolean_t cast(Prefix_t pre)
    {return pre && pre != &Prefix::EMPTY;}
    inline static Boolean_t cast(QName_t qname) {return qname;}

    inline static Boolean_t cast(String_t s) {return s.empty();}
    inline static Boolean_t cast(Integer_t x) {return x;}
    inline static Boolean_t cast(Real_t x) {return x;}
  };

  struct ToQName {
    inline static QName_t cast(String_t s)
    {return createQName(&Prefix::EMPTY, s);}
  };

  template <class From, class To, class Cast>
  struct ToSequence {
    inline static Sequence<To> cast(const Sequence<From> &s) {
      Sequence<To> result;
      result.reserve(s.size());

      for (unsigned int i = 0; i < s.size(); i++)
	result.append(Cast::cast(s[i]));

      return result;
    }
  };

  inline Node_t ToNode::cast(Prefix_t pre)
  {return createText(ToString::cast(pre));}
  inline Node_t ToNode::cast(QName_t qname)
  {return createText(ToString::cast(qname));}
  inline Node_t ToNode::cast(String_t s)
  {return createText(s);}
  inline Node_t ToNode::cast(Integer_t x)
  {return createText(ToString::cast(x));}
  inline Node_t ToNode::cast(Real_t x)
  {return createText(ToString::cast(x));}
  inline Node_t ToNode::cast(Boolean_t x)
  {return createText(ToString::cast(x));}

  inline Text_t ToText::cast(Prefix_t pre)
  {return createText(ToString::cast(pre));}
  inline Text_t ToText::cast(QName_t qname)
  {return createText(ToString::cast(qname));}
  inline Text_t ToText::cast(Integer_t x)
  {return createText(ToString::cast(x));}
  inline Text_t ToText::cast(Real_t x)
  {return createText(ToString::cast(x));}
  inline Text_t ToText::cast(Boolean_t x)
  {return createText(ToString::cast(x));}
};
#endif // CASTINGOBJS_H
