#include <stdio.h>
#include <stdlib.h>

int main(){
    char path[] = "sdcard/image/1/1002/L1/reg/reg/0088/00/V1/00009145_00058_96_c370_a0_success.bmp";
    int temperature, maskArea;
    if (!sscanf(path, "%*[^_]%*[^c]c%d", &temperature)) {
            return -1;
        }
    int ret = sscanf_s(path, "%*[^_]%*[^c]c%d", &temperature);
    printf("ret: %d, temperature: %d",ret, temperature);
}