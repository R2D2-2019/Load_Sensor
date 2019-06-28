#include <hx711.hpp>

namespace r2d2::load_sensor {
    int32_t hx711_c::read() {
        return (read_raw() - tare_value) / calibration_factor;
    };

    void hx711_c::tare() {
        tare_value = read_raw();
    };

    void hx711_c::clock_pulse() {
        clock_pin.write(1);
        hwlib::wait_us(1);
        clock_pin.write(0);
        hwlib::wait_us(1);
    };

    void hx711_c::wake() {
        clock_pin.write(0);
    };

    void hx711_c::sleep() {
        clock_pin.write(0);
        clock_pin.write(1);
    };

    bool hx711_c::is_ready() const {
        return data_pin.read() == 0;
    };

    int32_t hx711_c::read_average(const int &samples) {
        int sum = 0;
        for (int i = 0; i < samples; i++) {
            sum += read();
        }
        return sum / samples;
    };

    void hx711_c::calibrate(const int &grams) {
        tare();
        hwlib::cout << "Put your weight on the scale \n";
        hwlib::cout << "Wait 5 seconds \n";
        hwlib::wait_ms(5000);

        calibration_factor = read_average(20) / grams;
        hwlib::cout << calibration_factor << "\n";
    };

    int32_t hx711_c::read_raw() {
        wake();

        while (!is_ready()) {
        }

        clock_pin.write(0);

        int32_t value = 0;
        uint8_t data[3] = {0};
        for (int j = 3; j--;) {
            for (int i = 0; i < 8; ++i) {
                clock_pin.write(1);
                hwlib::wait_us(1);
                data[j] |= data_pin.read() << (7 - i);
                clock_pin.write(0);
                hwlib::wait_us(1);
            }
        }
        clock_pulse();

        value = (data[2] << 16) | (data[1] << 8) | data[0];
        return value;
    };

} // namespace r2d2::load_sensor