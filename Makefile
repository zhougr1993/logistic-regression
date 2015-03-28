CPPFLAGS=-g -Wall 
CXX = g++

LIBS= -L /usr/include/

logistic_gd: logistic_gd.cpp util.hpp data_loader.hpp
	$(CXX) $(CPPFLAGS) logistic_gd.cpp ${LIBS} -o logistic_gd

clean:
	rm -rf  *.o  logistic_gd
