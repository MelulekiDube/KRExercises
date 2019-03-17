/* 
	Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/
#include <stdlib.h>
#include <stdio.h>


unsigned getbits(unsigned x, int p, int n){
	unsigned mask = ~(~0<<n); //create the bitmask
	unsigned x_right = x>>(p+1-n); //isolate the n bits from in x beginning at p
	return x_right & mask; //returning the only the n bits we are intreseted in
}

unsigned setbits(unsigned x, int p, unsigned n, int y) {
	int shift_number = p - n +1;
	/*0...0->1...1->1(31-1 repeating)0n0*/
	unsigned y_n_bits = getbits(y, n-1, n);//gets me n y bits
	//now we want to push these to the right so left so the msb bit is aligned at positing p for x;
	y_n_bits = (y_n_bits << shift_number); //CORRECT
	//first clear the bits you want to write to and then set them later with 
	unsigned clear_mask = (~(~0<<n));/* gives me n ones*/
	clear_mask = ~(clear_mask <<  shift_number);
	x &= clear_mask;
	x |= y_n_bits;
	return x;
}

int main(void){
	printf("%x", setbits(0xAB, 5, 3, 0xAA));
}