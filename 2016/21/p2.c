/* compile gcc -o p2 p2.c -O3 -Wall */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void swap(char * s, int x, int y) {
  char ch = s[x];
  s[x] = s[y];
  s[y] = ch;
}

void swap_l(char * s, char a, char b) {
  for(int i = 0; i < strlen(s); i++) {
    if (s[i] == a) s[i] = b;
    else if (s[i] == b) s[i] = a;
  }
}

void rotate_l(char * s, int x) {
  for(int i = 0; i < x; i++) {
    for(int j = 0, t = s[0]; j < strlen(s); j++) {
        if (j == strlen(s)-1) s[j] = t;
        else s[j] = s[j+1];
    }
  }
}

void rotate_r(char * s, int x) {
  for(int i = 0; i < x; i++) {
    for(int j = 7, t = s[7]; j >= 0; j--) {
        if (!j) s[j] = t;
        else s[j] = s[j-1];
    }
  }
}

void rotate_b(char * s, char a) {
  int index = 1;
  int t_index = 0;
  
  while(1) {
   rotate_l(s, index);

   for(t_index = 0; t_index < strlen(s); t_index++) if (s[t_index] == a) break;
   if (t_index >= 4) t_index++;
   t_index++;

   if(index == t_index) break;

   // revert the process   
   rotate_r(s, index);
   index++;
  }
}

void reverse(char * s, int x, int y) {
  for(int i = 0; i <= (y-x)/2; i++) {
    char ch = s[y-i];
    s[y-i] = s[x+i];
    s[x+i] = ch;
  }
}

void move(char * s, int x, int y) {
  char temp[strlen(s)];
  char ch = s[x];

  // remove the character at position x
  for(int i = 0, j = 0; i < strlen(s); i++) {
    if (i != x) {
      temp[j] = s[i];
      j++;
    } 
  }

  // insert the character at position y
  for(int i = 0, j = 0; i < strlen(s); i++) {
    if (i != y) {
      s[i] = temp[j];
      j++;
    } else {
      s[i] = ch;
    }
  }
}

int main(int argc, char ** argv) {
  char input[9] = "fbgdceah\0";
  char instr[200][100];
  int x, y, k;
  char a, b;


  while(fgets(instr[k], 200, stdin) != NULL) {
    k++;
  }

  while(k >= 0) {
    if (sscanf(instr[k], "swap position %d with position %d", &x, &y) == 2) swap(input, y, x);
    if (sscanf(instr[k], "swap letter %c with letter %c", &a, &b) == 2) swap_l(input, b, a);
    if (sscanf(instr[k], "rotate left %d steps", &x) == 1) rotate_r(input, x);
    if (sscanf(instr[k], "rotate right %d steps", &x) == 1) rotate_l(input, x);
    if (sscanf(instr[k], "rotate based on position of letter %c", &a) == 1) rotate_b(input, a);
    if (sscanf(instr[k], "reverse positions %d through %d", &x, &y) == 2) reverse(input, x, y);
    if (sscanf(instr[k], "move position %d to position %d", &x, &y) == 2) move(input, y, x);
    k--;
  }

  printf("part 2 %s\n", input);
}
