#include <stdio.h>

typedef struct {
    char opcode[64];
    char op1[64];
    char op2[64];
} instruction;

instruction inst[1000];
long long reg[2];
int pc = 0;

int main(int argc, char ** argv) {
    int i = 0;

    while(1) {
        if (scanf("%s", &inst[i].opcode) == -1) break;

        scanf("%s", &inst[i].op1);
        if (strncmp(inst[i].opcode, "jie", 3) == 0) {
            inst[i].op1[1] = 0;
            scanf("%s", &inst[i].op2);
        }

        if (strncmp(inst[i].opcode, "jio", 3) == 0) {
            inst[i].op1[1] = 0;
            scanf("%s", &inst[i].op2);
        }

        i++;
    }

    while(inst[pc].opcode[0] != 0) {
        if (!strncmp(inst[pc].opcode, "inc", 3)) reg[inst[pc].op1[0]-'a']++;
        if (!strncmp(inst[pc].opcode, "jio", 3)) {
            if (reg[inst[pc].op1[0]-'a']==1) {
                pc += atoi(inst[pc].op2);
                continue;
            }
        }
        if (!strncmp(inst[pc].opcode, "jie", 3)) {
            if (!((reg[inst[pc].op1[0]-'a'])%2)) {
                pc += atoi(inst[pc].op2);
                continue;
            }
        }
 
        if (!strncmp(inst[pc].opcode, "tpl", 3)) reg[inst[pc].op1[0]-'a'] *= 3;
        if (!strncmp(inst[pc].opcode, "hlf", 3)) reg[inst[pc].op1[0]-'a'] /= 2;
        if (!strncmp(inst[pc].opcode, "jmp", 3)) {
            pc +=atoi(inst[pc].op1);
            continue;
        }

        pc++;
    }

    printf("%d\n", reg[0]);
    printf("%d\n", reg[1]);


}
