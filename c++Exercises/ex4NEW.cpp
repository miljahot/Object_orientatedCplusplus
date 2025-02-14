#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <regex>

using namespace std;

class Store {
private:
    string name;
    double price;
    int weight;
    int count;
public:
    Store() : name(""), price(0.0), weight(0), count(0) {}

    Store(const string &nam, double pr, int wt, int cnt) : name(nam), price(pr), weight(wt), count(cnt) {}

    // Output operator for printing store information
    friend ostream &operator<<(ostream &os, const pair<int, Store> &indexedStore);
    // Input operator for reading store information from a stream
    friend istream &operator>>(istream &is, Store &store);
    // Less than operator for comparing two stores by price/kg
    bool operator<(const Store &other) const;

    //Parsing the JSON format
    void parseJson(string &input, Store &store);

    //Print sorted list and networth
    void print(vector<Store> &items);

    int getCount() const { return count;}
    void setCount(const int cnt){ count = cnt;}

    void setPrice(double pr){ price = pr;}
    double getPrice() const{ return price;}

    void setName(const string &nam){ name = nam;}
    string getName() const { return name;}

    void setWeight(int wt){ weight = wt;}

    double netWorth() const { return price * count;}
};

// Overloading the output stream operator to print store details with an index
ostream &operator<<(ostream &os, const pair<int, Store> &indexedStore) {
    const auto &store = indexedStore.second;
    int index = indexedStore.first;

    os << left << setw(5) << index
       << setw(20) << store.name
       << setw(10) << store.price
       << setw(10) << store.weight
       << " Count: " << store.count;
    return os;
}
//Overloading the input operator
istream &operator>>(istream &is, Store &store) {
    string line;
    if (getline(is, line)) {
        stringstream ss(line);

        // Read the name until the last occurrence of a space before the numeric values
        string namePart;
        store.name = "";

        while (ss >> namePart) {
            if (isdigit(namePart[0]) || (namePart[0] == '-' && isdigit(namePart[1]))) {
                // If we hit a number, put it back and break
                ss.putback(' ');
                for (int i = namePart.length() - 1; i >= 0; --i) {
                    ss.putback(namePart[i]);
                }
                break;
            }
            if (!store.name.empty()) store.name += " ";
            store.name += namePart;
        }

        // Read the remaining numeric values
        ss >> store.price >> store.weight >> store.count;
    }
    return is;
}

bool Store::operator<(const Store &other) const {
    return (price / weight ) < ( other.price / other.weight );
}

void Store::parseJson(string &input, Store &store) {
    regex pattern(R"(\s*\"\s*name\s*\"\s*:\s*\"([^\"]+)\"\s*,\s*\"\s*price\s*\"\s*:\s*([\d\.]+)\s*,\s*\"\s*weight\s*\"\s*:\s*(\d+)\s*,\s*\"\s*count\s*\"\s*:\s*(\d+)\s*)");
    smatch matches;

    if (regex_search(input, matches, pattern)) {
        store.name = matches[1];
        store.price = stod(matches[2]);
        store.weight = stoi(matches[3]);
        store.count = stoi(matches[4]);
    } else {
        cerr << "Error: Invalid JSON format!" << endl;
    }
}
void printer(vector<Store> &items){
    // Sort the vector of stores
    sort(items.begin(), items.end());

    // Print the sorted item information
    cout << "\nSorted items:\n";
    double totalNetWorth = 0.0;

    for (int i = 0; i < items.size(); ++i) {
        // Print each store with an index
        cout << make_pair(i + 1, items[i]) << endl;
        totalNetWorth += items[i].netWorth(); // Accumulate the net worth
    }
    cout << "Total Net Worth: " << totalNetWorth  << "eur\n" << endl;
}

void modifyItemPrice(vector<Store> &items) {
    if (items.empty()) {
        cout << "No items available to modify.\n";
        return;
    }

    int index;
    double newPrice;
    char choice;

    do {
        // Ask the user to choose an item
        cout << "Enter the index number of the item to modify (or 0 to stop): ";
        cin >> index;

        // Stop if the user enters 0
        if (index == 0) {
            cout << "Exiting price modification.\n";
            break;
        }

        // Validate index
        if (index < 1 || index > items.size()) {
            cout << "Invalid index. Please try again.\n";
            continue;
        }

        // Ask for a new price
        cout << "Enter new price for " << items[index - 1].getName() << ": ";
        cin >> newPrice;

        // Validate the price
        if (newPrice < 0) {
            cout << "Price cannot be negative. Try again.\n";
            continue;
        }

        // Update the price
        items[index - 1].setPrice(newPrice);
        cout << "Price updated successfully!\n";

        // Ask if the user wants to modify another item
        cout << "Do you want to modify another item? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "All modifications completed.\n";
}



//--------------------------------------------------------------------------------------------
int main() {
    vector<Store> items;
    string input;
    Store store;

    while(true){
        cout << "Enter item info(name price weight count) or 'stop' to end, or 'json' to enter in JSON format \n";
        getline(cin, input);

        if(input =="stop") break;
        if(input =="json"){
            cout << "Enter JSON: ";
            getline(cin, input);

            store.parseJson(input,store);
            items.push_back(store);
        } else {
            stringstream ss(input);
            string name;
            double price;
            int weight;
            int count;
            ss >> name >> price >> weight >> count;
            items.emplace_back(name, price, weight, count);
        }
    }

    printer(items);
    modifyItemPrice(items);
    printer(items);
}