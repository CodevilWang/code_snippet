INCLUDE=-I/usr/local/Cellar/boost/1.69.0_2/include/
LIBS=-L/usr/local/Cellar/boost/1.69.0_2/lib -lboost_context-mt -lboost_chrono -lboost_system -lboost_thread-mt
CXX_FLAGS=-std=c++11
all: array_parse
array_parse:
	$(CXX) -g array_parse.cpp -o array_parse $(INCLUDE) $(LIBS) $(CXX_FLAGS)
clean:
	@-rm array_parse 
