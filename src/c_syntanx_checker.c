#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

extern void remove_comments(char file_name[], char save_file []);
typedef struct Node* node_ptr;

typedef struct Node{
	int c, line_number;
	node_ptr next;
}Node;

node_ptr head= NULL;

void push_char(int c, int line){
	node_ptr n = (node_ptr)malloc(sizeof(Node));
	n->c = c; n->line_number = line;
	n->next = head;
	head = n;
}

int pop_char(){
	int c = head->c;
	node_ptr temp = head;
	head = head->next;
	free(temp);
	return c;
}

void print_error(int c, int l){
	printf("Missed placed char %c,  on line number %d", c, l);
}

bool in_string(){
	return (head) && (head->c == '\'' || head->c=='\"');
}

void process_file(FILE* file){
	int c;
	int line = 1;
	while((c=fgetc(file))!=EOF){
		switch(c){
			case '{':
				if(!in_string())
					push_char(c, line);
				break;
			case '}':
				if(!in_string()){
					if(head&&(head->c=='{')){
						pop_char();
					}else{
						print_error(c, line);
					}
				}
				break;
			case '(':
				if(!in_string())
					push_char(c, line);
				break;
			case ')':
				if(!in_string()){
					if(head&&(head->c=='(')){
						pop_char();
					}else{
						//error
						print_error(c, line);
					}
				}
				break;
			case '\"':
				if(head&&(head->c==c))
					pop_char();
				else push_char(c, line);
				break;
			case '[':
				if(!in_string())
					push_char(c, line);
				break;
			case ']':
				if(!in_string()){
					if(head&&(head->c=='[')){
						pop_char();
					}else{
						print_error(c, line);
					}
				}
				break;
			case '\'':
				if(head&&(head->c==c))
					pop_char();
				else push_char(c, line);
				break;
			case '\n':
				++line;
				break;
		}
	}
	if(head){
		perror("Errors:\n");
		while(head){
				fprintf(stderr,"The char \'%c\' on line number %d is not closed.\n",head->c, head->line_number);
				head = head->next;
		}
	}else{
		printf("File looks on point!!!!\n");
	}
}


int main(int argc, char* args[]){
	char file_name []= ".temp.c";
	remove_comments(args[1], file_name);
	FILE* f = fopen(".temp.c", "r");
	process_file(f);
	fclose(f);
	remove(file_name);
}
//{[{{{]}}}}