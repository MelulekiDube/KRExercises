#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *fp;
	void filecopy(FILE *, FILE *);
	
	char *prog = argv[0]; /*1* progr~m name for errors */
	
	
	if(argc == 1) /*no arguments*/
		filecopy(stdin, stdout);
	else
		while(argc--)
			if((fp = fopen(*++argv, "r")) == NULL){
				fprintf(stderr, "%s: can't open %s\n" , prog, *argv);
				exit(1);
			}else{
				filecopy(fp, stdout);
				fclose(fp);
			}
		if(ferror(stdout)){
			fprintf(stderr, "%s: error writing stdout\n", prog);
			exit(2);
		}
	return 0;
	
}


void filecopy(FILE *src, FILE *dest){
	int c;
	while((c=getc(src))!=EOF)
		putc(c, dest);
}