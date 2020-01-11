
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<int, int> getAvailableLetters(std::string *lettersFileName);
void createWords(std::string *wordsFileName, std::string *resultFileName, std::unordered_map<int, int> availableLetters);

int main(int argc, const char * argv[]) {

    std::string lettersFileName, wordsFileName, resultFileName;
    std::cout << "Input path to file for letters" << std::endl;
    std::cin >> lettersFileName;
    std::cout << "Input path to file for words" << std::endl;
    std::cin >> wordsFileName;
    std::cout << "Input path to file for result" << std::endl;
    std::cin >> resultFileName;

    std::unordered_map<int, int> availableLetters = getAvailableLetters(&lettersFileName);

    createWords(&wordsFileName, &resultFileName, availableLetters);

    return 0;
}

std::unordered_map<int, int> getAvailableLetters(std::string *lettersFileName) {
    std::unordered_map<int, int> availableLetters;
    std::fstream lettersFileStream(*lettersFileName, std::ios::in);

    if (lettersFileStream.is_open()) {
        char letter;
        while (lettersFileStream.get(letter)) {
            availableLetters[letter]++;
        }
    } else {
        std::cout << "File with letters not found" << std::endl;
    }

    lettersFileStream.close();

    return availableLetters;
}

void createWords(std::string *wordsFileName, std::string *resultFileName, std::unordered_map<int, int> availableLetters) {
    std::fstream wordsFileStream(*wordsFileName, std::ios::in);
    std::ofstream resultFileStream(*resultFileName, std::ios::out | std::ios::trunc);

    if (wordsFileStream.is_open()) {
        std::string word;
        while (getline(wordsFileStream, word)) {
            std::unordered_map<int, int> letters;
            for (char letter : word) {
                letters[letter]++;
            }
            bool isBuild = true;
            // first is key
            // second is value
            for (std::pair<int, int> entity : letters) {
                if (availableLetters[entity.first] < entity.second) {
                    isBuild = false;
                    break;
                }
            }
            if (isBuild) {
                resultFileStream << word << "|";
            }
        }
    } else {
        std::cout << "File with words not found" << std::endl;
    }
    wordsFileStream.close();
    resultFileStream.close();
}
