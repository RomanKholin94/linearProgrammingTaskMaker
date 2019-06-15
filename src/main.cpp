#include <iostream>
#include <cstdio>
#include <vector>
#include "solver.h"

void ERROR(std::string error) {
    std::cerr << "ERROR: " << error << std::endl;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-i") {
            if (i + 1 < argc) {
                if (!freopen(argv[i + 1], "r", stdin)) {
                    ERROR("wrong input file");
                    return 1;
                }
                ++i;
            } else {
                ERROR("no input file");
                return 1;
            }
        } else if (std::string(argv[i]) == "-o") {
            if (i + 1 < argc) {
                if (!freopen(argv[i + 1], "w", stdout)) {
                    ERROR("wrong output file");
                    return 1;
                }
                ++i;
            } else {
                ERROR("no output file");
                return 1;
            }
        } else {
            ERROR("unknow option: " + std::string(argv[i]));
            return 1;
        }
    }

    Graph a(std::cin);
    Graph b(std::cin);
    Solver solver(std::cout);
    solver.solve(a, b);

    return 0;
}
