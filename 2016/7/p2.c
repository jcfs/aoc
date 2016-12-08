/* compile gcc -o p2 p2.c -Wall */

#include <stdio.h>
#include <regex.h>  
#include <string.h>
#include <stdlib.h>

// find the kth ocurrence of the pattern ABBA in the given string 
int check_pattern(char * str, int k, char * pattern, char * rev_pattern) {
  for(int i = 0; i < strlen(str) - 2; i++) {
    if (str[i] == str[i+2] && str[i] != str[i+1] && str[i] != '[' && str[i+1] != ']' && str[i] != ']' && str[i+1]!='[') {
      if (!--k) {
        rev_pattern[1] = (pattern[0] = str[i]);
        rev_pattern[0] = (rev_pattern[2] = (pattern[1] = str[i+1]));
        pattern[2] = str[i+2];
        return i;
      }
    }
  }

  return -1;
}

// finds the kth ocurrence of the pattern in the given string
int find_pattern(char * str, int k, char * pattern) {
  char * needle, * hay = str;

  while((needle = strstr(hay, pattern)) != NULL) {
    if (!--k) 
      return needle - str;
    
    hay = needle + strlen(pattern);
  }

  return -1;
}

// checks if index k is inside brackets [] in the given string
int check_inside(char * str, int k) {
  char inside = 0;

  for(int i = 0; i != k && i < strlen(str); i++) 
    inside = (str[i] == '[') ? 1 : (str[i] == ']') ? 0 : inside;

  return inside;
}

int main(int argc, char ** argv) {
  char str[256];
  int s = 0;

  while(scanf("%s\n", str) != EOF) {
    for(int p = 0, i = 1, f = 0; !f && p != -1; i++) {
      char pattern[4] = {[0 ... 3] = 0}, rev_pattern[4] = {[0 ... 3] = 0};

      // lets find the pattern ABBA and return the index, the pattern found and 
      // the reverse pattern
      if ((p = check_pattern(str, i, pattern, rev_pattern)) >= 0) {

        // check if found pattern is inside brackets
        char inside = check_inside(str, p);

        // we iterate until we don't find any more reverse pattern or we find a match
        for(int u = 0, j = 1; u != -1 && !f; j++) {

          // lets find the reverse pattern
          if ((u = find_pattern(str, j, rev_pattern)) >= 0) {
            // check if the reverse pattern is inside brackets
            char r_inside = check_inside(str, u);

            // if the pattern is inside and the reverse pattern is not inside
            // or if the pattern is not inside and the reverse is inside 
            // we found a match
            f = ((inside && !r_inside) || (!inside && r_inside));
          }
        }
        if (f) s++;
      }
    } 
  }

  printf("%d\n", s);

  return 0;
}
