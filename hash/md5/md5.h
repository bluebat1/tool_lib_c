#ifndef MD5_H
#define MD5_H
 
#include <stdio.h>
#include <stdint.h>
 
 
extern void MD5_String(char *input, uint8_t *result);
extern void MD5_Data(uint8_t *input, uint32_t length, uint8_t *result);
extern void MD5_File(FILE *file, uint8_t *result);
 
 
#endif