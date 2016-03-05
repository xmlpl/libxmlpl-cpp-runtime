#include "StreamTarget.h"
#include "Sequence.h"

using namespace xmlpl;

void StreamTarget::append(const Sequence<NodeRef> &s) {
  if (s.isTemporary() && s.getRefCount() <= 1) {
    Sequence<NodeRef> copy(s);
    for (unsigned int i = 0; i < copy.size(); i++)
      if (copy[i] != 0) copy[i].drop()->serialize(*this);

  } else
    for (unsigned int i = 0; i < s.size(); i++)
      if (s[i] != 0) s[i]->serialize(*this);
}

void StreamTarget::append(const Sequence<String> &s) {
  for (unsigned int i = 0; i < s.size(); i++)
    text(s[i]);
}
