#pragma once
#include "pch.h"
#include <iostream>
#include "OrientedGraph.h"
#include "NonOrientedGraph.h"
#include <fstream>
#include <ctime>
#include <string>

const string FILE_RESULT = "result_graph.txt";
const string FILE_COLOUR = "coloured_graph.txt";

void Write_graph(IGraph<HumanParameters> *graph, bool orientation);
int **Generate(int N);
int **Generate_symmetric(int N);
void Write_colour(IGraph<HumanParameters> *graph, bool orientation);
bool Check(int index, int max);
void Oriented(bool orientation);
void Choose_operation(IGraph<HumanParameters> *graph, bool orientation);
void Write(IGraph<HumanParameters> *graph, bool orientation);
bool Check_symmetric(int **arr, int N);
void Write_time(IGraph<HumanParameters> *graph);

using namespace std;
int main()
{
	int operation = 0;
	do {
		cout << "ALGORITHMS ON GRAPHS" << endl << endl;
		cout << "1) Oriented graph" << endl;
		cout << "2) NonOriented graph" << endl;
		cout << "3) Exit" << endl << endl;
		do {
			cin >> operation;
		} while (!Check(operation, 3));

		switch (operation) {
		case 1: Oriented(true); break;
		case 2: Oriented(false); break;
		case 3: break;
		}
	} while (operation != 3);
}

void Oriented(bool orientation) {
	int type = 0;
	do {
		cout << "1) Generate graph" << endl;
		cout << "2) Write yourself" << endl;
		cout << "3) Menu" << endl << endl;
		do {
			cin >> type;
		} while (!Check(type, 3));
		if (type == 3) break;
		int N;
		cout << "Enter the number of vertexes: ";
		do {
			cin >> N;
			cout << endl << endl;
		} while (N<=0);
		HumanParameters **arr_vertex = new HumanParameters *[N];
		int **arr = nullptr;
		IGraph<HumanParameters> *graph = nullptr;
		switch (type) {
		case 1: {
			for (int i = 0; i < N; i++) {
				arr_vertex[i] = new HumanParameters();
				arr_vertex[i]->Generate();
			}
			switch (orientation) {
			case true: arr = Generate(N); break;
			case false: arr = Generate_symmetric(N); break;
			}
			switch (orientation) {
			case true: graph = new OrientedGraph<HumanParameters>(arr_vertex, arr, N); break;
			case false: graph = new NonOrientedGraph<HumanParameters>(arr_vertex, arr, N); break;
			}
			Write_time(graph);
			Choose_operation(graph, orientation);
			break;
		}
		case 2: 
		{
			int age;
			float weight, height;
			for (int i = 0; i < N; i++) {
				cout << "Element " << i + 1 << "\n[Age] [Weight] [Height]\n";
				cin >> age >> weight >> height;
				cout << endl;
				arr_vertex[i] = new HumanParameters(age, weight, height);
			}
			cout << endl << "Enter the adjacency matrix:\n	 " << endl;
			arr = new int *[N];
			switch (orientation) {
			case true: {
				for (int i = 0; i < N; i++) {
					arr[i] = new int[N];
					for (int j = 0; j < N; j++) {
						cout << "arr[" << i << "][" << j << "] = ";
						int st;
						std::cin >> st;
						cout << endl;
						arr[i][j] = st;
					}
					cout << endl;
				}
				graph = new OrientedGraph<HumanParameters>(arr_vertex, arr, N);
				break;
			}
			case false: {
				for (int i = 0; i < N; i++) {
					arr[i] = new int[N];
					for (int j = i; j < N; j++) {
						cout << "arr[" << i << "][" << j << "] = ";
						int st;
						std::cin >> st;
						cout << endl;
						arr[i][j] = st;
					}
					cout << endl;
				}
				graph = new NonOrientedGraph<HumanParameters>(arr_vertex, arr, N); 
				break; }
			}
			Write_time(graph);
			Choose_operation(graph, orientation);
			break;
		}
		case 3: break;
		}
	} while (type != 3);
}

