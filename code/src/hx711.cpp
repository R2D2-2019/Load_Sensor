#include <hx711.hpp>

namespace r2d2::load_sensor {
        int hx711::read() {
            int data = 0;
             wake();

             for (int i = 0; i < 24; i++){
                //clock_pulse();
                clock_pin.write(1);
                hwlib::wait_us(1);
                //data += data_pin.read();
                hwlib::cout << data_pin.read();
                data = data << 1;
                clock_pin.write(0);
                hwlib::wait_us(1);
             }
             clock_pulse();
            return data - tare_value;

            // int value = 0;
            // uint8_t i;

            // for(i = 0; i < 24; ++i) {
            //     //digitalWrite(clockPin, HIGH);
            //     clock_pin.write(1);
            //     //delayMicroseconds(1);
            //     hwlib::wait_us(1);
            //     //if(bitOrder == LSBFIRST)
            //         value |= data_pin.read() << i;
            //     //else
            //     //    value |= digitalRead(dataPin) << (7 - i);
            //     //digitalWrite(clockPin, LOW);
            //     clock_pin.write(0);
            //     //delayMicroseconds(1);
            //     hwlib::wait_us(1);
            // }
            // return value;
        };

        void hx711::clock_pulse() {
            clock_pin.write(1);
            clock_pin.write(0);
        };
        void hx711::wake() {
            clock_pin.write(0);
        };

        void hx711::sleep() {
            clock_pin.write(0);
            clock_pin.write(1);
        };
        void hx711::tare() {
            tare_value = read();
        };
}