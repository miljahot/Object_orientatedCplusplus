#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

int main() {
    map<string, int> ageMap;
    string str;
    int inputInteger;

    while (true) {
        cout << "Enter a name, 'stop' or 'print': ";
        getline(cin, str);

        if (str == "stop") {
            break;
        } else if (str == "print") {
            cout << "Map contents:" << endl;
            for (const auto& pair : ageMap) {
                cout << pair.first << ": " << pair.second << endl;
            }
        } else {
            cout << "Enter integer: " ;
            cin >> inputInteger;
            if (cin.fail()) cin.clear() ;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ageMap[str] = inputInteger;

        }
    }
}