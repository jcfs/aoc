/* compile gcc -o p2 p2.c -Wall */
#include <stdio.h>

char p[8][26];

int main(int argc, char ** argv) {
  unsigned int code[8] = {[0 ... 7] = -1};
  char in[9];

  while(scanf("%s\n", in) != EOF) {
    for(int j = 0; j < 8; j++) {
      ++p[j][in[j]-'a'];
    }
  }

  // find the maximum
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 26; j++) {
      char ch = p[i][j];

      // because we are lazy we use one int to store both the max number of occurrences of
      // a character and the character itself
      if (ch < (code[i] & 0x0000ffff)) {
        code[i] = ((j+0x61) << 16 & 0xffff0000) | (ch & 0x0000ffff);
      }
    }
  }

  for(int j = 0; j < 8; j++) {
    printf("%c", *(code+j) >> 16);
  }

  printf("\n");

  return 0;
}
