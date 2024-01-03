#include <iostream>

#include "graph.h"
#include "random_generator.h"

using namespace std;

int main(int argc, char* argv[])
{ 
	random_generator rg;
	int n, m, w;

	n = 10;
	m = 20;


/*
 * check arguments
 */
	switch (argc) {
		case 4: {
			w = atoi(argv[3]);
			w = (w < 1) ? 1 : w;
		} 
		case 3: {
			m = atoi(argv[2]);
			m = (m < 1) ? 1 : m;
		} 
		case 2: {
			n = atoi(argv[1]);
		} break;
		default: {
			cout << argv[0] << " [n] [m] [w]" << endl;
			cout << "[n]              no vertices of the graph" << endl;
			cout << "[m]              no edges " << endl;
			cout << "[w]              weight interval " << endl;
			cout << endl;
			return 0;
		}
	}

/*
 * allocated and generate integer array
 */
	int** d;
	int* v_d;
	int** pi;
	int* v_pi;
	int u, v;

	graph* gr;

	if (n < 1)
	{
		n = 10;
		m = 20;	
		gr = new graph(n);
		gr->generate_random(m, w);
	}
	else
	{
		gr = new graph(n);
		gr->generate_random(m, w);
	}

	cout << "Graph:" << endl;
	gr->output();

	if(!gr->bellman_ford(0, v_d, v_pi))
		cout << "There was a negative weight cycle!";
	else
	{
		cout << endl << "Bellman-Ford:" << endl;
		cout << "D: [\t";
		for (int i = 0; i < gr->get_no_of_vertices(); i++)
			cout << v_d[i] << "\t";
		cout << "]" << endl;
		cout << "Pi: [\t";
		for (int i = 0; i < gr->get_no_of_vertices(); i++)
			cout << v_pi[i] << "\t";
		cout << "]" << endl;

		gr->floyd_warshall(d, pi);
		cout << endl << "Floyd-Warshall:" << endl;
		cout << "D: " << endl;
		gr->output(d);
		cout << endl;
		cout << "Pi: " << endl;
		gr->output(pi);

		/*
 		* delete Floyd-Warshall leftovers
 		*/
		for (int i = 0; i < gr->get_no_of_vertices(); i++)
		{
			delete[] d[i];
			delete[] pi[i];
		}

		delete[] d;
		delete[] pi;
	}

/*
 * delete Bellman-Ford leftovers
 */
	delete[] v_d;
	delete[] v_pi;



/*
 * delete graph
 */
	delete gr;

	return 0;
}

