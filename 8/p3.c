#include <stdio.h>
#include <string.h>


// shoult be run as: sed -e 's/\([^\\]\)\(\\x..\)[a-f0-9]/\1\2-/g' input | ./p1 > out.c ; make out ; ./out
int main(int argc, char ** argv) {
	char line[128];
	int result = 0;
		
	while(scanf("%s\n", line) != -1) {
		for(result = 0; result < strlen(line); result++)printf(">%c\n", line[result]);
		printf("%d\n", printf(line));
	}   
}
