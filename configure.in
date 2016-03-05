# Disable caching
define([AC_CACHE_LOAD], )
define([AC_CACHE_SAVE], )

# Init
AC_PREREQ(2.56)
AC_INIT([libxmlpl-cpp-runtime], 0.1.5, bugs@xmlpl.org)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_AUX_DIR(./config)

AM_INIT_AUTOMAKE([nostdinc])
AM_CONFIG_HEADER(config.h)


# Flags
AC_COMPILE_FLAGS


# Tools
AC_PROG_CPP
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AM_PROG_LIBTOOL

# Headers
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])


# Typedefs, structures, and compiler characteristics
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE


# Standard library functions
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strdup])


# Test install -C option
touch install.test
if $INSTALL -C install.test install.test2 >/dev/null 2>/dev/null; then
  INSTALL="${INSTALL} -C"
elif $INSTALL -p install.test install.test2 >/dev/null 2>/dev/null; then
  INSTALL="${INSTALL} -p"
fi
rm -f install.test install.test2


# Garbage Collector library
AC_CHECK_LIB(gc, main, , [AC_MSG_ERROR([Cannot find required library libgc])])

# CuRL network transfer library
AC_CHECK_LIB(curl, main, , [AC_MSG_ERROR([Cannot find required library libcurl])])

# BasicUtils
AC_CHECK_CONFIG(BasicUtils, 0.1.9, , [AC_MSG_ERROR([Required library BasicUtils not found!])])
AC_CHECK_LIB(BasicUtils, main, [true], [
  AC_MSG_ERROR([Could not link required library BasicUtils!])],
  $BasicUtils_LIBS)



# LibXML2
AC_CHECK_CONFIG(xml2, 2.6.11, , [AC_MSG_ERROR([Required library xml2 not found!])])
AC_CHECK_LIB(xml2, main, [true], [
  AC_MSG_ERROR([Could not link required library xml2!])],
  [$xml2_LIBS])


# Create Makefiles
AC_OUTPUT([Makefile
	  src/Makefile
	  src/xmlpl/Makefile
	  src/xmlpl/cpp/Makefile
	  src/xmlpl/cpp/runtime/Makefile
	  src/xmlpl/cpp/runtime/dom/Makefile
          scripts/Makefile
          scripts/libxmlpl_cpp_runtime-config
	  ], [chmod +x scripts/libxmlpl_cpp_runtime-config]
         )

echo
echo
echo "   Everything seems to be ok."
echo "Now run 'make' and 'make install'."
echo
echo
