#include <stdio.h>
#include "MD5.h"
 
int main()
{
    uint8_t md5[16] = {0};
    uint32_t i = 0;
 
    MD5_String("Hello,World", md5);
 
    for (i = 0; i < 16; i++)
    {
        printf("%x", md5[i]);
    }
 
    printf("\r\n");
 
    return 0;
}