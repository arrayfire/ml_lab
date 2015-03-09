CPP = g++

deep:  deep_belief_net.cpp
	$(CPP) -I/usr/local/include -o $@ $^ -L/usr/local/lib -lafcuda

deep_solution: solution/deep_belief_net.cpp
	$(CPP) -I. -I/usr/local/include -o $@ $^ -L/usr/local/lib -lafcuda

hello: helloworld.cpp
	$(CPP) -I/usr/local/include -o $@ $^ -L/usr/local/lib -lafcuda

