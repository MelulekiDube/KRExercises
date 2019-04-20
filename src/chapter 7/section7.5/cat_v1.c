#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *fp;
	void filecopy(FILE *, FILE *);
	
	if(argc == 1) /*no arguments*/
		filecopy(stdin, stdout);
	else
		while(argc--)
			if((fp = fopen(*++argv, "r")) == NULL){
				printf("cat: can't open s\n", *argv);//problem when we have many arguments and one of them has a //mistake. the erorr will be printed as if it were a file; check v2for the fix
				return 1;
			}else{
				filecopy(fp, stdout);
				fclose(fp);
			}
	return 0;
	
}


void filecopy(FILE *src, FILE *dest){
	int c;
	while((c=getc(src))!=EOF)
		putc(c, dest);
}