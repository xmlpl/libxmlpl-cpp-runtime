#ifndef ISTREAMDATASOURCE_H
#define ISTREAMDATASOURCE_H

#include "DataSource.h"

#include <iostream>

namespace xmlpl {
  class IStreamDataSource : public DataSource {
    static const unsigned int bufferSize = 1024;

    char buf[bufferSize];
    std::istream &in;
    
  public:
    IStreamDataSource(std::istream &in, const String &name = "");
    virtual ~IStreamDataSource();
    
    int read(char *&buffer);
    bool eof();
  };
};
#endif // ISTREAMDATASOURCE_H
