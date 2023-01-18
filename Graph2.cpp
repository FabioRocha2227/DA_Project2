//
// Created by nmls1 on 31/05/2022.
//

#include "Graph2.h"
#include "MaxHeapPQ.h"
#include "MinHeapPQ.h"
#include "algorithm"

Graph2::Graph2(int num, bool dir) : num_vertex(num), hasDir(dir), all_vertex(num+1) {
}

int Graph2::getMaxFlow(int dest){
    int maxFlow = 0;
    for(Node i : all_vertex){
        for(Edge e : i.adj){
            if(e.dest == dest){
                maxFlow += e.flow;
            }
        }
    }
    return maxFlow;
    //return maxFlow;
}


void Graph2::addEdgeCapacity(int sourc, int dest, int c, int d) {
    if (sourc < 1 || sourc >= num_vertex || dest < 1 || dest > num_vertex) return;
    all_vertex[sourc].adj.push_back(Edge{sourc, dest,0 ,c, d, true});
    all_vertex[dest].residual.push_back(new Edge{dest, sourc, 0, c, d, true});
}

void Graph2::maximizeCapacity(int ori) {
    for(int v = 1; v <= num_vertex; v++) {
        all_vertex[v].cap = 0;
        all_vertex[v].pred = 0/*nullptr*/;
    }
    all_vertex[ori].cap = INF;
    MaxHeapPQ<int, int> q(num_vertex, -1);
    // Adicionar todos os nodes

    for(int n = 1; n <= num_vertex; n++){
        q.insert(n, all_vertex[n].cap);
    }
    while( !q.empty() ) {
        int v = q.extractMax();
        for(auto e : all_vertex[v].adj) {
            if(std::min(all_vertex[v].cap, e.capacity) > all_vertex[e.dest].cap){
                all_vertex[e.dest].cap = std::min(all_vertex[v].cap, e.capacity);
                all_vertex[e.dest].pred = v;
                q.increaseKey(e.dest, all_vertex[e.dest].cap);
            }
        }
    }
    //q.print();
}

void Graph2::maxCapMinDist(int ori){
    for(int v = 1; v <= num_vertex; v++) {
        all_vertex[v].cap = 0;
        all_vertex[v].pred = 0/*nullptr*/;
        all_vertex[v].dist = INF;
    }
    all_vertex[ori].cap = INF;
    all_vertex[ori].dist = 0;
    MaxHeapPQ<int, int> q(num_vertex, -1);
    // Adicionar todos os nodes
    for(int n = 1; n <= num_vertex; n++){
        q.insert(n, all_vertex[n].cap);
    }
    while( !q.empty() ) {
        int v = q.extractMax();
        for(auto e : all_vertex[v].adj) {
            if(std::min(all_vertex[v].cap, e.capacity) > all_vertex[e.dest].cap){
                all_vertex[e.dest].cap = std::min(all_vertex[v].cap, e.capacity);
                all_vertex[e.dest].pred = v;
                all_vertex[e.dest].dist = all_vertex[v].dist + 1;
                q.increaseKey(e.dest, all_vertex[e.dest].cap);
            }
            else if(std::min(all_vertex[v].cap, e.capacity) == all_vertex[e.dest].cap && all_vertex[v].dist + 1 < all_vertex[e.dest].dist){
                all_vertex[e.dest].pred = v;
                all_vertex[e.dest].dist = all_vertex[v].dist + 1;
                q.increaseKey(e.dest, all_vertex[e.dest].cap);
            }
        }
    }
}

void Graph2::minDistMaxCap(int ori) {
    MinHeapPQ<int, int> q(num_vertex, -1);
    for(int v = 1; v <= num_vertex; v++) {
        all_vertex[v].cap = 0;
        all_vertex[v].pred = 0/*nullptr*/;
        all_vertex[v].dist = INF;
        all_vertex[v].visited = false;
    }
    all_vertex[ori].cap = INF;
    all_vertex[ori].dist = 0;
    all_vertex[ori].pred = ori;
    // Adicionar todos os nodes
    for(int n = 1; n <= num_vertex; n++){
        q.insert(n, all_vertex[n].dist);
    }
    while( !q.empty() ) {
        int v = q.extractMin();
        if(!all_vertex[v].visited){
            all_vertex[v].visited = true;
            for(auto e : all_vertex[v].adj) {
                if (!all_vertex[e.dest].visited && all_vertex[v].dist + 1 < all_vertex[e.dest].dist) {
                    all_vertex[e.dest].cap = std::min(all_vertex[v].cap, e.capacity);
                    all_vertex[e.dest].pred = v;
                    all_vertex[e.dest].dist = all_vertex[v].dist + 1;
                    q.decreaseKey(e.dest, all_vertex[e.dest].dist);
                } else if (!all_vertex[e.dest].visited && all_vertex[v].dist + 1 == all_vertex[e.dest].dist && std::min(all_vertex[v].cap, e.capacity) > all_vertex[e.dest].cap) {
                    all_vertex[e.dest].pred = v;
                    all_vertex[e.dest].cap = std::min(all_vertex[v].cap, e.capacity);
                    all_vertex[e.dest].dist = all_vertex[v].dist + 1;
                    q.decreaseKey(e.dest, all_vertex[e.dest].dist);
                }
            }
        }
    }
}

std::vector<int> Graph2::path(int ori, int dest) {
    std::vector<int> nodesPassed;
    while(dest != ori){
        nodesPassed.push_back(dest);
        dest = all_vertex[dest].pred;
    }
    nodesPassed.push_back(ori);
    return nodesPassed;
}

int Graph2::max_node_capacity(int n){
    return all_vertex[n].cap;
}

