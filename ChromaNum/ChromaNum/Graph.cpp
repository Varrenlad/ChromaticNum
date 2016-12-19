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

size_t* Graph::Exact() { //DSATUR
	///Preparation to DSATUR
	size_t *result = new size_t[nodes](); //init as zero
	std::vector<size_t> satLevel, top;
	//initialize satLevel as one all
	//top.resize(nodes, 0);
	satLevel.resize(nodes, 1);
	//find max degree
	size_t colour, i, max = 0;
	for (i = 0; i < nodes; ++i) {
		if (adj[i].size() > max) {
			max = adj[i].size();
			top.clear();
			top.push_back(i);
		}
	}
	max = top[0];
	top.clear();
	if (!max)
		throw 1;
	///Preparation end
	do {
		colour = 1; //set colour to first
		//find first available colour and apply it to node
		for (i = 0; i < adj[max].size(); ++i) {
			if (colour == result[adj[max][i]]) {
				i = 0; //if node has connection to already coloured by this colour
				++colour;
			}
		}
		result[max] = colour; //color the first one
		satLevel[max] = 0; //remove first
		for (i = 0; i < adj[max].size(); ++i) { //make near vetrices more saturated
			if (satLevel[adj[max][i]])
				satLevel[adj[max][i]] += 1;
		}
		//select next most saturated vertices
		max = 0;
		for (i = 0; i < nodes; ++i) {
			if (satLevel[i] >= max) {
				if (satLevel[i] > max) {
					top.clear();
				}
				top.push_back(i);
				max = satLevel[i];
			}
		}
		//filter most linked vertix
			while (top.size() > 1) {
				if (adj[top[0]] <= adj[top[1]]) //if first has less or equal connection
					top.erase(top.begin());		//remove first link from 
				else
					top.erase(top.begin() + 1);
			}
		max = top[0];
		if (!satLevel[max]) //if saturation of this node is zero -- we're done
			return result;
	} while (true); //when all nodes will be not saturated we will exit by return
}

size_t Graph::CountColours(size_t *arr) {
	size_t i, max = 1;
	for (i = 0; i < nodes; ++i)
		if (arr[i] > max)
			max = arr[i];
	return max;
}