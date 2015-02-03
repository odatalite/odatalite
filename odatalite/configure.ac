# Run autoconf to generate 'configure' script

AC_PREREQ([2.59])
AC_INIT([odatalite], [0.0.3])
AM_INIT_AUTOMAKE([1.10 no-define])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADER([src/config.h])
AC_PREFIX_DEFAULT(/opt/odatalite)
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_INSTALL

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_LIBTOOL

AC_CHECK_FUNCS([socket strcasecmp strncasecmp strstr getpwuid_r])
AC_CHECK_FUNCS([strtoll])
AC_CHECK_FUNCS([strtoull])
AC_CHECK_FUNCS([vsnprintf])

AC_TYPE_SIZE_T

AC_CHECK_HEADERS([netdb.h stddef.h sys/socket.h unistd.h])

AC_CHECK_HEADERS([security/pam_appl.h], [], [AC_MSG_ERROR([Missing pam.h dependency])])

AC_CHECK_LIB([pam], [pam_start], [], [AC_MSG_ERROR([Missing pam library dependency])])

AC_CHECK_HEADERS([expat.h], [], [AC_MSG_ERROR([Missing expat.h dependency])])

AC_CHECK_LIB([expat], [XML_ParserCreate], [], [AC_MSG_ERROR([Missing expat library dependency])])

#AC_CHECK_LIB([crypto],[CRYPTO_new_ex_data], [], [AC_MSG_ERROR([OpenSSL libraries required])])

#AC_CHECK_LIB([ssl],[SSL_library_init], [], [AC_MSG_ERROR([OpenSSL libraries required])])

AC_CHECK_HEADERS([openssl/crypto.h openssl/x509.h openssl/pem.h openssl/ssl.h openssl/err.h],[],[AC_MSG_ERROR([OpenSSL headers required])])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/base/Makefile
    src/tools/Makefile
    src/tools/dlopen/Makefile
    src/tools/gennstr/Makefile
    src/tools/base64enc/Makefile
    src/tools/base64dec/Makefile
    src/tools/bins/Makefile
    src/tools/octstr/Makefile
    src/tools/file2c/Makefile
    src/plugins/Makefile
    src/plugins/ping/Makefile
    src/plugins/hello/Makefile
    src/plugins/echo/Makefile
    src/plugins/odata/Makefile
    src/server/Makefile
    src/client/Makefile
    src/phitcli/Makefile
    src/olcli/Makefile
    src/odata/Makefile
    src/odata/providers/Makefile
    src/odata/providers/root/Makefile
    src/odata/providers/frog/Makefile
    src/odata/providers/heap/Makefile
    src/odata/providers/gadget/Makefile
    src/odata/providers/metadata/Makefile
    src/odata/providers/check/Makefile
    src/odata/providers/widget/Makefile
    src/json/Makefile
    src/csdl2c/Makefile
    src/tests/Makefile
    src/tests/base/Makefile
    src/tests/odata/Makefile
    src/tests/csdl/Makefile
    src/tests/odatacxx/Makefile])

##==============================================================================
##
## --enable-debug
##
##==============================================================================

AC_ARG_ENABLE(
[debug],
[  --enable-debug       Compile and link with debugging enabled],
[case "${enableval}" in
  yes)
    debug=1
    ;;
  no)
    debug=0
    ;;
  *)
    AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) 
    ;;
esac],
[debug=0])


SECTIONS+="-ffunction-sections "
SECTIONS+="-fdata-sections "
SECTIONS+="-Wl,--gc-sections "
#SECTIONS+="-Wl,--print-gc-sections "

__FLAGS+="-Wall "
__FLAGS+="-Werror "
#__FLAGS+="-Winline "
#__FLAGS+="-m32 "
__FLAGS+="-g "
__FLAGS+="-Os "
#__FLAGS+="-ansi "
__FLAGS+="-fPIC "
#_FLAGS+="-pedantic "
__FLAGS+="-Wno-long-long "
__FLAGS+="-fvisibility=hidden "

__FLAGS+="${SECTIONS} "

CXXFLAGS="$CXXFLAGS ${__FLAGS}"
CXXFLAGS="$CXXFLAGS -fno-exceptions"
CXXFLAGS="$CXXFLAGS -fno-enforce-eh-specs"
CXXFLAGS="$CXXFLAGS -fconserve-space"
CXXFLAGS="$CXXFLAGS -fno-rtti"
CXXFLAGS="$CXXFLAGS -fno-threadsafe-statics"

CFLAGS="$CFLAGS ${__FLAGS}"

runstatedir=$localstatedir/run

AC_DEFINE_UNQUOTED(SYSCONFDIR, "$__prefix", [prefix])
AC_DEFINE_UNQUOTED(SYSCONFDIR, "$sysconfdir", [sysconfdir])
AC_DEFINE_UNQUOTED(LOCALSTATEDIR, "$localstatedir", [localstatedir])
AC_DEFINE_UNQUOTED(RUNSTATEDIR, "$runstatedir", [runstatedir])
AC_DEFINE_UNQUOTED(LIBDIR, "$libdir", [libdir])
AC_DEFINE_UNQUOTED(DATAROOTDIR, "$datarootdir", [datarootdir])
AC_DEFINE_UNQUOTED([CONFIG_DEBUG], $debug, [debug enabled])

CPPFLAGS=-DPREFIX='"\"$(prefix)\""'

AC_OUTPUT
