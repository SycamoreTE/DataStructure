#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (15)

static char FinalResult[MAX_SIZE] = {0};

int GetResult(char* result){
    char* mResult = (char*)malloc(sizeof(char)*10);
    memset(mResult, -1, 10);

    memcpy(result, mResult, 10);
    return 0;
}

int main(){
    // for(int i = 0; i < MAX_SIZE; i++){
    //     FinalResult[i] = 'a';
    //     printf("%c\t",FinalResult[i]);
    // }
    GetResult(FinalResult);
    printf("\n");
    for(int i = 0; i < MAX_SIZE; i++){
        printf("%d\t",FinalResult[i]);
    }
    return 0;
}
