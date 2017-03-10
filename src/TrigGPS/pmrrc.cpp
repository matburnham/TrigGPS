#include "pmrrc.h"
#include "string.h"

#define PMRRC_COMMAND "$PMRRC"
#define MESSSAGE_ID_IDENT "04"
#define MESSSAGE_ID_FREQ "05"

// Calculate a checksum for a data packet
void checksum(char* data, unsigned int len, char checksum[2])
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

void strcat_c (char *str, char c)
{
  for (;*str;str++);
  *str++ = c; 
  *str++ = 0;
}

// Build a remote ident input packet which can be sent out the serial port
// Parameters:
//   - listType  index of list for this ident (0-9)
//   - ident     station identifier, generally airport ICAO code
//   - message   output buffer (TODO: size?)
void remoteIdentInput(uint8_t listType, char *ident, char* message)
{
  char chksum[3] = {0};
  char *chksum_start = message;

  strcpy(message, PMRRC_COMMAND);
  chksum_start += strlen(message); // skip command part of message for checksum
  strcat(message, MESSSAGE_ID_IDENT);
  strcat_c(message, '0' + (char) listType);
  strncat(message, ident, 4);
  checksum(chksum_start, strlen(chksum_start), chksum);
  strcat(message, chksum);
  strcat(message, "\r\n");
}

// Build a remote frequency list packet which can be sent out the serial port
void setRemoteFreqList(uint8_t listType, char freqType, char mhz, char khz, char* message)
{
  char chksum[3] = {0};
  char *chksum_start = message;

  strcpy(message, PMRRC_COMMAND);
  chksum_start += strlen(message);
  strcat(message, MESSSAGE_ID_FREQ);
  strcat_c(message, '0' + (char) listType);
  strncat(message, &freqType, 1);
  strncat(message, &mhz, 1);
  strncat(message, &khz, 1);
  checksum(chksum_start, strlen(chksum_start), chksum);
  strcat(message, chksum);
  strcat(message, "\r\n");
}

