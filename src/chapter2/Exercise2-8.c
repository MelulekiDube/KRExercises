/*
	Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit position
*/
#include <stdlib.h>
#include <stdio.h>

unsigned getbits(unsigned x, int p, int n){
	unsigned mask = ~(~0<<n); //create the bitmask
	unsigned x_right = x>>(p+1-n); //isolate the n bits from in x beginning at p
	return x_right & mask; //returning the only the n bits we are intreseted in
}

unsigned rightrot(unsigned x, int n){
	
	unsigned last_n = getbits(x, n-1, n);//gets me the last n bits
	x = x >> n; //we now have to fill the last first n from the msb with the last n;
	
	unsigned set_bits = last_n<<((sizeof(unsigned)*8)-n);
	x |= set_bits;
	return x;
}

int main(void){
	printf("%x", rightrot(0xAAAAAAA5, 4));//expect 5AAAAAAA
}



