#include "solution.h"
#include "configuration.h"
#include "solver.h"

#include <iostream>
using namespace nsp;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage : " << argv[0] <<" <config_file>\n";
        return -1;
    }

    Solver solver(Configuration::fromFile(argv[1]));
    solver.solve();
    auto best = solver.bestSoFar();
    if (best) {
//        cout << *best;
    } else {
//        cout << "Couldn't find solution!\n";
    }
    return 0;
}
