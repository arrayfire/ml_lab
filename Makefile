CPP = g++

all: dbn

dbn:  deep_belief_net.cpp mnist_common.h Makefile
	$(CPP) -I/usr/local/include $< -L/usr/local/lib -lafcuda -o $@

per:  perceptron.cpp mnist_common.h Makefile
	$(CPP) -I/usr/local/include $< -L/usr/local/lib -lafcuda -o $@

deep_solution: solution/deep_belief_net.cpp
	$(CPP) -I. -I/usr/local/include $^ -L/usr/local/lib -lafcuda -o $@

per_solution: solution/perceptron.cpp
	$(CPP) -I. -I/usr/local/include $^ -L/usr/local/lib -lafcuda -o $@

hello: helloworld.cpp
	$(CPP) -I/usr/local/include $^ -L/usr/local/lib -lafcuda -o $@

