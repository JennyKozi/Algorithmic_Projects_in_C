#define MINNUM 2100000000
#define MAXNUM 2101000000
#define MAXK 5
#define COMPUTATIONS 20
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	int n, i, a, b, x, y, z, num, temp, count, semiprimes = 0, total = 0;
	double c;
	long curtime;

	printf("\nChecking numbers from [%d, %d]\n\n", MINNUM, MAXNUM);
	for (num = MINNUM; num <= MAXNUM; num++) {
		temp = num;
		count = 0;
		a = 0;
		b = 0;

		while (temp % 2 == 0) {	// Checking to see if the number is even, so we divide by 2
			temp = temp / 2; // Note: If a number is even, it is definately not an interesting semiprime
			count++; // Every time the division is perfect, increase the number of prime factors by 1
		}
		while (temp % 3 == 0) {	// Checking to see if the number is divided by 3
			temp = temp / 3; // Note: If a number is divided by 3, it is definately not an interesting semiprime
			count++; // Every time the division is perfect, increase the number of prime factors by 1
		}
		for (n = 5; n * n <= num; n = n + 6) { // Checking for divisors that are not multiples of 2 and 3
			while (temp % n == 0) {
				temp = temp / n;
				count++; // Every time the division is perfect, increase the number of prime factors by 1
				if (count == 1)
					a = n; // The value of a is the first prime factor
			}
			while (temp % (n + 2) == 0) {
				temp = temp / (n + 2);
				count++; // Every time the division is perfect, increase the number of prime factors by 1
				if (count == 1)
					a = n + 2; // The value of a is the first prime factor
			}
		}
		if (temp > 1) // We still haven't found all of the prime factors
			count++; // There is only one prime factor bigger than sqrt(num)
		if (count == 2 && a != 0) // If we have an odd semiprime
			b = (num / a); // Calculate the second prime factor

		c = (99 * (double)b) / 100;
		if (count == 2)	// If the number has 2 prime factors
			semiprimes++;
		if (2 <= count && count <= MAXK) // If the number has 2-MAXK prime factors
			total++;
		if (count == 2 && a != b && a >= c) // If the number has the qualifications
			printf("An interesting semiprime is %d = %d * %d\n", num, a, b);
	}
	printf("\nFound %d k-almost prime numbers, 2<=k<=%d\n", total, MAXK);
	printf("Found %d semiprimes\n", semiprimes);

	curtime = time(NULL); // Current time
	srand((unsigned int) curtime); // Seed for random number generator
	printf("\nCurrent time is %ld\n", curtime);
	printf("\nChecking %d random numbers:\n\n", COMPUTATIONS);

	for (i = 0; i < COMPUTATIONS; i++) {
		count = 0;
		y = rand(); // Select first number
		z = rand(); // Select second number
		x = ((y % 32768) + 1) * ((z % 32768) + 1) + 1; // Calculate x
		temp = x;

		while (temp % 2 == 0) { // Checking to see if the number is even, so we divide by 2
			temp = temp / 2;
			count++; // Every time the division is perfect, increase the number of prime factors by 1
		}
		while (temp % 3 == 0) { // Checking to see if the number is divided by 3
			temp = temp / 3;
			count++; // Every time the division is perfect, increase the number of prime factors by 1
		}
		for (n = 5; n * n <= x; n = n + 6) { // Checking for divisors that are not multiples of 2 and 3
			while (temp % n == 0) {
				temp = temp / n;
				count++; // Every time the division is perfect, increase the number of prime factors by 1
 			}
			while (temp % (n + 2) == 0) {
				temp = temp / (n + 2);
				count++; // Every time the division is perfect, increase the number of prime factors by 1
			}
		}
		if (temp > 1) // There is one prime factor bigger than sqrt(x)
			count++; // Increase the number of prime factors by 1

		printf("%d is a %d-almost prime number\n", x, count);
	}
	printf("\n");

	return 0;
}
