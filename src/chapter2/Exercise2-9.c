/*

	In a two's complement number system, x &.= (x-1) deletes the rightmost l-bit in x. Explain why. Use this observation to write a faster version of bitcount.

Answer: to the first part of the question

If we had any number, subtracting 1 from it, will result in the right most bit being changed the value to zero example:
			       x  x is the rightmost 1-bit. 
			 10101010     111111111
			-       1
			 10101000
This is because the rightmost 1-bit in the x bit will be the first real bit that wll be able to subtract 1 without requiring a borrow. Hence this bit will be a 0. 

The bits before this will be a 1 and those after this bit will be a as they where.
when we and x with (x-1) we see the following
Now i&i = x and i&1 = i, therefore the other bits are going to be what they where and the only bit which will change will be where the rightmost 1-bit was as that is the bit that changed to 0 and i&0 is 0;
*/
#include <stdlib.h>
#include <stdio.h>

int bitcount(unsigned x){
	int b = 0;
	for(; x!=0; (x&=(x-1)))
		++b;
	return b;
}

int main(void){
	unsigned test_value = 0xAA;
	printf("number of 1-bits in %X is %d", test_value ,bitcount(test_value));//expect 4
}