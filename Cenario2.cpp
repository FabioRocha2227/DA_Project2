//
// Created by nmls1 on 01/06/2022.
//

#include "Cenario2.h"

Cenario2::Cenario2() {}

void Cenario2::cenario2(Graph2 &graph) {
    int ans;
    std::cout << "Which cenario do you want to choose: ";
    std::cin >> ans;
    switch (ans) {
        case 1:
            c2_1_2_2(graph);
            break;
        case 2:
            c2_1_2_2(graph);
            break;
        case 3:
            c2_3(graph);
            break;
        case 4:
            c2_4(graph);
            break;
        case 5:
            c2_5(graph);
            break;
    }
}

void Cenario2::c2_1_2_2(Graph2 & graph) {
    int ori, dest, size, plus;
    std::string ans;
    std::cout << "Choose your starting point: ";
    std::cin >> ori;
    std::cout << "Choose your destination: ";
    std::cin >> dest;
    std::cout << "How many people are in the group? ";
    std::cin >> size;
    if(graph.edmondsKarpGroupSize(ori, dest, size)){
        graph.printAllPaths();
        std::cout << "Do you wish to add more people to the group[yes/no]: ";
        std::cin >> ans;
        if(ans == "yes"){
            std::cout << "How many people do you want to add? ";
            std::cin >> plus;
            if(graph.edmondsKarpGroupSize(ori, dest, size + plus)){
                graph.printAllPaths();
            }
    }
    }
}

void Cenario2::c2_3(Graph2 &graph) {
    int ori, dest;
    std::string ans;
    std::cout << "Choose your starting point: ";
    std::cin >> ori;
    std::cout << "Choose your destination: ";
    std::cin >> dest;
    graph.edmondsKarp(ori, dest);
    graph.printAllPaths();
    std::cout << "Your group can have at most: " << graph.getMaxFlow(dest) << " people\n";
}

void Cenario2::c2_4(Graph2 & graph) {
    int ori, dest, size;
    std::string ans;
    std::cout << "Choose your starting point: ";
    std::cin >> ori;
    std::cout << "Choose your destination: ";
    std::cin >> dest;
    std::cout << "How many people are in the group? ";
    std::cin >> size;
    if(graph.edmondsKarpGroupSize(ori, dest, size)){
        std::cout << "The group will be reunited in " << graph.reuniteGroup(ori, dest, size) << " hours\n";
    }
}

void Cenario2::c2_5(Graph2 &graph){
    std::list<std::pair<int, int>> times;
    int ori;
    std::cout << "Choose your starting point: ";
    std::cin >> ori;
    graph.longestWait(ori);
    times = graph.nodeMaxTime(ori);
    std::cout << "The max time that you will have to wait is:";
    auto max = std::max_element(times.begin(), times.end(), [](const auto &lhs, const auto &rhs){ return lhs.second < rhs.second;});
    std::cout << max->second << " hours in the following stops: ";
    for(auto t : times){
        if(t.second == max->second){
            std::cout << t.first << " ";
        }
    }
}
