FLAG_FILE=flags
COMMON_FLAGS=`cat $(FLAG_FILE)`
OPENMP_FLAGS=-Xpreprocessor -fopenmp -lomp
TBB_DEPS=-I/usr/local/Cellar/tbb/2018_U5/include/  -L/usr/local/Cellar/tbb/2018_U5/lib/ -ltbb
FOLLY_DEPS=-I/usr/local/Cellar/folly/2019.03.18.00_2/include/ -L/usr/local/Cellar/folly/2019.03.18.00_2/lib/ -lfolly
EIGEN_INC=-I/usr/local/Cellar/eigen/3.3.7/include/eigen3/

all:
	g++ vector_bench.cpp $(COMMON_FLAGS) -o vector_bench -lbenchmark
	g++ openmp_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o openmp_bench -lbenchmark
	g++ multi_thread_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o multi_thread_bench -lbenchmark -lpthread
	g++ array_size_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o array_size_benchmark -lbenchmark
	g++ strlen_test.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o strlen_test_benchmark -lbenchmark -std=c++17
	g++ tbb_current_vector_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o tbb_current_vector_benchmark -lbenchmark $(TBB_DEPS) $(FOLLY_DEPS)
	g++ current_inc_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o current_inc_benchmark -lbenchmark $(FOLLY_DEPS) -lpthread
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
string_ret_bench:
	g++ string_ret_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o string_ret_bench -lbenchmark $(TBB_DEPS) $(FOLLY_DEPS)

strlen_test:
	g++ strlen_test.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o strlen_test_benchmark -lbenchmark $(TBB_DEPS) $(FOLLY_DEPS) -std=c++17
current_inc:
	g++ current_inc_benchmark.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o current_inc_benchmark -lbenchmark $(FOLLY_DEPS) -lpthread

lock_guard_uniq_lock:
	g++ lock_guard_uniq_lock.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -o lock_guard_uniq_lock -lbenchmark $(FOLLY_DEPS) -lpthread

eigen_bench:
	g++ eigen_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -Wno-unused-variable -o eigen_bench -lbenchmark $(EIGEN_INC)

time_eigen_product:
	g++ time_eigen_product.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -Wno-unused-variable -o time_eigen_product $(EIGEN_INC) -mavx

mv_bench:
	g++ mv_bench.cpp $(COMMON_FLAGS) $(OPENMP_FLAGS) -Wno-unused-variable -o mv_bench -lbenchmark $(EIGEN_INC) -mavx

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
	-rm strlen_test_benchmark 
	-rm current_inc
	-rm string_ret_bench
	-rm eigen_bench 
	-rm time_eigen_product 
	-rm lock_guard_uniq_lock
	-rm mv_bench 
