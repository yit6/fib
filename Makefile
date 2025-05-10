all: check gen printnum

check: pisano.o check_fib.c
	cc pisano.o check_fib.c -lgmp -o check

periods: pisano.o pisano_periods.c
	cc pisano.o pisano_periods.c -o periods

gen: gen_fib.c
	cc gen_fib.c -lgmp -o gen -lflint

pisano.o: pisano.c
	cc -c pisano.c

printnum: printnum.c
	cc printnum.c -lgmp -o printnum -lflint

clean:
	rm check periods gen pisano.o printnum
