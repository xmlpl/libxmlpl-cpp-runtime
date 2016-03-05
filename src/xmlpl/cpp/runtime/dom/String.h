#ifndef STRING_H
#define STRING_H

#include <libxml/xmlstring.h>
#include <xmlpl/cpp/runtime/Memory.h>

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

namespace xmlpl {
  class String : public Memory, public BasicObjCounter<String> {
    const xmlChar *str;

  public:
    String() : str(0) {}

    String(const String &s, const bool copy = false) : str(s.str)
    {if (copy) this->str = xmlStrdup(str);}

    String(const std::string &s, const bool copy = false) :
			str((const xmlChar *)s.c_str())
    {if (copy) this->str = xmlCharStrdup(s.c_str());}

    String(const xmlChar *str, const bool copy = false) : str(str)
    {if (copy) this->str = xmlStrdup(str);}

    String(const char *str, const bool copy = false) :
			str((const xmlChar *)str) 
    {if (copy) this->str = xmlCharStrdup(str);}

    String(const xmlChar *str, const int len) {
      this->str = xmlStrndup(str, len);
      ((char *)this->str)[len] = '\0';
    }

    String(const char *str, const int len) {
      this->str = xmlCharStrndup(str, len);
      ((char *)this->str)[len] = '\0';
    }

    String(const int x) {
      str = (const xmlChar *)XMLPL_MALLOC(12);
      sprintf((char *)str, "%i", x);
    }

    String(const unsigned int x) {
      str = (const xmlChar *)XMLPL_MALLOC(12);
      sprintf((char *)str, "%i", x);
    }

    String(const double x) {
      str = (const xmlChar *)XMLPL_MALLOC(16);
      sprintf((char *)str, "%g", x);
    }

    static String concat(const unsigned int count, ...);
    int length() const;
    bool empty() const {return !str || !*str;}

    String operator+(const String &s) const;
    String operator+=(const String &s) {
      return *this = *this + s;
    }

    bool operator==(const String &o) const {
      return xmlStrcmp(str, o.str) == 0;
    }

    bool operator!=(const String &o) const {
      return xmlStrcmp(str, o.str) != 0;
    }

    bool operator<(const String &o) const {
      return xmlStrcmp(str, o.str) < 0;
    }

    bool operator<=(const String &o) const {
      return xmlStrcmp(str, o.str) <= 0;
    }

    bool operator>(const String &o) const {
      return xmlStrcmp(str, o.str) > 0;
    }

    bool operator>=(const String &o) const {
      return xmlStrcmp(str, o.str) >= 0;
    }

    operator const xmlChar *() const {return str;}

    const xmlChar *get() const {return str;}

    std::string cpp_str() const {return str ? (const char *)str : "";}
    const char *cstr() const {return (const char *)str;}
  };

  inline std::ostream &operator<<(std::ostream &stream, const String &s) {
    stream << (const char *)s.get();
    return stream;
  }

  struct ltString {
    bool operator()(const String &s1, const String &s2) const {
      return s1 < s2;
    }
  };
};
#endif
