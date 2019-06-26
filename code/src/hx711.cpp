#include <hx711.hpp>

namespace r2d2::load_sensor {
        int32_t hx711::read() {
              wake();

             while(!is_ready()){}

        clock_pin.write(0);

        int32_t value = 0;
        uint8_t data[3] = { 0 };   
            for (int j = 3; j--;){
                for (int i = 0; i < 8; ++i){
                    clock_pin.write(1);
                    hwlib::wait_us(1);
                    data[j] |= data_pin.read() << (7 - i);
                    clock_pin.write(0);
                    hwlib::wait_us(1);
                }
            }
        clock_pulse();

    value = ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
    return (value - tare_value);
        };

        void hx711::clock_pulse() {
            clock_pin.write(1);
            hwlib::wait_us(1);
            clock_pin.write(0);
            hwlib::wait_us(1);
        };

        void hx711::wake() {
            clock_pin.write(0);
        };

        void hx711::sleep() {
            clock_pin.write(0);
            clock_pin.write(1);
        };

        void hx711::tare() {
        wake();

        while(!is_ready()){}

        clock_pin.write(0);

        int32_t value = 0;
        uint8_t data[3] = { 0 };   
            for (int j = 3; j--;){
                for (int i = 0; i < 8; ++i){
                    clock_pin.write(1);
                    hwlib::wait_us(1);
                    data[j] |= data_pin.read() << (7 - i);
                    clock_pin.write(0);
                    hwlib::wait_us(1);
                }
            }
        clock_pulse();

    value = ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
    tare_value = value;
        };

        bool hx711::is_ready() {
	        return data_pin.read() == 0;
        };
}