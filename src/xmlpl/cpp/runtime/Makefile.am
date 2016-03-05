SUBDIRS=dom

INCLUDES =\
	-I$(top_builddir)/src\
	@BasicUtils_CFLAGS@\
	@xml2_CFLAGS@

lib_LTLIBRARIES = libxmlpl_cpp_runtime.la

libxmlpl_cpp_runtime_includedir = $(includedir)/xmlpl/cpp/runtime
libxmlpl_cpp_runtime_include_HEADERS =\
	xmlpl.h\
	TypeID.h\
	Sequence.h\
	Target.h\
	StreamTarget.h\
	ChildBuilderTarget.h\
	BuilderTarget.h\
	DataSource.h\
	IStreamDataSource.h\
	CuRLDataSource.h\
	XMLEntities.h\
	XML2SAXHandler.h\
	LibXML2XMLSource.h\
	LibXML2XMLStream.h\
	ReferenceCounter.h\
	Memory.h\
	Reference.h\
	Exception.h\
	Symbol.h\
	LibraryInfo.h\
	Version.h\
	Functions.h\
	CastingObjs.h\
	NullValues.h\
	TargetCast.h\
	VoidTarget.h\
	Iterator.h\
	TypeClasses.h\
	XMLSerializer.h\
	XMLStream2SerializerAdapter.h\
	main.h

libxmlpl_cpp_runtime_la_SOURCES =\
	xmlpl.cpp\
	Sequence.cpp\
	StreamTarget.cpp\
	IStreamDataSource.cpp\
	CuRLDataSource.cpp\
	XMLEntities.cpp\
	XML2SAXHandler.cpp\
	LibXML2XMLSource.cpp\
	LibXML2XMLStream.cpp\
	Version.cpp\
	Functions.cpp\
        XMLSerializer.cpp\
        XMLStream2SerializerAdapter.cpp\
	main.cpp

libxmlpl_cpp_runtime_la_LIBADD =\
	dom/libxmlplDOM.la
