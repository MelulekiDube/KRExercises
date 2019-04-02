#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100
#define alloc(type, size) ((type*)malloc(sizeof(type)*size))//for space allocation


typedef struct tnode* tnode_ptr;
typedef struct lnode * lnode_ptr;

tnode_ptr root;
void parse_file(char *);
char *strdup_md(char *);
void treeprint(tnode_ptr);
tnode_ptr addtree(tnode_ptr, char*, int);

typedef struct lnode{
	int line_number;
	lnode_ptr next;
}lnode;

typedef struct tnode{
	char *word;
	lnode_ptr line_numbers;
	tnode_ptr left, right;
}tnode;

int main(int argc, char *argv[]){
	char *filename = argv[1];
	root = NULL;
	parse_file(filename);
}

void parse_file(char * filename){
	FILE *f; 
	int c;
	char word[MAX_WORD];
	char *p = word;
	
	f = fopen(filename, "r");
	int line = 1;
	while((c=fgetc(f))!=EOF){
		if(c == ' '||c=='\n'||c=='\t'){
			*p++ = '\0';
			if(p!=word)
				root = addtree(root, word, line);
			if(c=='\n')
				++line;
			p = word;
		}else{
			*p++ = c;
		}
	}
	//printf("Printing the details:\n");
	treeprint(root);
}	

void addlist(lnode_ptr h, int ln){
	lnode_ptr prev; 
	while(h){
		prev= h;
		h=h->next;
	}
	prev->next = alloc(lnode, 1);
	prev->next->line_number = ln;
	prev->next->next = NULL;
}

tnode_ptr addtree(tnode_ptr r, char *s, int line_number){
	int cond;
	if(r==NULL){
		r = alloc(tnode, 1);
		r->word = strdup(s);
		r->left = r->right=NULL;
		r->line_numbers = alloc(lnode, 1);
		r->line_numbers->next = NULL;
		r->line_numbers->line_number = line_number;
	}else if((cond=strcmp(s, r->word))==0){
		addlist(r->line_numbers, line_number);
	}else if (cond < 0){
		r->left = addtree(r->left, s, line_number);
	}else{
		r->right = addtree(r->right, s, line_number);
	}
	return r;
}

void listprint(lnode_ptr h){
	while(h){
		printf("%d ", h->line_number);
		h = h->next;
	}
}
void treeprint(tnode *r){
	if(r){
		treeprint(r->left);
		printf("%s: ", r->word);
		listprint(r->line_numbers);
		printf("\n");
		treeprint(r->right);
	}
}

char *strdup_md(char *s){
	char *p = alloc(char, 1);
	if(p)
		strcpy(p, s);
	return p;
}