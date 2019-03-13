#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>                                              
#define line_length  64
#define TABSTOPS 4
#define MAXLINE 65536 //random number

typedef char* string;
void detab(char s[], int limit);/*ex1.20*/
void entab(char s[], int limit);  /*ex1.21*/
int _get_line(char s[], int limit); /*ex 1.22*/
void fold(char file_name[], char save_file [], int limit);
int get_file_line(FILE* file, char buffer[], int maxline);

void remove_comments(char file_name[], char save_file []); /*ex1.23*/


static bool done = false;

/**
int main(int argc, char *args[]){
	printf("Running file_editing_tools\n");
	char *f1 = args[1];
	char *f2 = args[2];
    fold(f1, f2, 10);
}
*/

int _get_line(char s[], int limit){
    int i, c;
    for(i=0;i<limit-1 && (c=getchar())!=EOF && c!='\n';++i){
        s[i]= c;
    }
    if(c=='\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
}

/*This is to answer Ex1-20 of the K&R book*/
void detab(char s[], int limit){   
    int i=0, c;
    for (i=0;i<limit-1&&(c=getchar())!=EOF && c!='\n'; ++i){
        if(c=='\t'){
            int nb = abs(i-TABSTOPS)%TABSTOPS;
            while(nb !=0){
                s[i] = ' ';  
                ++i;
                --nb;
            }
            --i;//since we last incremented and ddnt puy anything;
        }else{
            s[i] = c;
        }
    }  
    if(c=='\n'){
       s[i] = c;
        ++i;
    }
    s[i] = '\0';
}

/*Answer to Ex1-21 of the K&R book*/
void entab(char s[], int limit){
    int counter=1, index=0, ns=0, c;
    for(;counter<limit-1&&(c=getchar())!=EOF&&c!='\n';++counter){
        if(c==' '){
            ++ns; 
            if(!(counter%TABSTOPS)){
                if(ns>1){
                    s[index]='\t';
                }else if(ns==1){
                    s[index] = ' ';
                }
                ++index;
                ns = 0;
            }
        }else{
            while(ns!=0){
                s[index]=' ';
                ++index;
                --ns;
            }
            s[index] = c;
            ++index;
        }
    }
    if(c=='\n'){
        s[index] = c;
        ++index;
    }
    s[index] = '\0';
}

int process_fold(FILE* file, char buffer[], int buff_limit, int line_limit) {
	int i, j, counter, c;//reason for c being int is that EOF is an int and not a char.
	
	counter  = 0;
	for(i=0;(c=fgetc(file))!=EOF&&c!='\n';++i){
		buffer[i] = c;
		if(c=='\t')
			counter+=TABSTOPS;
		else ++counter;
		if(counter>=line_limit-1){
			if(c==' '||c=='\t'){
				buffer[i] = '\n';
				++i;
				break;
			}else{
				//we wanna trace back to the last empty space and place the null terminator there
				j = i;
				while(j>=0&&buffer[j]!=' '&&buffer[j]!='\t'){
					--j;
				}
				if(j>=0){
					buffer[j] = '\n';
					counter = 0;
				}
			}
		}
	}
	
	if(c=='\n'){
		buffer[i] = '\n';
		++i;
	}
	if(c==EOF)
		done = true;
	buffer[i] = '\0';
	return i;
}

//Exercise 1-22.
void fold(char file_name[], char save_file [], int line_limit){
	int i, j;
	FILE* input_file;
	FILE* output_file;
	
	char buffer[MAXLINE];
	input_file = fopen(file_name, "r");
	output_file = fopen(save_file, "w");
	process_fold(input_file, buffer, MAXLINE, line_limit);
	while(!done){
		fprintf(output_file, "%s", buffer);
		process_fold(input_file, buffer, MAXLINE, line_limit);
	}
}

int get_file_line(FILE* file, char buffer[], int maxline){
	int c, i, j;
	static bool in_string;
	char comments[maxline];
	
	static bool multi_line_comment = false; //will keep it's previous value on each function call
	for(i=j=0; (c=fgetc(file))!=EOF&&c!='\n';){
		//catch //
		if(c=='/'&&((i-1>=0)&&buffer[i-1]=='/')){
			//replace buffer[i-1] with newline char, terminate the string and return as the comment continues for rest of line
			printf("%c", c);
			buffer[i-1] = '\n';
			buffer[i] ='\0';
			while((c=fgetc(file))!=EOF&&c!='\n');
			return i;
		}else if(!in_string&&c=='*'&&((i-1>=0)&&buffer[i-1]=='/')){ //catching/**/
			multi_line_comment = true;
			--i;
		}else if(multi_line_comment && c== '/' && (j>0) && comments[j-1]=='*'){
			multi_line_comment = false;
		}else if(!multi_line_comment){
			if(c=='\"'){
				in_string = in_string?false:true;
			}
			buffer[i] = c;
			++i;
		}else{
			comments[j] = c;
			++j;
		}
	}
	if(c=='\n'){
		printf("yes");
		buffer[i]='\n';
		++i;
	}
	buffer[i] ='\0';
	if(c==EOF)
		done = true;
	return i;
}

//Exercise 1-23.
void remove_comments(char file_name[], char save_file []){
    FILE *file = fopen(file_name,"r");
	FILE *file_save = fopen(save_file, "w");
	char buffer[MAXLINE];
	int size = get_file_line(file, buffer, MAXLINE);
	while(!done){
		fprintf(file_save, "%s", buffer);
		size = get_file_line(file, buffer, MAXLINE);
	}
	fclose(file_save);
    fclose(file);
}