bool Graph2::bfs(int ori, int dest) {
    for (int i = 1; i < num_vertex; i++) {
        all_vertex[i].visited = false;
    }
    all_vertex[ori].visited = true;
    std::queue<int> q;
    q.push(ori);
    while (!q.empty() && !all_vertex[dest].visited) {
        int cur = q.front();
        q.pop();
        for (auto e: all_vertex[cur].adj) {
            if (!all_vertex[e.dest].visited && (e.capacity - e.flow) > 0) {
                all_vertex[e.dest].visited = true;
                all_vertex[e.dest].pred = cur;
                all_vertex[e.dest].predEdge = e;
                q.push(e.dest);
            }
        }
    }
    return all_vertex[dest].visited;
}

int Graph2::findMaxFlowEK(int ori, int dest){
    int maxFlow;
    int cur = dest;
    list<int>path = {};
    path.push_back(cur);
    while(cur != ori){
        if(all_vertex[cur].predEdge.dest == cur){
            maxFlow = std::min(maxFlow, all_vertex[cur].predEdge.capacity - all_vertex[cur].predEdge.flow);
            cur = all_vertex[cur].pred;
            path.push_back(cur);
        }
        else{
            maxFlow = std::min(maxFlow, all_vertex[cur].predEdge.flow);
            cur = all_vertex[cur].predEdge.dest;
            path.push_back(cur);
        }
    }
    std::pair<list<int>,int> pathFlow;
    path.reverse();
    pathFlow.first = path;
    pathFlow.second = maxFlow;
    allPaths.push_back(pathFlow);
    return maxFlow;
}

void Graph2::updateFlows(int ori, int dest, int flow){
    int cur = dest;
    while(cur != ori){
        if(all_vertex[cur].predEdge.dest == cur){
            all_vertex[cur].predEdge.flow += flow;
            cur = all_vertex[cur].pred;
        }
        else{
            all_vertex[cur].predEdge.flow -= flow;
            cur = all_vertex[cur].predEdge.dest;
        }
    }
}

void Graph2::updateAdj(){
    for(int i = 1; i < num_vertex; i++){
        for(Edge &e : all_vertex[i].adj){
            for(int j = 1; j < num_vertex; j++){
                if(all_vertex[j].predEdge.dest == e.dest && all_vertex[j].predEdge.from == e.from){
                    e.flow = all_vertex[j].predEdge.flow;
                }
            }
        }
    }
}

void Graph2::edmondsKarp(int ori, int dest){
    for(auto v : all_vertex){
        for(auto e : v.adj){
            e.flow = 0;
        }
        for(auto e : v.residual){
            e->flow = 0;
        }
    }
    while(bfs(ori, dest)){
        int maxFlow = findMaxFlowEK(ori, dest);
        updateFlows(ori, dest , maxFlow);
        updateAdj();
    }
}

bool Graph2::edmondsKarpGroupSize(int ori, int dest, int size){
    for(auto v : all_vertex){
        for(auto e : v.adj){
            e.flow = 0;
        }
        for(auto e : v.residual){
            e->flow = 0;
        }
    }
    while(bfs(ori, dest)){
        int maxFlow = findMaxFlowEK(ori, dest);
        updateFlows(ori, dest , maxFlow);
        updateAdj();

        if(getMaxFlow(dest) >= size)
            break;
    }
    if(getMaxFlow(dest) < size){
        std::cout << "Group is too big!!\n";
        return false;
    }
    return true;

}

void Graph2::printAllPaths(){
    std::cout << "These are all the possible path your group can take and their maximum capacity: \n";
    for(std::pair<std::list<int>,int> pair : allPaths){
        for(int i : pair.first){
            std::cout << "->" << i;
        }
        std::cout << " Max Capacity - " << pair.second << "\n";
    }
}

int Graph2::reuniteGroup(int ori, int dest, int size){
    int minTime = INF;
    for(std::pair<std::list<int>,int> pair : allPaths){
        int time = 0;
        int pred = INF;
        for(auto n : pair.first){
            if(pred != INF) {
                for (Edge e: all_vertex[pred].adj){
                    if(e.dest == n)
                        time += e.duration;
                }
                pred = n;
            }
            else{
                pred = n;
            }
        }
        if(minTime > time){
            minTime = time;
        }
    }
    return minTime;
}

void Graph2::longestWait(int ori) {
    for(int i = 1; i < num_vertex; i++) {
        all_vertex[i].maxWait = 0;
        all_vertex[i].minWait = INF;
    }
    std::queue<int>q;
    all_vertex[ori].minWait = 0;
    q.push(ori);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(auto e : all_vertex[cur].adj){
            int n = e.dest;
            all_vertex[n].maxWait = std::max(all_vertex[n].maxWait, all_vertex[cur].maxWait + e.duration);
            all_vertex[n].minWait = std::min(all_vertex[n].minWait, all_vertex[cur].minWait + e.duration);
            q.push(n);
        }
    }
}

std::list<std::pair<int, int>> Graph2::nodeMaxTime(int ori) {
    for (auto n: all_vertex) {
        n.visited = false;
    }
    std::list<std::pair<int, int>> times;
    std::queue<int> q;
    q.push(ori);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (!all_vertex[cur].visited) {
            all_vertex[cur].visited = true;
            if (all_vertex[cur].maxWait != 0 && all_vertex[cur].minWait != INF) {
                times.push_back({cur, all_vertex[cur].maxWait - all_vertex[cur].minWait});
                //std::cout << all_vertex[cur].maxWait - all_vertex[cur].minWait;
            }
            for (auto e: all_vertex[cur].adj) {
                int n = e.dest;
                q.push(n);
            }
        }
    }
    return times;
}

