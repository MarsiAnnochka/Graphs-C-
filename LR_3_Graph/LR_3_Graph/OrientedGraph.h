#pragma once
#include "IGraph.h"

template<class TElement>
class OrientedGraph : public IGraph<TElement>
{
public:
	OrientedGraph<TElement>(TElement **arr_vertex, int **arr, int N) : IGraph<TElement>(arr_vertex, arr, N) {
		this->Add(arr_vertex, arr);
		this->Set_edges(arr);
		this->search_time -= clock();
	}

protected:
	void Add(TElement **arr_vertex, int **arr) {
		IGraph<TElement> :: Add(arr_vertex, arr);
		for (int j = 0; j < this->N; j++) {
			int counter = 0;
			for (int i = 0; i < this->N; i++) {
				if (arr[j][i] != 0) counter++;
			}
			this->vertex[j] = new Vertex<TElement>();
			this->vertex[j]->Set_parameters(arr_vertex[j], counter, j);
		}
	}

	virtual void Set_edges(int **arr) {
		IGraph<TElement> :: Set_edges(arr);
		int number = 0;
		for (int i = 0; i < this->N; i++)
			for (int j = 0; j < this->N; j++) {
				if (arr[i][j] != 0) number++;
			}
		this->edge = new Edge<TElement> *[number];
		this->edges_number = number;
		int k = 0;
		for (int i = 0; i < this->N; i++)
		{
			int l = 0;
			for (int j = 0; j < this->N; j++) {
				if (arr[i][j] != 0) {
					this->edge[k] = new Edge<TElement>();
					this->edge[k]->Set_parameters(this->vertex[i], this->vertex[j], arr[i][j]);
					k++;
					this->vertex[i]->connected[l] = this->vertex[j];
					l++;
				}
			}
		}
	}
};

