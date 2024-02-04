#include <iostream>
#include <vector>
#include <cmath>

void listenInput(
    int argc,
    char *argv[],
    const std::vector<std::string> &expectedParams,
    std::vector<std::string> &values
) {
    if (expectedParams.size() != values.size()) {
        values = std::vector<std::string>(expectedParams.size());
    }

    for (int i = 1; i < argc; i++) {
        if (i + 1 < argc) {
            for (int j = 0; j < expectedParams.size(); j++) {
                if (argv[i] == expectedParams.at(j)) {
                    values[j] = argv[i+1];
                }
            }
        }
    }
}

int parseInt(std::string &numStr) {
    std::string pureNum;

    for (auto ch : numStr) {
        if (ch == '0' ||
            ch == '1' ||
            ch == '2' ||
            ch == '3' ||
            ch == '4' ||
            ch == '5' ||
            ch == '6' ||
            ch == '7' ||
            ch == '8' ||
            ch == '9'
        ) {
            pureNum += ch;
        }
    }

    if (pureNum == "") return 0;
    return std::stoi(pureNum);
}

void printError() {
    std::cerr << "\nInput Error!\n";

    std::cout
        << "\nPlease enter:\n"
        << "--convert [INT] --next-count [INT<opt>] --next-difference [INT<opt>] --out [STR<opt>]\n";
}

int main(int argc, char *argv[]) {

    const char ALP[26] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    std::vector<std::string> values;

    listenInput(
        argc, argv,
        {
            "--convert",
            "--next-count",
            "--next-difference",
            "--out"
        },
        values
    );

    // required
    if (values[0] == "") {
        printError();
        return 0;
    }

    int numCol = parseInt(values[0]);

    if (numCol <= 0) {
        std::cerr << "\nError!\nInput column number must be greater than 0.\n";
        return 0;
    }

    /**
     * CONVERTION
     *
     * Note:
     * The possible number of formations of the first three digits in
     * the sequence (1D, 2D, 3D) is 26 + 26^2 + 26^3.
     */

    std::vector<std::string> alpCols = {""};
    numCol--;

    if (numCol < 26) {
        alpCols.back() = ALP[numCol];
    }
    else {
        int alp1StIdx = 26;

        while (alp1StIdx > 25) {
            numCol -= 26;
            alp1StIdx = numCol / 26;
            alpCols.back() = ALP[numCol % 26] + alpCols.back();
            numCol = alp1StIdx;
        }

        alpCols.back() = ALP[alp1StIdx] + alpCols.back();
    }

    for (int i = 0; i < alpCols.size(); i++) {
        std::cout << alpCols[i] << std::endl;
    }

    return 0;
}