void Choose_operation(IGraph<HumanParameters> *graph, bool orientation) {
	int operation = 0;
	do {
		cout << "1) Depth-first search" << endl;
		cout << "2) Colouring" << endl;
		cout << "3) Menu" << endl << endl;
		do {
			cin >> operation;
		} while (!Check(operation, 3));
		switch (operation) {
		case 1: graph->Search(); break;
		case 2: graph->Colour(); break;
		case 3: break;
		}
		if (operation == 3) break;
		Write_time(graph);
		Write(graph, orientation);
	} while (operation != 3);
}

bool Check(int index, int max) {
	int flag = true;
	if ((index > max) || (index < 1)) {
		cout << "Incorrect input! Please, try again." << endl;
		flag = false;
	}
	return flag;
}

void Write(IGraph<HumanParameters> *graph, bool orientation) {
	int output = 0;
	do {
		cout << "1) Draw graph" << endl;
		cout << "2) Draw coloured graph" << endl;
		cout << "3) Menu" << endl << endl;
		do {
			cin >> output;
		} while (!Check(output, 3));
		switch (output) {
		case 1: {
			Write_graph(graph, orientation);
			cout << "Check file result_graph.txt" << endl;
			break; 
		}
		case 2: {
			cout << "Number of colours: " << graph->max_colour << endl;
			Write_colour(graph, orientation); 
			cout << "Check file coloured_graph.txt" << endl;
			break; 
		}
		case 3: break;
		}
	} while (output != 3);
}

void Write_graph(IGraph<HumanParameters> *graph, bool orientation) {
	ofstream cout_result(FILE_RESULT, std::ios::out);
	cout_result << "@startuml\n";
	for (int i = 0; i < graph->N; i++) {
		cout_result << "usecase (Age: " << graph->vertex[i]->value->GetAge() << "\\nWeight: " << graph->vertex[i]->value->GetWeight();
		cout_result << "\\nHeight: " << graph->vertex[i]->value->GetHeight() << "\\n"<< graph->vertex[i]->mark << ") as " << i << endl;
	}
	string str;
	switch (orientation) {
	case true: str = " --> "; break;
	case false: str = " -- "; break;
	}
	for (int i = 0; i < graph->edges_number; i++) {
		cout_result << "(" << graph->edge[i]->start->index << ")" << str << "(" << graph->edge[i]->end->index;
		cout_result << ") : " << graph->edge[i]->weight << endl;
	}
	cout_result << "@enduml";
}

int **Generate(int N) {
	int **arr = new int*[N];
	for (int i = 0; i < N; i++) {
		arr[i] = new int [N];
	}
	srand(time(0));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			arr[i][j] = rand() % 100;
		}
	return arr;
}

int **Generate_symmetric(int N) {
	int **arr = new int*[N];
	for (int i = 0; i < N; i++) {
		arr[i] = new int[N];
	}
	srand(time(0));
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++) {
			arr[i][j] = rand() % 100;
			arr[j][i] = arr[i][j];
		}
	return arr;
}

void Write_colour(IGraph<HumanParameters> *graph, bool orientation) {
	ofstream cout_result(FILE_COLOUR, std::ios::out);
	cout_result << "@startuml\n";
	for (int i = 0; i < graph->N; i++) {
		cout_result << "usecase ("<< graph->vertex[i]->colour << ")  as " << i << endl;
	}
	string str;
	switch (orientation) {
	case true: str = " --> "; break;
	case false: str = " -- "; break;
	}
	for (int i = 0; i < graph->edges_number; i++) {
		cout_result << "(" << graph->edge[i]->start->index << ")" << str << "(" << graph->edge[i]->end->index;
		cout_result << ") : " << graph->edge[i]->weight << endl;
	}
	cout_result << "@enduml";
}

bool Check_symmetric(int **arr, int N) {
	bool flag = true;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (arr[i][j] != arr[j][i]) flag = false;
		}
	}
	return flag;
}

void Write_time(IGraph<HumanParameters> *graph) {
	cout << "Operation time: " << graph->search_time << endl;
}