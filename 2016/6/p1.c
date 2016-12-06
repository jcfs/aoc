#include <stdio.h>

char input[9];
char letters[8][26];
int code[9];

int main(int argc, char ** argv) {
  int j = 0;

  while(scanf("%s\n", input) != EOF) {
    for(j = 0; j < 8; j++) {
      int cnt = ++letters[j][input[j]-'a'];
      if (cnt > (code[j]&0x0000ffff)) {
        code[j] = (input[j] << 16 & 0xffff0000) | (cnt&0x0000ffff);
      }
    }
  }

  for(j = 0; j < 8; j++) {
    printf("%c", (code[j]>>16));
  }

  printf("\n");

}
