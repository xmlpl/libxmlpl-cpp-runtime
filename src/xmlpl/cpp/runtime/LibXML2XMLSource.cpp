#include "LibXML2XMLSource.h"

#include <BasicUtils/BasicException.h>

#include <libxml/parser.h>
#include <stdarg.h>
#include <stdio.h>

using namespace std;
using namespace xmlpl;

LibXML2XMLSource::LibXML2XMLSource(DataSource *in, DOMFactory *factory) :
  in(in), factory(factory), parser(0), saxHandler(factory) {
}

LibXML2XMLSource::~LibXML2XMLSource() {
  if (parser) xmlFreeParserCtxt(parser);
}

bool LibXML2XMLSource::pump(XMLStream *stream) {
  // TODO handle empty file

  if (in->eof()) THROW("No more data");

  // Read Chunk
  char *buf = 0;
  int count = in->read(buf);
  ASSERT_OR_THROW("Unexpected end of file or read error!", count || in->eof());

  stream->flush();

  if (count) {
    // Parse Chunk
    saxHandler.setStream(stream);

    if (!parser) {
      parser =
        xmlCreatePushParserCtxt(saxHandler.getSAXHandler(), &saxHandler,
                                buf, count, in->getName().cstr());
      parser->replaceEntities = 1;
    } else xmlParseChunk(parser, buf, count, 0);
    
    if (saxHandler.hasError()) {
      saxHandler.clearError();
      throw saxHandler.getError();
    }
  }
  
  // Terminate parse
  if (in->eof()) {
    xmlParseChunk(parser, 0, 0, 1);
    return false;
  }

  return true;
}
