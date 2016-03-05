#include "XMLSerializer.h"
#include "LibXML2XMLStream.h"
#include "XMLStream2SerializerAdapter.h"

using namespace std;
using namespace xmlpl;

XMLSerializer *XMLSerializer::createInstance(ostream &out) {
  return new XMLStream2SerializerAdapter(new LibXML2XMLStream(out));
}

