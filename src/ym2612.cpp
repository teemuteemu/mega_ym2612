#include <Arduino.h>

#include <stdint.h>

#include "ym2612.h"
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

void setReg(uint8_t reg, uint8_t data) {
	// specify registers (timers + channels 1-3) to write
	YM_CTRL_PORT &= ~_BV(YM_A0); // A0 LOW (select register)
	write_ym(reg);
	// write the data to those registers
	YM_CTRL_PORT |= _BV(YM_A0);  // A0 HIGH (write register)
	write_ym(data);
}

void initChannel(Channel channel) {
	// Feedback & algorithm
	setReg(YM_REG_FB_ALG_CH1, (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setReg(YM_REG_DET_MUL_OP1_CH1, (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setReg(YM_REG_DET_MUL_OP2_CH1, (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setReg(YM_REG_DET_MUL_OP3_CH1, (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setReg(YM_REG_DET_MUL_OP4_CH1, (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setReg(YM_REG_TL_OP1_CH1, channel.ops[0].totalLevel);
	setReg(YM_REG_TL_OP2_CH1, channel.ops[1].totalLevel);
	setReg(YM_REG_TL_OP3_CH1, channel.ops[2].totalLevel);
	setReg(YM_REG_TL_OP4_CH1, channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setReg(YM_REG_RS_AR_OP1_CH1, (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setReg(YM_REG_RS_AR_OP2_CH1, (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setReg(YM_REG_RS_AR_OP3_CH1, (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setReg(YM_REG_RS_AR_OP4_CH1, (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setReg(YM_REG_AM_DR_OP1_CH1, (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setReg(YM_REG_AM_DR_OP2_CH1, (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setReg(YM_REG_AM_DR_OP3_CH1, (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setReg(YM_REG_AM_DR_OP4_CH1, (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setReg(YM_REG_DR2_OP1_CH1, channel.ops[0].decayRate2);
	setReg(YM_REG_DR2_OP2_CH1, channel.ops[1].decayRate2);
	setReg(YM_REG_DR2_OP3_CH1, channel.ops[2].decayRate2);
	setReg(YM_REG_DR2_OP4_CH1, channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setReg(YM_REG_SL_RR_OP1_CH1, (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setReg(YM_REG_SL_RR_OP2_CH1, (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setReg(YM_REG_SL_RR_OP3_CH1, (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setReg(YM_REG_SL_RR_OP4_CH1, (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setReg(YM_REG_PROPR1_CH1, 0x00);
	setReg(YM_REG_PROPR2_CH1, 0x00);
	setReg(YM_REG_PROPR3_CH1, 0x00);
	setReg(YM_REG_PROPR4_CH1, 0x00);

	// Set frequency
	setReg(YM_REG_FREQ_MSB_CH1, (channel.frequencyOctave << 3) | channel.frequencyMSB);
	setReg(YM_REG_FREQ_LSB_CH1, channel.frequencyLSB);
}
