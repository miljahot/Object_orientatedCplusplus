#include <iostream>
#include <deque>

using namespace std;

class RunningAverage {
private:
    deque<int> values;
    size_t maxSize;

public:
    explicit RunningAverage(int size) : maxSize(size) {}

    void add_value(int value) {
        if (values.size() >= maxSize) {
            values.pop_front();
        }
        values.push_back(value);
        // Remove the oldest value if the price exceeds maxSize
    }

    double get_average() const {
        if (values.empty()) {
            return 0.0;
        }
        double sum = 0.0;
        for (int val: values) {
            sum += val;
        }
        return sum / values.size();
    }
};

int main() {
    RunningAverage avg(5);

    while (true) {
        int input;
        cout << "Enter a number (0 to stop): ";
        cin >> input;

        if (input == 0) {
            break;
        }
        avg.add_value(input);
        cout << "Current running average: " << avg.get_average();
    }
    cout << "Program stopped. Final running average: " << avg.get_average();
}