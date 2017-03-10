Garmin/Apollo SL40 protocol specification
=========================================

RS232 Inputs
------------
 * Baud rate: 9600
 * Data bits: 8
 * Stop bits: 1
 * Parity: none

The data format is as follows: `$PMRRC<msg_id><msg_data><chksum><cr>`

The checksum is computed by an 8 bit addition of the msg id and msg_data characters,
ignoring carry if any. The resulting 8 bit checksum is converted to two ASCII characters by
taking the upper and lower nibbles, adding 30h to each, and placing the most significant
character first in thc data message.

Remote ident input
------------------
This message is used to input a new ident, and reset the remote frequency input pointer.

### Message format
```
$PMRRC04tiiii<chksum><cr>

04 ......... message id
t .......... list type, input 1
iiii ....... ident, four character ASCII
```

### Example message
`$PMRRC041SLE<space>99<cr>`

Set the remote frequency ident to "SLE".

Remote frequency list input
---------------------------

This message is used to input frequencies for the remote recall function. Up to l0 frequencies are accepted.

### Message Format
```
$PMRRC05tfmk<chksum><cr>
05 .......message id
t ..........1ist type, input 1
f .......... frequency type:
0 = TWR, tower frequency           8 = CTF, cornmon traffic advisory frequency
1 = GND, ground frequency          9 = DEP, departure
2 = ATS, for ATIS                  : (3Ah) = FSS. flight scrvice statiorr
3 = ATF, air traffic frequcncy     ; (3Bh) = RFS, for rcmote flight servrcc station
4 = APP, for approach              < (3Ch) = UNI, for unicom
5 = ARR, for arrival               = (3Dh) = MF, mandatory frcquency
6 = AWS, automatic weather station > (3Eh) = not defined, do not use
7 : CLR, clearance/delivery        ? (3Fh) = undefined, for other frequency types
mk...... frequency:
m = desired fiequency in MHz in hexadecimal, where m = desired frequency -
30h , with desired frequency in range of 1l8 to 136 MHz, or 162 MHz.
k - desired frequency in kHz where k = (desired frequency / 25 kHz) + 30h, with
desired frequency in range of 000 to 97,5 kHz in 25kHz steps, or 0 to 39.
```

### Example Message
`$PMRRC0511IT64<cr>`

Input a ground lieclucncy type, l2l .900 MHz

*/

References
----------
1. [Model SL40 VHF COMM Installation Manual, Appendix E - Serial Interface Specifications](http://static.garmin.com/pumac/SL40Com_InstallationManual.pdf#page=33)
2. [GTR 200 COM Transceiver Installation Manual, Appendix B - Serial Interface Specifications](http://static.garmincdn.com/pumac/190-01553-00.pdf#page=) *- TODO incorporate details from this document*
