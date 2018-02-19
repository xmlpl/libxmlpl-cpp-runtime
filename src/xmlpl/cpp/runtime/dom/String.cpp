#include "String.h"

#include <BasicUtils/BasicArray.h>
#include <stdarg.h>
#include <string.h>

using namespace xmlpl;

String String::concat(const unsigned int count, ...) {
  va_list ap;
  BasicArray<unsigned int, BASIC_ALLOC> lengths;

  unsigned int total = 1;

  va_start(ap, count);
  for (unsigned int i = 0; i < count; i++) {
    const xmlChar *s = va_arg(ap, const xmlChar *);
    if (s) {
      unsigned int len = strlen((const char *)s);
      lengths.put(len);
      total += len;
    } else lengths.put(0);
  }
  va_end(ap);

  xmlChar *str = (xmlChar *)XMLPL_MALLOC(total);
  total = 0;

  va_start(ap, count);
  for (unsigned int i = 0; i < count; i++) {
    const xmlChar *s = va_arg(ap, const xmlChar *);
    memcpy(&str[total], s, lengths[i]);
    total += lengths[i];
  }
  va_end(ap);

  return String(str);
}

String String::operator+(const String &s) const {
  int len1 = this->str ? strlen((const char *)this->str) : 0;
  int len2 = s.str ? strlen((const char *)s.str) : 0;

  if (!len1) return s;
  if (!len2) return *this;

  xmlChar *str = (xmlChar *)XMLPL_MALLOC(len1 + len2 + 1);
  memcpy(str, this->str, len1);
  memcpy(&str[len1], s.str, len2);

  str[len1 + len2] = 0;

  return String(str);
}

int String::length() const {
  return xmlUTF8Strlen(str);
}
