/* compile gcc -o p1 p1.c -Wall */
/* solution for both p1 and p2 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

char cmd[300][80];
uint8_t out[300];
uint32_t chips[300];

// get the high chip of the bot
uint32_t high(int bot) {
  int c1 = chips[bot] & 0xffff;
  int c2 = chips[bot] >> 16;

  return (c1 > c2) ? c1 : c2;
}

// get the low chip of the bot
uint32_t low(int bot) {
  int c1 = chips[bot] & 0xffff;
  int c2 = chips[bot] >> 16;

  return (c1 < c2) ? c1 : c2;
}

void give_c(int bot, uint32_t chip) {
  uint32_t c = chips[bot];

  // these conditions only work because we never have a bot receive a chip if it already has 2
  if (!(c & 0xffff)) c |= (chip & 0xffff);
  else if (!(c >> 16)) c |= (chip << 16);

  chips[bot] = c;

  // solution for part 1, the bot that currently owns chip 17 and chip 61
  if (low(bot) == 17 && high(bot) == 61) 
    printf("Part 1: %d\n", bot);
}

int main(int argc, char ** argv) {
  int i = 0, chip_count = 0, arg1, arg2, arg3;

  while(fgets(cmd[i], 300, stdin) != NULL) {
    if (sscanf(cmd[i++], "value %d goes to bot %d\n", &arg1, &arg2) == 2) {
      give_c(arg2, arg1);
      chip_count++;
    }
  }

  while(chip_count) {
    for(int j = 0; j < i; j++) {
      // we just need the lines that start with bot %d, all 
      // the other lines are already processed
      if (sscanf(cmd[j], "bot %d", &arg1) == 1) {
        
        // we just process the command if the bot has two chips 
        if (!low(arg1) || !high(arg1)) 
          continue;

        char type_l[10] = {[0 ... 9] = 0};
        char type_h[10] = {[0 ... 9] = 0}; 

        // input parsing over and over
        if (sscanf(cmd[j], "bot %d gives low to %s %d and high to %s %d\n", &arg1, type_l, &arg2, type_h, &arg3) == 5) {
          !strcmp(type_l, "bot") ? give_c(arg2, low(arg1)) : (out[arg2] = low(arg1)) | chip_count--;
          !strcmp(type_h, "bot") ? give_c(arg3, high(arg1)) : (out[arg3] = high(arg1)) | chip_count--;
        }
      
        // this bot has no more chips
        chips[arg1] = 0;
      }
    }
  }

  printf("Part 2: %d\n", out[0] * out[1] * out[2]);
}
