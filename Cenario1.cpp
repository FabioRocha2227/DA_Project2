//
// Created by nmls1 on 22/05/2022.
//

#include "Cenario1.h"

Cenario1::Cenario1() {}

void Cenario1::cenario1(Graph2 &graph) {
    int ans;
    std::cout << "Which cenário do you want to choose: ";
    std::cin >> ans;
    switch (ans) {
        case 1:
            maximizeCapacity(graph);
            break;
        case 2:
            optimal(graph);
            break;
    }
}

void Cenario1::maximizeCapacity(Graph2 &graph) {
    int ori, dest;
    std::cout << "Choose your starting point: ";
    std::cin >> ori;
    std::cout << "Choose your destination: ";
    std::cin >> dest;
    graph.maximizeCapacity(ori);
    std::vector<int> path = graph.path(ori, dest);
    std::cout << "You can take this path to reach your destination: ";
    for(int i = path.size() - 1; i >= 0; i--){
        std::cout << path[i] << " ";
    }
    std::cout << "\nAnd you can take at most " << graph.max_node_capacity(dest) << " people\n";
}

void Cenario1::optimal(Graph2 &graph) {
    int ori, dest;
    std::cout << "Choose your starting point: ";
    std::cin >> ori;
    std::cout << "Choose your destination: ";
    std::cin >> dest;
    graph.maxCapMinDist(ori);
    std::vector<int> path = graph.path(ori, dest);
    std::cout << "The path that can take the most amount of people is: ";
    for(int i = path.size() - 1; i >= 0; i--){
        std::cout << path[i] << " ";
    }
    std::cout << "\nAnd it can take at most " << graph.max_node_capacity(dest) << " people\n";
    graph.minDistMaxCap(ori);
    std::vector<int> path2 = graph.path(ori, dest);
    std::cout << "The shortest path is: ";
    for(int i = path2.size() - 1; i >= 0; i--){
        std::cout << path2[i] << " ";
    }
    std::cout << "\nAnd it can take at most " << graph.max_node_capacity(dest) << " people\n";

}