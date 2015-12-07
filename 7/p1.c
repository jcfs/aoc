#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct instruction {
    char type;
    int op1;
    int op2;
    int op3;
    int op1_t;
    int op2_t;
    int output;
} instruction;

instruction instr[1000];
unsigned short wires[1000];
char wires_eval[1000];

int scalar(char * wire) {
    int result = 0;
    int i;

    for(i = 1; i <= strlen(wire); i++) { 
        result += (wire[i-1]-'a')+(strlen(wire)-i)*26*(wire[i-1]-'a'+1);
    }

    return result;
}

instruction * get(int wire) {
    int i = 0;

    for(i = 0; i < 1000; i++) {
        if (instr[i].output == wire) {
            return &instr[i];
        }
    }

    return NULL;
}

short eval(int wire, int type) {
    instruction * i = get(wire);

    printf("%d\n", wire);
    if (!type) return wire;
    if (wires_eval[i->output]) return wires[i->output];


    if (i->type == 5) {
        wires[i->output] = eval(i->op1, i->op1_t);
        printf("wire:%d type:%d op1:%d op1_t:%d = %d\n", wire, type, i->op1, i->op1_t, wires[i->output]);
    } else if (i->type == 4) {
        eval(i->op1, i->op1_t);
        wires[i->output] = wires[i->op1] >> i->op3;
    } else if (i->type == 3) {
        eval(i->op1, i->op1_t);
        wires[i->output] = wires[i->op1] << i->op3;
    } else if (i->type == 2) {
        eval(i->op1, i->op1_t);
        wires[i->output] = ~wires[i->op1];
    } else if (i->type == 1) {
        eval(i->op1, i->op1_t);
        eval(i->op2, i->op2_t);
        wires[i->output] = wires[i->op1] | wires[i->op2];
    } else if (i->type == 0) {
        if (i->op1_t) eval(i->op1, i->op1_t);
        if (i->op2_t) eval(i->op2, i->op2_t);
        wires[i->output] = ((i->op1_t) ? wires[i->op1] : i->op1 ) & ((i->op2_t) ? wires[i->op2] : i->op2_t);
    }
    
    wires_eval[i->output] = 1;
}


int main(int argc, char ** argv) {
    char left[64];
    char right[64];
    char op1[64];
    char op2[64];
    int op3;
    int c = 0;

    while(scanf("%20[0-9a-zA-Z ] -> %s\n", left, right) != -1) {
        if (strstr(left, "AND")) {
            sscanf(left, "%s AND %s", op1, op2);
            instr[c].type = 0;
        } else if (strstr(left, "OR")) {
            sscanf(left, "%s OR %s", op1, op2);
            instr[c].type = 1;
        } else if (strstr(left, "NOT")) {
            sscanf(left, "NOT %s", &op1);
            instr[c].type = 2;
        } else if (strstr(left, "LSHIFT")){
            sscanf(left, "%s LSHIFT %d", op1, &op3);
            instr[c].type = 3;
        } else if (strstr(left, "RSHIFT")){
            sscanf(left, "%s RSHIFT %d", op1, &op3);
            instr[c].type = 4;
        } else {
            sscanf(left, "%s", &op1);
            instr[c].type = 5;
        }

        instr[c].output = scalar(right);

        instr[c].op1_t = 1;
        instr[c].op2_t = 1;
        if (op1[0]-'a' >= 0) {
            instr[c].op1_t = 1;
            instr[c].op1 = scalar(op1);
        } else {
            instr[c].op1_t = 0;
            instr[c].op1 = atoi(op1);
        }
        
        if (op2[0]-'a' >= 0) {
            instr[c].op2_t = 1;
            instr[c].op2 = scalar(op2);
        } else {
            instr[c].op2 = atoi(op2);
            instr[c].op2_t = 0;
        }

        instr[c++].op3 = op3;
    }   

    eval(0, 1);
    printf("%d\n", wires[0]);
}
