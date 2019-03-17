#include <stdlib.h>
#include <stdio.h>
#define LIMIT 5
/*
for (i=O; i<lim-1 && (c=getchar(» 1= '\n' && c 1= EOF; ++i)
s[i] = c;
*/

int main(void){
	int i, c, lim;
	lim = LIMIT;
	char s[LIMIT];
	i=0;
	while(i<lim-1){
		c = getchar();
		if(c=='\n'){
			break;
		}else if(c==EOF){
			break;
		}else{
			s[i] = c;
		}
		++i;
	}
	s[i] = '\0';
	printf("%s\n", s);
	return 0;
}