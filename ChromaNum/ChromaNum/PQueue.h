#pragma once
#include "Graph.h"
class PQueue {
	size_t size;
	size_t *saturation;
	size_t *sorted_by_sat;
	size_t *sorted_by_deg;
	void ReSort();
public:
	size_t GetMaxIndex();
	size_t operator[](size_t index);
	void SetSat(size_t newSat, size_t index);
	PQueue(Graph &);
	~PQueue();
};

