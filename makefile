Ex: Explore_map.o Object.o
	g++ -o Ex Explore_map.o Object.o

Explore_map.o: Explore_map.cpp Object.o
	g++ -c Explore_map.cpp

Object.o: Object.cpp Object.o
	g++ -c Object.cpp