#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define CHECK_CALL(call, error_value)                                                   \
	do {                                                                                \
		if ((call) == error_value) {                                                    \
			fprintf(stderr,                                                             \
				"Call %s failed with an error message: (%s) at file %s at line %d\n",   \
				#call, strerror(errno), __FILE__, __LINE__);                            \
			exit(EXIT_FAILURE);                                                         \
		}                                                                               \
	} while (0);

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("Wrong number of arguments!\n");
		exit(1);
	}

	int count_nums = 0, k, result = 0, size = 1, sum = 0, num, *array;
	FILE *fp;

	// Command line arguments
	CHECK_CALL(fp = fopen(argv[1], "r"), NULL);
	k = atoi(argv[2]);

	CHECK_CALL(array = malloc(sizeof(int)), NULL);

	// Read file with data
	while (fscanf(fp, "%d", &num) == 1) {
		array = realloc(array, (count_nums + 1) * sizeof(int));
		array[count_nums] = num;
		count_nums++;
	}

	printf("\nArray: ");
	for (int i = 0; i < count_nums; i++) {
		printf("%d ", array[i]);
	}
	printf("\n\n");

	// Size of number sequence
	for (int i = 1; i <= count_nums; i++) {
		// First number of the sequence
		for (int j = 0; j < count_nums; j++) {
			sum = 0;
			// Create a sequence of a specific size
			if (j + i <= count_nums) {
				for (int t = j, count = 0; t < count_nums, count < i; t++, count++) {
					sum += array[t];
				}
				// Potential sum that could be divided by k
				if (sum % k == 0) {
					result++;
					for (int s = j; s < i + j; s++) {
						printf("%d ", array[s]);
					}
					printf("\n");
				}	
			}
			// Not another sequence from here on. Go to the next size
			else {
				break;
			}
		}
	}

	printf("\nResult: %d\n\n", result);
	fclose(fp);
	free(array);

	return 0;
}