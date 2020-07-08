#pragma once
#include "Vertex.h"
template<class TElement>
class Edge
{
public:
	int weight;
	Vertex<TElement> *start;
	Vertex<TElement> *end;

	Edge<TElement>() {}

	void Set_parameters(Vertex<TElement> *start, Vertex<TElement> *end, int weight) {
		this->start = start;
		this->end = end;
		this->weight = weight;
	}
};

