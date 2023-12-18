#include <stdio.h>

int main(void) {
	int a;
	int b;
	printf("Enter a : \n");
	scanf("%d", &a);
	printf("Enter b : \n");
	scanf("%d", &b);
	if (a<b) {
		printf("b is greater \n", b);
	}else{
		printf("a is greater \n", a);
	}

}
