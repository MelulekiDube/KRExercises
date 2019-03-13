#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */
int get_line(char line[], int maxline);
void copy(char to[], char from[]);
int getl_removeb(char line[], int maxline);
void revese_string(char  s[], int line);
    /* when no return type int is assumed */
eamain(){
	int len;	/* current line length*/
	int max;	/* maximum length seen so far*/
	char line[MAXLINE]; /* current input line*/
	char longest[MAXLINE]; /* longest line saved here */
	max = 0;

    while((len = getl_removeb(line, MAXLINE))>1 && line[0] != '\n') /* used 1 since after new line we added i to be 1*/
		if(len > max){
			max = len;
			copy(longest, line);
		}
	if(max > 0)
        printf("%s", longest);
    char st [MAXLINE];
    get_line(st, MAXLINE);
    revese_string(st, MAXLINE);
    printf("Reversed we get: %s\n", st);        
    return 0;
}
/* getline: read a line into line, return length*/
int get_line(char s[], int lim){
	int c, i;

	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	/*this is the bit to answer ex 1-7 and prints length greaterthan 80*/
	if(i > 80)
		printf("%s", s);
	return i;
}
/* similar to get_line but then removes the blanks from the line */
int getl_removeb(char s[], int lim){
	int c, i;
	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i){
		s[i] = (c=='\t')?' ' : c;
		if(c == ' '){
			while(c==' '&& (c=getchar())!=EOF && c!='\n');
			if((c=getchar())==EOF && c=='\n')
				break;
			s[++i] = (c=='\t')?' ' : c;
		}
	}
	if(c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	/*this is the bit to answer ex 1-7 and prints length greaterthan 80*/

	if(i > 80)
		printf("%s", s);
	return i;
}
/* copy: copy from from into to; assum to is big enough*/
void copy(char to[], char from[]){
	int i;
	i=0;
	while((to[i] = from[i]) != '\0')
		++i;
}

void revese_string(char str[], int size){
    int i, temp;
    int len = 0;
    i=0;
    printf("reversing: %s\n", str);
    while(str[i] != '\0'){
        ++i;
        ++len; 
    }
    --len;
    printf("Len is: %i\n", len);
    int lim = len/2;
    for(i=0; i<lim;++i){
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len-i-1] = temp;
    }

}
