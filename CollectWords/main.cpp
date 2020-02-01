
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::unordered_map<int, int>> getAvailableLetters(std::string *lettersFileName);
void createWords(std::string *wordsFileName, std::string *resultFileName, std::unordered_map<std::string, std::unordered_map<int, int>> allAvailableLetters, int minLength);

int main(int argc, const char * argv[]) {

    std::string lettersFileName, wordsFileName, resultFileName;
    int minLength;
    std::cout << "Input min word length" << std::endl;
    std::cin >> minLength;
    std::cout << "Input path to file for letters" << std::endl;
    std::cin >> lettersFileName;
    std::cout << "Input path to file for words" << std::endl;
    std::cin >> wordsFileName;
    std::cout << "Input path to file for result" << std::endl;
    std::cin >> resultFileName;

    std::unordered_map<std::string, std::unordered_map<int, int>> allAvailableLetters = getAvailableLetters(&lettersFileName);
    createWords(&wordsFileName, &resultFileName, allAvailableLetters, minLength);

    return 0;
}

std::unordered_map<std::string, std::unordered_map<int, int>> getAvailableLetters(std::string *lettersFileName) {
    std::unordered_map<std::string, std::unordered_map<int, int>> allAvailableLetters;
    std::fstream lettersFileStream(*lettersFileName, std::ios::in);

    if (lettersFileStream.is_open()) {
        std::string letters;
        while (getline(lettersFileStream, letters)) {
            std::unordered_map<int, int> availableLetters;
            for (char letter : letters) {
                availableLetters[letter]++;
            }
            allAvailableLetters[letters] = availableLetters;
        }
    } else {
        std::cout << "File with letters not found" << std::endl;
    }

    lettersFileStream.close();

    return allAvailableLetters;
}

void createWords(std::string *wordsFileName, std::string *resultFileName, std::unordered_map<std::string, std::unordered_map<int, int>> allAvailableLetters, int minLength) {
    std::fstream wordsFileStream(*wordsFileName, std::ios::in);
    std::ofstream resultFileStream(*resultFileName, std::ios::out | std::ios::trunc);

    for (auto parameters : allAvailableLetters) {
        resultFileStream << parameters.first << std::endl;

        if (wordsFileStream.is_open()) {
            std::string word;
            wordsFileStream.clear();
            wordsFileStream.seekg(0);
            while (getline(wordsFileStream, word)) {
                std::unordered_map<int, int> letters;
                for (char letter : word) {
                    letters[letter]++;
                }
                bool isBuild = true;
                for (std::pair<int, int> entity : letters) {
                    if (parameters.second[entity.first] < entity.second) {
                        isBuild = false;
                        break;
                    }
                }
                if (isBuild && word.size() >= minLength) {
                    resultFileStream << word << "|";
                }
            }
        } else {
            std::cout << "File with words not found" << std::endl;
        }

        resultFileStream << std::endl << "------------" << std::endl;
    }

    wordsFileStream.close();
    resultFileStream.close();
}
