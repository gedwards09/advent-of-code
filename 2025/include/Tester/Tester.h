#ifndef __TESTER_H__
#define __TESTER_H__

#include <filesystem>

#include "ISolution.h"
#include "SolutionFactory.h"

namespace fs = std::filesystem;

class Tester
{
    public:
        static void RunAllTests();

    private:
        static const fs::path s_testsRoot;

        static void RunDayTests(SolutionFactory* factory, const fs::path& dayDir);
        static void RunTestCase(
                SolutionFactory* factory, int dayNum,
                const fs::path& dayDir, const fs::path& inputPath);
        static void RunPart(
                ISolution* solution, int dayNum,
                const std::string& inputFilename, const fs::path& outPath,
                int partNum, bool isEasy);

        static void InitDirs(std::vector<fs::path>& dirs, const fs::path& root);
        static bool TryParseDayNumberFromDirName(const std::string& name, int& dayNum);
        static bool IsDigit(char c);
        static void InitInputFiles(std::vector<fs::path>& inputs, fs::path dir);
        static bool IsInputFile(const fs::path& p);
        static ISolution* GetSolution(
                SolutionFactory* factory, int dayNum, std::string filename);
        static bool ResultsAreEqual(std::string expected, std::string actual);
};

#endif // __TESTER_H__