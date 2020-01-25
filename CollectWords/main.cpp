
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<int, int> getAvailableLetters(std::string *word);
void createWords(std::string *wordsFileName, std::unordered_map<int, int> availableLetters);

int main(int argc, const char * argv[]) {

    std::string wordsFileName, word;

    std::cout << "Input path to file for words" << std::endl;
    std::cin >> wordsFileName;

    while (true) {
        std::cout << "Input word" << std::endl;
        std::cin >> word;
        std::unordered_map<int, int> availableLetters = getAvailableLetters(&word);
        createWords(&wordsFileName, availableLetters);

    }

    return 0;
}

std::unordered_map<int, int> getAvailableLetters(std::string *word) {
    std::unordered_map<int, int> availableLetters;

    for (int letter : *word) {
        availableLetters[letter]++;
    }

    return availableLetters;
}

void createWords(std::string *wordsFileName, std::unordered_map<int, int> availableLetters) {
    std::fstream wordsFileStream(*wordsFileName, std::ios::in);

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
            std::cout << word << "|";
        }
    }

    wordsFileStream.close();
    std::cout << std::endl;
}
