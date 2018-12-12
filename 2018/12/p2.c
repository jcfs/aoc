#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct k {
  char r[6];
  char outcome;
} rule;

rule rules[100];
int n_rules = 0;
int initial_size; 

int sum(char * s) {
  int off = (strlen(s) - initial_size) / 2;
  int su = 0;
  for(int i = 0; i < strlen(s); i++) {
    if (s[i] == '#') {
      su += (i - off);
    }
  }

  return su;
}

char * net_gen(char * s, int size) {
  char * new = calloc(size + 9, sizeof(char));

  for(int i = 0; i < size + 8; i++) {
    if (i < 4) new[i] = '.';
    else if (i >= size+4) new[i] = '.';
    else new[i] = s[i-4];
  }

  char sub[6];
  char * n_s = calloc(size+5, sizeof(char));
  for(int i = 2; i < strlen(new) - 2; i++) {
    strncpy(sub, new+i-2, 5);
    sub[5] = 0;

    char found = 0;
    for(int k = 0; k < n_rules; k++) {
      if (!strncmp(sub, rules[k].r, 5)) {
        n_s[i-2] = rules[k].outcome;
        found = 1;
        break;
      }
    }

    if (!found) n_s[i-2] = '.';
  }

  return n_s;
}

int main() {
  char s[101];

  scanf("initial state: %s\n\n", s);

  initial_size = strlen(s);

  while(scanf("%s => %c\n", rules[n_rules].r, &rules[n_rules].outcome) != -1)
    n_rules++;

  char * t = s;
  int o_s = sum(t);
  int off = 0;
  for(int i = 0; i < 201; i++) {
    t = net_gen(t, strlen(t));
    int o = sum(t);
    off = o-o_s;
    o_s = o;
  }

  printf("%ld\n", (50000000000 - 201) * off + sum(t));
}
