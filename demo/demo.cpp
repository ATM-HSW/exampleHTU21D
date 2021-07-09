/* 
 HTU21D Humidity Sensor Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 15th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Uses the HTU21D library to display the current humidity and temperature
 
 Open serial monitor at 115200 baud to see readings. Errors 998 if not sensor is detected. Error 999 if CRC is bad.
  
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

int main() {
  printf("HTU21D Example\n");

  myHumidity.begin(i2c);

  while(true) {
    float humd = myHumidity.readHumidity();
    float temp = myHumidity.readTemperature();

    printf(" Temperature: %f[C]\n", temp);
    printf(" Humidity: %f[%%]\n", humd);

    thread_sleep_for(1000);
  }
}