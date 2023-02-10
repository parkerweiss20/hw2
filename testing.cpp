#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <string>


using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    std::string word;
    rawWords = convToLower(rawWords);
    std::istringstream iss(rawWords);
    while (iss >> word) {
        std::string stripped;
        for (char c : word) {
            if (!std::ispunct(c)) {
                stripped += c;
            }
        }
        if (stripped.length() >= 2) {
            keywords.insert(stripped);
        }
    }
    return keywords;
}


int main()
  {
    std::string input = "Hello, World! This is a Test.";
    std::set<std::string> keywords = parseStringToWords(input);
    std::string ISBN_ = "900-64783828-6573";
    keywords.insert(ISBN_);
    std::cout << "Input string: " << input << std::endl;
    std::cout << "Parsed words: ";

    for (const std::string& word : keywords) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
