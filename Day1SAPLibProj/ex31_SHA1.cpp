#include<stdio.h>
#include<malloc.h>
#include<openssl/sha.h>

#define INPUT_BLOCK_LENGTH 15

int main() {

	unsigned char input[] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
							  0x11,0x02,0x03,0x04,0x55,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
							  0x21,0x02,0x03,0x04,0x65,0x06,0x07,0x08,0x09,0xAA,0x0B,0x0C,0xDD,0x0E,0x0F,
							  0x01,0x02,0x03,0x04,0x75,0x06,0x07,0x08,0x09,0xBA,0x0B,0x0C,0xDD,0x0E };

	SHA_CTX ctx;
	SHA1_Init(&ctx);

	//be careful, the char type can store values up to 256; it isn't an issue here with a small hardcoded value, but it is not recommend for larger files
	unsigned char inputLength=sizeof(input) / sizeof(unsigned char); // total length of byteArray input
	unsigned char remainingLength = inputLength;

	while (remainingLength > 0) {

		if (remainingLength > INPUT_BLOCK_LENGTH) {
			//sha1 update done for 15-byte input
			SHA1_Update(&ctx,&(input[inputLength-remainingLength]), INPUT_BLOCK_LENGTH);
			remainingLength -= INPUT_BLOCK_LENGTH;
		}
		else {
			//sha1 update done for less than 15 bytes
			SHA1_Update(&ctx, &(input[inputLength - remainingLength]), remainingLength);
			remainingLength = 0; //instruction for exiting from the while
		}
	}

	unsigned char finalDigest[SHA_DIGEST_LENGTH];
	SHA1_Final(finalDigest, &ctx); //this call also returns a int value for error codes

	printf("\n\nSHA1 = ");
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		printf("%02X ", finalDigest[i]);
		printf(" ");
	}
	printf(" \n\n");
	return 0;
}

