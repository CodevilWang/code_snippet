CXX=g++
INCLUDE=-I/usr/local/Cellar/boost/1.67.0_1/include
LIBS=-L/usr/local/Cellar/boost/1.67.0_1/lib -lboost_context-mt
CXX_FLAGS=-std=c++11
all: context_test
context_test:
	$(CXX) -g context_test.cpp -o context_test $(INCLUDE) $(LIBS) $(CXX_FLAGS)


