#ifndef _PMRRC_H
#define _PMRRC_H

void checksum(char* data, int len, char checksum[2]);
void remoteIdentInput(char *icao, char* message);
void setRemoteFreqList(char freqType, char mhz, char khz, char* message);

#endif // _PMRRC_H
