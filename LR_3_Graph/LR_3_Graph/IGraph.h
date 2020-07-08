#pragma once
#include "..\..\ËÐ0\ËÐ0\HumanParameters.h"
#include "Vertex.h"
#include "Edge.h"

template<class TElement = HumanParameters>
class IGraph
{
public:
	double search_time;
	int max_colour;
	int N;
	int edges_number;
	Vertex<TElement> **vertex;
	Edge<TElement> **edge;

	
	IGraph<TElement>(TElement **arr_vertex, int **arr, int N) {
		search_time = clock();
		this->N = N;
		this->max_colour = 0;
	}
	
	void Search() {
		for (int i = 0; i < this->N; i++) {
			Depth_search(this->vertex[i]);
		}
	}

	void Null_marks() {
		for (int i = 0; i < this->N; i++) {
			vertex[i]->mark = 0;
		}
	}

	void Colour() {
		this->Null_marks();
		for (int i = 0; i < this->N; i++) {
			this->Colour_selection(this->vertex[i]);
		}
		this->Null_marks();
	}

protected:
	
	virtual void Set_edges(int **arr) {}

	void Depth_search(Vertex<HumanParameters> *vertex) {
		if (vertex->mark == 0) {
			vertex->mark = 1;
			for (int i = 0; i < vertex->counter; i++) {
				if (vertex->connected[i] != 0)
					if (vertex->connected[i]->mark == 0)
						Depth_search(vertex->connected[i]);
			}
		}
	}

	virtual void Add(TElement **arr_vertex, int **arr) {
		this->vertex = new Vertex<TElement>*[this->N];
	}

	void Colour_selection(Vertex<TElement> *vertex) {
		if (vertex->mark == 0) {
			vertex->mark = 1;
			if (vertex->index == 0) {
				vertex->colour = 1;
			}
			else {
				int min = this->N, max = 0;
				for (int i = 0; i < this->edges_number; i++) {
					if (this->edge[i]->start == vertex) {
						if ((this->edge[i]->end->colour < min) && (this->edge[i]->end->colour != 0)) min = this->edge[i]->end->colour;
						if ((this->edge[i]->end->colour > max) && (this->edge[i]->end->colour != 0)) max = this->edge[i]->end->colour;
					}

					if (this->edge[i]->end == vertex) {
						if ((this->edge[i]->start->colour < min) && (this->edge[i]->start->colour != 0)) min = this->edge[i]->start->colour;
						if ((this->edge[i]->start->colour > max) && (this->edge[i]->start->colour != 0)) max = this->edge[i]->start->colour;
					}
				}

				if (min == 1) vertex->colour = max + 1;
				else vertex->colour = min - 1;

				if (vertex->colour > this->max_colour) this->max_colour = vertex->colour;
			}
			for (int i = 0; i < vertex->counter; i++) {
				if (vertex->connected[i] != 0)
					if (vertex->connected[i]->mark == 0)
						this->Colour_selection(vertex->connected[i]);
			}
		}
	}

};

