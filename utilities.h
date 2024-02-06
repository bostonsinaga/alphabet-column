#include <cmath>

namespace util {
    const char ALP[52] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m',
        'n','o','p','q','r','s','t','u','v','w','x','y','z'
    };

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
        bool isAnyNum = false,
            isNegative = false;

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
                isAnyNum = true;
            }
            else if (!isAnyNum && ch == '-') {
                isNegative = true;
            }
        }

        if (pureNum == "") return 0;
        return std::stoi(pureNum) * (1 - isNegative * 2);
    }

    void alphabetToDecimal(std::string input) {
        std::vector<int> alpIdx;

        for (int i = 0; i < input.length(); i++) {
            for (int j = 0; j < 52; j++) {
                if (input[i] == ALP[j]) {
                    alpIdx.push_back(j > 25 ? j - 25 : j + 1);
                    break;
                }
            }
        }

        int index = 0;

        for (int i = 0; i < alpIdx.size(); i++) {
            index += std::pow(26, alpIdx.size() - 1 - i) * alpIdx[i];
        }

        std::cout << "\nRESULT: " << index << std::endl;
    }

    void printError() {
        std::cerr << "\nInput Error!\n";

        std::cout
            << "\nPlease enter:\n\n"
            << "Decimal -> Alphabet\n"
            << "--convert [INT] --next-count [INT<opt>] --next-difference [INT<opt>] --out [STR<opt>]\n"
            << "\nAlphabet -> Decimal\n"
            << "--decimal [STR]\n";
    }
};

