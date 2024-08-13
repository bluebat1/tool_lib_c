#include "mystring.h"

typedef struct 
{
    char *key;
    char *val;
}StrMapUnitDef;


typedef struct 
{
    int max;
    int size;
    char *is;
    const char *spliteA;
    const char *spliteB;
    StrMapUnitDef *data;
} StrMapDef;


// 解析
int StrMapParse(StrMapDef *map);

// 查找
char * StrMapFind(StrMapDef *map, char *key);

