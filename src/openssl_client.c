#include <stdio.h>
#include <stdlib.h>
#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"

inline void init_open_ssl()
{
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	//OpenSSL_add_all_algorithms();
	SSL_library_init();
}

int main()
{
	init_open_ssl();
	BIO *bio;
	SSL *ssl;

	SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
	if(ctx == NULL)
	{
		printf("ssl ctx new error!\n");
		return -1;
	}

	if(! SSL_CTX_load_verify_locations(ctx ,NULL ,"/usr/lib/ssl/certs/"))
	{
		printf("verify certs error!\n");
		return -1;
	}

	bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio , &ssl);
	SSL_set_mode(ssl , SSL_MODE_AUTO_RETRY);

	BIO_set_conn_hostname(bio , "www.google.com:443");
	if(BIO_do_connect(bio) <= 0)
	{
		printf("connect ssl error!!!\n");
		return -1;
	}

	printf("cert verify result : %lu \n" , 	SSL_get_verify_result(ssl));
	printf("X509_V_OK:%d\n" , X509_V_OK);

	char *req = "GET / HTTP/1.1 \r\n\r\n";
	if(! BIO_write(bio , req , strlen(req)))
	{
		printf("req error!!\n");
		return -1;	
	}

	char buf[1024];
	if(!BIO_read(bio , buf , 1024))
	{
		printf("read data error!!! \n");
	}
	else
	{
		printf("%s" , buf);
	}
	SSL_CTX_free(ctx);
	BIO_free_all(bio);
	return 0;

}
