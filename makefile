obj=kuaipan.o base64.o url_encode.o hmac_sha1.o oauth_nonce.o

test_kuaipan: test_kuaipan.o $(obj)
	gcc -o test_kuaipan test_kuaipan.o $(obj) -lcurl -g
	
test_kuaipan.o:test_kuaipan.c
	gcc -c test_kuaipan.c -g
oauth_nonce.o:oauth_nonce.c oauth_nonce.h
	gcc -c oauth_nonce.c -g	
	
kuaipan.o:kuaipan.c kuaipan.h
	gcc -c kuaipan.c -g
	
base64.o:base64.c base64.h
	gcc -c base64.c -g
	
url_encode.o:url_encode.c url_encode.h
	gcc -c url_encode.c -g
	
hmac_sha1.o:hmac_sha1.c hmac_sha1.h
	gcc -c hmac_sha1.c -g

	
clean:
	rm -f *.o
