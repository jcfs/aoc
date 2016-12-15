#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

uint32_t disc_p[64];
uint32_t disc_s[64];

int main(int argc, char ** argv) {
  uint32_t disc, pos, init, time = 0, count;

  while(scanf("Disc #%d has %d positions; at time=0, it is at position %d.\n", &disc, &pos, &init) == 3) {
    disc_p[disc] = pos;
    disc_s[disc] = init;
  } 

  // stupid straigh forward algorithm, just keep increasing the time and check if they are aligned

  while(count != disc) {
    count = 0;
    for(int i = 1; i < disc + 1; i++) 
      if (!((disc_s[i] + (time + i)) % disc_p[i])) 
        count++;;

    time++;
  }

  printf("%d\n", time - 1);

}
