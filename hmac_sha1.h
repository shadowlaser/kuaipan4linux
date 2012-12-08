#ifndef __HMAC_SHA1__
#define __HMAC_SHA1__

/* Function to compute the digest */
char* hmac_sha(
	char* k, /* secret key */
	int lk, /* length of the key in bytes */
	char* d, /* data */
	int ld, /* length of data in bytes */
	char* out, /* output buffer, at least "t" bytes */
	int t
);

#endif