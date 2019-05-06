CXX=g++
VERSION=2019.03.18.00_2
all:
	$(CXX) fbstring_test.cpp -o fbstring_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly
	# $(CXX) logging_test.cpp -o logging_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly
	$(CXX) threaded_pool_ex_test.cpp -o threaded_pool_ex_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly -DTHREAD_POOL_EX
	$(CXX) io_record_test.cpp -o io_record_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly
	$(CXX) async_timeout_test.cpp -o async_timeout_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly
	# $(CXX) future_test.cpp -o future_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly /usr/local/opt/glog/lib/libglog.dylib
	$(CXX) future_vec.cpp -o future_vec -std=c++14
	$(CXX) rcu_test.cpp -o rcu_test -std=c++14 -I/usr/local/Cellar/folly/$(VERSION)/include -L/usr/local/Cellar/folly/$(VERSION)/lib -lfolly -lpthread /usr/local/opt/glog/lib/libglog.dylib
clean:
	@rm fbstring_test
	# @rm logging_test 
	@rm threaded_pool_ex_test 
	@rm io_record_test 
	@rm async_timeout_test 
	# @rm future_test 
	@rm future_vec
	@rm rcu_test  
	
