#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct instruction {
    int type;
    int op1;
    int op2;
    int op3;
    int op1_t;
    int op2_t;
    int output_wire;
} instruction;

instruction instruction_set[1000];
unsigned short wires[1000];
char wires_eval[1000];

int wire_to_int(char * wire) {
    int result = 0;
    int i;

    for(i = 1; i <= strlen(wire); i++) { 
        result += (wire[i-1]-'a')+(strlen(wire)-i)*26*(wire[i-1]-'a'+1);
    }

    return result;
}

instruction get_output_instruction(int wire) {
    int i = 0;

    for(i = 0; i < 1000; i++) {
        if (instruction_set[i].output_wire == wire) {
            printf("%d\n", instruction_set[i].output_wire);
            return instruction_set[i];
        }
    }
}

int is_active(int wire) {
    return wires_eval[wire];
}


void print_instr(instruction i) {
    printf("type: %d output wire: %d - wire1:%d wire2:%d - op:%d\n", i.type, i.output_wire, i.op1, i.op2, i.op3);
    printf("output wire value: %d\n", wires[i.output_wire]);
}
void eval_instruction(instruction i) {


    if (i.type == 5) {
        if(i.op1_t && !is_active(i.op1))  eval_instruction(get_output_instruction(i.op1));
        wires[i.output_wire] = ((i.op1_t) ? wires[i.op1] : i.op1 ) ;
    } else if (i.type == 4) {
        if (!is_active(i.op1)) eval_instruction(get_output_instruction(i.op1));
        wires[i.output_wire] = wires[i.op1] >> i.op3;
    } else if (i.type == 3) {
        if (!is_active(i.op1)) eval_instruction(get_output_instruction(i.op1));
        wires[i.output_wire] = wires[i.op1] << i.op3;
    } else if (i.type == 2) {
        if (!is_active(i.op1)) eval_instruction(get_output_instruction(i.op1));
        wires[i.output_wire] = ~wires[i.op1];
    } else if (i.type == 1) {
        if (!is_active(i.op1)) eval_instruction(get_output_instruction(i.op1));
        if (!is_active(i.op2)) eval_instruction(get_output_instruction(i.op2));
         wires[i.output_wire] = wires[i.op1] | wires[i.op2];
    } else if (i.type == 0) {
        if (i.op1_t && !is_active(i.op1)) eval_instruction(get_output_instruction(i.op1));
        if (i.op2_t && !is_active(i.op2)) eval_instruction(get_output_instruction(i.op2));
        wires[i.output_wire] = ((i.op1_t) ? wires[i.op1] : i.op1 ) & ((i.op2_t) ? wires[i.op2] : i.op2_t);;
    }
    
    print_instr(i);
    wires_eval[i.output_wire] = 1;
}


int main(int argc, char ** argv) {
    char left_side[64];
    char right_side[64];
    char attr_wire;
    char op1[64];
    char op2[64];
    int op3;
    int c = 0;

    for(c = 0; c < 1000; c++) instruction_set[c].output_wire = -1;

    c = 0;
    while(scanf("%20[0-9a-zA-Z ] -> %s\n", left_side, right_side) != -1) {
        if (strstr(left_side, "AND")) {
            sscanf(left_side, "%s AND %s", op1, op2);
            instruction_set[c].type = 0;
        } else if (strstr(left_side, "OR")) {
            sscanf(left_side, "%s OR %s", op1, op2);
            instruction_set[c].type = 1;
        } else if (strstr(left_side, "NOT")) {
            sscanf(left_side, "NOT %s", &op1);
            instruction_set[c].type = 2;
        } else if (strstr(left_side, "LSHIFT")){
             sscanf(left_side, "%s LSHIFT %d", op1, &op3);
            instruction_set[c].type = 3;
        } else if (strstr(left_side, "RSHIFT")){
            sscanf(left_side, "%s RSHIFT %d", op1, &op3);
            instruction_set[c].type = 4;
        } else {
            sscanf(left_side, "%s", &op1);
            instruction_set[c].type = 5;
        }


        instruction_set[c].output_wire = wire_to_int(right_side);

        if (op1[0]-'a' >= 0) {
            instruction_set[c].op1_t = 1;
            instruction_set[c].op1 = wire_to_int(op1);
        } else {
            instruction_set[c].op1 = atoi(op1);
        }
        
        if (op2[0]-'a' >= 0) {
            instruction_set[c].op2_t = 1;
            instruction_set[c].op2 = wire_to_int(op2);
        } else {
            instruction_set[c].op2 = atoi(op2);
        }


        instruction_set[c].op3 = op3;

        print_instr(instruction_set[c]);
        c++;
        op3 = -1;
    }   

    printf("EVAL %d!!!\n", 0);

    eval_instruction(get_output_instruction(0));

    printf("Result %d\n", wires[0]);
}
