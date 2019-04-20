#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 400

char *fgets_md(char *s, int n, FILE *iop); /*fgets: get at most n chars from iop */
int fputs_md(char *s, FILE* iop); /* fputs: put string s on file iop */

int main(int argc, char *argv[]){
	FILE *fp1, *fp2;
	
	char *prog = argv[0]; /*1* program name for errors */
	if(argc < 3){
		fprintf(stderr, "%s: few number of arguments: expected 2 arguments\n", prog);
		exit(1);
	}
	if((fp1 = fopen(*++argv, "r"))==NULL){
		fprintf(stderr, "%s: can't open %s\n" , prog, *argv);
		exit(2);
	}
	if((fp2 = fopen(*++argv, "r"))==NULL){
		fprintf(stderr, "%s: can't open %s\n" , prog, *argv);
		exit(2);
	}
	int line_number =0;
	char s1[MAX_LINE], s2[MAX_LINE];
	char *c1, *c2;
	int done = 0;
	while((c1=fgets_md(s1, MAX_LINE, fp1)) && (c2= fgets_md(s2, MAX_LINE, fp2))){
		++line_number;
		if(strcmp(s1, s2)!=0){
			printf("File %s and FILE %s differ on line number %d\n", *(argv-1), *argv, line_number);
			printf("File %s has contents: %s\nFile %s has contents: %s",*(argv-1), s1,  *argv, s2);
			done = 1;
			break;
		}
	}
	if(!done && ((feof(fp1) && !feof(fp2)) || (feof(fp2) && !feof(fp1)))){
		printf("File %s and FILE %s differ on line number %d\n", *(argv-1), *argv, line_number);
	}
	fclose(fp1);
	fclose(fp2);
	exit(0);	
}

char *fgets_md(char *s, int n, FILE *iop){
	register int c;
	register  char *cs;
	cs = s;
	while(--n > 0 && (c=getc(iop))!=EOF)
		if((*cs++=c) == '\n')
			break;
	*cs = '\0';
	return (c==EOF && cs == s)?NULL:s;
}

int fputs_md(char *s, FILE *iop){
	int c;
	while(c = *s++)
		putc(c, iop);
	return ferror(iop)?EOF:0;
}