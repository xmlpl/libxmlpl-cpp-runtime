#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "dom/String.h"
#include <iostream>

#include <BasicUtils/BasicException.h>

namespace xmlpl {
  class Exception {
    BasicFileLocation l;
    BasicException e;

  public:
    Exception(String message, const int line = 0, const int column = 0) :
      l("", line, column), e(message.cpp_str(), l) {}

    String getMessage() const {return String(e.getMessage().c_str());}
    int getLine() const {return l.getLine();}
    int getColumn() const {return l.getCol();}

    friend std::ostream &operator<<(std::ostream &stream, const Exception &e);
  };

  inline std::ostream &operator<<(std::ostream &stream, const Exception &e) {
    stream << e.e;
    return stream;
  }

  /*
  class Exception {
    String message;
    int line;
    int column;

  public:
    Exception(String message, const int line = 0, const int column = 0) :
      message(message), line(line), column(column) {}
    
    String getMessage() const {return message;}
    int getLine() const {return line;}
    int getColumn() const {return column;}
  };

  inline std::ostream &operator<<(std::ostream &stream, const Exception &e) {
    if (e.getLine())
      stream << e.getLine() << ":" << e.getColumn() << ": ";
    stream << e.getMessage();

    return stream;
  }
  */
};
#endif // EXCEPTION_H
