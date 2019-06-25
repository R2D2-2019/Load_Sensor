#include "hwlib.hpp"
#include <hx711.hpp>

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto data = hwlib::target::pin_in(hwlib::target::pins::d2);
    auto clk = hwlib::target::pin_out(hwlib::target::pins::d3);
    
    r2d2::load_sensor::hx711 scale = r2d2::load_sensor::hx711(clk , data);
    hwlib::wait_ms(500);

    hwlib::cout << scale.tare_value << "\n";
    scale.tare();
    hwlib::cout << scale.tare_value << "\n";
    for(;;){

      int a = scale.read();
      hwlib::cout << a << "\n";
      hwlib::wait_ms(1000);
    }

}