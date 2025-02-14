#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iterator>
#include <stdio.h>
#include "pico/stdlib.h"

using namespace std;

class GPIOpin{
public:
    GPIOpin(int pin, bool input = true, bool pullup = true, bool invert = false);
    GPIOpin(const GPIOpin &) = delete;
    bool read();
    bool operator() (); //returns the state of the pin
    void write(bool value);
    void operator() (bool); //this writes a value to the pin
    operator int(); //this return the GPIO pin number

};
GPIOpin(int pin, bool input = true, bool pullup = true, bool invert = false){

}
bool read() { return invert_? !gpio_get(pin_) : gpio_get(pin_);}

int main(){
    //Buttons
    GPIOpin sw0(9, true, true, false);
    GPIOpin sw1(8, true, true, false);
    GPIOpin sw2(7, true, true, false);

    //LEDs
    GPIOpin led1(22, false, false, false);
    GPIOpin led2(21, false, false, false);
    GPIOpin led3(20, false, false, false);

    while(true){

    }
}