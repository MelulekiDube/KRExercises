#include <stdio.h>
#include <stdbool.h>

void ex17(){
	printf("%i\n", EOF);
}

void count_spechars(char *filename){
	int tabs, spaces, nl, ch;
	tabs = spaces = nl = 0;
	++nl;
	FILE *file = fopen(filename, "r");
	while((ch = fgetc(file))!= EOF){
		switch(ch){
			case ' ':
				++spaces;
				break;
			case '\t':
				++tabs;
				break;
			case '\n':
				++nl;
				break;
				
		}
	}
	fclose(file);
	printf("Spaces is: %d, Tabs is: %d, New lines is: %d, Total is: %d\n", spaces, tabs, nl, (spaces+tabs+nl));
}


int char_count(char *filename){
	FILE *f =fopen(filename, "r");
	int c, char_number;
	char_number = 0;
	while((c=fgetc(f)) != EOF){
		++char_number;
	}
	fclose(f);
	return char_number;
}

double char_count2(char* filename){
	FILE *f = fopen(filename, "r");
	double nc;
	for(nc =0; fgetc(f)!= EOF; ++nc);
	fclose(f);
	return nc;
}

int line_count(char* filename){
	FILE *file = fopen(filename,"r");
	int ln, ch;
	while((ch = fgetc(file))!=EOF){
		if(ch == '\n')
			++ln;
	}
	fclose(file);
	return ln;
}

void copy_and_replace(char *srcfname, char* desname){
	/*ex1-9*/
	FILE *srcfile = fopen(srcfname, "r");
	FILE *destfile = fopen(desname, "w");
	int c;
	while((c=fgetc(srcfile)) != EOF){
		fputc(c, destfile);
		if(c ==' '){
			while((c=fgetc(srcfile))==' ');
			if(c == EOF)
				break;
			fputc(c, destfile);
		}
	}
	fclose(srcfile);
	fclose(destfile);
}

void copy_and_replace2(char *srcfname, char* desname){
	/* ex1-10 */
	FILE *srcfile = fopen(srcfname, "r");
	FILE *destfile = fopen(desname, "w");
	int c;
	while((c=fgetc(srcfile)) != EOF){
		
		switch(c){
			case '\t':
				fputc('\\', destfile);
				fputc('t', destfile);
				break;
			case '\b':
				fputc('\\', destfile);
				fputc('b', destfile);
				break;
			case '\\':
				fputc('\\', destfile);
				fputc('\\', destfile);
				break;
			default:
				fputc(c, destfile);
		}
	}
	fclose(srcfile);
	fclose(destfile);
}

void fcopy(char *srcfname, char* desname){
	FILE *src = fopen(srcfname, "r");
	FILE *dest = fopen(desname, "w");
	int c;
	while((c = fgetc(src))!= EOF){
		fputc(c, dest);
	}
	fclose(src);
	fclose(dest);
}

int kmain(int argc, char*argv[]){
	ex17();
	copy_and_replace(argv[1], argv[2]);
	count_spechars(argv[1]);
	return 0;
}
