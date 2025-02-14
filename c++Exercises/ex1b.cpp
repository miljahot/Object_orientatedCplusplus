#include <iostream>
#include <string>

void replacer_function(std::string &str, char replace);

int main() {
    std::string str1, str2;
    while (true) {
        std::cout << "Enter a string: ";
        std::getline(std::cin, str1);

        std::cout << "Enter character to replace or 'stop': ";
        std::cin >> str2;

        if (str2 == "stop" ){
            break;
        } else {
            replacer_function(str1, str2[0]);
            std::cout << "Result: " << str1 << "\n";
        }
        std::cin.ignore();
    }
}

void replacer_function(std::string &str, const char replace) {
    for (char &c: str) {
        if (c == replace) {
            c = '_';
        }
    }
}