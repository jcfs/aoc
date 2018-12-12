#include <stdio.h>
#include <string.h>

typedef struct r {
  char f;
  char s;
} rule;

typedef struct w {
  char c;
  int time;
} worker;

worker workers[5];
rule rules[1000];
char steps[1000];
char avai[26];
int ns = 0;

char calculate_next(int n) {
  char err[26];

  for(int i = 0; i < 26; i++) err[i] = 0;

  for(int i = 0; i < n; i++) {
    if (rules[i].s) {
      err[rules[i].s-'A'] = 1;
    }
  }


  for(int i = 0; i < 26; i++) avai[i] = 0;

  int a = 0;
  for(int i = 0; i < 26; i++) {
    if (!err[i] && strchr(steps, i+'A') == NULL) {
      avai[a++] = i+'A'; 
    }
  }

  return 1;
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

  int t = 0;
  int co = 1;
  while(1) {
    co = 0;
    calculate_next(n);

    int a = 0;
    for(int i = 0; i < 5; i++) {
      if (!workers[i].c && avai[a]) {
        workers[i].c = avai[a];
        workers[i].time = 60 + (workers[i].c - 'A' + 1);
        steps[ns] = avai[a];
        a++;
        ns++;
      }
    }

    for(int i = 0; i < 5; i++) {
      if (workers[i].c) {
        workers[i].time--;

        if (!workers[i].time) {

          if (t+1==848) {
            printf("%d\n", t+1);
            return 1;
          }
          for(int j = 0; j < n; j++)
            if (rules[j].f == workers[i].c) {
              rules[j].s = 0;
            }

          workers[i].c = 0;
       } else {
          co = 1;
       }
      }
    }

    t++;

  }

}
