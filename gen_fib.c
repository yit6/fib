#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

#include <flint/flint.h>
#include <flint/fmpz.h>

int main(int argc, char *argv[])
{
	// Get User Input
	if (argc != 2) {
		printf("usage: %s NUM\n", argv[0]);
		return EXIT_FAILURE;
	}

	long mcount = 0;

	clock_t start_time = clock();
	unsigned long long count = strtoll(argv[1], NULL, 10);

	fmpz_t a, b, c, d; // Current term, previous term, matrix terms
	fmpz_init_set_ui(a, 1);
	fmpz_init_set_ui(b, 0);
	fmpz_init_set_ui(c, 1);
	fmpz_init_set_ui(d, 0);

	fmpz_t c2;
	fmpz_init(c2);

	flint_set_num_threads(4);

	while (count) {
		printf("\r%lld      \n", count);
		if (count % 2 == 0) { // 2x boost
			printf("[   ]\r[");
			fflush(stdout);
			fmpz_mul(c2, c, c);
			printf(".");
			fflush(stdout);
			fmpz_mul(c, c, d);
			printf(".");
			fflush(stdout);
			fmpz_mul_2exp(c, c, 1);
			fmpz_mul(d, d, d);
			printf(".");
			fflush(stdout);
			fmpz_add(c, c, c2);
			fmpz_add(d, d, c2);

			mcount += 3;
			count /= 2;
		} else { // Increment
			printf("[    ]\r[");
			fflush(stdout);
			fmpz_mul(c2, a, c);
			printf(".");
			fflush(stdout);
			fmpz_mul(a, a, d);
			printf(".");
			fflush(stdout);
			fmpz_addmul(a, b, c);
			printf(".");
			fflush(stdout);
			fmpz_add(a, a, c2);
			fmpz_mul(b, b, d);
			printf(".");
			fflush(stdout);
			fmpz_add(b, b, c2);
			mcount += 4;
			count--;
		}
	}

	clock_t end_time = clock();
	double taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;

	printf("\ncalculation time: %f seconds\n", taken);
	printf("%lu multiplications taken\n", mcount);

	FILE* fp = fopen("fib.fmpz", "w");
	fmpz_out_raw(fp, b);
	fclose(fp);

	printf("result saved to \'fib.fmpz\'\n");

	fmpz_clear(a);
	fmpz_clear(b);
	fmpz_clear(c);
	fmpz_clear(d);
	fmpz_clear(c2);

	return 0;
}
