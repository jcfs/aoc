/* compile with gcc -o p2 p2.c -Wall */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

char cmd[40][200];
uint64_t reg[4] = {12, 0, 0, 0};

void toggle(int t) {
  if (strstr(cmd[t], "jnz")) {
    memcpy(cmd[t], "cpy", 3);
  } else if (strstr(cmd[t], "cpy")) {
    memcpy(cmd[t], "jnz", 3);
  } else if (strstr(cmd[t], "inc")) {
    memcpy(cmd[t], "dec", 3);
  } else if (strstr(cmd[t], "dec")) {
    memcpy(cmd[t], "inc", 3);
  } else if (strstr(cmd[t], "tgl")) {
    memcpy(cmd[t], "inc", 3);
  }
}

int main(int agrc, char ** argv) {
  int i = 0;
  int pc = 0;

  while(fgets(cmd[i++], 200, stdin));

  while(cmd[pc][0]) {
    int val, val1;
    char re, ri, rs;
    if (sscanf(cmd[pc], "cpy %d %c", &val, &re) == 2) reg[re - 'a'] = val;
    else if (sscanf(cmd[pc], "cpy %c %c", &ri, &re) == 2) reg[re - 'a'] = reg[ri - 'a'];
    else if (sscanf(cmd[pc], "inc %c", &re) == 1) reg[re-'a']++;
    else if (sscanf(cmd[pc], "dec %c", &re) == 1) reg[re-'a']--;
    else if (sscanf(cmd[pc], "jnz %d %d", &val, &val1) == 2) {if (val) pc += val1 - 1;}
    else if (sscanf(cmd[pc], "jnz %c %d", &re, &val) == 2) {if (reg[re - 'a']) pc += val - 1;}
    else if (sscanf(cmd[pc], "jnz %d %c", &val, &re) == 2) {if (val) pc += reg[re-'a'] - 1;}
    else if (sscanf(cmd[pc], "tgl %d", &val) == 1) toggle(pc + val);
    else if (sscanf(cmd[pc], "tgl %c", &re) == 1) toggle(pc + reg[re-'a']);
    else if (sscanf(cmd[pc], "mul %c %c %c", &re, &ri, &rs) == 3) {
      reg[rs-'a'] = reg[ri-'a'] * reg[re-'a'];
    }

    pc++;
  }

  for(int j = 0; j < 4; j++) 
    printf("Reg %c = %lld\n", j + 0x61, reg[j]); 

} 
