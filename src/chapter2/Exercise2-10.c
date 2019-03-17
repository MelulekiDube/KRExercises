/*
	Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.
*/
#include <stdlib.h>
#include <stdio.h>

int lower_c(int c){
	return (c>='A'&&c<='Z')?(c+('a'-'A')):(c);
}

void lower(char s[]){
	int i, c;
	
	for(i=0; (c=s[i])!='\0';++i){
		s[i] = lower_c(c);
	}
}

int main(void){
	char s1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!!!!)000000";
	char s2[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ!!!!)000000";
	lower(s2);
	printf("%s to lower is %s\n", s1, s2);
	return 0;
}


