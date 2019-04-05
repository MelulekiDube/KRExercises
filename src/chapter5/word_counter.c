#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100
#define alloc(type, size) ((type*)malloc(sizeof(type)*size))//for space allocation


typedef struct tnode* tnode_ptr;
typedef struct lnode * lnode_ptr;

lnode_ptr head;
void parse_file(char *);
void sort_list(lnode_ptr);
void listprint(lnode_ptr h);
char *strdup_md(char *);
void addlist(lnode_ptr, char*);

typedef struct lnode{
	int counter;
	char *word;
	lnode_ptr next;
}lnode;


int main(int argc, char *argv[]){
	char *filename = argv[1];
	head = NULL;
	parse_file(filename);
}

void parse_file(char * filename){
	FILE *f; 
	int c;
	char word[MAX_WORD];
	char *p = word;
	
	f = fopen(filename, "r");
	while((c=fgetc(f))!=EOF){
		if(c == ' '||c=='\n'||c=='\t'){
			*p++ = '\0';
			addlist(head, word);
			p = word;
		}else{
			*p++ = c;
		}
	}
	sort_list(head);
	listprint(head);
}	

lnode_ptr create_node(char *s){
	lnode_ptr temp = alloc(lnode, 1);
	temp->counter = 1;
	temp->word = strdup_md(s);
	temp->next = NULL;
	return temp;
}

void addlist(lnode_ptr h, char* s){
	lnode_ptr prev=NULL, curr=h;
	while(curr){
		if(strcmp(s, curr->word)==0){
			++(curr->counter);
			return;
		}
		prev= curr;
		curr=curr->next;
	}
	if(prev)
		prev->next = create_node(s);
	else
		head = create_node(s);
}

void swap(lnode_ptr p1, lnode_ptr p2){
	int temp = p1->counter;
	char *tmp_word = strdup_md(p1->word);
	
	//copy p2 into p1
	free(p1->word);
	p1->word = strdup_md(p2->word);
	p1->counter = p2->counter;
	//copy temp into p2
	free(p2->word);
	p2->counter = temp;
	p2->word = strdup_md(tmp_word);
	
	free(tmp_word);
}

void sort_list(lnode_ptr h){
	lnode_ptr curr = h;
	while(curr){
		lnode_ptr max = curr, next = curr->next;
		while(next){
			if(max->counter < next->counter){
				max = next;
			}
			next = next->next;
		}
		if(max!=curr)
			swap(curr, max);
		curr = curr->next;
	}
}

void listprint(lnode_ptr h){
	while(h){
		printf("%s: %d\n", h->word, h->counter);
		h = h->next;
	}
}

char *strdup_md(char *s){
	char *p =alloc(char, strlen(s));
	if(p)
		strcpy(p, s);
	return p;
}