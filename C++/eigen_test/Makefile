EIGEN_INC=-I/usr/local/Cellar/eigen/3.3.7/include/eigen3/

all:
	g++ tensor_map_test.cpp -O3 -std=c++11  -o tensor_map_test $(EIGEN_INC)
	g++ tensor_rows_binary_search_test.cpp -O3 -std=c++11  -o tensor_rows_binary_search_test $(EIGEN_INC)

clean:
	-rm tensor_map_test 
	-rm tensor_rows_binary_search_test 
