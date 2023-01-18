//
// Created by nmls1 on 22/05/2022.
//

#ifndef PROJETODA_2_POPULATE_GRAPH_H
#define PROJETODA_2_POPULATE_GRAPH_H

#include "vector"
//#include "Graph.h"
#include "Graph2.h"


class populate_graph {
    int num_nodes;
    int num_branches;
public:
    populate_graph();

    Graph2 read_tests();
};


#endif //PROJETODA_2_POPULATE_GRAPH_H
