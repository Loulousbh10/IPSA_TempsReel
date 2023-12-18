#include <stdio.h>

int main(void) {
	int blbl[] = {0, 2, 4, 6, 8};
	int valuei;

	printf("Enter value to find : \n");
	scanf("%d", &valuei);
	
	for (int i = 0; i < 5; i++) {
    	if (valuei == blbl[i]) {
    		printf("Iteration %d de la liste.\n", i);
    	}
	}	
	return 0;
}
