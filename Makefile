BENCHMARK_DIRS := $(wildcard benchmarks/*)
BENCHMARKS := $(notdir $(BENCHMARK_DIRS))

.PHONY: all clean run

all: $(BENCHMARKS)

$(BENCHMARKS):
	@echo "Building benchmark: $@"
	@$(MAKE) -C benchmarks/$@ all

clean:
	@for dir in $(BENCHMARKS); do \
		echo "Cleaning benchmark: $$dir"; \
		$(MAKE) -C benchmarks/$$dir clean; \
	done

run:
	@for dir in $(BENCHMARKS); do \
		echo "Running benchmark: $$dir"; \
		./benchmarks/$$dir/$$dir; \
	done
