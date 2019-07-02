#include "hwlib.hpp"
#include <hx711.hpp>

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    namespace target = hwlib::target;

    auto data = hwlib::target::pin_in(hwlib::target::pins::d2);
    auto clk = hwlib::target::pin_out(hwlib::target::pins::d3);
    auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
    auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled_channel = i2c_bus.channel( 0x3c );
    auto oled         = hwlib::glcd_oled_i2c_128x64_direct( oled_channel );  
   
    auto font = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from( oled, font );

    r2d2::load_sensor::hx711_c scale = r2d2::load_sensor::hx711_c(clk , data);
    hwlib::wait_ms(500);

    scale.calibrate(217);

    char letter_array[5];
    for(;;){
      int value = scale.read_average(20);
      letter_array[4] = (value % 10) + '0'; value /= 10;
      letter_array[3] = (value % 10) + '0'; value /= 10;
      letter_array[2] = (value % 10) + '0'; value /= 10;
      letter_array[1] = (value % 10) + '0'; value /= 10;
      letter_array[0] = (value % 10) + '0'; value /= 10;

        //display << letter_array[i];
      display << "\t0000" << letter_array[0];
      display << "\t0100" << letter_array[1];
      display << "\t0200" << letter_array[2];
      display << "\t0300" << letter_array[3];
      display << "\t0400" << letter_array[4];
      display << " grams" <<'\n';
      // << (int)(scale.read_average(20)) << " grams" << "\n";
      //display << a << " grams" << "\n"; 
      hwlib::wait_ms(1000);
      oled.clear();
      display << hwlib::flush;
    }

}