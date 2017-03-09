#include "pmrrc.h"
#include "string.h"

#define PMRRC_COMMAND "$PMRRC"
#define MESSSAGE_ID_IDENT "04"
#define MESSSAGE_ID_FREQ "05"
#define LIST_TYPE "1"

// Calculate a checksum for a data packet
void checksum(char* data, int len, char checksum[2])
{
  char c = 0;

  // checksum is 8-bit addition of msg_id and msg_data. ignoring any carry
  for (int i = 0; i < len; i++)
  {
    c += data[i];
  }
  // convert to ascii by taking upper and lower nibbles and add 30h to each,
  // most significant nibble first
  checksum[0] = ((c & 0xf0) >> 4) + 0x30;
  checksum[1] = (c & 0x0f) + 0x30;
}

// Build a remote ident input packet which can be sent out the serial port
void remoteIdentInput(char *icao, char* message)
{
  char chksum[3] = {0};
  char *chksum_start = message;

  strcpy(message, PMRRC_COMMAND);
  chksum_start += strlen(message);
  strcat(message, MESSSAGE_ID_IDENT);
  strcat(message, LIST_TYPE);
  strcat(message, icao);
  checksum(chksum_start, strlen(chksum_start), chksum);
  strcat(message, chksum);
  strcat(message, "\n"); // TODO: do they actually mean \r from <cr> or \n?
}

// Build a remote frequency list packet which can be sent out the serial port
void setRemoteFreqList(char freqType, char mhz, char khz, char* message)
{
  char chksum[3] = {0};
  char *chksum_start = message;

  strcpy(message, PMRRC_COMMAND);
  chksum_start += strlen(message);
  strcat(message, MESSSAGE_ID_FREQ);
  strcat(message, LIST_TYPE);
  strncat(message, &freqType, 1);
  strncat(message, &mhz, 1);
  strncat(message, &khz, 1);
  checksum(chksum_start, strlen(chksum_start), chksum);
  strcat(message, chksum);
  strcat(message, "\n");	
}

