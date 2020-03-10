#include <stdio.h>
/*
Yasin Enes Polat 150117015
This program finds the total ear number of bunnies. Number of bunnies taken from user.
*/
int bunnyEars(int n){ //This function finds the total ears recursively.
	int sum;
	if (n % 2 == 0 && n > 0) { //If the number is even, add 3 to sum.
		sum = bunnyEars(n-1) + 3;
		printf("bunnyEars2 (%d) -> %d \n", n, sum);
		return sum;
	}
	else if (n % 2 == 1 && n > 0) { //If the number is odd, add 2 to sum.
		sum = bunnyEars(n-1) + 2;
		printf("bunnyEars2 (%d) -> %d \n", n, sum);
		return sum;
	}
	else { // If the number is 0, return 0 to previous caller.
		sum = 0;
		printf("bunnyEars2 (%d) -> %d \n", n, sum);
		return sum;
	}
	
}

int main() {
	
	int numofLines;
	printf("Please enter the number of lines: ");
	scanf("%d", &numofLines);
	bunnyEars(numofLines);
	
	return 0;	
}
