#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

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

	mpz_t a, b, c, d; // Current term, previous term, matrix terms
	mpz_init_set_ui(a, 1);
	mpz_init_set_ui(b, 0);
	mpz_init_set_ui(c, 1);
	mpz_init_set_ui(d, 0);

	mpz_t c2;
	mpz_init(c2);

	while (count) {
		printf("%lld\n", count);
		if (count % 2 == 0) { // 2x boost
			mpz_mul(c2, c, c);
			mpz_mul(c, c, d);
			mpz_mul_2exp(c, c, 1);
			mpz_mul(d, d, d);
			mpz_add(c, c, c2);
			mpz_add(d, d, c2);

			mcount += 3;
			count /= 2;
		} else { // Increment
			mpz_mul(c2, a, c);
			mpz_mul(a, a, d);
			mpz_addmul(a, b, c);
			mpz_add(a, a, c2);
			mpz_mul(b, b, d);
			mpz_add(b, b, c2);
			mcount += 4;
			count--;
		}
	}

	clock_t end_time = clock();
	double taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;

	printf("\ncalculation time: %f seconds\n", taken);
	printf("%lu multiplications taken\n", mcount);

	FILE* fp = fopen("fib.mpz", "w");
	mpz_out_raw(fp, b);
	fclose(fp);

	printf("result saved to \'fib.mpz\'\n");

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(d);
	mpz_clear(c2);

	return 0;
}
