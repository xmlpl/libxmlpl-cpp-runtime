#include "Prefix.h"

using namespace xmlpl;

Prefix Prefix::EMPTY = Prefix((const xmlChar *)0, (const xmlChar *)0);
Prefix Prefix::ANY = Prefix("*", (const xmlChar *)0);
