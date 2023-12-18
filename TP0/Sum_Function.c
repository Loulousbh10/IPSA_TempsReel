#include <stdio.h>

int Sum(int a, int b) {
	int sum = a + b;
	return sum;
}

int main(void) {
	int a = 3;
	int b = 8;
	int sum = Sum(a, b);
	
	printf("Result = %u\n", sum);

}
