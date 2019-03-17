/*
Exercise 2-5. Write the function any (s 1, s2 ), which returns the first location
in the string s1 where any character from the string s2 occurs, or -1 if s1
contains no characters from s2. (The standard library function strpbrk does
the same job but returns a pointer to the location.) 
*/

#include <stdlib.h>
#include <stdio.h>

#define LENGTH 256 //assumes utf8 

int any(char s1[], char s2[]){
	int freq_table[LENGTH] = {0};//works becoz LENGTH is a constant and is known at compile time
	int i = 0, c;
	//populate the frequency table with chars of s2
	while((c=s2[i++])!='\0')
		++freq_table[c];
	
	i = 0; 
	
	while((c=s1[i++])!='\0')
		if(freq_table[c])
			return i; // we return the index of character not 0-indexed : therfore index 0 will return 1
	
	return -1;
}

int main(void){
	char s1[] = "Meluleki";
	char s2[] = "lol";
	printf("%d", any(s1, s2)); //expect 3 
	return 0;
}

