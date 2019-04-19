CXX=/opt/compiler/gcc-4.8.2/bin/g++
INCLUDE=-I/home/work/tr07/ann/test/boost-1-66-0/include/
LIBS=-L/home/work/tr07/ann/test/boost-1-66-0/lib -lboost_context -lboost_chrono -lboost_system -lboost_thread
CXX_FLAGS=-std=c++11
all: context_test
context_test:
	$(CXX) -g context_test.cpp -o context_test $(INCLUDE) $(LIBS) $(CXX_FLAGS) -Wl,-rpath=/home/work/tr07/ann/test/boost-1-66-0/lib
clean:
	@-rm context_test
