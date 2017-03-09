#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h> // Include the TinyGPS++ library

#include "global.h"
#include "kdtree.h"
#include "pmrrc.h"

#define ARDUINO_USD_CS 8  // uSD card CS pin (pin 8 on Duinopeak GPS Logger Shield)
#define ARDUINO_GPS_RX 7  // GPS TX, Arduino RX pin
#define ARDUINO_GPS_TX 6  // GPS RX, Arduino TX pin
#define ARDUINO_SL40_RX 5 // SL40 TX, Arduino RX pin 
#define ARDUINO_SL40_TX 4 // SL40 RX, Arduino TX pin

#define DATA_FILENAME "airports.csv"

#define GPS_BAUD 9600  // GPS module baud rate. GP3906 defaults to 9600.
#define SL40_BAUD 9600 // SL40 protocol baud rate

TinyGPSPlus tinyGPS;
SoftwareSerial ssGPS(ARDUINO_GPS_TX, ARDUINO_GPS_RX);
SoftwareSerial ssSL40(ARDUINO_SL40_TX, ARDUINO_SL40_RX);
#define gpsPort ssGPS

void setup()
{
  SerialMonitor.begin(9600);
  gpsPort.begin(GPS_BAUD);
  SerialMonitor.println("Booted"); // TOOD: removeme
  Serial.print("TinyGPS v");
  Serial.println(TinyGPSPlus::libraryVersion());

  SerialMonitor.println("Setting up SD card.");
  // see if the card is present and can be initialized:
  if (!SD.begin(ARDUINO_USD_CS))
  {
    SerialMonitor.println("Error initializing SD card.");
    // TODO: then what?
  }
}

// TODO: removethis
void printLocation()
{
  SerialMonitor.print(tinyGPS.location.lat(), 6);
  SerialMonitor.println(tinyGPS.location.lng(), 6);
}

// This custom version of delay() ensures that the tinyGPS object is being "fed". From the TinyGPS++ examples.
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (gpsPort.available())
    {
      tinyGPS.encode(gpsPort.read()); // Send it to the encode function
    }
    // tinyGPS.encode(char) continues to "load" the tinGPS object with new
    // data coming in from the GPS module. As full NMEA strings begin to come in
    // the tinyGPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}

void loop()
{
  // "Smart delay" looks for GPS data while the Arduino's not doing anything else
  smartDelay(1000);

  if(tinyGPS.location.isValid())
  {
    printLocation(); // TODO: removethis

    // TODO: lookup airports and frequencies
    // TODO: set airport and frequencies
    
    lookupGPS(tinyGPS.location.lat()*10, tinyGPS.location.lng()*10);
  }
  else
  {
    SerialMonitor.println("GPS data invalid");
    // TODO: but what to do about it?
  }
}


