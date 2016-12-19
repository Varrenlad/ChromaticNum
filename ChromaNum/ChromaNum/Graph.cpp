#include "Graph.h"

size_t Graph::Nodes() {
	return nodes;
}

void Graph::Load(std::istream &st) {
	size_t temp, temp2;
	if (st.rdstate() & std::ios::failbit)
		throw 0;
	do {
		std::string ssf;
		std::getline(st, ssf);
		std::stringstream lineTok(ssf);
		std::string token;
		while (lineTok >> token) { //split original data to tokens searching for numbers in header
			if (token.compare("Nodes:") == 0)
				lineTok >> nodes;
		}
	} while (!(nodes || st.eof()));
	if (!nodes) {
		std::exception e("Cannot find number of nodes, data might be corrupt");
		throw e;
	}
	while (!isdigit(temp = st.peek()))
		st.get(); //pass remainings of the header
	adj = new std::vector<size_t>[nodes];
	while (!st.eof()) {
		++edges;
		st >> temp >> temp2;
		if (temp == temp2) {
			hasCycle = true; //a graph with a cycle cannot be coloured
			return;
		}
		adj[temp].push_back(temp2);
		adj[temp2].push_back(temp);
	}
}

Graph::Graph() {
}


Graph::~Graph() {
}

size_t Graph::Chroma(Algorithm type) {
	if (!edges || nodes == 1)
		return 1;
	if (hasCycle)
		return 0;
	if (nodes == 2)
		return 2;
	try {
		if (type == FAST)
			return CountColours(Greedy());
		else
			return CountColours(Exact());
	}
	catch (int e) {
		return e;
	}
}

size_t Graph::Size() {
	return nodes;
}

size_t* Graph::Greedy() {
	size_t i, u, cr;
	size_t *result = new size_t[nodes](); //init as zero
	// Assign the first color to first vertex
	result[0] = 1;
	bool *available = new bool[nodes](); //init as zero
	// Assign colors to remaining V-1 vertices
	for (u = 1; u < nodes; u++)	{
		// Process all adjacent vertices and flag their colors
		// as unavailable
		for (i = 0; i < adj[u].size(); ++i)
			//if (result[i] != -1)
			if (result)
				available[result[i]] = true;
		// Find the first available color
		for (cr = 1; cr <= nodes; cr++)
			if (available[cr] == false)
				break;
		result[u] = cr; // Assign the found color
						// Reset the values back to false for the next iteration
		for (i = 0; i < adj[u].size(); ++i)
			//if (result[i] != -1)
			if (result)
				available[result[i]] = false;
	}

	for (int u = 0; u < nodes; u++)
		std::cout << "Vertex " << u << " --->  Color "
		<< result[u] << std::endl;
	return result;
}

size_t* Graph::Exact() { //there should be DSATUR
	//FIX ME : https://community.topcoder.com/longcontest/?module=Static&d1=match_editorials&d2=intel_mtcs_10
	//find maximal degree vertex to color first and color with 1
	size_t *result = new size_t[nodes](); //init as zero
	size_t max = 0, i;
	for (i = 0; i < nodes; ++i) {
		if (adj[i].size() > max)
			max = adj[i].size();
	}
	if (!max) {
		throw 0;
		std::cerr << "No edges found by exact\n";
	}
	result[max] = 1;
	//std::priority_queue<int, std::vector<int>> saturationLevel;









}

size_t Graph::CountColours(size_t *arr) {
	size_t i, max = 1;
	for (i = 0; i < nodes; ++i)
		if (arr[i] > max)
			max = arr[i];
	return max;
}