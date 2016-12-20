/* compile gcc -o p2 p2.c -O3 -Wall */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint32_t low;
  uint32_t high;
} range_t;

range_t r[2000];
uint32_t ind = 0;

int compare(const void * a, const void * b) {
  range_t * a1 = (range_t *)a;
  range_t * b1 = (range_t *)b;

  if (a1->low > b1->low) return 1;
  else if (a1->low < b1->low) return -1;
  else return 0;
}

int main(int argc, char ** argv) {
  uint32_t l, h;

  while(scanf("%d-%d", &l, &h) == 2) {
    r[ind].low = l;
    r[ind].high = h;
    ind++;
  }

  qsort (r, ind, sizeof(range_t), compare);

  int count = 0;
  for(uint64_t i = 0, index = 0; i < UINT32_MAX; i++) {
    uint32_t low = r[index].low;
    uint32_t high = r[index].high;

    if (i < low) {
      count++;
    } else {
      if (i <= high) {
        i = high;
        continue;
      }
      index++;
      i--;
    }
  }
  printf("part 2: %d\n", count);
}
