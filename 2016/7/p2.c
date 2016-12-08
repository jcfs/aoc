#include <stdio.h>
#include <regex.h>  
#include <string.h>
#include <stdlib.h>

int check_pattern(char * str, int k, char * pattern, char * rev_pattern) {
  int c = 1;

  for(int i = 0; i < strlen(str)-2; i++) {
    if (str[i] == str[i+2] && str[i] != str[i+1] && str[i] != '[' && str[i+1] != ']' && str[i] != ']' && str[i+1]!='[') {
      if (c == k) {
        pattern[0] = str[i];
        pattern[1] = str[i+1];
        pattern[2] = str[i+2];

        rev_pattern[0] = rev_pattern[2] = pattern[1];
        rev_pattern[1] = pattern[0];

        return i;
      }
      c++;
    }
  }

  return -1;
}

int find_pattern(char * str, int k, char * pattern) {
  int c = 1;

  for(int i = 0; i < strlen(str)-2; i++) {
    if (str[i] == pattern[0] && str[i+1] == pattern[1] && str[i+2] == pattern[2]) {
      if (c == k) {
        return i;
      }
      c++;
    }
  }

  return -1;
}

int check_inside(char * str, int k) {
  char inside = 0;

  for(int i = 0; i < strlen(str); i++) {
    if (str[i] == '[') inside = 1;
    else if (str[i] == ']') inside = 0;

    if (i == k && inside) return 1;
    else if (i == k) return 0;
  }

  return -1;
}

int main(int argc, char ** argv) {
  regex_t regex;
  char str[256], result[1000];
  int s = 0;
  regmatch_t pmatch[10];

  while(scanf("%s\n", str) != EOF) {
    char pattern[4] = {[0 ... 3] = 0};
    char rev_pattern[4] = {[0 ... 3] = 0};

    for(int i = 1; ; i++) {
      int p, u = 0, f = 0;
      p = check_pattern(str, i, pattern, rev_pattern);
      if (p == -1) break;

      if (check_inside(str, p)) {
        for(int j = 1; u != -1; j++) {
          u = find_pattern(str, j, rev_pattern);
          if (u == -1)
            break;
          if (!check_inside(str, u)) {
            f=1;
          }
        }
      } else {
        for(int j = 1; u != -1; j++) {
          u = find_pattern(str, j, rev_pattern);
          if (u == -1)
            break;
          if (check_inside(str, u)) {
            f=1;
          }
        }   
      }

      if (f) {
        s++;
        break;
      }
    } 
  }

  printf("%d\n", s);

  return 0;
}
