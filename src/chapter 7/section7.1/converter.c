#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]){
	int c;
	int status = tolower(argv[0][0]) == 'u';
	while((c=getchar())!=EOF){
		 //status != 0 that is not upper
		 c=status?toupper(c):tolower(c);
		 putchar(c);
	}
}