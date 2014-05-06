#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "openssl/err.h"
#include "openssl/bio.h"
#include "openssl/ssl.h"

#define CHAR_ARRAY_SIZE	        1024
#define LOG(...)		printf(__VA_ARGS__)
#define INIT_OPEN_SSL_LIB	init_open_ssl()

/**init openssl library*/
inline void init_open_ssl()
{
        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();
        SSL_library_init();
}
