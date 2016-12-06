#include <stdio.h>

char input[700][9];

int main(int argc, char ** argv) {
  int i = 0, j = 0, k = 0, w = 0, y = 0;
  while(scanf("%s\n", input[i]) != EOF) {
    i++;
  }

  for(j = 0; j < 8; j++) {
    char letters[26] = {0};
    char cl;
    int m = 1000;

    for(w = 0; w < i; w++) {
      letters[input[w][j]-'a']++;
    }

    for(y = 0; y < 26; y++) {
      if (letters[y] < m) {
        m = letters[y];
        cl = y+'a';
      }
    }

    printf("%c", cl);
  }
  printf("\n");

}
