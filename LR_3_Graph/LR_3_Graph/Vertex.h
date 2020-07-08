#pragma once
#include "..\..\ËÐ0\ËÐ0\HumanParameters.h"
template<class TElement = HumanParameters>
class Vertex
{
public:
	bool mark;
	TElement *value;
	Vertex<HumanParameters> **connected;
	int counter;
	int index;
	int colour;

	Vertex() {
		this->mark = 0;
		this->colour = 0;
	}

	void Set_parameters(TElement *value, int N, int index) {
		this->connected = new Vertex<HumanParameters>*[N];
		this->counter = N;
		this->value = value;
		this->index = index;
	}
};

