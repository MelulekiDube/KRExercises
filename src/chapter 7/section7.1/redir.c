#include <stdio.h>

int main(int argc, char *args[]){
	int a;
	while((a=getchar())!=EOF){
		putchar(a);
	}
	return 0;
}