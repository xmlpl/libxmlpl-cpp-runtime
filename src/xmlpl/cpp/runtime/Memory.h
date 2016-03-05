#ifndef MEMORY_H
#define MEMORY_H

#define NO_BASICOBJCOUNTERS
#include <BasicUtils/BasicObjCounter.h>
#include <BasicUtils/BasicException.h>

#define NO_GC
#ifndef NO_GC
#include <gc/gc_cpp.h>
#include <gc/gc_allocator.h>
#define xmlpl_alloc gc_allocator

#include <BasicUtils/BasicGCAllocator.h>
#define BASIC_ALLOC BasicGCAllocator

#else
#include <memory>
#define xmlpl_alloc std::allocator

#include <BasicUtils/BasicAllocator.h>
#define BASIC_ALLOC BasicAllocator
#endif

#ifdef NO_GC
#include <stdlib.h>

namespace xmlpl {
  class Memory : public BasicObjCounter<Memory> {};
};

#define XMLPL_MALLOC(x) malloc(x)
#define XMLPL_FREE(x) free(x)
#define XMLPL_MALLOC_ATOMIC(x) malloc(x)
#define XMLPL_REALLOC(x, y) realloc(x, y)

#else

namespace xmlpl {
  class Memory : public gc, public BasicObjCounter<Memory> {};
};

#define XMLPL_MALLOC(x) GC_MALLOC(x)
#define XMLPL_FREE(x) GC_FREE(x)
#define XMLPL_MALLOC_ATOMIC(x) GC_MALLOC_ATOMIC(x)
#define XMLPL_REALLOC(x, y) GC_REALLOC(x, y)

#endif

#endif // MEMORY_H
