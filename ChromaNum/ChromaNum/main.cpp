#include "Graph.h"


int main() {
	Graph g;
	Algorithm type;
	std::ifstream fs;
	std::string fn;
	std::cout << "Use exact algorythm? Y/n" << std::endl;
	(std::cin.get() == 'n') ? (type = FAST) : (type = EXACT);
	std::cout << "Type in name of input file" << std::endl;
	std::cin >> fn;
	fs.open("fn");
	std::cin.clear();
	try {
		g.Load(fs);
		g.Chroma(type);
	}
	catch (int e) {
		if (!e) {
			std::cout << "No file found/access denied" << std::endl;
			std::cin.get();
			return 1;
		}
		if (e == 1) {
			std::cout << "Someone has changed bits in memory, this message should not be shown" << std::endl;
			std::cin.get();
			return 0;
		}
		if (e == 2) {
			std::cout << "Input file structure is corrupt" << std::endl;
			std::cin.get();
			return 1;
		}
		if (e == 3) {
			std::cout << "Vertix links are out of bounds" << std::endl;
			std::cin.get();
			return 1;
		}
	}
#ifdef DSATUR
	g.Chroma(EXACT);
#else
	g.Chroma(FAST);
#endif
	std::cin.get();
	return 0;
}