#include<stdio.h>
#include<malloc.h>
#include<openssl/sha.h>

#define INPUT_BLOCK_LENGTH 15

int main() {
	FILE* inputFile = NULL;
	errno_t err;

	err = fopen_s(&inputFile, "input_SHA1.bin", "rb");
	if (err == 0) {
		SHA_CTX ctx;
		SHA1_Init(&ctx);
		
		unsigned char* input = (unsigned char*)malloc(INPUT_BLOCK_LENGTH);
		
		int read_length = INPUT_BLOCK_LENGTH;
		while (read_length == INPUT_BLOCK_LENGTH) {
			read_length = fread(input, 1, INPUT_BLOCK_LENGTH, inputFile);
			if (read_length > 0) {
				SHA1_Update(&ctx, input, read_length);
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
		
		FILE* outputFile = NULL;
		err = fopen_s(&outputFile, "outputFile.txt", "w+");
		if (err == 0) {
			fprintf(outputFile,"\nSHA1 = ");
			for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
				fprintf(outputFile,"%02X ", finalDigest[i]);
				fprintf(outputFile," ");
			}
			fclose(outputFile);
		}

		fclose(inputFile);
	}
	return 0;
}

