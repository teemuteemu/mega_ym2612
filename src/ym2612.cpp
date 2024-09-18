#include <Arduino.h>

#include <stdint.h>

#include "platform.h"

void write_ym(uint8_t data) {
	// open the data bus and pass the data
	YM_CTRL_PORT &= ~_BV(YM_CS); // CS LOW (sets data bus impedances low)
	YM_DATA_PORT = data;
	_delay_us(1);
	// set write-to mode
	YM_CTRL_PORT &= ~_BV(YM_WR); // write data LOW (write mode on)
	YM_CTRL_PORT |= _BV(YM_RD);  // read data HIGH (write mode on)
	_delay_us(5);
	// set read statuses mode
	YM_CTRL_PORT |= _BV(YM_WR);  // write data HIGH (read mode on)
	YM_CTRL_PORT &= ~_BV(YM_RD); // read data LOW (read mode on)
	_delay_us(5);
	// close the data bus
	YM_CTRL_PORT |= _BV(YM_CS); // CS HIGH
}

void setreg(uint8_t reg, uint8_t data) {
	// specify registers (timers + channels 1-3) to write
	YM_CTRL_PORT &= ~_BV(YM_A0); // A0 LOW (select register)
	write_ym(reg);
	// write the data to those registers
	YM_CTRL_PORT |= _BV(YM_A0);  // A0 HIGH (write register)
	write_ym(data);
}

