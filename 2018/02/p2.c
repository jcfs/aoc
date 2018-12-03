#include <stdio.h>
#include <string.h>

char line[260][100];

int cmp(char * line1, char * line2) {
  int c = 0;

  for(int i = 0; i < strlen(line1); i++) {
    if (line1[i] != line2[i]) {
      c++;
    }
  }

  return c == 1;
}

int main() {
  int i = 0;
  while(scanf("%s\n", line[i++]) != -1);
  for(int j = 0; j < 249; j++) {
    for(int k = j+1; k < 250; k++) {
      if (cmp(line[j], line[k])) {
        printf("%s %s\n", line[j], line[k]); 
      }
    }
  }
}
