#ifndef SYMBOL_T
#define SYMBOL_T

namespace xmlpl {
  struct Symbol {
    enum {FUNCTION = 1,
	  VARIABLE = 2,
	  ARGUMENT = 4,
	  CONSTANT = 8,
	  BYREFERENCE = 16};

    const unsigned int flags;
    const unsigned int type;
    const char *name;
    const Symbol *args;

    bool isFunction() const {return flags & FUNCTION;}
    bool isVariable() const {return flags & VARIABLE;}
    bool isArgument() const {return flags & ARGUMENT;}
    bool isConstant() const {return flags & CONSTANT;}
    bool isByReference() const {return flags & BYREFERENCE;}
  };
};
#endif // SYMBOL_T
