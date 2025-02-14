#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iterator>


using namespace std;

//Function object
class RandGen_2 {
public:
    RandGen_2(int a = 0, int b = 100) : numbers(), min(a), max(b) { srand(time(nullptr)); }

    int operator()();
private:
    vector<int> numbers;
    int min;
    int max;
};

class MatchCount {
private:
    int count;
public:
    MatchCount() : count(1) {};
    void operator()(const int &num);
};

void MatchCount::operator()(const int &num) {
    cout << "# "<< count++ << ": " << num << endl;
}

int RandGen_2::operator()() {
    int number;
    do {
        number = rand() % max - min + 1 + min;
    } while (find(numbers.begin(), numbers.end(), number) != numbers.end());
    numbers.push_back(number);
    return number;
}

stringstream GenerateLotteryNum(int min, int max, vector<int> &numbers) {
    RandGen_2 random(min, max);
    stringstream output;

    generate(numbers.begin(), numbers.end(), random);
    sort(numbers.begin(), numbers.end());
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(output, " "));

    return output;
}
vector<int> findMatches (const vector<int> &v1, const vector<int> &v2){
    MatchCount matchCount;
    vector<int> matches;

    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(matches));
    for_each(matches.begin(), matches.end(), matchCount);

    return matches;
}

int main() {
    vector<int> vec1(7);
    vector<int> vec2(6);
    vector<int> vec3(5);
    string input;

    do {
        cout << "Lotto: " << GenerateLotteryNum(1, 40, vec1).str() << endl;
        cout << "Viking lotto: " << GenerateLotteryNum(1, 48, vec2).str() << endl;
        cout << "Matching numbers: " << endl;
        vector<int> vec4 = findMatches(vec1, vec2);

        cout << "Eurojackpot: " << GenerateLotteryNum(1, 50, vec3).str() << endl;
        cout << "Matching numbers in three sets: " << endl;
        findMatches(vec3, vec4);

        cout << "Type yes if you want to continue." << endl;
        cin >> input;
    }while (input == "yes");

    return 0;
}