
/*
	Answers to Exercise 2-4
	@Author: Meluleki Dube
	17 March 2019
	
	Write an alternate version of squeeze (s1,s2) that deletes each character in s1 that matches any character in the string s2.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 256 //assumes utf8 

void squeeze(char s1[], const char s2[]){
	int freq_table[LENGTH] = {0};//works becoz LENGTH is a constant and is known at compile time
	int i = 0, j, c;
	//populate the frequency table with chars of s2
	while((c=s2[i++])!='\0'){
		++freq_table[c];
	}
	
	//now loop through s1 to see if anything from s1 is in the freq_table
	i=0; j =0;
	while((c= s1[i++])!='\0'){
		if(!freq_table[c])//if this char is not in freq_table then we can add it to s2
			s1[j++] = c;
	}
	s1[j] = '\0';
}

int main(void){
	char s1[] = "Meluleki";
	char s2[] = "Mellar";
	squeeze(s1, s2);
	printf("%s", s1);
}