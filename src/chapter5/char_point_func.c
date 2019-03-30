#include <stdio.h>
/**
*	@Author Meluleki Dube
*	@Brief Answers to the end of charater pointers and functions section in K&r
*	@Date 24/03/2019
*/


/**strcat_md:
*	@Brief copies the string t to the end of s. Assumes that s has enough space to handle the combination.
*	@Param  s the pointer to beginning of string we are looking atan
*			t the string that we are appending to s;
*/
void strcat_md(char *s, char *t){
	while(*s++) //loop to go to the end of string. "Meluleki\0"
		;
	s--;//go back to where we failed from
	while((*s++=*t++))//copy everything from t to s
		;
}

int strlen_md(char *s){
	int i=0;
	while(*s++)
		++i;
	return i;
}

/**strend:
	@Brief returns 1 if the string t occurs at the end of the string s, and zero otherwise. We therfore assume that length of s is greater than length of t.
	@Param  s The string we are searching occurance from
			t The string we are checking if occurs
	@Returns returns 1 if the string t occurs at the end of the string s, and zero otherwise.
*/
int strend(char *s, char *t){
	int len_s = strlen_md(s);
	int len_t = strlen_md(t);
	s+=(len_s-len_t);
	while((*s++==*t++)){
		if(!(*s))
			return 1;
	}
	return 0;
}

/**5. Write versions of the library functions, and
strncmp; which operate on at most the first n characters of their argument
strings. For example, strncpy (s,t ,n) copies at most n characters of t to s.
Full descriptions are in Appendix B*/

/**strncpy_md:
*	@Brief copies the first n characters from t to s--
*	@Param  s: the pointer to the string which we are copying to.
*			t: the pointer to the string we are copying to s
*			n: the number of characters we are copying from t to s
*/
void strncpy_md(char* s, char *t, int n){
	int i =0;
	while((*s++=*t++)&&++i<n);
	*s= '\0';
}

/**strncat_md:
*	@Brief Copies n characters from the string t to the end of s. Assumes that s has enough space to handle the combination.
*	@Param  s: the pointer to the string which we are combining to.
*			t: the pointer to the string we are combing s with
*			n: the number of characters we are copying from t to s
*/
void strncat_md(char *s, char *t, int n){
	while(*s++)
		;
	s--;
	strncpy_md(s, t, n);
	
}

/**strncmp_md
*	@Brief compares the first n characters of s and t and returns a value based on how the two subset of the string compare lexicographically.
*	@Param  s: The pointer to the first string
*			t: Pointer to the second string
*			n: number of characters we are comparing between s and t
*/
int strncmp_md(char *s, char *t, int n){
	int i=0;
	while((*s++==*t++)&&++i<n);
	s--; t--;
	return *s-*t;
}

int main(int argc, char *args[]){
	char name[100];
	char name2[100];
	strncpy_md(name, args[1], 4);//many nicknames in zim are first 4 letters so it was fun to use it to test.
	printf("%s\n", name);
	
}