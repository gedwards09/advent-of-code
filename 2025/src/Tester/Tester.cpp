
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "FileReader.h"
#include "SolutionArgs.h"

#include "Tester.h"

namespace fs = std::filesystem;

static const fs::path s_testsRoot = fs::path(".") / "tests";

void Tester::RunAllTests()
{
    const fs::path testsRoot = fs::path(".") / "tests";
    SolutionFactory factory;
    SolutionFactory* pFactory;
    std::vector<fs::path> dayDirs;

    pFactory = &factory;

    if (!fs::exists(testsRoot) || !fs::is_directory(testsRoot))
    {
        std::cout << "Tests root not found: " << testsRoot.string() << std::endl;
        return;
    }

    Tester::InitDirs(dayDirs, testsRoot);

    for (const fs::path& dayDir : dayDirs)
    {
        Tester::RunDayTests(pFactory, dayDir);
    }
}

void Tester::RunDayTests(SolutionFactory* factory, const fs::path& dayDir)
{
    int dayNum = 0;
    std::string dayName = dayDir.filename().string();

    if (!Tester::TryParseDayNumberFromDirName(dayName, dayNum))
    {
        return;
    }

    std::vector<fs::path> inputs;
    Tester::InitInputFiles(inputs, dayDir);

    for (const fs::path& inputPath : inputs)
    {
        Tester::RunTestCase(factory, dayNum, dayDir, inputPath);
    }
}

void Tester::RunTestCase(SolutionFactory* factory, int dayNum,
        const fs::path& dayDir, const fs::path& inputPath)
{
    const std::string inputFilename = inputPath.filename().string();
    const std::string stem = inputPath.stem().string();
    const fs::path outEasyPath = dayDir / (stem + "-1.out");
    const fs::path outHardPath = dayDir / (stem + "-2.out");

    ISolution* solution = GetSolution(factory, dayNum, inputPath.string());
    if (solution == NULL)
    {
        std::cout << "Day " << dayNum << " Test: " << inputFilename
                  << " Skipped: no solution built" << std::endl;
        return;
    }

    Tester::RunPart(solution, dayNum, inputFilename, outEasyPath, 1, true);
    Tester::RunPart(solution, dayNum, inputFilename, outHardPath, 2, false);

    delete solution;
}

void Tester::RunPart(ISolution* solution, int dayNum,
        const std::string& inputFilename, const fs::path& outPath,
        int partNum, bool isEasy)
{
    if (!fs::exists(outPath) || !fs::is_regular_file(outPath))
    {
        std::cout << "Day " << dayNum << " Test: " << inputFilename
                  << " Part " << partNum << " Skipped: " << outPath.string()
                  << " not found." << std::endl;
        return;
    }

    std::string expected[1];
    FileReader::ReadContentsIntoBuffer(outPath.string(), expected, 1);

    auto start = std::chrono::high_resolution_clock::now();
    std::string actual = isEasy ? solution->SolveEasy() : solution->SolveHard();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Day " << dayNum << " Test: " << inputFilename
              << " Part " << partNum;

    if (Tester::ResultsAreEqual(expected[0], actual))
    {
        std::cout << " (" << duration.count() << " ms)." << std::endl;
    }
    else
    {
        std::cout << " failed: " << outPath.string() << std::endl;
        std::cout << "Expected: " << expected[0] << " Actual: "
                  << actual << std::endl;
    }
}

void Tester::InitDirs(std::vector<fs::path>& dirs, const fs::path& root)
{
    for (const fs::directory_entry& entry : fs::directory_iterator(root))
    {
        if (!entry.is_directory())
        {
            continue;
        }
        dirs.push_back(entry.path());
    }
    std::sort(dirs.begin(), dirs.end());
}

bool Tester::TryParseDayNumberFromDirName(const std::string& name, int& dayNum)
{
    std::string digits;

    if (name.rfind("Day", 0) != 0) 
    {
        return false;
    }

    digits = name.substr(3);

    if (digits.empty())
    {
        return false;
    }

    for (char c : digits)
    {
        if (!IsDigit(c))
        {
            return false;
        }
    }

    dayNum = std::atoi(digits.c_str());
    return dayNum > 0;
}

bool Tester::IsDigit(char c)
{
    return '0' <= c && c <= '9';
}

void Tester::InitInputFiles(std::vector<fs::path>& inputs, fs::path dir)
{
    for (const fs::directory_entry& entry : fs::directory_iterator(dir))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        if (Tester::IsInputFile(entry.path()))
        {
            inputs.push_back(entry.path());
        }
    }
    std::sort(inputs.begin(), inputs.end());
};

bool Tester::IsInputFile(const fs::path& p)
{
    return p.has_filename() && p.extension() == ".in";
}

ISolution* Tester::GetSolution(SolutionFactory* factory, int dayNum, std::string filename)
{
    SolutionArgs* solutionArgs;
    ISolution* solution;

    solutionArgs = new SolutionArgs(filename);
    solution = factory->Build(dayNum, solutionArgs);
    delete solutionArgs;

    return solution;
}

bool Tester::ResultsAreEqual(std::string expected, std::string actual)
{
    return actual == expected;
}