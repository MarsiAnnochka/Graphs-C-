#include "stdafx.h"
#include "CppUnitTest.h"
#include "C:\Users\Аня Егорова\source\repos\LR_3_Graph\LR_3_Graph\LR_3_Graph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Graph_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		bool Check_marks(IGraph<HumanParameters> *graph) {
			bool flag = true;
			for (int i = 0; i < graph->N; i++) {
				if (graph->vertex[i]->mark == 0) flag = false;
			}
			return flag;
		}

		bool Check_colours(IGraph<HumanParameters> *graph) {
			bool flag = true;
			for (int i = 0; i < graph->edges_number; i++) {
				if (graph->edge[i]->start->colour == graph->edge[i]->end->colour) flag = false;
			}
			return flag;
		}

		IGraph<HumanParameters> *Create_graph() {
			int N = 1000;
			HumanParameters **arr_vertex = new HumanParameters *[N];
			IGraph<HumanParameters> *graph = nullptr;
			for (int i = 0; i < N; i++) {
				arr_vertex[i] = new HumanParameters();
				arr_vertex[i]->Generate();
			}
			int **arr = new int*[N];
			for (int i = 0; i < N; i++) {
				arr[i] = new int[N];
			}
			srand(time(0));
			for (int i = 0; i < N - 1; i++)
				for (int j = 0; j < N; j++) {
					if ((i - j) % 8 == 1) arr[i][j] = rand() % 100;
					else arr[i][j] = 0;
				}
			for (int i = 0; i < N; i++) arr[N - 1][i] = 0;
			graph = new OrientedGraph<HumanParameters>(arr_vertex, arr, N);
			return graph;
		}

		TEST_METHOD(Searching)
		{
			IGraph<HumanParameters> *graph = Create_graph();
			graph->Search();
			Assert::IsTrue(Check_marks(graph));
		}

		TEST_METHOD(Colouring)
		{
			IGraph<HumanParameters> *graph = Create_graph();
			graph->Colour();
			Assert::IsTrue(Check_colours(graph));
		}
	};
}