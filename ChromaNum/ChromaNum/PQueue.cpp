#include "PQueue.h"



PQueue::PQueue(Graph &g) {
	saturation = new size_t[g.Size()]();
	sorted_by_deg = new size_t[g.Size()]();
	sorted_by_sat = new size_t[g.Size()]();

	size_t i;
	size_t *temp_deg = new size_t[g.Size()]();
	for (i = 0; i < g.Size(); ++i) {
		te
	}
}


PQueue::~PQueue() {
	delete saturation;
}

size_t PQueue::operator[](size_t index) {
	if (index < size)
		return saturation[index];
	return 0;
}

void PQueue::SetSat(size_t newSat, size_t index) {
	if (index > size)
		return;
	saturation[index] = newSat;
	ReSort();
}

void PQueue::ReSort() {

}