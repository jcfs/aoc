#include <stdio.h>
#include <string.h>

char rotate(char ch, int n) {
  int i = 0;

  for(i = 0; i < n; i++) 
    if (++ch > 'z') ch = 'a';
  
  return ch;
}

int main(int argc, char ** argv) {
  char room[100], cs[5];
  int id, i;  

  while(scanf("%s%d %s", room, &id, cs) == 3) {
    for(i = 0; i < strlen(room); i++){
      room[i] = rotate(room[i], id);
    }

    if (strstr(room, "pole") != NULL)
      printf("%s - %d\n", room, id);
  }

}
