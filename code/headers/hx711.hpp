// #pragma once

// #include <base_module.hpp>

// namespace r2d2::load_sensor {

//     class module_c : public base_module_c {

//     }
// }

#pragma once

#include <hwlib.hpp>

namespace r2d2::load_sensor {
    class hx711_c {
    private:
        hwlib::pin_out &clock_pin;
        hwlib::pin_in &data_pin;

    public:
        hx711_c(hwlib::pin_out &clock_pin, hwlib::pin_in &data_pin)
            : clock_pin(clock_pin), data_pin(data_pin), tare_value(0) {}

        int32_t read() const;
        int32_t read_average(const int &samples) const;
        void tare();
        void calibrate(const int &grams);

    private:
        void clock_pulse();
        void wake();
        void sleep();
        bool is_ready() const;

        int tare_value;
        int calibration_factor = 1;
    };
} // namespace r2d2::load_sensor