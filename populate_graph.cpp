//
// Created by nmls1 on 22/05/2022.
//

#include <fstream>
#include "populate_graph.h"
#include "iostream"

populate_graph::populate_graph() {}

Graph2 populate_graph::read_tests(){
    int ori;
    int dest;
    int cap;
    int dur;
    int ans;
    std::string filename;

    std::cout << "Choose the test file[1-10]: ";
    std::cin >> ans;

    switch (ans) {
        case 1:
            filename = "../Tests/Tests_B/in01_b.txt";
            break;
        case 2:
            filename = "../Tests/Tests_B/in02_b.txt";
            break;
        case 3:
            filename = "../Tests/Tests_B/in03_b.txt";
            break;
        case 4:
            filename = "../Tests/Tests_B/in04_b.txt";
            break;
        case 5:
            filename = "../Tests/Tests_B/in05_b.txt";
            break;
        case 6:
            filename = "../Tests/Tests_B/in06_b.txt";
            break;
        case 7:
            filename = "../Tests/Tests_B/in07_b.txt";
            break;
        case 8:
            filename = "../Tests/Tests_B/in08_b.txt";
            break;
        case 9:
            filename = "../Tests/Tests_B/in09_b.txt";
            break;
        case 10:
            filename = "../Tests/Tests_B/in10_b.txt";
            break;

    }

    std::ifstream fin(filename);

    fin >> num_nodes >> num_branches;

    Graph2 g(num_nodes+1, true);

    while (fin >> ori >> dest >> cap >> dur){
        g.addEdgeCapacity(ori, dest, cap, dur);
    }

    fin.close();

    return g;

    //std::cout << info_vector.size();
}


