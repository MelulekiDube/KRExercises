#include <stdlib.h>
#include <stdio.h>


int ctoi(char c){
	return c - '0';
}

int atoi(char s[]){
	int i, n;
	
	n=0;
	for(i=0;s[i]>='0'&&s[i]<='9';++i){
		n = 10*n + ctoi(s[i]);
	}
	return n;
}