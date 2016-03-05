#ifndef LIBRARYINFO_T
#define LIBRARYINFO_T

#include "Symbol.h"
#include "Version.h"

#define LIBRARY_INFO_NAME "libraryInfo"

namespace xmlpl {
  struct LibraryInfo {
    const char *namespaceStr;
    const char *namespaceHash;
    Version version;
    unsigned int tableSize;
    const Symbol *table;
  };
};
#endif // LIBRARYINFO_T
