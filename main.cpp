#include <iostream>
#include "populate_graph.h"
#include "Cenario1.h"
#include "Cenario2.h"

int main() {
    populate_graph pf;
    Cenario1 c1;
    Cenario2 c2;
    int ans;

    Graph2 g = pf.read_tests();
    std::cout << "Which cenario do you want to choose: ";
    std::cin >> ans;
    switch (ans) {
        case 1:
            c1.cenario1(g);
            break;
        case 2:
            c2.cenario2(g);
        case 0:
            exit(0);

    }
    return 0;
}
