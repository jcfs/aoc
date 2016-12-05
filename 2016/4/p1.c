#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
  char room[100], checksum[5];
  int i, j, sum = 0, id;

  while(scanf("%s%d %s", room, &id, checksum) == 3) {
    char alpha[26] = {0};

    for(i = 0; i < strlen(room); i++) {
      alpha[room[i]-'a']++;
    }

    int h[5] = {0};
    char c[5] = {0};    

    for(j = 0; j < 5; j++) {
      for(i = 0; i < 26; i++) {
        if (alpha[i] > h[j]) {
          h[j] = alpha[i];
          c[j] = i + 'a';
        }
      }
      alpha[c[j]-'a'] = 0;
    }
    
    if (strncmp(c, checksum, 5) == 0) {
      sum += id;
    }

  }
  printf("%d\n", sum);
}
