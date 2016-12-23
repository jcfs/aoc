/* compile with gcc -o p2 p2.c -Wall */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ARG_V(in, k) ((in.reg[k]) ? reg[in.reg[k] - 'a'] : in.val[k])

int64_t reg[4] = {12, 0, 1, 0};

const char * opcode_n[6] = {"cpy", "inc", "dec", "jnz", "tgl", "mul"};

typedef enum {
  cpy, inc, dec, jnz, tgl, mul
} opcode;

typedef struct {
  opcode code;
  int32_t val[3];
  char reg[3];
} instr;

instr program[200];

// pretty print the instruction - it could be better tho
void print_i(instr * i) {
  printf("%s (%d %d %d) [%c:%lld] [%c:%lld] [%c:%lld]\n", opcode_n[i->code],
    i->val[0], i->val[1], i->val[2], 
    (i->reg[0]) ? i->reg[0] : '*', (i->reg[0]) ? reg[i->reg[0] -'a'] : 0, 
    (i->reg[1]) ? i->reg[1] : '*', (i->reg[1]) ? reg[i->reg[1] -'a'] : 0,
    (i->reg[2]) ? i->reg[2] : '*', (i->reg[2]) ? reg[i->reg[2] -'a'] : 0);
}

// toggle an instruction according to the rules
void toggle_i(instr * i) {
  switch(i->code) {
    case jnz: i->code = cpy; break;
    case cpy: i->code = jnz; break;
    case inc: i->code = dec; break;
    case dec: i->code = inc; break;
    case tgl: i->code = inc; break;
    default: break;
  }
}

int main(int agrc, char ** argv) {
  int64_t n = 0, pc = 0, count = 0;
  char cmd[200];

  while(fgets(cmd, 200, stdin)) {
    instr * p = &program[n];
    char * s = cmd+3, r = 0;

    // parse the input... wtf am I doing...
    for(int32_t o = 0, v = 0; o < 3 && s != NULL; o++, s=strchr(s+1, ' ')) {
      if (sscanf(s+1, "%d", &v) == 1) 
        p->val[o] = v;
      else if (sscanf(s+1, "%c", &r) == 1) 
        p->reg[o] = r;
    }

    // fill the opcode id
    for(int k = 0; k < 6; k++) {
      if (!strncmp(cmd, opcode_n[k], 3)) p->code = k;
    }

    // lets print it just to make sure it is ok
    print_i(p);
    n++;
  }

  printf("Loaded %lld instructions [pc %lld]\n", n, pc);

  // main execution loop
  for(pc = 0; pc < n; pc++, count++) {
    instr in = program[pc];

    switch(in.code) {
      case cpy: reg[in.reg[1] - 'a'] = ARG_V(in, 0); break;
      case inc: reg[in.reg[0] - 'a']++; break;
      case dec: reg[in.reg[0] - 'a']--; break;
      case jnz: if (ARG_V(in, 0)) pc += ARG_V(in, 1) - 1; break;
      case tgl: toggle_i(&program[pc + ARG_V(in, 0)]); break;
      case mul: reg[in.reg[2] - 'a'] = ARG_V(in, 0) * ARG_V(in, 1); break;
    }
  }

  printf("Executed %lld instructions\n", count);
  for(int j = 0; j < 4; j++) 
    printf("reg [%c] = %lld\n", j + 0x61, reg[j]); 

} 
