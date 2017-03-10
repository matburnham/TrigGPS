#include <SD.h>

#include "search.h"

#define DATA_FILENAME "testdata.dat"

//[ 2 bytes  | 2 bytes   | 4 bytes ]
//[ latitude | longitude | ident    ]

// TODO: change ident to a pointer to frequencies in due course
typedef struct {
  int16_t lat;
  int16_t lng;
  int32_t ptr;
} kd_node;

void lookupGPS(int16_t lat, int16_t lng)
{
  File dataFile = SD.open(DATA_FILENAME, FILE_READ);
  if(dataFile)
  {
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
  else
  {
    SerialMonitor.println("Error opening data file.");
  }
}

void find_airports(int16_t lat, int16_t lng, int16_t airports[10])
{
  airports[0] = 0;
  return;
}

void get_airport_details(int16_t pos, airport *airport_data)
{
  File dataFile = SD.open(DATA_FILENAME, FILE_READ);
  if(dataFile)
  {
    dataFile.seek(pos);
    dataFile.read(airport_data, sizeof(airport));
    dataFile.close();

    // Count of entries is held as an ASCII value to match the rest of the file,
    // but needs to be converted to an integer value as it is actually used
    // programmatically rather than passed on
    airport_data->freq_count -= (int) '0';
  }
  else
  {
    SerialMonitor.println("Error opening data file.");
  }
}

/* TODO:
 * 
 * Mock the SD card data and try to follow the struct
 *
 */
