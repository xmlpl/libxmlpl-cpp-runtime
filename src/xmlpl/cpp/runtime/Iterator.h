#ifndef ITERATOR_H
#define ITERATOR_H

namespace xmlpl {
  template <class T>
  class Iterator {
  public:
    virtual ~Iterator() {}

    virtual T &get() = 0;
    virtual T &next() = 0;
    virtual bool hasNext() = 0;

    operator T &() {return get();}
  };
};
#endif // ITERATOR_H
