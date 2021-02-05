/*
 * Advanced Encryption Standard
 * @author Dani Huertas
 * @email huertas.dani@gmail.com
 *
 * Based on the document FIPS PUB 197
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include<stdbool.h>
#include "aes.h"
#include "mainAES.h"
#include "md5.h"


#define MAXLINE 4096 /*max text line length*/

uint8_t* Encrypt(char *text);
void  Decrypt(uint8_t *cipher,int size,uint8_t hash[]);
	uint8_t i;
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13,
		0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b,
		0x1c, 0x1d, 0x1e, 0x1f};

		uint8_t *w;
		// int textsize;


		// int main(int argc, char const **argv)
		// {
		// 	if (argc != 2)
		// 	{
		// 		printf("input text\n");
		// 		exit(0);
		// 	}

		// 	char *text =(char*)malloc(sizeof(char)*MAXLINE);

		// 	strcpy(text,argv[1]);

		// 	char *dtext=(char*)malloc(sizeof(char)*MAXLINE);;
		// 	dtext = Decrypt(Encrypt(text),strlen(text));

		// 	printf("Success : %s",dtext);

		// 	return 0;
		// }

//ENCRYPT
 uint8_t* Encrypt(char *text){
// printf("ENCRYPTING...\n");
		

		uint8_t in[16];
		uint8_t out[16];


		w = aes_init(sizeof(key));
		aes_key_expansion(key, w);

	if(strlen(text)>16){
	int indx=0;		uint8_t *out_long=(uint8_t*)malloc(sizeof(uint8_t)*strlen(text));  
	// printf("Plaintext message:\n");
	// for (i = 0; i < strlen(text); i++) {printf("%c", in[i]);}printf("\n");
	// printf("%s\n",text);
		
			int loop=0;
			// Encryption 
		while(indx < strlen(text)){
			char *subText = (char *)malloc(16* sizeof(char));
			strncpy(subText,(text+indx),16); indx+=16;

			memmove(in,subText,strlen(subText));
			aes_cipher(in /* in */, (out_long+(loop*16)) /* out */, w /* expanded key */);	loop++;

			free(subText);
		}

			// printf("Ciphered message (in hexadecimal format):\n<");
			// for (i = 0; i < strlen(text); ++i){printf("%x", out_long[i]);}printf(">\n");
				// printf("length=%lu\n",sizeof(out_long)/sizeof(out_long[0]));
			


			memset(out,0,16);
			memset(in,0,16);

			return	out_long;
		
	}else{
		

		memmove(in,text,strlen(text));

		// printf("Plaintext message:\n");
		// for (i = 0; i < strlen(text); i++) {printf("%c", in[i]);}printf("\n");

			aes_cipher(in /* in */, out /* out */, w /* expanded key */);

		// printf("Ciphered message (in hexadecimal format):\n<");
		// for (i = 0; i < sizeof(out)/sizeof(out[0]); i++) {printf("%x", out[i]);} printf(">\n");
			// printf("length=%lu\n",sizeof(out)/sizeof(out[0]));
		uint8_t *dout = (uint8_t*)malloc(sizeof(uint8_t)*16);
		memmove(dout,out,16);

		memset(out,0,16);
		memset(in,0,16);

		return dout;
	}

	free(w);

}


//DECRYPT
void  Decrypt(uint8_t *cipher,int size,uint8_t hash[]){
// printf("DECRYPTING...\n");

		// printf("size %d \n",size);
		uint8_t in[16];
		uint8_t out[16];
		uint8_t inverOut[16];

		w = aes_init(sizeof(key));
		aes_key_expansion(key, w);


	if(size>16){
	uint8_t inverOut_long[size];
	

			// printf("Ciphered message received (in hexadecimal format):\n<");
			//for (i = 0; i <size; ++i){printf("%x", cipher[i]);}printf(">\n");
				// printf("length=%lu\n",sizeof(out_long)/sizeof(out_long[0]));
			//Decription
				int loop1=0,loop2=size%16 ==0 ? size/16 : (size/16)+1; 
			while(loop1<loop2){
				memmove(out,(cipher+(loop1*16)),16); 
				aes_inv_cipher(out, (inverOut_long+(loop1*16)), w); loop1++;
			}
		
			char *text=(char*)malloc(sizeof(char)*(size+1));

			// printf("Original message (after decryption):\n");
			for (i = 0; i <size; i++) {
			text[i]=inverOut_long[i];}
			// printf("%c", inverOut_long[i]);}	printf("\n");

			text[i]='\0';

			memset(inverOut,0,16);
			memset(out,0,16);
			memset(in,0,16);

			// check against hash value from other client & then print derypted text 
			// printf("Hashing decrypted message and checking against the received hash from sender\n");
			uint8_t *currentHash = HashingMD5(text);
			bool check=true;
			for(int i=0;i<16;i++)
				if(currentHash[i]!=hash[i]) {check=false; break;}
			

			if(check)
				printf("\nMessage received from Client  : %s\n",text);
			else
				printf("text dosen't match the Client's sent text (decrypted msg Hash is different from Sender's Hash)\n");
		
	}else if(size>0){

		// printf("Ciphered message received (in hexadecimal format):\n<");
		// for (i = 0; i < 16; i++) {printf("%x", cipher[i]);} printf(">\n");
			// printf("length=%lu\n",sizeof(out)/sizeof(out[0]));

		aes_inv_cipher(cipher, inverOut, w);

		char *text=(char*)malloc(sizeof(char)*((sizeof(inverOut)/sizeof(inverOut[0]))+1));
		// printf("Original message (after decryption):\n");
		for (i = 0; i < size; i++) {
			text[i]=inverOut[i];}
			// printf("%c", inverOut[i]);}	printf("\n");
		
			text[i]='\0';

		memset(inverOut,0,16);
		memset(out,0,16);
		memset(in,0,16);

		// check against hash value from other client & then print derypted text 
		// printf("Hashing decrypted message and checking against the received hash from sender\n");
		uint8_t *currentHash = HashingMD5(text);
			bool check=true;
			for(int i=0;i<16;i++)
				if(currentHash[i]!=hash[i]) {check=false; break;}
			

			if(check)
				printf("\nMessage received from Client  : %s\n",text);
			else
				printf("text dosen't match the Client's sent text (decrypted msg Hash is different from Sender's Hash)\n");
	}
	// else	 printf("\n");
	

free(w);

}
