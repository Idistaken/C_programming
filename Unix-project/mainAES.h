#include <stdint.h>
#include <stdlib.h>

uint8_t* Encrypt(char *text);
void  Decrypt(uint8_t *cipher,int size,uint8_t hash[]);