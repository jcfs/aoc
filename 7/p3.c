#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct instruction {
    int type;
    int op1;
    int op2;
    int op1_t;
    int op2_t;
    int output;
} instruction;

instruction instr[1000];
unsigned short wires[1000] = {33};

int wire_to_int(char * wire) {
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

void print_instr(instruction i) {
    printf("type: %d output wire: %d - op1=%d:%d wire2=%d:%d ", i.type, i.output, i.op1, i.op1_t,i.op2,i.op2_t );
    printf("output wire value: %d\n", wires[i.output]);
}

// evaluates the given instruction
short eval(instruction * i) {

    short op1 = (i->op1_t) ? (wires[i->op1] != 33 ? wires[i->op1] : eval(get(i->op1))) : i->op1;
    short op2 = (i->op2_t) ? (wires[i->op2] != 33 ? wires[i->op2] : eval(get(i->op2))) : i->op2;

    if (i->type == 5) {
        return wires[i->output] = op1;
    } else if (i->type == 4) {
        return wires[i->output] = op1 >> op2; 
    } else if (i->type == 3) {
        return wires[i->output] = op1 << op2;
    } else if (i->type == 2) {
        return wires[i->output] = ~op1; 
    } else if (i->type == 1) {
        return wires[i->output] = op1 | op2;
    } else if (i->type == 0) {
        return wires[i->output] = op1 & op2;
    }

    return wires[i->output];

}

int main(int argc, char ** argv) {
    char left[64];
    char right[64];
    char op1[64];
    char op2[64];
    int c = 0;

    for(c=0;c<1000;c++)wires[c]=33;
    c=0;
    while(scanf("%20[0-9a-zA-Z ] -> %s\n", left, right) != -1) {
        bzero((char*)op1, 64); 
        bzero((char*)op2, 64); 
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
            sscanf(left, "%s LSHIFT %s", op1, op2);
            instr[c].type = 3;
        } else if (strstr(left, "RSHIFT")){
            sscanf(left, "%s RSHIFT %s", op1, op2);
            instr[c].type = 4;
        } else {
            sscanf(left, "%s", &op1);
            instr[c].type = 5;
        }

        instr[c].output = wire_to_int(right);
        instr[c].op1_t = 0;
        instr[c].op2_t = 0;

        if (op1[0]-'a' >= 0) {
            instr[c].op1_t = 1;
            instr[c].op1 = wire_to_int(op1);
        } else {
            instr[c].op1 = atoi(op1);
        }

        if (op2[0]-'a' >= 0) {
            instr[c].op2_t = 1;
            instr[c].op2 = wire_to_int(op2);
        } else {
            instr[c].op2 = atoi(op2);
        }
        c++;
    }   

    printf("eval\n");
    eval(get(0));
    printf("Result %d\n", wires[0]);
}
