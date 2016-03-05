#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "dom/String.h"
#include "Memory.h"

namespace xmlpl {
  class DataSource : public virtual Memory {
    String name;
    
  public:
    DataSource(const String name = "") : name(name) {}
		virtual ~DataSource() {}
    
    const String getName() const {return name;}
    virtual int read(char *&buffer) = 0;
    virtual bool eof() = 0;
  };
};
#endif // DATASOURCE_H
