#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

class Store {
private:
    string name;
    double price;
    int weight;
public:
    Store() : name(""), price(0.0), weight(0) {}

    Store(const string &addr, double sz, int pr) : name(addr), price(sz), weight(pr) {}

    // Output operator for printing housing information
    friend ostream &operator<<(ostream &os, const Store &house);

    // Input operator for reading housing information from a stream
    friend istream &operator>>(istream &is, Store &house);

    // Less than operator for comparing two houses by weight/m^2
    bool operator<(const Store &other) const;

    void setName(const string &addr) {
        name = addr;
    }

    void setWeight(double sz) {
        price = sz;
    }

    void setPrice(int pr) {
        weight = pr;
    }
};

ostream &operator<<(ostream &os, const Store &house) {
    os << left << house.name << ':'
       << right << house.price << ' '
        << right << house.weight;
    return os;
}

istream &operator>>(istream &is, Store &house) {
    getline(is, house.name, ':');
    cin >> house.price >> house.weight;

    return is;
}

bool Store::operator<(const Store &other) const {
    return (weight / price) < (other.weight / other.price);
}

int main() {
    vector<Store> houses;
    string address;
    double sizeStr;
    int priceStr;

    // Method 1: Using constructor
    cout << "Enter name, price and weight";
    getline(cin, address, ':');
    cin >> sizeStr >> priceStr;

    Store house1(address, sizeStr, priceStr);
    houses.push_back(house1);

    // Method 2: Using default constructor and setter functions
    Store house2;
    cout << "Enter name, price and weight";
    getline(cin, address, ':');
    cin >> sizeStr >> priceStr;

    house2.setName(address);
    house2.setWeight(sizeStr);
    house2.setPrice(priceStr);

    houses.push_back(house2);

    // Method 3: Using default constructor and input operator
    Store house3;
    cout << "Enter house information for Method 3 (name price weight): ";
    cin >> house3;

    houses.push_back(house3);

    // Method 4: Using default constructor, setter functions, and constructor
    cout << "Enter name, price and weight";
    getline(cin, address, ':');
    cin >> sizeStr >> priceStr;

    Store house4(address, sizeStr, priceStr);
    houses.push_back(house4);

    houses.push_back(house4);

    // Method 5: Using default constructor and setter functions
    Store house5;
    cout << "Enter name, price and weight";
    getline(cin, address, ':');
    cin >> sizeStr >> priceStr;

    house5.setName(address);
    house5.setWeight(sizeStr);
    house5.setPrice(priceStr);

    houses.push_back(house5);

    // Sort the vector of houses
    sort(houses.begin(), houses.end());

    // Print the sorted house information
    cout << "\nSorted Store Information:\n";
    for (const auto &house : houses) {
        cout << house << endl;
    }
}