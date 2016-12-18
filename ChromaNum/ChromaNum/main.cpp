#include "Graph.h"


int main() {
	Graph g;
	std::ifstream fs;
	fs.open("input.txt");
	g.Load(fs);
	g.Chroma(FAST);
	std::cin.get();
	return 0;
}