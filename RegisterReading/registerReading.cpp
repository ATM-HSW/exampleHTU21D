/* 
 HTU21D Humidity Sensor Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 15th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 This example demonstrates how to read the user registers to display resolution and other settings.
 
 Uses the HTU21D library to display the current humidity and temperature
 
 Open serial monitor at 9600 baud to see readings. Errors 998 if not sensor is detected. Error 999 if CRC is bad.
  
 Hardware Connections (Breakoutboard to Arduino):
 -VCC = 3.3V
 -GND = GND
 -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 -SCL = A5 (use inline 330 ohm resistor if your board is 5V)

 */

#include "mbed.h"
#include "SparkFunHTU21D.h"

I2C i2c(I2C_SDA , I2C_SCL );

//Create an instance of the object
HTU21D myHumidity;

void show_yes_no(const char *prefix, int val) {
  printf("%s%s\n", prefix, val?"yes":"no");
}

void dump_user_register() {
  uint8_t reg = myHumidity.readUserRegister();

  printf("Resolution (Humidity, Temperature): ");
  switch (reg & USER_REGISTER_RESOLUTION_MASK) {
    case USER_REGISTER_RESOLUTION_RH12_TEMP14: printf("12, 14\n"); break;
    case USER_REGISTER_RESOLUTION_RH8_TEMP12:  printf(" 8, 12\n"); break;
    case USER_REGISTER_RESOLUTION_RH10_TEMP13: printf("10, 13\n"); break;
    case USER_REGISTER_RESOLUTION_RH11_TEMP11: printf("11, 11\n"); break;
  }

  show_yes_no("End of battery: ", reg & USER_REGISTER_END_OF_BATTERY);
  show_yes_no("Heater enabled: ", reg & USER_REGISTER_HEATER_ENABLED);
  show_yes_no("Disable OTP reload: ", reg & USER_REGISTER_DISABLE_OTP_RELOAD);
}

int main() {
  printf("HTU21D Example\n");

  myHumidity.begin(i2c);
  
  dump_user_register();

  while(true) {
    float humd = myHumidity.readHumidity();
    float temp = myHumidity.readTemperature();

    printf(" Temperature: %f[C]\n", temp);
    printf(" Humidity: %f[%%]\n", humd);

    thread_sleep_for(1000);
  }
}
