FLAG_FILE=flags
COMMON_FLAGS=`cat $(FLAG_FILE)`
OPENMP_FLAGS=-Xpreprocessor -fopenmp -lomp
all:
	g++ vector_bench.cpp $(COMMON_FLAGS) -o vector_bench -lbenchmark
	g++ openmp_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o openmp_bench -lbenchmark
	g++ multi_thread_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o multi_thread_bench -lbenchmark -lpthread
	g++ array_size_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o array_size_benchmark -lbenchmark
clean:
	@rm vector_bench
	@rm openmp_bench
	@rm multi_thread_bench 
	@rm array_size_benchmark

