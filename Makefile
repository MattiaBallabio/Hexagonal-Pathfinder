pathfinder: main.o disjointSet.o sampler.o hexoutput.o
	g++ -o pathfinder main.o disjointSet.o sampler.o hexoutput.o

main.o: main.cc hexpathfinder.h disjointSet.h sampler.h queue.h
	g++ -c main.cc

disjointSet.o: disjointSet.cc disjointSet.h
	g++ -c disjointSet.cc

sampler.o: sampler.cc sampler.h
	g++ -c sampler.cc

hexoutput.o: hexoutput.cc hexpathfinder.h
	g++ -c hexoutput.cc