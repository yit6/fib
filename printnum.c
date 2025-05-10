#include <stdio.h>
#include <flint/flint.h>
#include <flint/fmpz.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: ./printnum [gmp file]");
		return -1;
	}

	fmpz_t num;

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		printf("Failed to open file \"%s\".", argv[1]);
		return -1;
	}

	fmpz_inp_raw(num, fp);
	fclose(fp);

	// Put status info to stderr so it doesn't get piped or redirected
	fprintf(stderr, "Converting to base 10\n");
	fflush(stderr);

	fmpz_print(num);
	fflush(stdout);

	// See above
	fprintf(stderr, "\n");
	fflush(stderr);
}
