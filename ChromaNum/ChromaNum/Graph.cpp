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
	top.resize(nodes, 0);
	satLevel.resize(nodes, 1);
	//find max degree
	size_t colour, i, max = 0;
	for (i = 0; i < nodes; ++i) {
		if (adj[i].size() > max)
			max = adj[i].size();
	}
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
			if (!satLevel[adj[max][i]])
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

//size_t* Graph::Exact() { //there should be DSATUR
//	//FIX ME : https://community.topcoder.com/longcontest/?module=Static&d1=match_editorials&d2=intel_mtcs_10
//	//find maximal degree vertex to color first and color with 1
//	size_t *result = new size_t[nodes](); //init as zero
//	size_t max_degree = 0, i;
//	for (i = 0; i < nodes; ++i) {
//		if (adj[i].size() > max_degree)
//			max_degree = adj[i].size();
//	}
//	if (!max_degree) {
//		throw 0;
//		std::cerr << "No edges found by exact\n";
//	}
//	result[max_degree] = 1;
//	//std::priority_queue<int, std::vector<int>> saturationLevel;
//
//	std::vector<size_t> todo;
//
//	int degree = -1; //?
//	std::map<size_t, size_t> saturationLevel;
//	for (i = 0; i < nodes; ++i) {
//		saturationLevel.insert(std::make_pair(1, i));
//	}
//	saturationLevel[max_degree] = 0;
//	for (i = 0; i < adj[max_degree].size(); ++i) {
//		++saturationLevel[adj[max_degree][i]];
//	}
//	for (i = 0; i < nodes; ++i) {
//		if (i != max_degree) {
//			
//		}
//	}
//		//Create saturation_level so that we can see which graph nodes have the
//		//highest saturation without having to scan through the entire graph
//		//each time
//		//map<string, int> saturation_level;
//
//		//Add all nodes and set their saturation level to 0
//		for (map<string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++)
//		{
//			saturation_level[(*i).first] = 0;
//		}
//
//		//For the single node that has been colored, increment its neighbors so
//		//that their current saturation level is correct
//		for (int i = 0; i < graph[max_degree].size(); i++)
//		{
//			saturation_level[graph[max_degree][i]] += 1;
//		}
//
//		//Set the saturation level of the already completed node to -infinity so
//		//that it is not chosen and recolored
//		saturation_level[max_degree] = std::numeric_limits<int>::min();
//
//		//Populate the todo list with the rest of the vertices that need to be colored
//		for (map< string, vector<string> >::iterator i = graph.begin(); i != graph.end(); i++)
//		{
//			if ((*i).first != max_degree) {
//				coloring[(*i).first] = -1;
//				todo.push_back((*i).first);
//			}
//		}
//
//		//Color all the remaining nodes in the todo list
//		while (!todo.empty())
//		{
//			int saturation = -1;
//			string saturation_name = "";
//			vector<int> saturation_colors;
//			//Find the vertex with the highest saturation level, since we keep the
//			//saturation levels along the way we can do this in a single pass
//			for (map<string, int>::iterator i = saturation_level.begin(); i != saturation_level.end(); i++)
//			{
//				//Find the highest saturated node and keep its name and neighbors colors
//				if ((*i).second > saturation)
//				{
//					saturation = (*i).second;
//					saturation_name = (*i).first;
//
//					//Since we're in this loop it means we've found a new most saturated
//					//node, which means we need to clear the old list of neighbors colors
//					//and replace it with the new highest saturated nodes neighbors colors
//					//Since uncolored nodes are given a -1, we can add all neighbors and
//					//start the check for lowest available color at greater than 0
//					saturation_colors.clear();
//					for (int j = 0; j < graph[(*i).first].size(); j++)
//					{
//						saturation_colors.push_back(coloring[graph[(*i).first][j]]);
//					}
//				}
//			}
//			if (saturation_name == "")
//			{
//				cerr << "Error: Could not find a max saturated node in the graph (reason unknown)" << endl;
//				return;
//			}
//
//			//We now know the most saturated node, so we remove it from the todo list
//			todo.erase(std::find(todo.begin(), todo.end(), saturation_name));
//
//			//Find the lowest color that is not being used by any of the most saturated
//			//nodes neighbors, then color the most saturated node
//			int lowest_color = 0;
//			int done = 0;
//			while (!done)
//			{
//				done = 1;
//				for (unsigned i = 0; i<saturation_colors.size(); i++)
//				{
//					if (saturation_colors[i] == lowest_color)
//					{
//						lowest_color += 1;
//						done = 0;
//					}
//				}
//			}
//			coloring[saturation_name] = lowest_color;
//
//			//Since we have colored another node, that nodes neighbors have now
//			//become more saturated, so we increase each ones saturation level
//			//However we first check that that node has not already been colored
//			//(This check is only necessary for enormeous test cases, but is
//			//included here for robustness)
//			for (int i = 0; i < graph[saturation_name].size(); i++)
//			{
//				if (saturation_level[graph[saturation_name][i]] != std::numeric_limits<int>::min())
//				{
//					saturation_level[graph[saturation_name][i]] += 1;
//				}
//			}
//			saturation_level[saturation_name] = std::numeric_limits<int>::min();
//		}
//
//
//
//
//
//
//
//}

size_t Graph::CountColours(size_t *arr) {
	size_t i, max = 1;
	for (i = 0; i < nodes; ++i)
		if (arr[i] > max)
			max = arr[i];
	return max;
}