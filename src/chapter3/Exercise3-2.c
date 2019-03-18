/*
	Write a function escape (s, t) that converts characters like newline and tab into visible escape sequences like \n and \ t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters
*/

#include <stdio.h>

/**/
void escape_reverse(char s[], char t[]){
	int i, j, c;
	
	j=0; i=0;
	int waiting_for_escape = 0;
	while((c=t[i++])!='\0'){
		switch(c){
			case 'n':
				if(waiting_for_escape){
					s[j++] = '\n';
					waiting_for_escape = 0;
				}
				else
					s[j++] = c;
				break;
			case 't':
				if(waiting_for_escape){
					s[j++] = '\t';
					waiting_for_escape = 0;
				}
				else
					s[j++] = c;
				break;
			case '\\':
				if(waiting_for_escape){
					s[j++] = '\\';
					s[j++] = '\\';
					waiting_for_escape = 0;
				}else{
					waiting_for_escape = 1;
				}
				break;
			default:
				s[j++] = c;
				waiting_for_escape = waiting_for_escape?0:1;
				break;
		}
	}
}

/*assumes that  has enough space to handle the newer bigger nuber of characters*/
void escape(char s[], char t[]){
	int i, j, c; //variable that will be used within the loop
	
	j = 0; i=0;
	while((c=t[i++])!='\0'){
		switch(c){
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = c;
				break;
		}
	}
}

void get_line(char buff[], int limit){
	int i ,c;
	
	i=0;
	while((c=getchar())!=EOF&&(c!='\n')){
		buff[i++] = c;
		if(i==limit-1){
			buff[++i] = '\0';
			break;
		}
	}
	buff[i] = '\0';
}

int main(void){
	char buf[100];
	char buff[250];
	char buf2[100];
	get_line(buf, 100);
	escape(buff, buf);
	escape_reverse(buf, buff);
	printf("%s\n%s\n", buff, buf);
}