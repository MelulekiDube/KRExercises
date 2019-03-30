#define ALLOC_SIZE 10000 /* size of available space */

static char allocbuff[ALLOC_SIZE]; /*storeage for allo*/
static char *allocp = allocbuff; /*pointer to next free position*/

char *alloc(int n){/*return pointer to next free allocation*/
	char *temp = NULL;
	if((&allocbuff+ALLOC_SIZE)/*this is max address possible*/-allocp>=n){
		temp =  allocp;
		allocp+=n;
	}
	return temp;
	
}

void afree(char *p){/*assumes that p is not in between memory that is being used**/
	if(p>=allocbuff && p<allocbuff+ALLOC_SIZE)
		allocp = p;
}
