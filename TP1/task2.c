#include <stdio.h>

int main() {
	double celsius;
    double fahrenheit = 98.60;
    celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
    printf("The temperature in Fahrenheit is %.2f, so the temperature in Celsius is: %.2f\n", fahrenheit, celsius);
}
