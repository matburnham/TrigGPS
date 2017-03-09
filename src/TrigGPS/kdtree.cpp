#include <SD.h>

#include "kdtree.h"

#define DATA_FILENAME "output_trunc.dat"

//#define byte uint8_t
//#define byte unsigned char 

typedef struct {
  byte type;
  byte mhz;
  byte khz;
} freq;

typedef struct {
  char icao[4];
  byte count;
  freq freqs[1]; // one or more frequencies
} airport;

//[ 2 bytes  | 2 bytes   | 4 bytes ]
//[ latitude | longitude | icao    ]

// TODO: change icao to a pointer to frequencies in due course
typedef struct {
  int16_t lat;
  int16_t lng;
  int32_t ptr;
} kd_node;

void lookupGPS(int16_t lat, int16_t lng)
{
  File dataFile = SD.open(DATA_FILENAME, FILE_READ);
  if(!dataFile)
  {
    SerialMonitor.println("Error opening data file.");
    return;
  }
  
  kd_node node;
  
  dataFile.read(&node, sizeof(kd_node));
  // TODO: left = pos x 2 + 1; right = pos x 2 + 2 (* sizeof struct)
  int pos = 0;
  dataFile.seek(pos);
  
  //while (dataFile.available()) {
  //  dataFile.read();
  //}
  dataFile.close();
  Serial.print("Done");
}

void find_airports(int16_t lat, int16_t lng, int16_t airports[10])
{
  airports[0] = 0;
  return;
}

/* TODO:
 * 
 * Mock the SD card data and try to follow the struct
 *
 */
