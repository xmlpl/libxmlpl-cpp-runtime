#include "main.h"

#include <xmlpl/cpp/runtime/Memory.h>

#ifndef NO_GC
#include <libxml/xmlversion.h>
#include <libxml/xmlmemory.h>
#include <string.h>

using namespace xmlpl;

char *GC_xmlStrdup(const char *str) {
  unsigned int len = strlen(str) + 1;
  char *newStr = (char *)GC_MALLOC_ATOMIC(len);
  memcpy(newStr, str, len);
  
  return newStr;
}
#endif

namespace xmlpl {
  void xmlplInit() {
    /*
     * This initializes libxml2 and checks for potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * in library use.
     */
    LIBXML_TEST_VERSION
      
#ifndef NO_GC
    GC_init();
    xmlGcMemSetup(GC_free, GC_malloc, GC_malloc_atomic, GC_realloc, GC_xmlStrdup);
#endif
  }
};
