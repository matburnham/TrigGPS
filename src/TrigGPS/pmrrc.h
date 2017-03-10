#ifndef _PMRRC_H
#define _PMRRC_H

#include <stdint.h>

// TODO: this doesn't need to be exposed except for test
void checksum(char* data, unsigned int len, char checksum[2]);
void strcat_c (char *str, char c);
void remoteIdentInput(uint8_t listType, char *ident, char* message);
void setRemoteFreqList(uint8_t listType, char freqType, char mhz, char khz, char* message);

#endif // _PMRRC_H
