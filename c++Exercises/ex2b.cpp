#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main() {
    string str;
    vector<string> directoryNames;

    while (true) {
        cout << "Enter a directory name or blank to stop. \n";
        getline(cin, str);

        if (str.empty()){
            break;
        }else {
            directoryNames.push_back((str));
        }
    }

    fs::path relativePath;

    for(const auto& dir : directoryNames){
        relativePath /= dir;
    }

    fs::create_directories(relativePath);

    fs::path filePath = relativePath / "result.txt";
    ofstream outFile(filePath);

    if(!outFile.is_open()){
        cerr << "Error opening file: " << filePath ;
        return 1;
    }
    // Output information to the file and the screen
    cout << "Absolute path to the file: " << fs::absolute(filePath) << endl;
    outFile << "Absolute path to the file: " << fs::absolute(filePath) << endl;

    cout << "Content of the string vector:" << endl;
    outFile << "Content of the string vector:" << endl;

    for (const auto& dir : directoryNames) {
        cout << dir << endl;
        outFile << dir << endl;
    }
//C:\Users\milja\CLionProjects\c++Exercises
    cout << "Relative path to the file: " << relativePath << endl;
    outFile << "Relative path to the file: " << relativePath << endl;

    return 0;

}