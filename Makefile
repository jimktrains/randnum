CXX=g++
CXXFLAGS=--std=c++1z

all: randnum

randnum: randnum.o
	$(CXX) $(CXXFLAGS) -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
