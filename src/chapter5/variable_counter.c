#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define DEFAULT_LENGTH 6
#define MAXTOKEN 100

#define md_alloc(type) ((type*)malloc(sizeof(type)))
#define KEY_WORD_SIZE 20
#define TYPE_SIZE 11

enum { NAME=1, SPECIFIER, BRACKETS, COMMENTS, INCLUDE, FUN_DCL};
char *types[] = {"auto",  "char", "double",  "float", "int", "long", "register", "short", "signed", "unsigned", "void"};

int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char name [MAXTOKEN] ; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out [1000] ; /* output string */
/**dcl: parse a declarator*/

/**
	List of that will hold the variables
*/
typedef struct lnode {
	struct lnode * next;
	char *data;
}lnode;

/**
	Tree structuer to hold the entir thing
*/
typedef struct tnode{
	lnode *head; //for list of variables
	struct tnode * left, *right;
}tnode;
tnode *root = NULL;

tnode *talloc(void){
	return (tnode *)malloc(sizeof(tnode));
}

/**strncmp_md
*	@Brief compares the first n characters of s and t and returns a value based on how the two subset of the string compare lexicographically.
*	@Param  s: The pointer to the first string
*			t: Pointer to the second string
*			n: number of characters we are comparing between s and t
*/
int strncmp_md(const char *s, const char *t, int n){
	int i =0;
	int lens = strlen(s);
	int lent = strlen(t);
	int lim = (lens>lent?lent:lens);
	while((*s++==*t++)&&(i<lim && ++i<n))
		;
	--s; --t;
	return *s - *t;
}

char *strdup_md(char *s){
	char *p = (char*)malloc(sizeof(strlen(s)+1));
	if(p)
		strcpy(p, s);
	return p;
}
void swap(char *s, char* t){
	char temp[strlen(s)];
	strcpy(temp, s);
	strcpy(s, t);
	strcpy(t, temp);
}

void add_node(lnode* h, char *s, int n){
	lnode *temp = h, *prev=NULL;
		while(temp){
			if(strcmp(s, h->data)<=0){
				swap(s, h->data);
			}
			prev = temp;
			temp = temp->next;
		}
		prev->next = md_alloc(lnode);
		prev->next->data = strdup_md(s);
		prev->next->next = NULL;
}


tnode *add_tree(tnode *r, char *s, int n){
	int cond;
	if(!r){
		r = md_alloc(tnode);
		r->head = md_alloc(lnode);
		r->head->data = strdup_md(s);
		r->head->next = NULL;
		r->left = r->right = NULL;
	}else if((cond = strncmp_md(s, r->head->data, n))==0)
		add_node(r->head, s, n);
	else if(cond<0){
		r->left = add_tree(r->left, s, n);
	}else
		r->right = add_tree(r->right, s, n);
	return r;
}

void print_list(lnode *head){
	while(head){
		printf("%s ",head->data);
		head = head->next;
	}
	printf("\n");
}

void treeprint(tnode *r){
	if(r){
		treeprint(r->left);
		print_list(r->head);
		treeprint(r->right);
	}
}

int binsearch(char* x, char *v[], int n){
	int low, mid, high;
	low = 0;
	high= n-1;
	mid = (low+high)/2;
	int cmp;
	//start timer
	while(low <= high){
		//printf("mid is: %s\n", v[mid]);
		cmp = strcmp(x, v[mid]);
		if(cmp< 0)
			high = mid - 1;
		else if (cmp == 0 )
			return mid;
		else 
			low = mid+1;
		mid  = (high+low)/2;
	}
	return -1;
}

/*
5. varDeclaration → typeSpecifier varDeclList ;
6. scopedVarDeclaration → scopedTypeSpecifier varDeclList ;
7. varDeclList → varDeclList , varDeclInitialize | varDeclInitialize
8. varDeclInitialize → varDeclId | varDeclId : simpleExpression
9. varDeclId → ID | ID [ NUMCONST ]
10. scopedTypeSpecifier → static typeSpecifier | typeSpecifier
11. typeSpecifier → returnTypeSpecifier | RECTYPE
12. returnTypeSpecifier → int | bool | char
*/
void ignore_whitespace(FILE* f){
	int c;
	while((c=fgetc(f))==' '|| c == '\t' || c=='\n')
		;
	ungetc(c, f);
}

int get_word(FILE* f, char *word){
	int c;
	void ungetch(int, FILE*);
	/*Handling comments*/
	ignore_whitespace(f);
	if((c=fgetc(f))=='/'){
		if((c=fgetc(f))=='/'){
			while((c=fgetc(f)!='\n'));
			return COMMENTS;
		}else if(c=='*'){
			while((c=fgetc(f))!=EOF){
				if(c=='*'){
					if((c=fgetc(f))=='/')/**/
						return COMMENTS;
				}
			}
		}else
			ungetc(c, f);
	}
	if(c==EOF)
		return 0;
	*word++ = c;
	while((c=fgetc(f))!=' ' && c != '\t' && c!='\n' && c!=EOF){
		*word++ = c;
	}
	*word = '\0';
	return 1;
}
int gettoken(FILE* f) {/* return next token */
	int status = get_word(f, name);
	if(!status){
		return EOF;
	}
	int index;
	if((index= binsearch(name, types, TYPE_SIZE))>=0){
		return tokentype = SPECIFIER;
	}
	return tokentype = status;
}

int func_definations(FILE* f, int n){
	int c;
	int varDeclList(FILE*, int);
	if((c=fgetc(f))!=',');
		ungetc(c, f);
	while(gettoken(f)==SPECIFIER){
		tokentype = FUN_DCL;
		if((c=varDeclList(f, n))==')')
			break;
		
	}
}

int varDeclList(FILE* f, int n){
	int c;
	char *p = token;
	ignore_whitespace(f);
	while((c=fgetc(f))=='*');
	if(isalpha(c)||c=='_'){
		for(*p++=c; isalnum(c=fgetc(f))||c=='_';)
			*p++ = c;
		*p='\0';
		ignore_whitespace(f);
		if(c!='(')
			root = add_tree(root, token, n);
		if(c==','&&tokentype!=FUN_DCL)
			varDeclList(f, n);
		if(c=='(')
			func_definations(f, n);
		if(tokentype!=FUN_DCL)
			ungetc(c, f);
	}
	return c;
}

int main(int argc, char *argv[]){
	char str[100];
	int size =DEFAULT_LENGTH;
	if(argc > 2)
		size = atoi(argv[2]);
	FILE* f= fopen(argv[1], "r");
	while ((tokentype =gettoken (f)) != EOF) {/* 1st token on line */
		if(tokentype==SPECIFIER){
			varDeclList(f, size);
		}
	}
	treeprint(root);
}