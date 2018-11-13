FLAG_FILE=flags
COMMON_FLAGS=`cat $(FLAG_FILE)`
OPENMP_FLAGS=-Xpreprocessor -fopenmp -lomp
TBB_DEPS=-I/usr/local/Cellar/tbb/2018_U5/include/  -L/usr/local/Cellar/tbb/2018_U5/lib/ -ltbb
FOLLY_DEPS=-I/usr/local/Cellar/folly//2018.08.27.00/include/ -L/usr/local/Cellar/folly//2018.08.27.00/lib/ -lfolly

all:
	g++ vector_bench.cpp $(COMMON_FLAGS) -o vector_bench -lbenchmark
	g++ openmp_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o openmp_bench -lbenchmark
	g++ multi_thread_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o multi_thread_bench -lbenchmark -lpthread
	g++ array_size_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o array_size_benchmark -lbenchmark
div_bench:
	g++ std_div_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o std_div_benchmark -lbenchmark
generate_test:
	g++ generate_test.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o generate_test -lbenchmark
double_add_avx:
	g++ double_add_avx.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o double_add_avx -lbenchmark -mavx
array_add_benchmark:
	g++ array_add_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o array_add_benchmark -lbenchmark
atomic_benchmark:
	g++ atomic_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o atomic_benchmark -lbenchmark
tbb_current_vector_benchmark:
	g++ tbb_current_vector_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o tbb_current_vector_benchmark -lbenchmark $(TBB_DEPS) $(FOLLY_DEPS)

clean:
	-rm vector_bench
	-rm openmp_bench
	-rm multi_thread_bench 
	-rm array_size_benchmark
	-rm std_div_benchmark 
	-rm generate_test 
	-rm double_add_avx 
	-rm array_add_benchmark 
	-rm atomic_benchmark 
	-rm tbb_current_vector_benchmark 