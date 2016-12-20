/* compile gcc -o p2 p2.c -O3 -Wall */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint64_t low;
  uint64_t high;
} range_t;

range_t r[2000];

int compare(const void * a, const void * b) {
  return (((range_t *)a)->low > ((range_t *)b)->low) ? 1 : -1;
}

int main(int argc, char ** argv) {
  uint64_t i = 0, k = 0;

  while(scanf("%lld-%lld", &r[k].low, &r[k].high) == 2) {
    k++;
  }

  // sort the input
  qsort (r, k, sizeof(range_t), compare);

  k = 0;

  while(i <= UINT32_MAX) {
    uint64_t low = r[k].low;
    uint64_t high = r[k].high;

    if (i < low) {
      // if we are below the current low, then this is a valid ip address
      // we break out of the cycle
      break;
    } else if (i <= high) {
      // if we are above the low and below the high 
      // we skip to the current high + 1
      i = high + 1;
    } else { 
      // if we are above the high we keep the current ip 
      // and proceed to the next range
      k++;
    }
  }

  printf("part 1: %lld\n", i);
}
