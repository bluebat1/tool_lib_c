#include "StrStream.h"


// 初始化循环缓冲区
void StrStreamInit(StrStreamDef *cb) {
    cb->read_index = 0;
    cb->write_index = 0;
    cb->size = 0;
}

// 向循环缓冲区写入数据
// 这里假设输入数据不超过 BUFFER_SIZE
void StrStreamWrite(StrStreamDef *cb, const char *data, int len) {
    for (int i = 0; i < len; i++) {
        cb->buffer[cb->write_index] = data[i];
        cb->write_index = (cb->write_index + 1) % BUFFER_SIZE;

        // 如果缓冲区满了，则移动读指针以覆盖旧数据
        if (cb->size == BUFFER_SIZE) {
            cb->read_index = (cb->read_index + 1) % BUFFER_SIZE;
        } else {
            cb->size++;
        }
    }
}

// 从循环缓冲区获取一行数据
// 返回指向获取的行的指针，调用者需要释放
int StrStreamReadLine(StrStreamDef *cb, char * buf, int size) {
    if (cb->size == 0) {
        return -1; // 没有可读取的数据
    }

    int line_length = 0;
    int read_length = 0;
    int start_index = cb->read_index;

    // 查找换行符、计算长度
    int index = cb->read_index;
    int dataSize = cb->size;
    int findFlag = 0;
    while (dataSize > 0) {
        // 找到换行符
        if (cb->buffer[index] == '\n') {
            index = (index + 1) % BUFFER_SIZE;
            dataSize--;
            findFlag = 1;
            break;
        }
        read_length++;
        index = (index + 1) % BUFFER_SIZE;
        dataSize--;
    }
    // 在整个缓冲区中没有找到换行符
    if(dataSize == 0 && findFlag == 0) {
        // 缓冲区未满
        if(cb->size < BUFFER_SIZE) {
            return 0; // 没有可读取的数据
        }
    }
    // 取出内容
    cb->read_index = index;
    cb->size = dataSize;

    // 如果读取到的内容长度超过size，则截断
    if(read_length > size) {
        line_length = size;
    }else{
        line_length = read_length;
    }

    for (int i = 0; i < line_length; i++) {
        buf[i] = cb->buffer[(start_index + i) % BUFFER_SIZE];
    }
    buf[line_length] = '\0'; // 以 NULL 结尾

    
    return line_length;
}
