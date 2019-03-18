/*
	Our binary search makes two tests inside the loop, when one
	would suffice (at the price of more tests outside). Write a version with only one
	test inside the loop and measure the difference in run-time
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

/* binsearch: find x in v[O] <= v[1] <= ••• <= v[n-1] */
int binsearch(int x, int v[], int n){
	int low, mid, high;
	
	low = 0;
	high= n-1;
	mid = (low+high)/2;
	//start timer
	while((low <= high)&&(v[mid]!=x)){
		if(x < v[mid])
			high = mid - 1;
		else 
			low = mid+1;
		mid  = (high+low)/2;
	}
	if(low<=high){
		//end timer
		return mid;
	}
	return -1;
}

int binsearch1(int x, int v[], int n){
	int low, mid, high;
	
	low=0;
	high=n-1;
	//start timer;
	while(low<=high){
		mid = (high+low)/2;
		if(x< v[mid])
			high = mid-1;
		else if(x>v[mid])
			low = mid+1;
		else{
			//end timer;
			return mid;
		}
	}
	//end timer
	return -1;
}

int main(void){
	
	int v[] = {1000009,3012012,4129012,5090129, 6012990,7210310, 8123102,9010220, INT_MAX-1, INT_MAX};
    
	double avg_time_taken = 0;
	for(int i=0;i<1000000; ++i){
		clock_t t = clock(); 
		binsearch1(INT_MAX-2, v, 10);
		t = clock() - t; 
		avg_time_taken += ((double)t)/CLOCKS_PER_SEC;
	}
	printf("%lx\n", CLOCKS_PER_SEC);
	
	
    printf("binsearch1() took %f seconds to execute \n\n", avg_time_taken);
	
	avg_time_taken = 0;
	for(int i=0;i<1000000; ++i){
		clock_t t = clock(); 
		binsearch(INT_MAX-2, v, 10);
		t = clock() - t; 
		avg_time_taken += ((double)t)/CLOCKS_PER_SEC;
	}
    printf("binsearch() took %f seconds to execute \n", avg_time_taken);
}
