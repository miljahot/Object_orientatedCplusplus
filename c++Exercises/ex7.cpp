#include <string>
#include <iostream>

using namespace std;

class Person {
public:
    Person(const char *name = "nobody");
    virtual ~Person() = default;
    virtual void identity() const;
    virtual void interrogate();
protected:
    string name;
};

Person::Person(const char *name) : name(name) {}

void Person::identity() const { cout << "My name is: " << name << endl; }

void Person::interrogate() {}


//-----------------------------------------------------------------------
class Spy : public Person {
public:
    Spy(const char *name, const string &al, int res) : Person(name), alias(al), resistance(res) {}

    //Set spy's alias
    void set_identity(const char *new_alias) {
        alias = new_alias;
    }

    //override identity to print either alias or name depenting on spy's resistance
    void identity() const override {
        if (resistance > 0) {
            cout << "My name is: " << alias << endl; //print alias when resistance > 0
        } else {
            cout << "My name is: "<<  name << "\nMy alias is: " << alias << endl;
        }
    }

    //override interrogate to decrease spy's resistance
    void interrogate() override {
        if (resistance > 0) {
            resistance--;
        }
    }

private:
    string alias;
    int resistance;
};

//--------------------------------------------------------------------
int main(int argc, char **argv) {
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);
    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();
    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }
    return 0;
}