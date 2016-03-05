#ifndef PROXYSTACK_H
#define PROXYSTACK_H

#include <BasicUtils/BasicException.h>

#include <xmlpl/cpp/runtime/Memory.h>
#include "Proxy.h"

namespace xmlpl {
  class DOMBuilder;

  class ProxyStack : public Memory {
    Proxy *_top;
    Proxy *cache;

  public:
    ProxyStack() : _top(0), cache(0) {}

    bool empty() {return _top == 0;}
    Proxy *top() {return _top;}

    void push(DOMBuilder &builder, Element *elem) {
      if (!cache) cache = new Proxy(builder);

      cache->attach(elem);
      cache->setNext(_top);
      _top = cache;
      cache = 0;
    }

    void pop() {
      ASSERT_OR_THROW("Proxy Stack empty!", !empty());

      _top->release();
      cache = _top;
      _top = (Proxy *)_top->getNextRaw();
    }
  };
};
#endif // PROXYSTACK_H
