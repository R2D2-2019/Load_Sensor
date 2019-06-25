#include <hx711.hpp>

namespace r2d2::load_sensor {
        int32_t hx711::read() {
            int data = 0;
             wake();

             while(!is_ready()){}

             for (int i = 0; i < 24; i++){
                clock_pin.write(1);
                hwlib::wait_us(1);
                data |= data_pin.read() << (7 - i);
                clock_pin.write(0);
                hwlib::wait_us(1);
             }
             clock_pulse();
            return (data - tare_value);
        // int32_t value = 0;
        // uint8_t data[3] = { 0 };   
        //     for (int j = 0; j < 3; j++){
        //         for (int i = 0; i < 8; i++){
        //             clock_pin.write(1);
        //             hwlib::wait_us(1);
        //             data[j] |= data_pin.read() << i;//(7 - i);
        //             clock_pin.write(0);
        //             hwlib::wait_us(1);
        //         }
        //     }
        //     value = (static_cast<int32_t>(0) << 24 | static_cast<int32_t>(data[2]) << 16 | static_cast<int32_t>(data[1]) << 8 | static_cast<int32_t>(data[0]));
        //     return value;
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
            int data = 0;
             wake();

             while(!is_ready()){}

             for (int i = 0; i < 24; i++){
                clock_pin.write(1);
                hwlib::wait_us(1);
                data |= data_pin.read() << (7 - i);
                clock_pin.write(0);
                hwlib::wait_us(1);
             }
             clock_pulse();
            tare_value = data;
        };

        bool hx711::is_ready() {
	        return data_pin.read() == 0;
        };
}