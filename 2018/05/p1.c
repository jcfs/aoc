#include <stdio.h>
#include <string.h>

char line[60000];

int retract(char * l) {
  char stack[60000] = {0};

  for(int i = 0, j = 0; i < strlen(l); i++) {
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

  return strlen(stack);
}

int main() {
  scanf("%s", line);
  printf("%d\n", retract(line));
}
