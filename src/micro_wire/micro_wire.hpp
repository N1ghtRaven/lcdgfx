/*
	A lightweight library with a standard set of tools for working with hardware I2C.
	Support for all standard functions in the master role is implemented.
	Make your code easier by simply replacing Wire.h on microWire.h
	Not all libraries on Wire will be able to work with microWire , check the detailed list of supported libraries on the website.
	Controller support: ATmega168/328p (nano, uno, mini), ATmega32u4 (leonardo, micro), ATmega2560 (mega)
	Version 2.1 by Egor 'Nich1con' Zaharov from 02.03.2020
*/

/*
	ATTENTION!!!
	To save space and request a large number of bytes (for example, reading EEPROM packets), there ARE no buffers for reading and writing!!!
	The write function immediately sends a byte to the bus without waiting for endTransmission, there is no queue for sending , and sending takes some time.
	The read function directly reads a byte from the bus, the specifics of working with the bus require reading the last byte in a special order, read all the requested bytes at once.
	Until the last byte is read , the bus is busy. To read all bytes, use the "for(unt8_t i = 0; Wire" construction.available() ,i++){ data[i] = Wire.read } ".
*/

#ifndef microWire_h
#define microWire_h
#include <Arduino.h>
#include "pins_arduino.h"

class TwoWire {
public:
void begin (void);                                                      // bus initialization
	void setClock(uint32_t clock);                                      // manual setting of the bus frequency 31-900 kHz (in Hertz)
	void beginTransmission(uint8_t address);                            // open a connection (for writing data)
	uint8_t endTransmission(bool stop);                                 // close the connection , make a stop or restart (by default - stop)
	uint8_t endTransmission(void);                                      // close the connection , to make the stop
	void write(uint8_t data);                                           // send a byte of data to the bus, sending is performed immediately, the format is byte "unsigned char"
	void requestFrom(uint8_t address , uint8_t length , bool stop);     // open a connection and request data from the device, release or hold the bus
	void requestFrom(uint8_t address , uint8_t length);                 // open a connection and request data from the device, release the bus
	uint8_t read(void);                                                 // read bytes, no BUFFER!!! , read all requested bytes at once, stop or restart after reading the last byte, configured in requestFrom
	uint8_t available(void);                                            // returns the number of bytes remaining for reading
private:
	uint8_t _requested_bytes = 0;                                       // the variable stores the number of requested and unread bytes
	bool _address_nack = false;                                         // Flag for tracking an error when sending an address
	bool _data_nack = false;                                            // Flag for tracking data transfer errors
	bool _stop_after_request = true;                                    // stop or restart after reading the last byte
	void start (void);                                                  // the service function starts any work with the bus from it
	void stop (void);                                                   // service function it ends working with the bus
};
extern TwoWire Wire;
#endif