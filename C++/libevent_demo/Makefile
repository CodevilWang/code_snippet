CXX=g++
INC=-I/usr/local/Cellar/libevent/2.1.8/include
LIBS=-L/usr/local/Cellar/libevent/2.1.8/lib -levent

all:
	$(CXX) libevent_server0.cpp -o libevent_server0 -O3 $(INC) $(LIBS)
	$(CXX) libevent_server1.cpp -o libevent_server1 -O3 $(INC) $(LIBS)
clean:
	@rm libevent_server0
	@rm libevent_server1
