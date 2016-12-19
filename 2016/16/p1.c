/* compile gcc -o p1 p1.c -Wall -O3 */
/* solution to part 1 and part 2 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char * get_checksum(char * input_s, int input_n) {
  char * a = calloc((input_n * 4 + 2), sizeof(char));
  uint32_t l = strlen(input_s);

  memcpy(a, input_s, l);

  for(; l < input_n; a[l] = '0', l = l * 2 + 1) 
    for(int i = 0, l2 = l * 2; i < l; i++) 
      a[l2 - i] = (~(a[i] ^ '0') & 1);
  // truncate the result to the chars needed
  a[input_n] = 0;

  do {
    for(int i = 0, j = 0; i < input_n; i += 2, j++) 
      a[j] = (~(a[i] ^ a[i+1]) & 1) + '0';

    input_n /= 2;
  } while(!(input_n % 2));

  a[input_n] = 0;
  
  return a;
}

int main(int argc, char ** argv) {
  char * input_s = "11011110011011101";

  printf("part1 %s\n", get_checksum(input_s, 272));
  printf("part2 %s\n", get_checksum(input_s, 35651584));
}
