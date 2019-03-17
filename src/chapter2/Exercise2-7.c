/*
	Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., I changed into 0 and vice versa), leaving the others unchanged
*/
#include <stdlib.h>
#include <stdio.h>

unsigned invert(unsigned x, int p, int n){
	int shift_by = p - n + 1;
	unsigned mask = ~(~0<<n);
	mask = mask << shift_by;
	
	x ^= mask;
	return x;
}

int main(void){
	printf("%x", invert(0xAB, 5, 3));//expect 92
}