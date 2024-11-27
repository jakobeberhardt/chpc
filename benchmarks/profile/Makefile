CC = clang
CFLAGS = -O1 \
    -fno-inline \
    -fno-unroll-loops \
    -fno-vectorize \
    -fno-slp-vectorize \
    -fno-builtin \
    -fno-omit-frame-pointer \
    -fno-merge-all-constants

SRCS = main.c
OBJS = main.o

all: main

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main main.o main_restricted main_boosting main_restricted_pgo main_boosting_pgo main.prof *.profdata *.profraw

main_restricted: main.c
	$(CC) $(CFLAGS) -o main_restricted main.c -mllvm -enable-misched=false

main_boosting: main.c
	$(CC) $(CFLAGS) -o main_boosting main.c -mllvm -enable-misched=true

benchmark: main_restricted main_boosting
	@echo "Running Restricted Code Percolation version..."
	./main_restricted 100000000 0.80
	@echo "Running Boosting Code Percolation version..."
	./main_boosting 100000000 0.80

# rules for profiling and using profile data
main.prof: main.c
	$(CC) -O2 -fprofile-instr-generate -o main.prof main.c

default.profraw: main.prof
	@echo "Running instrumented program to collect profile data..."
	./main.prof 100000000 0.99

profile.profdata: default.profraw
	@echo "Merging profile data..."
	llvm-profdata merge -output=profile.profdata default.profraw

main_restricted_pgo: main.c profile.profdata
	$(CC) $(CFLAGS) -fprofile-instr-use=profile.profdata -o main_restricted_pgo main.c -mllvm -enable-misched=false

main_boosting_pgo: main.c profile.profdata
	$(CC) $(CFLAGS) -fprofile-instr-use=profile.profdata -o main_boosting_pgo main.c -mllvm -enable-misched=true

benchmark_pgo: main_restricted_pgo main_boosting_pgo
	@echo "Running Restricted Code Percolation version with PGO..."
	./main_restricted_pgo 200000000 0.01
	@echo "Running Boosting Code Percolation version with PGO..."
	./main_boosting_pgo 200000000 0.01
