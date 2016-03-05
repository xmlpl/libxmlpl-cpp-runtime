#include "XMLStream2SerializerAdapter.h"

#include "BasicUtils/BasicException.h"

using namespace std;
using namespace xmlpl;

XMLStream2SerializerAdapter::XMLStream2SerializerAdapter(XMLStream *stream) :
	stream(stream) {
	
	ASSERT_OR_THROW("Stream cannot be null", stream);
}

void XMLStream2SerializerAdapter::startDocument() {
	stream->startDocument();
}

void XMLStream2SerializerAdapter::startElement(const String qname,
																							 attributes_t &attributes) {
	startElement(qname);

	attributes_t::reverse_iterator it;
	for (it = attributes.rbegin(); it != attributes.rend(); it++)
		stream->attribute(new QName((*it).first), (*it).second);
}

void XMLStream2SerializerAdapter::startElement(const String qname) {
	stream->startElement(new QName(qname));
}

void XMLStream2SerializerAdapter::characters(const String text) {
	stream->text(text);
}

void XMLStream2SerializerAdapter::endElement() {
	stream->endElement();
}

void XMLStream2SerializerAdapter::endDocument() {
	stream->endDocument();
}

void XMLStream2SerializerAdapter::comment(const String text) {
	stream->comment(text);
}

void XMLStream2SerializerAdapter::processingInstruction(const String target, 
																												const String data) {
	stream->pi(target, data);
}

void XMLStream2SerializerAdapter::flush() {
	stream->flush();
}

void XMLStream2SerializerAdapter::close() {
	stream->close();
}
