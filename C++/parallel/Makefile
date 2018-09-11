CXX=g++
OPMP_FLAGS=-Xpreprocessor -fopenmp 
INC=-I/usr/local/opt/libomp/include
LIB=-L/usr/local/opt/libomp/lib -lomp
all:
	$(CXX) openmp_test.cpp  -o openmp_test $(OPMP_FLAGS) $(INC) $(LIB) 
openmp_helloworld:
	$(CXX) openmp_helloworld.cpp  -o openmp_helloworld $(OPMP_FLAGS) $(INC) $(LIB) 
openmp_pi:
	$(CXX) pi_cal.cpp  -o pi_cal $(OPMP_FLAGS) $(INC) $(LIB) 
clean:
	@rm openmp_test
