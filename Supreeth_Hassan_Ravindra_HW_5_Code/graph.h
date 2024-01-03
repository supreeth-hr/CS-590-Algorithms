#ifndef __AM_GRAPH_H__
#define __AM_GRAPH_H__

#include <limits.h>
#include "random_generator.h"

class graph
{
protected:
  int**	m_edge;
  int		no_vert;


public:
  graph(int);
  ~graph();

  int get_no_of_vertices()
  { return no_vert; }

  void generate_random(int, int);
  bool bellman_ford(int, int*&, int*&);
  void floyd_warshall(int**&, int**&);

  void output(int** = 0, int** = 0);

protected:
  void initialize();
  void permutation(int*, int);
};



#endif
