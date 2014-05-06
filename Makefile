ssl_bio_client:
	gcc src/* -o $@ -lssl
	./$@
