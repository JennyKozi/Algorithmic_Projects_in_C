#include <stdio.h>

#define MAXNUM 10000000

int main (void) {
	int num, i, K = 1, temp, temp2 = 1, sum, div, SY, count, children, count_mp = 0, count_abundant = 0, count_both = 0;

	printf("\nChecking numbers from [1, %d]\n", MAXNUM);
	printf("\nNumbers both one-child and abundant:\n");

	for (num = 1; num <= MAXNUM; num++) {
		sum = 1;
		div = 1;
		children = 0;
		
		// K = Number of digits in the number
		if (num >= 10 * temp2) {
			K++;
			temp2 *= 10;
		}

		// Find all of the SY and check for children
		for (i = 1; i <= K; i++) { // i = Number of digits in SY
			temp = num;
			count = 0; // Number of SY with i digits
			div *= 10;
			while (count <= K-i && temp != 0) {
				SY = temp % div;
				if (SY % K == 0) {
					children++;
					if (children == 2)
						break;
				}
				count++;
				temp = temp / 10;
			}
			if (children == 2)
				break;
		}

		// Find sum of divisors to check if the num is abundant
		for (div = 2; div * div < num; div++) {
			if (num % div == 0)
				sum += div + (num / div);
		}
		if (num == div * div)
			sum += div;

		// Check and print
		if (sum > num) { // num is abundant
			count_abundant++;
			if (children == 1) { // num is MP and abundant
				count_mp++;
				count_both++;
				printf("%d  ", num);
				if (count_both % 15 == 0)
					printf("\n");
			}
		}
		else if (children == 1) // num is MP
			count_mp++;
	}

	// Print results
	printf("\n\nFound %d one-child numbers\n", count_mp);
	printf("Found %d abundant numbers\n", count_abundant);
	printf("Found %d numbers in both classes\n\n", count_both);
	
	return 0;
}
