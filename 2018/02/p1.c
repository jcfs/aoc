#include <stdio.h>
#include <string.h>

char line[100];

int count(char * line, char c) {
  int cnt = 0;
  for(int i = 0; i < strlen(line); i++) {
    if (line[i] == c) {
      cnt++;
      line[i] = '#';
    }
  }

  return cnt;
}

int main() {
  int result = 0;
  int t2 = 0, t3 = 0;
  while(scanf("%s\n", line) != -1) {
    int n2 = 0, n3 = 0;

    for(int i = 0; i < strlen(line); i++) {
      if (line[i] != '#') {
        int c = count(line, line[i]);
        if (c == 3) n3 = 1;
        if (c == 2) n2 = 1;
      }
    }

    t2 += n2;
    t3 += n3;
  }

  printf("%d\n", t2*t3);
}
