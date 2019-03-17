/*****
Exercise 2·3
*/
#include <stdlib.h>
#include <stdio.h>

/*checks if the given character is part of the characters that make up the hex digits*/
int is_hex_digit(const char c){
	return (c>='0'&&c<='9') || (c>='a'&&c<='f') || (c>='A'&&c<='F');
}

/*converts hex digit char into the equivalent int*/
int  ctoi(const char c){
	if((c>='0'&&c<='9'))
		return c-'0';
	else if((c>='a'&&c<='f') )
		return 10+(c-'a');
		return 10 + (c - 'A');
}

/*this method converts a hex string to it's equivalent int value*/
int htoi(const char s[]){
	//variable declaration
	int i, num;
	
	//variable initialization
	num = 0;
	i = 0;
	
	//first check if the string begins with 0x or 0x
	if((s[i]!='\0')/*avoid checking empty string*/&&(s[i]=='0'&&(s[i+1]=='x'||s[i+1]=='X'))){
		i=2;
	}
	
	//loop through the character producing the represented number
	while(is_hex_digit(s[i])){
		num = (16*num)+(ctoi(s[i++]));
	}
	//return the answer
	return num;
}

int main(void){
	char * nums[] = {"0xa" /*return 10 */
			,"0X0b" // returns 11
			,"ab" //equivalent to 16*10+11 = 171
			,"0x1a" // equivalent to 16+10 = 26
			,"0X1Ab" // equivalent to (16*16)+(16*10)+11
			,"0x12ab"
	};
	
	for(int i=0; i<6; ++i){
		printf("Value of %s is %d\n", nums[i], htoi(nums[i]));
	}
	
	return 0;
}