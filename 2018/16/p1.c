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

int op, a, b, c;

int main() {
  int n = 0;

  int r1, r2, r3, r4;
  int f1, f2, f3, f4;
  int result = 0;
  int e = 1;

  while(scanf("Before: [%d, %d, %d, %d]\n", &r1, &r2, &r3, &r4) != -1) {
    scanf("%d %d %d %d\n", &op, &a, &b, &c);
    scanf("After: [%d, %d, %d, %d]\n", &f1, &f2, &f3, &f4);

    int cn = 0;

    for(int i = 0; i < 16; i++) {
      reg[0] = r1;
      reg[1] = r2;
      reg[2] = r3;
      reg[3] = r4;

      (*func_ptr[i])(a, b, c);

      if (f1 == reg[0] && f2 == reg[1] && f3 == reg[2] && f4 == reg[3]) {
        cn++;
      }
    }
    if (cn > 2) result++;
  }

  printf("%d\n", result);
}
