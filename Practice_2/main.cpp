#include <iostream>
#include <vector>
#include <algorithm>
#include <tgmath.h>


std::string xorForString(std::string iFirstString, std::string iSecondString) {
    std::string finishString(iFirstString);
    for (int i = 0; i < iFirstString.size(); ++i) {
        if (iSecondString[i] == iFirstString[i]) {
            finishString[i] = '0';
        } else {
            finishString[i] = '1';

        }
    }
    return finishString;
}

std::string grayenCode(std::string inString) {
    std::string shiftString(inString);
    for (unsigned long j = shiftString.size(); j > 0; j--) {
        shiftString[j] = shiftString[j - 1];
    }
    shiftString[0] = '0';
    std::string finishString = xorForString(inString, shiftString);
    return finishString;
}

std::vector<std::string> *generateVariance(std::string iString) {

    if ((int) iString.find('?') >= 0) {
        std::string copy1(iString);
        std::string copy2(iString);
        copy1.replace(iString.find('?'), 1, "1");
        copy2.replace(iString.find('?'), 1, "0");
        std::vector<std::string> *ret_vec1 = generateVariance(copy1);
        std::vector<std::string> *ret_vec2 = generateVariance(copy2);
        ret_vec1->insert(ret_vec1->end(), ret_vec2->begin(), ret_vec2->end());
        delete ret_vec2;
        return ret_vec1;
    } else {
        std::vector<std::string> *vec = new std::vector<std::string>;
        vec->push_back(iString);
        return vec;
    }


}

std::string myXor(char iFirst, char iSecond) {
    if (iFirst == iSecond) {
        return "0";
    } else return "1";
}

std::vector<std::string> *smartXor(std::string iNum, std::string iGrey) {
    std::vector<std::string> *resultVector = new std::vector<std::string>;
    std::string prevNumChar = "0";

    int countOfDoubleQuestions = 0;
    int countOfSingleQuestions = 0;
    for (int i = 0; i < iNum.size(); ++i) {
        if (std::count(iNum.begin(), iNum.end(), '?') == 0 &&
            std::count(iGrey.begin(), iGrey.end(), '?') == 0) {
            break;
        }

        if (prevNumChar[0] == '?' && iNum[i] == '?' ||
            iNum[i] == '?' && iGrey[i] == '?' ||
            prevNumChar[0] == '?' && iGrey[i] == '?') {
            countOfDoubleQuestions++;
            if (i == 0) {
                prevNumChar.replace(0, 1, iNum.substr(i, 1));
            } else prevNumChar = iNum[i - 1];
        } else {
            for (int j = i; j > i - (countOfDoubleQuestions + 1); j--) {
                if (j == 0) {
                    prevNumChar.replace(0, 1, "0");
                } else prevNumChar = iNum[j - 1];
                if (prevNumChar == "?") {
                    iNum.replace(j - 1, 1, myXor(iNum[j], iGrey[j]));
                } else if (iNum[j] == '?') {
                    iNum.replace(j, 1, myXor(prevNumChar[0], iGrey[j]));
                } else {
                    iGrey.replace(j, 1, myXor(prevNumChar[0], iNum[j]));
                }

                countOfSingleQuestions++;
            }
            countOfDoubleQuestions = 0;
            prevNumChar = iNum[i - 1];

        }


    }
    resultVector->push_back(iNum);
    resultVector->push_back(iGrey);
    return resultVector;
}


int main() {
    std::string firstNum;
    std::string secondNum;
    std::cin >> firstNum >> secondNum;

    int countFirst = std::count(firstNum.begin(), firstNum.end(), '?');
    int countSecond = std::count(secondNum.begin(), secondNum.end(), '?');

    std::vector<std::string> *vecOfVariance;

    if (countFirst == 0 && countSecond == 0) {
        if (grayenCode(firstNum) == secondNum) {
            std::cout << firstNum << "\n" << secondNum;
            return 0;
        } else {
            std::cout << "Impossible";
            return 0;
        }
    }
    vecOfVariance = smartXor(firstNum, secondNum);

    countFirst = std::count(vecOfVariance->at(0).begin(),
                            vecOfVariance->at(0).end(), '?');
    countSecond = std::count(vecOfVariance->at(1).begin(),
                             vecOfVariance->at(1).end(), '?');

    if (countFirst > 0 || countSecond > 0) {
        std::cout << "Ambiguity";
        return 0;
    }
    if (grayenCode(vecOfVariance->at(0)) != vecOfVariance->at(1)) {
        std::cout << "Impossible";
        return 0;
    }

    std::cout << vecOfVariance->at(0) << "\n" << vecOfVariance->at(1);

    return 0;
}