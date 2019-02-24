#include <stdlib.h>
#include <stdio.h>

                                                                                       
#define line_length  64
#define TABSTOPS 4
#define MAXLINE 1000

typedef char* string;
void detab(char s[], int limit);/*ex1.20*/
void entab(char s[], int limit);  /*ex1.21*/
int _get_line(char s[], int limit); /*ex 1.22*/
void fold(char s[], int n);
void remove_comments(char filename[]); /*ex1.23*/

int main(int argc, char *args[]){
    char line[MAXLINE];
    entab(line, MAXLINE);
    printf("%s",line);
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

void remove_comments(char file_name[]){
    FILE *file = fopen(file_name,"r+");
    int c;
    while((c= fgetc(file))!=EOF){
        if(c == '/'){
            int next_char;
            if(next_char == '/'){
                while((c=fgetc(file))!=EOF&&c!='\n'){
                    next_char = fgetc(file);       
                }
            }
        }
    }
    fclose(file);
}
