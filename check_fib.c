#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define MAX_BASE 1000

long fib_remainder_base(long, long);

/* Get a number and index from the user,
 * and check if the remainders match up */
int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage: ./check [gmp file] [index]\n");
		return -1;
	}

	unsigned long long index = strtoll(argv[2], NULL, 10), lremainder;
	if (index == 0 && *argv[2] != '0') {
		printf("Failed to parse \"%s\" as integer", argv[2]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		printf("Failed to open file \"%s\".", argv[1]);
		return -1;
	}

	mpz_t num, remainder;
	mpz_inp_raw(num, fp);
	fclose(fp);
	
	for (int base = 2; base <= MAX_BASE; ++base) {
		mpz_mod_ui(remainder, num, base);
		lremainder = fib_remainder_base(index, base);
		gmp_printf("base %4ld: %4ld, %4Zd\n", base, lremainder, remainder);
		if (mpz_cmp_ui(remainder, lremainder)) {
			printf("Failed check\n");
			return 0;
		}
	}

	printf("Passed all bases up to %d.\n", MAX_BASE);
}
