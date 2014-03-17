#include <stdio.h>
#include <stdlib.h>

char* bitreverse(int n, char* ptr) {
  //We are assuming 32 bit integers where 1 <= n <= 10^9
  int i = 0;
  int temp = 0;
  int len = 0;
  char* revptr = (char*) malloc((32 + 1)*sizeof(char));

  for(i = 0; i < 32; i++) {
    temp = n >> i;
    temp = temp & 1;
    if(temp) {
      len = i+1;
    }
    temp += 48;
    ptr[31-i] = temp;
  }
  ptr[32] = 0;

  //printf("Length of bitstring is %d\n", len);
  for(i = 0; i < 32-len; i++) {
    revptr[i] = 48;
  }

  for(i = 0; i < len; i++) {
    revptr[32-len+i] = ptr[31-i];
  }
  revptr[32] = 0;

  int revn = 0;
  for(i = 0; i < len; i++) {
    if(revptr[31-i] == 49) {
      //printf("Adding %d, i = %d\n", 1<<i, i);
      revn += (1 << i);
    }
  }
  printf("%d\n", revn);
  //printf("%d reversed is %d\n", n, revn);
  return revptr;
}

int main() {
  //printf("Enter integer to represent:\n");
  int n = 0;
  scanf("%d", &n);
  char* ptr = (char*) malloc((32 + 1) * sizeof(char));
  char* revptr = bitreverse(n, ptr);
  //printf("%d in binary is\n%s\n", n, ptr);
  //printf("%d's reversed binary is\n%s\n", n, revptr);
  return 0;
}
