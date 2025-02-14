#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <iterator>
#include <stdio.h>
#include "pico/stdlib.h"
#include <sys/time.h>
#include <map>
#include <chrono>


using namespace std;

class GPIOpin{
public:
    GPIOpin(uint pin, bool input = true, bool pullup = true, bool invert = false);
    GPIOpin(const GPIOpin &) = delete;
    bool read();
    bool operator() (); //returns the state of the pin
    void write(bool value);
    void operator() (bool); //this writes a value to the pin
    operator int(){return m_pin;}; //this return the GPIO pin number
private:
    uint m_pin;
    bool m_input;
    bool m_invert;

};

GPIOpin::GPIOpin(uint pin, bool input, bool pullup, bool invert) : m_pin{pin}, m_input{input}, m_invert{invert}{
    gpio_init(m_pin);
    gpio_set_dir(m_pin, !input);

    if(m_input && pullup) {
        gpio_pull_up(m_pin);
    } else if (m_input && !pullup) {
        gpio_pull_down(m_pin);
    }

    if (invert) {
        if (m_input) {
            gpio_set_inover(m_pin, GPIO_OVERRIDE_INVERT); // Invert input
        } else {
            gpio_set_outover(m_pin, GPIO_OVERRIDE_INVERT); // Invert output
        }
    }
}

bool GPIOpin::read() { return m_invert? !gpio_get(m_pin) : gpio_get(m_pin);}
bool GPIOpin::operator()() { return read();}
void GPIOpin::write(bool value) {
        gpio_put(m_pin, value);

}
void GPIOpin::operator()(bool value) {write(value);}

//--------------------------------------------------------------------------------
class ButtonLEDController {
public:
    ButtonLEDController(GPIOpin& button, GPIOpin& led, int release_key)
            : m_button(button), m_led(led), m_release_key(release_key), m_release_time() {}

    void update() {
        bool button_state = m_button();  // Read button state

        if (!button_state) {
            m_led(true);  // Turn on LED immediately
            m_release_time = std::chrono::steady_clock::now();  // Start timer when button is pressed
        } else {
            if (std::chrono::steady_clock::now() - m_release_time > std::chrono::seconds(1)) {
                m_led(false);  // Turn off LED after 1 second of release
            }
        }
    }

private:
    GPIOpin& m_button;
    GPIOpin& m_led;
    int m_release_key;
    std::chrono::steady_clock::time_point m_release_time;
};

//----------------------------------------------------------------

int main(){
    //Buttons
    GPIOpin sw0(9, true, true, false);
    GPIOpin sw1(8, true, true, false);
    GPIOpin sw2(7, true, true, false);

    //LEDs
    GPIOpin led1(22, false);
    GPIOpin led2(21, false);
    GPIOpin led3(20, false);

    // Create ButtonLEDController objects for each button and LED pair
    ButtonLEDController button_led1(sw2, led1, 3);
    ButtonLEDController button_led2(sw1, led2, 4);
    ButtonLEDController button_led3(sw0, led3, 5);

    while(true){
        // Update each button-LED controller
        button_led1.update();
        button_led2.update();
        button_led3.update();

        sleep_ms(10);
    }
}