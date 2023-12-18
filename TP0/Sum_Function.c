#include <stdio.h>

float Sum(float a, float b) {
	
	float sum = a + b;
	return sum;
}

int main(void) {
	float a;
	float b;
	printf("Enter a : \n");
	scanf("%f", &a);
	printf("Enter b : \n");
	scanf("%f", &b);
	float sum = Sum(a, b);
	
	printf("Result = %f\n", sum);

}
