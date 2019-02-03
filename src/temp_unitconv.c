#include <stdio.h>
#include <string.h>

float convert_temp(float F);

int main1(int argv, char*argc[]){
	float celc, fehr;
	int lower, upper, step;
	printf("%i\n", argv);
	if(argv == 2){
		fehr = atoi(argc[1]);
		celc = convert_temp(fehr);
		printf("Converting input %f F to %f C\n", fehr, celc);
	}else{
		lower =0; /* lower limit of the temperature table*/
		upper = 300; /* upper limit of the temperature table*/
		step = 20; /* increment of the temperature table*/
		printf("************** Temperature conversion Table ");
		printf("**************\n");
		while(lower <= upper){
			fehr = lower;
			celc = convert_temp(fehr);
			printf("%3.0f %6.1f\n", fehr, celc);
			lower += step;
		}
	}
    return 0;
}

float convert_temp(float f){
	return (5.0/9.0)*(f-32);
}
