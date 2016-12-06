#include <stdio.h>

char input[8];
char letters[8][26];
unsigned int code[9] = {-1,-1,-1,-1,-1,-1,-1,-1};

int main(int argc, char ** argv) {
  int j = 0, i = 0;

  while(scanf("%s\n", input) != EOF) {
    for(j = 0; j < 8; j++) {
      ++letters[j][input[j]-'a'];
    }
  }

  for(i = 0; i < 8; i++) {
    for(j = 0; j < 26; j++) {
      if (letters[i][j] < (code[i] & 0x0000ffff)) {
        code[i] = (j << 16 & 0xffff0000) | (letters[i][j] & 0x0000ffff);
      }
    }
  }

  for(j = 0; j < 8; j++) {
    printf("%c", (code[j]>>16)+'a');
  }

  printf("\n");

}
