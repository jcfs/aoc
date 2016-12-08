#include <stdio.h>
#include <regex.h>  
#include <string.h>
#include <stdlib.h>

char * get_match(char * source, int k, int len) {
  char * match = (char *) calloc(sizeof(char), len + 1);
  strncpy(match, source+k, len);
  return match;
}

int main(int argc, char ** argv) {
  regex_t regex[2];

  char str[256];
  int count = 0;

  if (regcomp(&regex[0], "([a-z])([a-z])\\2\\1", REG_EXTENDED | REG_ENHANCED) == -1) {
    perror("Error compiling regex");
    exit(1);
  }

  while(scanf("%s\n", str) != EOF) {
    regmatch_t groups[5];

    if (!regexec(&regex[0], str, 5, groups, 0)) {
        printf("--------------------------------\n");
        printf("%s\n", str);
        char pattern[66] = {[0 ... 65] = 0};
        int k = 0;

        char * match = get_match(str, groups[k].rm_so, groups[k].rm_eo - groups[k].rm_so);
    
        sprintf(pattern, "\\\\[[^\\\\]]*?%s[^\\\\[]*?\\\\]", match);

        printf("%s %s\n---------------------------------------\n", match, pattern);

        free(match);

        if (regcomp(&regex[1], pattern, REG_EXTENDED | REG_ENHANCED | REG_UNGREEDY) == -1) {
          perror("error compiling regex");
          exit(1);
        }

        if (regexec(&regex[1], str, 0, NULL, REG_NOTBOL | REG_NOTEOL)) {
          count++; 
        } else {
          printf("YES %s %s\n", pattern, str);
        }
    } 
  }

  printf("%d\n", count);
}
