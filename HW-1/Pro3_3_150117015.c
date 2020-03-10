/*
Yasin Enes Polat 150117015
This program implements Sierpinski triangle by taking iteration time from user.
*/

#include <stdio.h>

void draw(int itr, char shapeArr[32][63]) { //This function takes iteration time and array of shape as parameters, then changes corresponding indexes to create appropriate triangles.
		int i, j;
		int temp = itr;
		int nOT = 1; //Number of small triangles.
		while (temp > 0) { //This loop finds the total number of small triangles.
			nOT *= 2;
			temp--;
		}
		int condition = (63 / nOT); //This method finds interval between each '_' at bottom of each small triangles.
		
		if (itr > 0) { //This statement draws triangles recursively.
			for (i = 31; i > 0; i -= 32 / nOT) { //These nested loops changes corresponding '1's to '_'.
				for (j = 0; j < 63; j++) {
					if ((j - (30 - i)) % (condition + 1) == 0 && j != 31 - i && j != 31 + i) {
				
						int n = 0;
						int b = i;
						for (; i > b - (32 / nOT); i--) {
							int f = n;
							for (; f >= 0; f--) {
								if ((j+f) != (31+i) || (j-f) != (31-i)) {
									shapeArr[i][j + f] = '_';
									shapeArr[i][j - f] = '_';
								}
					
							}
						n++;
						}
					i = b;
					}
				}
			//printf("\n");
			}
			draw(itr - 1, shapeArr);
		}		
}

int main() {
	
	int iteration;
	
	printf("Please enter the iteration time: ");
	scanf("%d", &iteration);
	while (iteration > 4) { //This loop checks if user enters a number bigger than 4 or not.
		printf("Please enter a number between 0 and 4: ");
		scanf("%d", &iteration);
	}
	char shapeArr[32][63] = {'-'};
	int i, j;
	for (i = 0; i < 32; i++) { //These nested loops creates the biggest triangle.
		for (j = 0; j < 63; j++) {
					
			if (j >= 31 - i && j <= 31 + i) 
					shapeArr[i][j] = '1';
			else
					shapeArr[i][j] = '_';
			
			//printf("%c", shapeArr[i][j]);
		}
		//printf("\n");
	}
	
	draw(iteration, shapeArr);
	for (i = 0; i < 32; i++) { //These loops prints out the Sierpinski Triangle.
		for (j = 0; j < 63; j++) {
			printf("%c", shapeArr[i][j]);
		}
		printf("\n");
		}
	return 0;
}


	
	

