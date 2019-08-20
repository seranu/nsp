#include <printers.h>
#include <iostream>
#include "configuration_factory.h"
#include "solution.h"
#include "solution_factory.h"
#include "solver.h"
#include "utils.h"
using namespace nsp;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage : " << argv[0] <<" <config_file>\n";
        return -1;
    }
    auto configuration =
        ConfigurationFactory::createFromFile(ConfigurationType::JSON, argv[1]);
    std::cout << *configuration;
    auto sol = SolutionFactory::createRandomSolution(*configuration);
    std::cout << sol;
    //    Solver
    //    solver(ConfigurationFactory::create(ConfigurationType::JSON,
    //    argv[1])); solver.solve(); auto best = solver.bestSoFar(); if
    //    (best) {
    ////        cout << *best;
    //    } else {
    ////        cout << "Couldn't find solution!\n";
    //    }
    return 0;
}
