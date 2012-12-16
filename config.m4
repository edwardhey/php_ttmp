dnl $Id$
dnl config.m4 for extension ttmp

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(ttmp, for ttmp support,
dnl Make sure that the comment is aligned:
dnl [  --with-ttmp             Include ttmp support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(ttmp, whether to enable ttmp support,
[  --enable-ttmp           Enable ttmp support])

if test "$PHP_TTMP" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-ttmp -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/ttmp.h"  # you most likely want to change this
  dnl if test -r $PHP_TTMP/$SEARCH_FOR; then # path given as parameter
  dnl   TTMP_DIR=$PHP_TTMP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for ttmp files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TTMP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TTMP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the ttmp distribution])
  dnl fi

  dnl # --with-ttmp -> add include path
  dnl PHP_ADD_INCLUDE($TTMP_DIR/include)

  dnl # --with-ttmp -> check for lib and symbol presence
  dnl LIBNAME=ttmp # you may want to change this
  dnl LIBSYMBOL=ttmp # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TTMP_DIR/lib, TTMP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TTMPLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong ttmp lib version or lib not found])
  dnl ],[
  dnl   -L$TTMP_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TTMP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(ttmp, ttmp.c, $ext_shared)
fi
