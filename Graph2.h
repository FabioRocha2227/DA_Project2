//
// Created by nmls1 on 30/05/2022.
//

#ifndef PROJETODA_2_GRAPH2_H
#define PROJETODA_2_GRAPH2_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <algorithm>
//#include "MutablePriorityQueue.h"


#define INF (INT_MAX/2)

/************************* Vertex  **************************/

class Graph2{
    struct Edge {
        int from;
        int dest;      // destination vertex
        int flow; // edge weight
        int capacity, duration;
        bool visited = true;
    };

    struct Node {
        std::list<Edge> adj;
        std::list<Edge*> residual;
        int pred;
        int cap;
        int dur;
        int dist;
        int maxWait;
        int minWait;
        Edge predEdge = Edge{0,0,0,0,0, true};
        bool visited;
    };

    int num_vertex;
    std::list<std::pair<std::list<int>,int>> allPaths = {};
    bool hasDir;
    std::vector<Node> all_vertex;

public:
    Graph2(int nodes, bool dir = false);

    int getMaxFlow(int dest);
    void addEdgeCapacity(int sourc, int dest, int c, int d);
    std::vector<int>path(int ori, int dest);
    int max_node_capacity(int n);
    void maxCapMinDist(int ori);
    void minDistMaxCap(int ori);
    void maximizeCapacity(int ori);
    bool operator<(Node & node) const;
    bool bfs(int ori, int dest);
    int findMaxFlowEK(int ori, int dest);
    void updateFlows(int ori, int dest, int flow);
    void updateAdj();
    void edmondsKarp(int ori, int dest);
    bool edmondsKarpGroupSize(int ori, int dest, int size);
    void printAllPaths();
    int reuniteGroup(int ori, int dest, int size);
    void longestWait(int ori);
    std::list<std::pair<int, int>> nodeMaxTime(int ori);

};
#endif //PROJETODA_2_GRAPH2_H
