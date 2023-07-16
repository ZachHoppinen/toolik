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
  // #include <SD.h>
  #include <stdint.h>
  #include <Wire.h>
  #include "LIDARLite_v4LED.h"

///////////////////////////////
//// Variable Definitions ////
/////////////////////////////
#define DEBUG_PORT SERIAL_PORT_USBVIRTUAL
#define BAUD_USB_SERIAL 9600

///////////////////////////////
//// Lidar Config  ////// ////
/////////////////////////////
LIDARLite_v4LED myLidarLite;
#define FAST_I2C
//#define MonitorPin    10  //This is wrong (6)
//#define TriggerPin    11 //This might also be wrong (5)

uint16_t distance;
uint16_t  newDistance;

enum rangeType_T
{
    RANGE_NONE,
    RANGE_SINGLE,
    RANGE_CONTINUOUS,
    RANGE_SINGLE_GPIO,
    RANGE_CONTINUOUS_GPIO
};

void setup() {
  // put your setup code here, to run once:
  DEBUG_PORT.begin(BAUD_USB_SERIAL);
  while (!DEBUG_PORT);
  DEBUG_PORT.println("Debug Port Started..");

  // Lidar Setup
  // Initialize Arduino I2C for communication to Lidar
  Wire.begin();
  #ifdef FAST_I2C
      #if ARDUINO >= 157
          Wire.setClock(400000UL); // Set I2C frequency to 400kHz (for Arduino Due)
      #else
          TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
      #endif
  #endif

  // ---------------------------------------------------------------------------------------------------
  // External pull-ups are NOT present on the Arduino feather m0 and must be added manually. 
  // Needs 2.2k-10K pull-up resistors to 3.3V
  // ---------------------------------------------------------------------------------------------------
//  pinMode(MonitorPin, INPUT);// Optional GPIO pin assignments for measurement triggering & monitoring
//  pinMode(TriggerPin, OUTPUT);// Optional GPIO pin assignments for measurement triggering & monitoring
//  digitalWrite(TriggerPin, LOW);// Optional GPIO pin assignments for measurement triggering & monitoring7
  myLidarLite.configure(1); 

  delay(2000);
};

void loop() {
  // put your main code here, to run repeatedly:
  // print labels
  DEBUG_PORT.println("Started..");

  newDistance = 0;
  newDistance = distanceSingle(&distance);
  DEBUG_PORT.println(distance);

  delay(2000);
};
////////////////////////////
///////////////////////////
/// LIDAR SETTINGS  //////
/////////////////////////
////////////////////////
//---------------------------------------------------------------------
// Read Single Distance Measurement
//
// This is the simplest form of taking a measurement. This is a
// blocking function as it will not return until a range has been
// taken and a new distance measurement can be read.
//---------------------------------------------------------------------
uint8_t distanceSingle(uint16_t * distance)
{
    // 1. Trigger range measurement.
    myLidarLite.takeRange();
    
    // 2. Wait for busyFlag to indicate device is idle.
    myLidarLite.waitForBusy();

    // 3. Read new distance data from device registers
    *distance = myLidarLite.readDistance();

    return 1;
}

