#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>                                              
#define line_length  64
#define TABSTOPS 4
#define MAXLINE 2000

typedef char* string;
void detab(char s[], int limit);/*ex1.20*/
void entab(char s[], int limit);  /*ex1.21*/
int _get_line(char s[], int limit); /*ex 1.22*/
void fold(char s[], int n);
int get_file_line(FILE* file, char buffer[], int maxline);

void remove_comments(char file_name[], char save_file []); /*ex1.23*/

int main(int argc, char *args[]){
	printf("Running file_editing_tools\n");
	char *f1 = args[1];
	char *f2 = args[2];
    remove_comments(f1, f2);
}

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
//            printf("ns value is: %i, counter value is: %i\n", ns, counter);
            if(!(counter%TABSTOPS)){//we will deal ==1 later
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

void fold(char s[], int n){
	
}
bool done = false;
int get_file_line(FILE* file, char buffer[], int maxline){
	int c, i, j = 0;
	static bool multi_line_comment = false; //will keep it's previous value on each function call
	char comments[maxline];
	for(i=0; (c=fgetc(file))!=EOF&&c!='\n';){
		//catch //
		if(c=='/'&&((i-1>=0)&&buffer[i-1]=='/')){
			//replace buffer[i-1] with newline char, terminate the string and return as the comment continues for rest of line
			printf("%c", c);
			buffer[i-1] = '\n';
			buffer[i] ='\0';
			while((c=fgetc(file))!=EOF&&c!='\n');
			return i;
		}else if(c=='*'&&((i-1>=0)&&buffer[i-1]=='/')){ //catching/**/
			multi_line_comment = true;
			--i;
		}else if(multi_line_comment && c== '/' && (j>0) && comments[j-1]=='*'){
			multi_line_comment = false;
		}else if(!multi_line_comment){
			buffer[i] = c;
			++i;
		}else{
			comments[j] = c;
			++j;
		}
	}
	if(c=='n'){
		printf("yes");
		buffer[i]='\n';
		++i;
	}
	buffer[i] ='\0';
	if(c==EOF)
		done = true;
	return i;
}

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
