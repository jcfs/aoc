/* compile gcc -o p1 p1.c -O3 -Wall */
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
  int index = 0;
  for(index = 0; index < strlen(s); index++) if (s[index] == a) break;
  if (index >= 4) index++;

  rotate_r(s, ++index);
}

void reverse(char * s, int x, int y) {
  for(int i = 0; i <= (y-x)/2; i++) {
    char ch = s[y-i];
    s[y-i] = s[x+i];
    s[x+i] = ch;
  }
}

void move(char * s, int x, int y) {
  char ch = s[x];

  char * temp = calloc(strlen(s)+1, sizeof(char));

  for(int i = 0, j = 0; i < strlen(s); i++) {
    if (i != x) {
      temp[j] = s[i];
      j++;
    } 
  }

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
  char  input[9] = "abcdefgh\0";
  char instr[200];
  int x, y;
  char a, b;

  while(fgets(instr, 200, stdin) != NULL) {
    if (sscanf(instr, "swap position %d with position %d", &x, &y) == 2) swap(input, x, y);
    if (sscanf(instr, "swap letter %c with letter %c", &a, &b) == 2) swap_l(input, a, b);
    if (sscanf(instr, "rotate left %d steps", &x) == 1) rotate_l(input, x);
    if (sscanf(instr, "rotate right %d steps", &x) == 1) rotate_r(input, x);
    if (sscanf(instr, "rotate based on position of letter %c", &a) == 1) rotate_b(input, a);
    if (sscanf(instr, "reverse positions %d through %d", &x, &y) == 2) reverse(input, x, y);
    if (sscanf(instr, "move position %d to position %d", &x, &y) == 2) move(input, x, y);
  }

  printf("part1 %s\n", input);
}
