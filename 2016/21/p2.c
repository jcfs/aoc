/* compile gcc -o p2 p2.c -O3 -Wall */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// swap character at position x with character at position y
void swap(char * s, int x, int y) {
  s[x] ^= s[y] ^= s[x] ^= s[y];
}

// swap character a with character b
void swap_c(char * s, char a, char b) {
  for(int i = 0; i < strlen(s); i++) {
    if (s[i] == a) s[i] = b;
    else if (s[i] == b) s[i] = a;
  }
}

// rotate the string s left x times
void rol(char * s, int x) {
  for(int i = 0; i < x; i++) {
    for(int j = 0, t = s[0]; j < strlen(s); j++) {
      s[j] = (j == strlen(s) - 1) ? t : s[j+1];
    }
  }
}

// rotate the string s right x times
void ror(char * s, int x) {
  for(int i = 0; i < x; i++) {
    for(int j = strlen(s) - 1, t = s[strlen(s) - 1]; j >= 0; j--) {
      s[j] = (j) ? s[j-1] : t;
    }
  }
}

// inverse function of part one function:
// rotate the string s right X times, where X is the position
// of character a on the string, plus one, and plus one if the character 
// position is ge than four
void rob(char * s, char a) {
  int n = 1;
  int target_n = 0;

  while(1) {
    //rotate the string left n times
    rol(s, n);

    // calculate the target n after the string is rotated left
    for(target_n = 0; target_n < strlen(s); target_n++) 
      if (s[target_n] == a) 
        break;

    target_n += (target_n >= 4) ? 2 : 1;

    //if the target n and n are then same then we successfully found
    //the reverse of the function 
    if(n == target_n) 
      break;

    // revert the process   
    ror(s, n++);
  }
}

// reverts the character os the string s between x and y
void reverse(char * s, int x, int y) {
  for(int i = 0; i <= (y-x)/2; i++) {
    char ch = s[y-i];
    s[y-i] = s[x+i];
    s[x+i] = ch;
  }
}

// move the character at position x to the position y
void move(char * s, int x, int y) {
  char temp[strlen(s)];
  char ch = s[x];

  // remove the character at position x
  for(int i = 0, j = 0; i < strlen(s); i++) {
    if (i != x) {
      temp[j++] = s[i];
    } 
  }

  //temp now holds the original string without the character at
  //position x which is saved in var ch

  // insert the character at position y
  // we copy all the charaters in temp to s, except if we reach
  // the index y we insert the saved ch character
  for(int i = 0, j = 0; i < strlen(s); i++) {
    s[i] = (i != y) ? temp[j++] : ch;
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
    if (sscanf(instr[k], "swap letter %c with letter %c", &a, &b) == 2) swap_c(input, b, a);
    if (sscanf(instr[k], "rotate left %d steps", &x) == 1) ror(input, x);
    if (sscanf(instr[k], "rotate right %d steps", &x) == 1) rol(input, x);
    if (sscanf(instr[k], "rotate based on position of letter %c", &a) == 1) rob(input, a);
    if (sscanf(instr[k], "reverse positions %d through %d", &x, &y) == 2) reverse(input, x, y);
    if (sscanf(instr[k], "move position %d to position %d", &x, &y) == 2) move(input, y, x);
    k--;
  }

  printf("part 2 %s\n", input);
}
