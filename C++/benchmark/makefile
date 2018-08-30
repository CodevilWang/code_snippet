FLAG_FILE=flags
COMMON_FLAGS=`cat $(FLAG_FILE)`
all:
	g++ vector_bench.cpp $(COMMON_FLAGS) -o vector_bench -lbenchmark
clean:
	@rm vector_bench
