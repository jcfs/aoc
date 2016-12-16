#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// reverse a string of l length
void reverse_s(char * s, int l) {
  for(int i = 0; i < l/2; i++) {
    int j = l - i - 1;
    s[i] ^= s[j] ^= s[i] ^= s[j];
  }
}

// invert the bits on a string of "101101001"
void invert(char *s, int l) {
  for(int  i = 0; i < l; i++) 
    s[i] = (s[i] == '0') ? '1' : '0';
}

void concat(char *a, char * b, int l) {
  a[l] = '0';
  memcpy(a+l+1, b, l);
}

void get_checksum(char * input_s, int input_n) {
  int l = input_n * 2 + 1;
  char * a = calloc(l, sizeof(char));
  char * b = calloc(l, sizeof(char));

  strcpy(a, input_s);
  l = strlen(a);

  while(l < input_n) {
    memcpy(b, a, l);
    reverse_s(b, l);
    invert(b, l);
    concat(a, b, l);
    l = l * 2 + 1;
  }
  // truncate the result to the chars needed
  a[input_n] = 0;

  do {
    for(int i = 0, j = 0; i < input_n; i+=2, j++) {
      a[j] = (a[i] == a[i+1]) ? '1' : '0';
      a[j+1] = 0;
    }
    input_n /= 2;
  } while(!(input_n % 2));

  printf("final cs %s\n", a);

  free(a);
  free(b);
}

int main(int argc, char ** argv) {
  char * input_s = "11011110011011101";

  get_checksum(input_s, 272);
  get_checksum(input_s, 35651584);
}
