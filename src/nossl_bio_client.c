#include "ssl_shared.h"

int main()
{
	INIT_OPEN_SSL_LIB;
	BIO *bio;
	bio = BIO_new_connect("www.baidu.com:80");
	if(bio == NULL)
	{
		LOG("bio new connect error!\n");
		return -1;
	}

	if(BIO_do_connect(bio) <= 0)
	{
		LOG("connection success!!!\n");
		return -1;
	}
	else
	{
		LOG("connection success !!!\n");
	}

	char *req = "GET / HTTP/1.1\n\n";
	if(BIO_write(bio , req , strlen(req)) <= 0)
	{
		LOG("send data error!\n");
		BIO_free_all(bio);
		return -1;
	}else{
		LOG("send data success \n%s\n" , req);
	}

	char buf[CHAR_ARRAY_SIZE];
	memset(buf , '\0' , CHAR_ARRAY_SIZE);
	int x = BIO_read(bio , buf , CHAR_ARRAY_SIZE);
	if(x == 0)
	{
		LOG("socket connection has closed!!!");
	}
	else if(x < 0 )
	{
		LOG("connection error !!!\n");
		if(! BIO_should_retry(bio))
		{
			LOG("retry error!!!\n");
		}
	}else
	{
		LOG("return data \n%s\n" , buf);
	}

	BIO_free_all(bio);

	return 0;
}

