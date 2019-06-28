// #pragma once

// #include <base_module.hpp>

// namespace r2d2::load_sensor {

//     class module_c : public base_module_c {

//     }
// }

#pragma once

#include <hwlib.hpp>

namespace r2d2::load_sensor {
    /**
     * hx711_c is an adc and amplifier that is used to read 
     * data from the load cell
     */
    class hx711_c {
    private:
        // This is the clock pin of the hx711
        hwlib::pin_out &clock_pin;
        // This is the data pin of the hx711
        hwlib::pin_in &data_pin;

    public:
        /**
         * Constructs the interface for the hx711
         */
        hx711_c(hwlib::pin_out &clock_pin, hwlib::pin_in &data_pin)
            : clock_pin(clock_pin), data_pin(data_pin), tare_value(0) {}

        /**
         * Reads the data from the hx711 and converts it to grams by
         * removing the tare_value deviding it by the calibration_factor
         */
        int32_t read();

        /**
         * This method reads multiple times and returns the average value
         * @param samples Samples is the amount of readings it performs
         */
        int32_t read_average(const int &samples);

        /**
         * Reads the value from the hx711 and sets it as its base value
         */
        void tare();

        /**
         * Used to calibrate the load cell
         * Takes a knows weight and uses it to convert its data to grams
         * @param grams The known weight of the objects used to calibrate.
         */
        void calibrate(const int &grams);

    private:
        /**
         * Used to send one clock pulse
         * Writes a 1 and a 0
         */
        void clock_pulse();

        /**
         * Used to wake the hx711
         * Writes a 0
         */
        void wake();

        /**
         * Used to put the hx711 to sleep
         * Writes a 0 and a 1
         */
        void sleep();

        /**
         * Check if the data pin is 0
         * Data pin 0 means ready to send data
         */
        bool is_ready() const;

        /**
         * Reads raw data from the hx711
         */
        int32_t read_raw();

        /**
         * This is the base value of the loadcell 
         * used to calculate the weight
         */
        int tare_value;

        /**
         * This is used to convert the data to grams
         */
        int calibration_factor = 1;
    };
} // namespace r2d2::load_sensor