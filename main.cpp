#include <iostream>
#include <fstream>
#include <vector>
#include "utilities.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> values;

    const int
        CONVERT = 0,
        DECIMAL = 1
        NEXT_COUNT = 2,
        NEXT_DIFFERENCE = 3,
        OUT = 4;

    util::listenInput(
        argc, argv,
        {
            "--convert",
            "--decimal"
            "--next-count",
            "--next-difference",
            "--out"
        },
        values
    );

    /** Formation Errors */

    if ((
            values[CONVERT] == "" &&
            values[DECIMAL] == ""
        ) || (
            values[NEXT_COUNT] == "" &&
            values[NEXT_DIFFERENCE] != "" &&
            values[DECIMAL] == ""
        ) || (
            values[DECIMAL] != "" && (
                values[CONVERT] != "" ||
                values[NEXT_COUNT] != "" ||
                values[NEXT_DIFFERENCE] != "" ||
                values[OUT] != ""
            )
        )
    ) {
        util::printError();
        return 0;
    }

    // directly process alphabet to decimal
    if (values[DECIMAL] != "") {
        alphabetToDecimal(values[DECIMAL]);
        return 0;
    }

    /** Minimum Value Errors */

    int numCol = util::parseInt(values[CONVERT]),
        alpsTotal = util::parseInt(values[NEXT_COUNT]),
        alpsDiff = util::parseInt(values[NEXT_DIFFERENCE]);

    if (numCol <= 0) {
        std::cerr << "\nError!\nInput '--convert' must be greater than 0.\n";
        return 0;
    }
    else if (values[NEXT_COUNT] != "" && alpsTotal < 0) {
        std::cerr << "\nError!\nInput '--next-count' cannot be negative.\n";
        return 0;
    }
    else if (values[NEXT_DIFFERENCE] != "" && alpsDiff < 0) {
        std::cerr << "\nError!\nInput '--next-difference' cannot be negative.\n";
        return 0;
    }

    /**
     * CONVERTION
     *
     * Note:
     * The possible number of formations of the first three digits in
     * the sequence (1D, 2D, 3D) is 26 + 26^2 + 26^3.
     */

    std::vector<std::string> alpCols;
    numCol--;

    for (int i = 0; i < alpsTotal + 1; i++) {

        int numCol_copy = numCol;
        alpCols.push_back("");
        numCol += alpsDiff;

        if (numCol_copy < 26) {
            alpCols.back() = util::ALP[numCol_copy];
        }
        else {
            int alp1StIdx = 26;

            while (alp1StIdx > 25) {
                numCol_copy -= 26;
                alp1StIdx = numCol_copy / 26;
                alpCols.back() = util::ALP[numCol_copy % 26] + alpCols.back();
                numCol_copy = alp1StIdx;
            }

            alpCols.back() = util::ALP[alp1StIdx] + alpCols.back();
        }
    }

    /** OUTPUT */

    auto displayOnScreen = [&]() {
        std::cout << "\nRESULT:\n\n";

        for (int i = 0; i < alpCols.size(); i++) {
            std::cout << alpCols[i] << std::endl;
        }
    };

    if (values[OUT] == "" ) {
        displayOnScreen();
    }
    else {
        /** Check Existing File */

        std::ifstream fileRead(values[OUT]);

        if (fileRead.good()) {
            std::cout << "\nWarning! The file already exists. Do you want to overwrite it?\n(Y/N) ";

            std::string isIt;
            std::cin >> isIt;

            if (isIt != "Y" && isIt != "y") {
                std::cout << "\nDo you still want to display the result on the screen?\n(Y/N) ";

                std::string stillDisplayResult;
                std::cin >> stillDisplayResult;

                if (stillDisplayResult == "Y" || stillDisplayResult == "y") {
                    displayOnScreen();
                }
                else std::cout << "\nResult is discarded.\n";

                return 0;
            }
        }

        /** Write File */

        std::ofstream fileWrite;
        fileWrite.open(values[OUT]);

        for (int i = 0; i < alpCols.size(); i++) {
            fileWrite << alpCols[i] << (i < alpCols.size() - 1 ? "\n" : "");
        }

        fileWrite.close();
        std::cout << "\nFile written to '" << values[OUT] << "'.\n";
    }

    return 0;
}

