/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Edwardyang                                                   |
  | Email: 247689486@qq.com                                              |
  | Site: edwardhey.webbeb.com                                           |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_TTMP_H
#define PHP_TTMP_H

extern zend_module_entry ttmp_module_entry;
#define phpext_ttmp_ptr &ttmp_module_entry

#ifdef PHP_WIN32
#	define PHP_TTMP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TTMP_API __attribute__ ((visibility("default")))
#else
#	define PHP_TTMP_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(ttmp);
PHP_MSHUTDOWN_FUNCTION(ttmp);
PHP_RINIT_FUNCTION(ttmp);
PHP_RSHUTDOWN_FUNCTION(ttmp);
PHP_MINFO_FUNCTION(ttmp);

PHP_FUNCTION(ttmp_check);
PHP_FUNCTION(ttmp_hash);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(ttmp)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(ttmp)
*/

/* In every utility function you add that needs to use variables 
   in php_ttmp_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as TTMP_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define TTMP_G(v) TSRMG(ttmp_globals_id, zend_ttmp_globals *, v)
#else
#define TTMP_G(v) (ttmp_globals.v)
#endif

#endif	/* PHP_TTMP_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
#define MAX_TTMP_HASH_STRLEN 7
#define N_TTMP_CHAR sizeof(char)*3+1
int ttmp_bit_len(int);
