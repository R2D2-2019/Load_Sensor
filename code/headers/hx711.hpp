// #pragma once

// #include <base_module.hpp>

// namespace r2d2::load_sensor {

//     class module_c : public base_module_c {
        
//     }
// }

#pragma once

#include <hwlib.hpp>

namespace r2d2::load_sensor {
    class hx711 {
    private:
        hwlib::pin_out &clock_pin;
        hwlib::pin_in &data_pin;

        int tare_value = 0;

    public:
        hx711(hwlib::pin_out &clock_pin, hwlib::pin_in &data_pin):
            clock_pin(clock_pin),
            data_pin(data_pin)
        {}

    //protected:
        int read();
        void tare();

    private:
        void clock_pulse();
        void wake();
        void sleep();
    };
}