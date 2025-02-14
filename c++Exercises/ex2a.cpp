#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    string str;
    vector<int> numbers;

    while (true) {
        cout << "Enter a line with numbers or 'stop': ";
        getline(cin, str);

        if (str == "stop") {
            break;
        } else {
            stringstream ss(str);
            int sum = 0;
            int count = 0;
            int num;

            while (ss >> num) {
//                if (!ss.fail()) {
                    sum += num;
                    count++;
//                }
            }
            cout << "Total of " << count << " numbers is " << sum << '\n';
        }
    }
}