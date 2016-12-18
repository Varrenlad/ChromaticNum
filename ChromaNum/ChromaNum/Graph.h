#pragma once
#include "common.h"

class Graph {
	std::vector<size_t> *adj;
	size_t nodes = 0;
	size_t edges = 0;
	bool hasCycle = 0;
	size_t CountColours(size_t *colorArr);
	size_t* Greedy();
	size_t* Exact(); //exact algo is DSATUR
public:
	size_t Chroma(Algorithm);
	size_t Nodes();
	void Load(std::istream &);
	Graph();
	~Graph();
	
};