#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool DeleteMin(SqList L, int *value) {
  if (L.length == 0) {
    return false;
  }
  *value = L.data[0];
  int pos = 0;
  for (int i = 0; i < L.length; i++) {
    if (L.data[i] < *value) {
      *value = L.data[i];
      pos = i;
    }
  }
  L.data[pos] = L.data[L.length - 1];
  L.length--;
  return true;
}

int main(){
  SqList list = {0};
  list.data[0] = 7;
  list.data[1] = 6;
  list.data[2] = 5;
  list.data[3] = 3;
  list.length = 4;
  int min = 0;
  DeleteMin(list, &min);
  printf("Delete Min: %d\n",min);
  return 0;
}