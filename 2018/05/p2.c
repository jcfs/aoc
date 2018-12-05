#include <stdio.h>
#include <string.h>

int retract(char * l) {
  char stack[60000] = {0};
  int j = 0, len = strlen(l);

  for(int i = 0; i < len; i++) {
    if (!j) {
      stack[j++] = l[i];
    } else {
      if ((stack[j-1]^l[i]) == 32) {
        stack[--j] = 0;
      } else {
        stack[j++] = l[i];
      }
    }
  }

  return j;
}

int main() {
  char line[60000];
  char nline[60000];
  unsigned min = -1;

  scanf("%s", line);
  int len = strlen(line);

  for(char c = 'a' ; c <= 'z'; c++) {
    for(int i = 0, j = 0; i < len; i++) {
      if ((line[i]|32) != c) {
        nline[j] = line[i];
        nline[++j] = 0;
      }
    }

    int cnt = retract(nline);
    if (cnt < min) {
      min = cnt;
    }
  }

  printf("%d\n", min);
}
