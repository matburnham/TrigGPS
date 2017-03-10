#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#include "global.h"
#include "search.h"
#include "pmrrc.h"

// For simplicity only a single software serial port is used.
// NMEA is RX from the GPS
// SL40 is TX to the Trig TY91
#define ARDUINO_USD_CS             8  // uSD card CS pin (pin 8 on Duinopeak GPS Logger Shield)
#define GPS_RX_ARDUINO_TX          7  // Arduino TX to GPS RX (unused)
#define GPS_TX_ARDUINO_RX_TXPDR_RX 6  // GPS TX to Arduino RX and Transponder RX
#define TXPDR_TX_ARDUINIO_RX       5  // Transponder TX to Arduino RX (unused)
#define SL40_RX_ARDUINO_TX         4 // Arduino TX to SL40 RX
#define SL40_TX_ARDUINO_RX         3 // SL40 TX to Arduino RX (unused) 

#define SERIAL_MONITOR_BAUD_RATE 9600
#define SOFTSERIAL_BAUD_RATE 9600

TinyGPSPlus tinyGPS;
SoftwareSerial softSerial(GPS_TX_ARDUINO_RX_TXPDR_RX, SL40_RX_ARDUINO_TX); // RX, TX

// Use LED_BUILTIN as a fault indicator:
// SD fault = LED on
// GPS fault = LED flash
bool errorLed = LOW;

void setup()
{
  // Tried to use LED_BUILTIN as an error indicator as there's not much else we can do in an error
  // condition other than output on the serial monitor which is unlikely to be connected when in-situ
  // but pin 13 is used for SPI by the SD library
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Set up serial ports
  SerialMonitor.begin(SERIAL_MONITOR_BAUD_RATE);
  softSerial.begin(SOFTSERIAL_BAUD_RATE);

  // Print version info
  SerialMonitor.println("TrigGPS SL40 transfobulator v0.1");
  // TODO: get an automatic version number here
  SerialMonitor.print("TinyGPS v");
  SerialMonitor.println(TinyGPSPlus::libraryVersion());

  SerialMonitor.println("SD card init");
  // see if the card is present and can be initialized:
  if (!SD.begin(ARDUINO_USD_CS))
  {
    SerialMonitor.println("Error initializing SD card.");
    // TODO: possibly try to craft an error message in valid SL40
  }
}

// TODO: removethis
void printLocation()
{
  SerialMonitor.print("Location: ");
  SerialMonitor.print(tinyGPS.location.lat(), 6);
  SerialMonitor.print(", ");
  SerialMonitor.println(tinyGPS.location.lng(), 6);
}

// This custom version of delay() ensures that the tinyGPS object is being "fed". From the TinyGPS++ examples.
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (softSerial.available())
    {
      tinyGPS.encode(softSerial.read()); // Send it to the encode function
    }
    // tinyGPS.encode(char) continues to "load" the tinGPS object with new
    // data coming in from the GPS module. As full NMEA strings begin to come in
    // the tinyGPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}

// Helper function to dump the fixed length non-null terminated identifier string
void dump_ident(char *ident)
{
  char nullterminated[5] = {0};
  strncpy(nullterminated, ident, 4);
  SerialMonitor.println(nullterminated);
}

// Helper function to print to both radio RS232 port and Ardunio hardware serial.
// It is assumed the output message comes with a <CR><LF> terminator
void SL40_println(char *message)
{
  softSerial.print(message);
  SerialMonitor.print("SL40>");
  SerialMonitor.print(message);
}

void findDumpLocalAirfields(int16_t lat, int16_t lng)
{
  int16_t airports[10] = {0};

  // TODO: fill the list of airports - code not yet completed, so bodge it for now with a manually created file
  airports[0] = 0x100;
  airports[1] = 0x200;
  //void find_airports(int16_t lat, int16_t lng, int16_t airports[10]);

  // iterate found airports and load freqs
  for(uint8_t i=0; i < 10 && airports[i] != 0; i++)
  {
    airport airport = {0};
    get_airport_details(airports[i], &airport);

    // TODO: removethis
    SerialMonitor.print("Airport #");
    SerialMonitor.print(i);
    SerialMonitor.print(" (ptr:");
    SerialMonitor.print(airports[i]);
    SerialMonitor.print(") ");
    dump_ident(airport.ident);

    char message[30] = {0}; // TODO: length??

    remoteIdentInput(i, airport.ident, message);
    SL40_println(message);

    for(uint8_t j=0; j<airport.freq_count; j++)
    {
      frequency *freq = &(airport.freqs[j]);
      setRemoteFreqList(i, freq->type, freq->mhz, freq->khz, message);
      SL40_println(message);
    }    
  }
}

void loop()
{
  // "Smart delay" looks for GPS data while the Arduino's not doing anything else
  smartDelay(1000);

  if(tinyGPS.location.isValid())
  {
    SerialMonitor.println();
    printLocation();
    findDumpLocalAirfields(tinyGPS.location.lat()*10, tinyGPS.location.lng()*10); 
  }
  else
  {
    SerialMonitor.println("GPS data invalid");
    // TODO: possibly try to craft an error message in valid SL40
    // Not much we can do - carry on in case it recovers
  }
}

