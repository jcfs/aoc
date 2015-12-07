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
unsigned short wires[1000];

int wire_to_int(char * wire) {
    int result = 0;
    int i;

    for(i = 1; i <= strlen(wire); i++) { 
        result += (wire[i-1]-'a')+(strlen(wire)-i)*26*(wire[i-1]-'a'+1);
    }

    return result;
}

instruction get(int wire) {
    int i = 0;

    for(i = 0; i < 1000; i++) {
        if (instr[i].output == wire) {
            return instr[i];
        }
    }
}

void print_instr(instruction i) {
    printf("type: %d output wire: %d - wire1:%d wire2:%d\n", i.type, i.output, i.op1, i.op2);
    printf("output wire value: %d\n", wires[i.output]);
}


short eval(instruction * i) {

    short op1 = (i->op1_t) ? eval(get(i->op1)) : i->op1;
    short op2 = (i->op2_t) ? eval(get(i->op2)) : i->op2;

    if (i->type == 5) {
        return wires[i->output] = op1;
    }
}

void eval_instruction(instruction i) {
    if (i.type == 5) {
        if(i.op1_t)  eval_instruction(get(i.op1));
        wires[i.output] = ((i.op1_t) ? wires[i.op1] : i.op1 ) ;
    } else if (i.type == 4) {
        eval_instruction(get(i.op1));
        wires[i.output] = wires[i.op1] >> i.op2;
    } else if (i.type == 3) {
        eval_instruction(get(i.op1));
        wires[i.output] = wires[i.op1] << i.op2;
    } else if (i.type == 2) {
        eval_instruction(get(i.op1));
        wires[i.output] = ~wires[i.op1];
    } else if (i.type == 1) {
        eval_instruction(get(i.op1));
        eval_instruction(get(i.op2));
        wires[i.output] = wires[i.op1] | wires[i.op2];
    } else if (i.type == 0) {
        if (i.op1_t) eval_instruction(get(i.op1));
        if (i.op2_t) eval_instruction(get(i.op2));
        wires[i.output] = ((i.op1_t) ? wires[i.op1] : i.op1 ) & ((i.op2_t) ? wires[i.op2] : i.op2_t);;
    }
}


int main(int argc, char ** argv) {
    char left[64];
    char right[64];
    char op1[64];
    char op2[64];
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

    eval_instruction(get(0));
    printf("Result %d\n", wires[0]);
}
