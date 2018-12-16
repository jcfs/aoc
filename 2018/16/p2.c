#include <stdio.h>

typedef struct i {
  int op;
  int a, b, c;
} inst;

inst code[1000];
int reg[4];

void addr(int a, int b, int c) {
  reg[c] = reg[a] + reg[b]; 
}

void addi(int a, int b, int c) {
  reg[c] = reg[a] + b;
}

void mulr(int a, int b, int c) {
  reg[c] = reg[a]*reg[b];
}

void muli(int a, int b, int c) {
  reg[c] = reg[a] * b;
}

void banr(int a, int b, int c) {
  reg[c] = reg[a] & reg[b];
}

void bani(int a, int b, int c) {
  reg[c] = reg[a] & b;
}

void borr(int a, int b, int c) {
  reg[c] = reg[a] | reg[b];
}

void bori(int a, int b, int c) {
  reg[c] = reg[a] | b;
}

void setr(int a, int b, int c) {
  reg[c] = reg[a];
}

void seti(int a, int b, int c) {
  reg[c] = a;
}

void gtir(int a, int b, int c) {
  reg[c] = a > reg[b];
}

void gtri(int a, int b, int c) {
  reg[c] = reg[a] > b;
}

void gtrr(int a, int b, int c) {
  reg[c] = reg[a] > reg[b];
}

void eqir(int a, int b, int c) {
  reg[c] = a == reg[b];
}

void eqri(int a, int b, int c) {
  reg[c] = reg[a] == b;
}

void eqrr(int a, int b, int c) {
  reg[c] = reg[a] == reg[b];
}

void (*func_ptr[16])(int a, int b, int c) = {addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr};

char * names[16] = {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"};

int op, a, b, c;

int f[16];

int ispowerof2(unsigned int x) {
  return x && !(x & (x - 1));
}

int main() {
  int n = 0;

  int r1, r2, r3, r4;
  int f1, f2, f3, f4;
  int result = 0, k;

  for(int i = 0; i < 16; i++) f[i] = 0xffffffff;
  int e = 0;

  while(scanf("Before: [%d, %d, %d, %d]\n", &r1, &r2, &r3, &r4) != -1) {
    scanf("%d %d %d %d\n", &op, &a, &b, &c);
    scanf("After:  [%d, %d, %d, %d]\n", &f1, &f2, &f3, &f4);

    int cn = 0;

    k = 0;

    for(int i = 0; i < 16; i++) {
      reg[0] = r1;
      reg[1] = r2;
      reg[2] = r3;
      reg[3] = r4;

      (*func_ptr[i])(a, b, c);

      if (f1 == reg[0] && f2 == reg[1] && f3 == reg[2] && f4 == reg[3]) {
        k = k | (1 << i);
      }
    }

    f[op] = f[op] & k;
    e++;
    if (e==824)break;
  }

  int y = 1;

  // reduce to find the opcodes
  while(y) {
    y = 0;
    for(int i = 0; i < 16; i++) {
      if (ispowerof2(f[i])) {
        for(int l = 0; l < 16; l++) {
          if (l == i) continue;
          if (!(f[l] & f[i])) continue;
          int x = f[l];
          f[l] = f[l] & (~f[i]);
          y = 1;
        }
      }
    }
  }

  for(int i = 0; i < 16; i++) {
    int u = 0;
    for(int j = 0; j < 16; j++) {
      if (f[i] & 1) break;
      f[i] = f[i] >> 1;
      u++;
    }
    f[i] = u;
    printf("%d %s\n", i, names[u]);
  }


  reg[0] = reg[1] = reg[2] = reg[3] = 0;

  while(scanf("%d %d %d %d\n", &op, &a, &b, &c) != -1) {
    (*func_ptr[f[op]])(a, b, c);
  }

  printf("%d\n", reg[0]);
}
