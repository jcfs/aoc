/* compile gcc -o p1 p1.c -Wall */
#include <stdio.h>

char in[9], p[8][26];

int main(int argc, char ** argv) {
  unsigned int code[8] = {[0 ... 7] = 0};

  while(scanf("%s\n", in) != EOF) {
    for(int j = 0; j < 8; j++) {
      int k = ++p[j][in[j] - 'a'];
      
      if (k > (code[j] & 0x0000ffff)) {
        code[j] = (in[j] << 16 & 0xffff0000) | (k & 0x0000ffff);
      }
    }
  }

  for(int j = 0; j < 8; j++) {
    printf("%c", *(code + j) >> 16);
  }

  printf("\n");

  return 0;
}
