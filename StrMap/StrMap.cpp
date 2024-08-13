#include "StrMap.h"

// 解析
int StrMapParse(StrMapDef *map) {
    char *ss;
    char *os;
    char *ss2;
    char *os2;
    os = strtok_r(map->is, map->spliteA, &ss);
    for (int i = 0; i < map->max; i++)
    {
        if(os == NULL){
        	map->size = i+1;
            return i+1;
        }
        os2 = strtok_r(os, map->spliteB, &ss2);
        map->data[i].key = os2;
        map->data[i].val = ss2;
        os = strtok_r(NULL, map->spliteA, &ss);
    }
    map->size = map->max;
    return map->max;
}

// 查找
char * StrMapFind(StrMapDef *map, char *key) {
    for (int i = 0; i < map->size; i++)
    {
        if(strncmp(map->data[i].key, key, 32) == 0){
            return map->data[i].val;
        }
    }
    return NULL;
}

