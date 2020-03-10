/*
Yasin Enes Polat 150117015
This program first concatenates the given number by given times, then finds its super digit.
*/

#include <stdio.h>
long int concatenate(int, int);
long int super_digit(int);
int main () {
	
	int n, k;
	long int x;
	printf("Please enter a number: ");
	scanf("%d", &n);
	printf("Please enter repetition factor: ");
	scanf("%d", &k);
	
	x = concatenate(n, k);
	
	printf("Super digit of number %ld is %d.\n", x, super_digit(x));
	//printf("deneme %ld", super_digit(x));
	
	return 0;
}
long int sumOfNumbers(int n) { //This function finds the sum of the given number's digits.
	if (n > 9) {
		return n % 10 + sumOfNumbers(n / 10);
	}
	else {
		return n;
	}
}

long int super_digit(int n) { //This function finds the super digit of concatenated number recursively.
	int x = sumOfNumbers(n);
	if (x > 9) {
		return super_digit(x);
	}
	else {
		return x;
	}
}

long int concatenate(int n, int k) { //This function concatenates the given number by given times recursively.
	long int f;
	int digit;
	digit = 1;
	f = n;
	while (f > 0) { //This loop finds the total digit of given number.
		if (f / 10 > 0)
			digit++;
	f /= 10;			
	}
	f = 1;
	while (digit > 0) {
		f *= 10;
		digit--;
	}
	if (k > 1) {
		return concatenate(n, k-1) * f + n;
	}
	else {
		return n;
	}
}
