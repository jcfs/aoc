#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
	char line[128];
	int result = 0;
	printf("int main(int argc, char ** argv) {\n int result = 0; \n");
		
	while(scanf("%s\n", line) != -1) {
		result += strlen(line);
		printf(" result += printf(%s);\n",line);
	}   
	printf("printf(\"%%d\\n\", %d- result);\n}", result);  
}
