#include <stdio.h>
// #include <android/log.h>

#define LOGTAG "litongxi"
#define LOGE(format,...) printf(LOGTAG " %s " format, __FUNCTION__, __VA_ARGS__)
// #define LOGD(format, ...) printf("debug: %s" format, __FUNCTION__, __VA_ARGS__)

#define LOGD(format,...) printf(LOGTAG " %s "format, __FUNCTION__, ##__VA_ARGS__)

int main(){
    LOGE("Hello World%d\n",7);
    LOGD("hello %d",7);
    LOGD("hello");
    return 0;
}