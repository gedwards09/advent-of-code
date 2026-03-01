#include <iostream>
#include <memory>

#include "Days.h"
#include "ISolution.h"
#include "SolutionFactory.h"
#include "Tester.h"

int main (int argc, char* argv[])
{
    std::string arg;
    std::string path;
    bool runTests;
    std::string filename;
    int num;
    SolutionArgs* args;
    SolutionFactory* factory;

    num = 1; // default
    runTests = false;
    path = "./tests/";

    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];

        if ((arg == "-t") || (arg == "--test"))
        {
            runTests = true;
        }

        if ((arg == "-f") || (arg == "--file"))
        {
            i++;

            if (i >= argc)
            {
                throw std::runtime_error("main.cpp: --file option requires one argument\n");
            }

            filename = argv[i];
        }

        if ((arg == "-n") || (arg == "--number"))
        {
            i++;

            if (i >= argc)
            {
                throw std::runtime_error("main.cpp: --number option requires one argument\n");
            }

            num = std::atoi(argv[i]);
        }
    }

    if (runTests)
    {
        Tester::RunAllTests();
    }
    else
    {    
        filename = path + filename;
        args = new SolutionArgs(filename);
        factory = new SolutionFactory();

        ISolution* solution = factory->Build(num, args);
        std::cout << solution->SolveEasy() << std::endl;
        std::cout << solution->SolveHard() << std::endl;

        delete args;
        delete factory;
    }

    return 0;
}