  /******************************************************************************
  Log GPS data and Lidar Distance to a CSV file as soon as Toolik is turned on
  By Thomas Van Der Weide
  March 16, 2023
  Adapted by Zachary Hoppinen
  July 11, 2023

  Use the NeoGPS library to parse the NMEA strings sent by the GPS module,
  and print interesting GPS information - comma separated - to a newly created
  file on the SD card.

  Resources:
  SD Library (Built-in)
  NeoGPS Library (NMEAGPS)
  LiquidCrystal_I2C
  LIDARLite_v4LED.h

  Development/hardware environment specifics:
  Arduino Feather M0
  Ardusimple RTK3B
  - Update GPS Firmware
  - Set Position Output to Serial -> UART with 115200 baud
    Emlid S1 Ground  (pin 1) to Arduino GND
    Emlid S1 TX (pin 4) to Arduino RX
  Garmin LidarLite LED v4
    LIDAR-Lite 5 VDC   (pin 1) to Arduino 5V
    LIDAR-Lite Ground  (pin 2) to Arduino GND
    LIDAR-Lite I2C SDA (pin 3) to Arduino SDA
    LIDAR-Lite I2C SCL (pin 4) to Arduino SCL
    (Capacitor recommended to mitigate inrush current when device is enabled)
    680uF capacitor (+) to Arduino 5V
    680uF capacitor (-) to Arduino GND]
******************************************************************************/

  #include <SPI.h>
  #include <SD.h>
  #include <stdint.h>

///////////////////////////////
//// Variable Definitions ////
/////////////////////////////
#define DEBUG_PORT SERIAL_PORT_USBVIRTUAL
#define BAUD_USB_SERIAL 9600

//File to log to
File logFile;
// SD card read/write
#define CS 4

void setup() {
  // put your setup code here, to run once:
  serial.println("Here");
}

void loop() {
  // put your main code here, to run repeatedly:

}
