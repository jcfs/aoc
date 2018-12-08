#include <stdio.h>

typedef struct r {
  char f;
  char s;
} rule;

rule rules[1000];
char steps[1000];
int ns = 0;

char calculate_next(int n) {
  char err[26];

  for(int i = 0; i < 26; i++) err[i] = 0;

  for(int i = 0; i < n; i++) {
    if (rules[i].s) {
      err[rules[i].s-'A'] = 1;
    }
  }

  char r = 40;

  for(int i = 0; i < 26; i++) {
    if (!err[i] && i < r && strchr(steps, i+'A') == NULL) {
      r = i;
    }
  }

  r += 'A';

  for(int i = 0; i < n; i++) 
    if (rules[i].f == r) rules[i].s = 0;

  

  steps[ns] = r;
  printf("%s\n", steps);
  ns++;
  return r;
}


int main() {
  char f, s;
  int n = 0;
  int ns = 0;

  while(scanf("Step %c must be finished before step %c can begin.\n", &f, &s) != -1) {
    rules[n].f = f;
    rules[n].s = s;
    n++;
  }

  for(int i = 0; i < 26; i++)
    calculate_next(n);


}
