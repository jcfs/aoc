#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_table(int table[5]) {
  for(int i = 0; i < 5; i++) printf("elf %d has %d presents\n", i, table[i]);
  printf("------------\n");
}
uint32_t table[3001330];
int main(int argc, char ** argv) {
  int input = 3001330, index = 0;

  
  for(int i = 0; i < input; i++) table[i] = 1;
  while(1) {
    if (!table[index]) {
      index = (index + 1) % input;
      continue;
    }
    int k = 0;
    int j = 0;
    for(j = (index + 1) % input;; j = (j + 1) % input) {
      if (table[j]) {
        k = table[j];
        table[j] = 0;
        break;
      }
    }
    table[index] += k;
    if (table[index] == input) {
      printf("%d\n", index+1);
      exit(1);
    }
    index = (j + 1) % input;
  }

}
