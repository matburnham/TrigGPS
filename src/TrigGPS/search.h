#include "global.h"

typedef struct {
  char type;
  char mhz;
  char khz;
} frequency;

typedef struct {
  char ident[4];
  char freq_count;
  frequency freqs[20];
} airport;

void lookupGPS(int16_t lat, int16_t lng);
void find_airports(int16_t lat, int16_t lng, int16_t airports[10]);
void get_airport_details(int16_t pos, airport *airport_data);
