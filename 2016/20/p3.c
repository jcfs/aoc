#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool r[UINT32_MAX];

int main(int argc, char ** argv) {
  uint32_t l, h;

  while(scanf("%u-%u", &l, &h) == 2) {
    memset(r+l, true, h-l+1);
  }

  bool p1 = false;
  uint32_t count = 0;
  for(uint64_t i = 0; i <= UINT32_MAX; i++) {
    if (!r[i]) {
      if (!p1) printf("part 1 %llu\n", i) && (p1 = true);
      count++;
    }
  }
  printf("part 2 %d\n", count);
}
