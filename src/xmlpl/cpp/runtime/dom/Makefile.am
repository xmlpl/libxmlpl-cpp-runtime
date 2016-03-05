INCLUDES =\
	-I$(top_builddir)/src\
	@BasicUtils_CFLAGS@\
	@xml2_CFLAGS@

noinst_LTLIBRARIES = libxmlplDOM.la

libxmlplDOM_includedir = $(includedir)/xmlpl/cpp/runtime/dom
libxmlplDOM_include_HEADERS =\
	Attribute.h\
	Comment.h\
	DOM.h\
	DOMBuilder.h\
	DOMFactory.h\
	Document.h\
	Element.h\
	Node.h\
	PI.h\
	Proxy.h\
	ProxyStack.h\
	QName.h\
	Prefix.h\
	String.h\
	Text.h\
	XMLSource.h\
	XMLStream.h\
	NodeStack.h

libxmlplDOM_la_SOURCES =\
	String.cpp\
	DOMBuilder.cpp\
	DOMFactory.cpp\
	Document.cpp\
	Element.cpp\
	Node.cpp\
	Prefix.cpp\
	Proxy.cpp

