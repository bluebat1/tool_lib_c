/*
 * StrStream.h
 *
 *  Created on: 2024年8月25日
 *      Author: work-1
 */

#ifndef JNI_UTIL_STRSTREAM_H_
#define JNI_UTIL_STRSTREAM_H_

#include <string>

// #include "Mutex.h"

#define BUFFER_SIZE 124

using namespace std;

typedef struct {
    char buffer[BUFFER_SIZE];
    int read_index;
    int write_index;
    int size;
} StrStreamDef;

void StrStreamInit(StrStreamDef *cb);
void StrStreamWrite(StrStreamDef *cb, const char *data, int len);
int StrStreamReadLine(StrStreamDef *cb, char * buf, int size);

#endif /* JNI_UTIL_STRSTREAM_H_ */
