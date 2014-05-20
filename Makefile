nossl_bio_client:
	gcc src/ssl_shared.h src/nossl_bio_client.c -o $@ -lssl
	./$@
openssl_client:
	gcc src/openssl_client.c -o $@ -lssl
	./$@
