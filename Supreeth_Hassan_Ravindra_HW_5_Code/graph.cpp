#include "graph.h"
#include <list>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * constructor/destructor
 */
graph::graph(int n)
{ /*<<<*/
  no_vert = (n > 0) ? n : 1;

/*
 * allocate adjacency matrix
 */
  m_edge = new int*[no_vert];
  for (int i = 0; i < no_vert; i++)
    m_edge[i] = new int[no_vert];

  initialize();
} /*>>>*/

graph::~graph()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  for (int i = 0; i < no_vert; i++)
    delete[] m_edge[i];
  delete[] m_edge;
} /*>>>*/


void graph::initialize()
{ /*<<<*/
/*
 * initialize adjacency matrix
 * -> use infinity to allow 0 weight edges
 */
  for (int i = 0; i < no_vert; i++)
    for (int j = 0; j < no_vert; j++)
      m_edge[i][j] = INT_MAX;

} /*>>>*/

void graph::permutation(int* perm, int n)
{ /*<<<*/
  random_generator rg;
  int p_tmp, p_pos;

  for (int i = 0; i < n; i++)
    perm[i] = i;
  
  for (int i = 0; i < n; i++)
    {
      rg >> p_pos;
      p_pos = (p_pos % (n - i)) + i;

      p_tmp = perm[i];
      perm[i] = perm[p_pos];
      perm[p_pos] = p_tmp;
    }
} /*>>>*/

void graph::output(int** m_out, int** m_out_2)
{ /*<<<*/
  if (!m_out)
    m_out = m_edge;

  cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
  if (m_out[i][j] == INT_MAX)
    cout << "inf\t";
  else
    cout << m_out[i][j] << "\t";

      if (m_out_2)
  {
    cout << "]\t\t[\t";
    for (int j = 0; j < no_vert; j++)
      if (m_out_2[i][j] == INT_MAX)
        cout << "inf\t";
      else
        cout << m_out_2[i][j] << "\t";
  }

      cout << "]" << endl;
    }
  cout << "]" << endl;
} /*>>>*/


// TODO: Implement problem 1
void graph::generate_random(int n_edges, int max_weight)
{
    // Generate a random permutation of vertices
    int* vertices_permutation = new int[no_vert];
    permutation(vertices_permutation, no_vert);

    int edges_added = 0;
    int edge_weight;
    while (edges_added < n_edges)
    {   
        // Randomly select two vertices
        int u = vertices_permutation[rand() % no_vert];
        int v = vertices_permutation[rand() % no_vert];
        
        // Ensure the selected vertices are different and the edge does not already exist
        if (u != v && m_edge[u][v] == INT_MAX)
        {   
            // Generate a random weight within the specified interval [-max_weight, max_weight]
            edge_weight = (rand() % (2 * max_weight + 1)) - max_weight;
            
            // Assign the random weight to the edge
            m_edge[u][v] = edge_weight;
            
            // Increment the count of added edges
            edges_added++;
        }
    }
}

// TODO: Implement problem 3
bool graph::bellman_ford(int s, int*& v_d, int*& v_pi)
{
    // Initialize arrays to store distances and predecessors
    v_d = new int[no_vert];
    v_pi = new int[no_vert];

    // Initialize distances and predecessors
    for (int i = 0; i < no_vert; ++i)
    {
        v_d[i] = INT_MAX;
        v_pi[i] = -1;
    }

    // Set the distance to the source vertex to 0
    v_d[s] = 0;

    // Relax edges repeatedly
    for (int i = 0; i < no_vert - 1; ++i)
    {
        for (int j = 0; j < no_vert; ++j)
        {
            for (int k = 0; k < no_vert; ++k)
            {
                if (m_edge[j][k] != INT_MAX)
                {
                    if (v_d[j] != INT_MAX && v_d[j] + m_edge[j][k] < v_d[k])
                    {
                        v_d[k] = v_d[j] + m_edge[j][k];
                        v_pi[k] = j;
                    }
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < no_vert; ++j)
    {
        for (int k = 0; k < no_vert; ++k)
        {
            if (m_edge[j][k] != INT_MAX)
            {
                if (v_d[j] != INT_MAX && v_d[j] + m_edge[j][k] < v_d[k])
                {
                    // Negative weight cycle detected
                    return false;
                }
            }
        }
    }

    return true;
}

// TODO: Implement problem 4
void graph::floyd_warshall(int**& d, int**& pi)
{
    // Initialize matrices
    d = new int*[no_vert];
    pi = new int*[no_vert];
    for (int i = 0; i < no_vert; ++i)
    {
        d[i] = new int[no_vert];
        pi[i] = new int[no_vert];
    }

    // Copy the adjacency matrix to the D matrix
    for (int i = 0; i < no_vert; ++i)
    {
        for (int j = 0; j < no_vert; ++j)
        {
            d[i][j] = m_edge[i][j];
            pi[i][j] = (m_edge[i][j] != INT_MAX) ? i : -1;
        }
    }

    // Apply the Floyd-Warshall algorithm
    for (int k = 0; k < no_vert; ++k)
    {
        for (int i = 0; i < no_vert; ++i)
        {
            for (int j = 0; j < no_vert; ++j)
            {
                if (d[i][k] != INT_MAX && d[k][j] != INT_MAX && d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    pi[i][j] = pi[k][j];
                }
            }
        }
    }
}