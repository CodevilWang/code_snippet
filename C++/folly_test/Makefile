CXX=g++
all:
	$(CXX) fbstring_test.cpp -o fbstring_test -std=c++14 -I/usr/local/Cellar/folly/2018.08.27.00/include -L/usr/local/Cellar/folly/2018.08.27.00/lib -lfolly
	$(CXX) logging_test.cpp -o logging_test -std=c++14 -I/usr/local/Cellar/folly/2018.08.27.00/include -L/usr/local/Cellar/folly/2018.08.27.00/lib -lfolly
	$(CXX) threaded_pool_ex_test.cpp -o threaded_pool_ex_test -std=c++11 -I/usr/local/Cellar/folly/2018.08.27.00/include -L/usr/local/Cellar/folly/2018.08.27.00/lib -lfolly
clean:
	@rm fbstring_test
	@rm logging_test 
	@rm threaded_pool_ex_test 
	
