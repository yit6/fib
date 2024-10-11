# Fibonacci Suite

Set of programs to generate, verify and print large fibonacci numbers.

## Building

```sh
make all
```

## Usage

### Generate

Run the `gen` command to generate a large number, and store it in the file `fib.mpz`.

Example:
```sh
./gen 10000000000
```

### Check

Check if the fibonacci number has the right remainders in all bases up to 1000.

Example:
```sh
./check fib.mpz 10000000000
```

### Print

Print a number loaded from a mpz file.

Example:
```sh
./printnum fib.mpz
```
