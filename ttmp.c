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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_ttmp.h"

/* If you declare any globals in php_ttmp.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(ttmp)
*/

/* True global resources - no need for thread safety here */
static int le_ttmp;

/* {{{ ttmp_functions[]
 *
 * Every user visible function must have an entry in ttmp_functions[].
 */
const zend_function_entry ttmp_functions[] = {
    PHP_FE(ttmp_check, NULL)
    PHP_FE(ttmp_hash, NULL)
	PHP_FE_END	/* Must be the last line in ttmp_functions[] */
};
/* }}} */


/* {{{ ttmp_module_entry
 */
zend_module_entry ttmp_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"ttmp",
	ttmp_functions,
	PHP_MINIT(ttmp),
	PHP_MSHUTDOWN(ttmp),
	PHP_RINIT(ttmp),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(ttmp),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(ttmp),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TTMP
ZEND_GET_MODULE(ttmp)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("ttmp.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_ttmp_globals, ttmp_globals)
    STD_PHP_INI_ENTRY("ttmp.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_ttmp_globals, ttmp_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_ttmp_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_ttmp_init_globals(zend_ttmp_globals *ttmp_globals)
{
	ttmp_globals->global_value = 0;
	ttmp_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(ttmp)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(ttmp)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(ttmp)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(ttmp)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ttmp)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ttmp support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ proto bool ttmp_check(string str, array arr)
 */
PHP_FUNCTION(ttmp_check)
{
    char *str = NULL;
    int argc = ZEND_NUM_ARGS();
    int str_len;
    char *pStr = NULL;
    zval *arr = NULL;
    
    if (zend_parse_parameters(argc TSRMLS_CC, "sz", &str, &str_len, &arr) == FAILURE)
        return;
    
    if (str_len<1) {
        RETURN_NULL();
    }
    
    pStr=str;
    HashTable *arr_hash = Z_ARRVAL_P(arr);
    
    char *token = (char *)emalloc(N_TTMP_CHAR);
    memset(token, '\0', N_TTMP_CHAR);
    
    int nStrBitLen = ttmp_bit_len(*pStr);
    int nStrBitPos = 0;
	int nStrPos = 0;
    zval **zvalue;
    
   
    //char *nTrackBackEnd = pStr;
	int nPosTrackBackEnd = 0;
	int nPosTrackBackStart = 0;
    int nTrackBackMaxTimes = MAX_TTMP_HASH_STRLEN * 4;//utf-8最多4个字节
    int nTrackBackTimes = 0;
    char *pTrackBackStart;

    unsigned long hashCode = 0;

	//return array
	array_init(return_value);

    while (*pStr!='\0') {
        
        *(token+nStrBitPos) = *pStr;
        
        nStrBitLen--;
        pStr++;
        nStrBitPos++;
		nStrPos++;
        
        if (!nStrBitLen) {
            //判断token 是否命中
            if(zend_hash_find(arr_hash, token, (unsigned int)strlen(token)+1, (void**)&zvalue)==SUCCESS){
                //开始回朔
                pTrackBackStart = pStr-1;
				
				nPosTrackBackStart = nStrPos-1;
                int bitHead2 = 0;
                int move8 = 0;

                while (nPosTrackBackStart>=nPosTrackBackEnd && nTrackBackTimes<= nTrackBackMaxTimes) {
                    bitHead2 = (*pTrackBackStart&0xFF)>>6;
                    hashCode+=((*pTrackBackStart&0xFF)<<(move8*8));
                    
                    if (bitHead2!=2) {//验证
                        if(Z_TYPE_P(*zvalue)==IS_ARRAY){
                            
                            const HashTable *htArr = Z_ARRVAL_PP(zvalue);
                            zval **ppStr=NULL;
                            if(zend_hash_index_find(htArr, hashCode, (void **)&ppStr)==SUCCESS){
								nPosTrackBackEnd = nStrPos;
								add_next_index_string(return_value, Z_STRVAL_PP(ppStr), 1);
								break;
                            }
                        }
                        move8 = 0;
                    }else{
                        move8++;
                    }
                    
					nPosTrackBackStart--;
                    nTrackBackTimes++;
                    pTrackBackStart--;
                }
                hashCode = 0;
                nTrackBackTimes = 0;
                
            }
            efree(token);
            token = (char*)emalloc(N_TTMP_CHAR);
            memset(token, '\0', N_TTMP_CHAR);
            nStrBitLen = ttmp_bit_len(*pStr);
            nStrBitPos = 0;
        }
    }
    efree(token);
}
/* }}} */


/* {{{ proto int ttmp_hash(string str)
 */
PHP_FUNCTION(ttmp_hash)
{
    char *str = NULL;
    int argc = ZEND_NUM_ARGS();
    int str_len;
    
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &str, &str_len) == FAILURE)
        return;
    
    
    char *pStr = str;
    int iBitLen = ttmp_bit_len(*pStr);
    
    int ret = 0;
    int strlen = 0;
    
    while(*pStr!='\0'){
        ret += ((*pStr)&0xFF)<<((iBitLen-1)*8) ;
        iBitLen--;
        pStr++;
        if(!iBitLen){
            iBitLen = ttmp_bit_len(*pStr);
            if(++strlen>MAX_TTMP_HASH_STRLEN){
                php_error_docref(NULL TSRMLS_CC, E_ERROR, "ttmp_hash: hash function only can count %d words, %s not match!",MAX_TTMP_HASH_STRLEN,str);
            }
        }
    }
    RETURN_LONG(ret);
}
/* }}} */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
/* {{{ proto int ttmp_bit_len(int c)
 */
int ttmp_bit_len(int c){
    int bit;
    if(c){
        bit = (c&0xFF)>>4;
        if(bit<11){
            return 1;
        }else if(bit<14){
            return 2;
        }else if(bit==14){
            return 3;
        }else{//bit==15
            return 4;
        }
    }else{
        return 0;
    }
}
/* }}} */
