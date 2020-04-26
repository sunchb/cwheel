#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void cutil_log(const char* file, const char* func, int line, int level, const char *cmd, ...)  
{  
    printf("[lev:%d][%s][line:%d]", level, func, line);
    va_list args;
    va_start(args,cmd);
    vprintf(cmd,args);
    va_end(args);
}

void* cutil_malloc(int size){
    return malloc(size);
}

void cutil_free(void* ptr){
    free(ptr);
}
