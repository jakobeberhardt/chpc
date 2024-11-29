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

main_restricted: main.c
	$(CC) $(CFLAGS) -o main_restricted main.c -mllvm -enable-misched=false -mllvm -avoid-speculation=true

main_boosting: main.c
	$(CC) $(CFLAGS) -o main_boosting main.c -mllvm -enable-misched=true -mllvm -avoid-speculation=false

benchmark: main_restricted main_boosting
	./main_restricted 600000000 0.0
	./main_boosting 600000000 0.0

main.prof: main.c
	$(CC) $(CFLAGS) -fprofile-instr-generate -o main.prof main.c

default.profraw: main.prof
	./main.prof 1000000 0.99

profile.profdata: default.profraw
	llvm-profdata merge -output=profile.profdata default.profraw

main_restricted_pgo: main.c profile.profdata
	$(CC) $(CFLAGS) -fprofile-instr-use=profile.profdata -o main_restricted_pgo main.c -mllvm -enable-misched=false -mllvm -avoid-speculation=true

main_boosting_pgo: main.c profile.profdata
	$(CC) $(CFLAGS) -fprofile-instr-use=profile.profdata -o main_boosting_pgo main.c -mllvm -enable-misched=true -mllvm -avoid-speculation=false

benchmark_restricted: main_restricted_pgo
	@echo "Benchmarking main_restricted with profiling..."
	@count=5; \
	for i in `seq 1 $$count`; do \
		time=`./main_restricted_pgo 600000000 1.0`; \
		echo "Run $$i: $$time seconds"; \
	done; 

benchmark_boosting: main_boosting_pgo
	@echo "Benchmarking main_boosting with profiling..."
	@count=5; \
	for i in `seq 1 $$count`; do \
		time=`./main_boosting_pgo 600000000 1.0`; \
		echo "Run $$i: $$time seconds"; \
	done; 

benchmark_unprofiled: main_restricted
	@echo "Benchmarking main_restricted without profile..."
	@count=5; \
	for i in `seq 1 $$count`; do \
		time=`./main_restricted 600000000 1.0`; \
		echo "Run $$i: $$time seconds"; \
	done; 

clean:
	rm -f main main.o main_restricted main_boosting main_restricted_pgo main_boosting_pgo main.prof *.profdata *.profraw
