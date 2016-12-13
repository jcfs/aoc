/* compile with gcc -o p1 p1.c -Wall */
#include <stdio.h>

char cmd[40][200];
int reg[4] = {[0 ... 3] = 0};

int main(int agrc, char ** argv) {
  int i = 0;
  int pc = 0;
  
  while(fgets(cmd[i++], 200, stdin));

  while(cmd[pc][0]) {
    int val, val1;
    char re, ri;
    if (sscanf(cmd[pc], "cpy %d %c", &val, &re) == 2) reg[re - 'a'] = val;
    else if (sscanf(cmd[pc], "cpy %c %c", &ri, &re) == 2) reg[re - 'a'] = reg[ri - 'a'];
    else if (sscanf(cmd[pc], "inc %c", &re) == 1) reg[re-'a']++;
    else if (sscanf(cmd[pc], "dec %c", &re) == 1) reg[re-'a']--;
    else if (sscanf(cmd[pc], "jnz %c %d", &re, &val) == 2) if (reg[re - 'a']) pc += val - 1;
    else if (sscanf(cmd[pc], "jnz %d %d", &val, &val1) == 2) if (val) pc += val1 - 1;

    pc++;
  }

  for(int j = 0; j < 4; j++) printf("Reg %c = %d\n", j + 0x61, reg[j]); 

} 
