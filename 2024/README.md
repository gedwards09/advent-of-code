## Advent of Code 2024

`TEMPLATE.py` is a template file for AOC solutions. The file provides stubs to be completed with two algorithms, `Alg1()` and `Alg2()`, which solve Part 1 and Part 2 of the AOC puzzle for each day when run on an input file containing the puzzle text. The template passes the two functions pointers, and any arguments passed via the command line, to an AocController class which handles running the methods on the input text for each part of the puzzle.

`AocController.py` has one public method, `Execute()`, which clients can call to run the algorithm on the puzzle text. The client passes the command line arguments to AocController, which determines which function should be invoked on the puzzle script (whether the caller is solving Part 1 or Part 2), and whether the output should be compared to an output file (if the expected output is known and the script is being invoked in test-mode).

`AocArgs.py` is helper class used by AocController responsible for parsing the command line arguments and determining each of: the input file containing the puzzle text, the day-number being tested, the part-number being solved, the test-number being run, whether the output is being tested against a known solution, and, if so, the output file to compare the result against.

The solution for each day is contained in the script day-DAYNUMBER.py which can be invoked from the command line by:
```
python3 ./day-DAYNUMBER.py PARTNUMBER [-t [-a TESTNUMBER]]
```
where:

    `DAYNUMBER=(1[0-9]|2[0-5]|[0-9])` is the puzzle number from 1 to 25

    `PARTNUMBER=(1|2)` is the part number being run

    `TESTNUMBER` is the test number being run.

`aoc-run.py` is a helper script which calls the solution for a given puzzle number and part number using arguments passed via the command line:
```python3 ./aoc-run.py DAYNUMBER [--part=PARTNUMBER]```
The algorithm result is printed through standard I/O.

`run-tests.py` is a script which runs the solution script for each day against each of its test cases.

The test files are stored in the `/tests/` directory. I have only included the example inputs and solutions given in the problem statement of each day as test files, as sharing puzzle inputs or answer keys is considered to be against the terms of Advent of Code. New test cases can added by including aditional files with the naming convention: `DAYNUMBER-TESTNUMBER.in` with solution files `DAYNUMBER-TESTNUMBER-PARTNUMBER.out`. In some cases (e.g. Day 3), different example inputs are used in the statement of Parts 1 and 2. In these cases I have only included the output file for the relevant Part in the set of output files.