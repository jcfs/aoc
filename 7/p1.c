#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned short w[1000];

typedef struct {
    int type;
    char op1[64];
    char op2[64];
    unsigned short output;
} instruction;

instruction instr[1000];

// convert a string to its scalar value "a" -> 0, "aa" -> 26
int scalar(char * str) {
    int result = 0;
    int i;

    for(i = 1; i <= strlen(str); i++) { 
        result += (str[i-1]-'a')+(strlen(str)-i)*26*(str[i-1]-'a'+1);
    }

    return result;
}

// get and instucrion by its output 
instruction * get(char * str) {
    int i = 0;

    int wire = atoi(str);

    if (!wire && *str && *str != '0') {
        wire = scalar(str);

        for(i = 0; i < 1000; i++) {
            if (instr[i].output == wire) {
                return &instr[i];
            }
        }
    }

    return NULL;
}

// evaluates the given instruction
unsigned short eval(instruction * i) {

    //if (w[i->output]) return w[i->output];

    unsigned short op1 = get(i->op1) == NULL ? atoi(i->op1) : eval(get(i->op1));
    unsigned short op2 = get(i->op2) == NULL ? atoi(i->op2) : eval(get(i->op2));

    if (i->type == 5) {
        return w[i->output] = op1;
    } else if (i->type == 4) {
        return w[i->output] = op1 >> op2; 
    } else if (i->type == 3) {
        return w[i->output] = op1 << op2;
    } else if (i->type == 2) {
        return w[i->output] = ~op1; 
    } else if (i->type == 1) {
        return w[i->output] = op1 | op2;
    } else if (i->type == 0) {
        return w[i->output] = op1 & op2;
    }

    return w[i->output];

}

int main(int argc, char ** argv) {
    char left[64], right[64];
    int c = 0;

    while(scanf("%20[0-9a-zA-Z ] -> %s\n", left, right) != -1) {
        if (strstr(left, "AND")) {
            sscanf(left, "%s AND %s", instr[c].op1, instr[c].op2);
            instr[c].type = 0;
        } else if (strstr(left, "OR")) {
            sscanf(left, "%s OR %s", instr[c].op1, instr[c].op2);
            instr[c].type = 1;
        } else if (strstr(left, "NOT")) {
            sscanf(left, "NOT %s", instr[c].op1);
            instr[c].type = 2;
        } else if (strstr(left, "LSHIFT")){
            sscanf(left, "%s LSHIFT %s", instr[c].op1, instr[c].op2);
            instr[c].type = 3;
        } else if (strstr(left, "RSHIFT")){
            sscanf(left, "%s RSHIFT %s", instr[c].op1, instr[c].op2);
            instr[c].type = 4;
        } else {
            sscanf(left, "%s", instr[c].op1);
            instr[c].type = 5;
        }

        instr[c++].output = scalar(right);
    }   
    printf("%d\n", eval(get("a")));
}
