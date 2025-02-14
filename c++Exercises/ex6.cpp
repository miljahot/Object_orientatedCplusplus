#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <memory>

using namespace std;

class House {
private:
    string address;
    double size;
    double price;
public:

    House(const string &addr, double sz, double pr) : address(addr), size(sz), price(pr) {}

    // Output operator for printing housing information
    friend ostream &operator<<(ostream &os, const House &house);

    // Input operator for reading housing information from a stream
    friend istream &operator>>(istream &is, House &house);

    // Less than operator for comparing two houses by area/m^2
    bool operator<(const House &other) const;

    void setAddress(const string &addr) { address = addr;}
    void setPrice(int pr) { price = pr;}
    void setArea(double sz) { size = sz;}

    string getAddress() const { return address;}

};

ostream &operator<<(ostream &os, const House &house) {
    os << left << house.address << ' '
       << right << house.size << "m^2 "
       << right << house.price << "eur";
    return os;
}

istream &operator>>(istream &is, House &house) {
    getline(is, house.address, ':');
    is >> house.size >> house.price;

    return is;
}

bool House::operator<(const House &other) const {
    return (price / size ) < (other.price / other.size);
}

//--------------------------------------------------------------------

class Apartment{
private:
    shared_ptr<House> house;
    int apartmentNr;
    double size;
    double monthlyRent;

public:
    Apartment(shared_ptr<House> h, int aptNumber, double sz, double rent)
            : house(move(h)), apartmentNr(aptNumber), size(sz), monthlyRent(rent) {}

    void setHouse(shared_ptr<House> h) { house = move(h); }
    void setApartmentNumber(int aptNumber) { apartmentNr = aptNumber; }
    void setSize(double sz) { size = sz; }
    void setMonthlyRent(double rent) { monthlyRent = rent; }

    shared_ptr<House> getHouse() const { return house; }
    int getApartmentNumber() const { return apartmentNr; }
    double getSize() const { return size; }
    double getMonthlyRent() const { return monthlyRent; }

    // Less than operator for comparing two apartments by monthly rent
    bool operator<(const Apartment &other) const;

    void printer() const {
        cout << "Address: " << house->getAddress() << "\n";
        cout << "Apartment number: " << getApartmentNumber() << "\n";
        cout << "size: " << getSize() << "m^2\n";
        cout << "Rent: " << getMonthlyRent() << "eur\n";
    }

};
bool Apartment::operator<(const Apartment &other) const {
    return (monthlyRent) < (other.monthlyRent);
}
int main() {
    House house1("Kirkutie 4",200, 20000);
    House house2("Linnunkuja 61", 400, 50000);

    vector<Apartment> apartments;

    // Apartments for the first house (house1)
    apartments.push_back(Apartment(make_shared<House>(house1), 101, 75.5, 1200));
    apartments.push_back(Apartment(make_shared<House>(house1), 102, 85.0, 1400));
    apartments.push_back(Apartment(make_shared<House>(house1), 103, 95.0, 1600));

    // Apartments for the second house (house2)
    apartments.push_back(Apartment(make_shared<House>(house2), 201, 60.0, 1000));
    apartments.push_back(Apartment(make_shared<House>(house2), 202, 70.0, 1200));
    apartments.push_back(Apartment(make_shared<House>(house2), 203, 80.0, 1500));
    apartments.push_back(Apartment(make_shared<House>(house2), 204, 100.0, 1800));

    // Sort apartments by rent
    sort(apartments.begin(), apartments.end());

    // Print apartment info
    for(const auto &apt : apartments){
        apt.printer();
        cout << "----------------------------------\n";
    }

    // Print house info
    cout << house1 << endl;
    cout << house2 << endl;

}