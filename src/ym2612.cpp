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

void setRegPt1(uint8_t reg, uint8_t data) {
	// A0 LOW and A1 LOW => write register for channels 1-3
	YM_CTRL_PORT &= ~_BV(YM_A0); // A0 LOW (select register)
	YM_CTRL_PORT &= ~_BV(YM_A1); // A1 LOW (select register)
	write_ym(reg);
	// A0 HIGH and A1 LOW => write data for channels 1-3
	YM_CTRL_PORT |= _BV(YM_A0);  // A0 HIGH (write register)
	YM_CTRL_PORT &= ~_BV(YM_A1); // A1 LOW (write register)
	write_ym(data);
}

void setRegPt2(uint8_t reg, uint8_t data) {
	// A0 LOW and A1 HIGH => write register for channels 4-6
	YM_CTRL_PORT &= ~_BV(YM_A0); // A0 LOW (select register)
	YM_CTRL_PORT |= _BV(YM_A1);  // A1 HIGH (select register)
	write_ym(reg);
	// A0 HIGH and A1 HIGH => write data for channels 4-6
	YM_CTRL_PORT |= _BV(YM_A0);  // A0 HIGH (write register)
	YM_CTRL_PORT |= _BV(YM_A1);  // A1 HIGH (write register)
	write_ym(data);
}

void initChannel1(Channel channel) {
	// Feedback & algorithm
	setRegPt1(YM_REG_CH(FB_ALG, 1), (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setRegPt1(YM_REG_CH(DET_MUL_OP1, 1), (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP2, 1), (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP3, 1), (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP4, 1), (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setRegPt1(YM_REG_CH(TL_OP1, 1), channel.ops[0].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP2, 1), channel.ops[1].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP3, 1), channel.ops[2].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP4, 1), channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setRegPt1(YM_REG_CH(RS_AR_OP1, 1), (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP2, 1), (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP3, 1), (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP4, 1), (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setRegPt1(YM_REG_CH(AM_DR_OP1, 1), (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP2, 1), (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP3, 1), (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP4, 1), (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setRegPt1(YM_REG_CH(DR2_OP1, 1), channel.ops[0].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP2, 1), channel.ops[1].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP3, 1), channel.ops[2].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP4, 1), channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setRegPt1(YM_REG_CH(SL_RR_OP1, 1), (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP2, 1), (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP3, 1), (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP4, 1), (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setRegPt1(YM_REG_CH(PROPR1, 1), 0x00);
	setRegPt1(YM_REG_CH(PROPR2, 1), 0x00);
	setRegPt1(YM_REG_CH(PROPR3, 1), 0x00);
	setRegPt1(YM_REG_CH(PROPR4, 1), 0x00);

	// Set frequency. Important: set MSB first
	setRegPt1(YM_REG_CH(FREQ_MSB, 1), ((channel.frequencyOctave << 3) | (channel.frequency >> 8)));
	setRegPt1(YM_REG_CH(FREQ_LSB, 1), (channel.frequency & 0xFF));
}

void initChannel2(Channel channel) {
	// Feedback & algorithm
	setRegPt1(YM_REG_CH(FB_ALG, 2), (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setRegPt1(YM_REG_CH(DET_MUL_OP1, 2), (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP2, 2), (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP3, 2), (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP4, 2), (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setRegPt1(YM_REG_CH(TL_OP1, 2), channel.ops[0].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP2, 2), channel.ops[1].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP3, 2), channel.ops[2].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP4, 2), channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setRegPt1(YM_REG_CH(RS_AR_OP1, 2), (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP2, 2), (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP3, 2), (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP4, 2), (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setRegPt1(YM_REG_CH(AM_DR_OP1, 2), (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP2, 2), (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP3, 2), (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP4, 2), (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setRegPt1(YM_REG_CH(DR2_OP1, 2), channel.ops[0].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP2, 2), channel.ops[1].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP3, 2), channel.ops[2].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP4, 2), channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setRegPt1(YM_REG_CH(SL_RR_OP1, 2), (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP2, 2), (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP3, 2), (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP4, 2), (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setRegPt1(YM_REG_CH(PROPR1, 2), 0x00);
	setRegPt1(YM_REG_CH(PROPR2, 2), 0x00);
	setRegPt1(YM_REG_CH(PROPR3, 2), 0x00);
	setRegPt1(YM_REG_CH(PROPR4, 2), 0x00);

	// Set frequency. Important: set MSB first
	setRegPt1(YM_REG_CH(FREQ_MSB, 2), ((channel.frequencyOctave << 3) | (channel.frequency >> 8)));
	setRegPt1(YM_REG_CH(FREQ_LSB, 2), (channel.frequency & 0xFF));
}

void initChannel3(Channel channel) {
	// Feedback & algorithm
	setRegPt1(YM_REG_CH(FB_ALG, 3), (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setRegPt1(YM_REG_CH(DET_MUL_OP1, 3), (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP2, 3), (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP3, 3), (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setRegPt1(YM_REG_CH(DET_MUL_OP4, 3), (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setRegPt1(YM_REG_CH(TL_OP1, 3), channel.ops[0].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP2, 3), channel.ops[1].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP3, 3), channel.ops[2].totalLevel);
	setRegPt1(YM_REG_CH(TL_OP4, 3), channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setRegPt1(YM_REG_CH(RS_AR_OP1, 3), (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP2, 3), (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP3, 3), (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setRegPt1(YM_REG_CH(RS_AR_OP4, 3), (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setRegPt1(YM_REG_CH(AM_DR_OP1, 3), (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP2, 3), (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP3, 3), (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setRegPt1(YM_REG_CH(AM_DR_OP4, 3), (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setRegPt1(YM_REG_CH(DR2_OP1, 3), channel.ops[0].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP2, 3), channel.ops[1].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP3, 3), channel.ops[2].decayRate2);
	setRegPt1(YM_REG_CH(DR2_OP4, 3), channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setRegPt1(YM_REG_CH(SL_RR_OP1, 3), (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP2, 3), (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP3, 3), (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setRegPt1(YM_REG_CH(SL_RR_OP4, 3), (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setRegPt1(YM_REG_CH(PROPR1, 3), 0x00);
	setRegPt1(YM_REG_CH(PROPR2, 3), 0x00);
	setRegPt1(YM_REG_CH(PROPR3, 3), 0x00);
	setRegPt1(YM_REG_CH(PROPR4, 3), 0x00);

	// Set frequency. Important: set MSB first
	setRegPt1(YM_REG_CH(FREQ_MSB, 3), ((channel.frequencyOctave << 3) | (channel.frequency >> 8)));
	setRegPt1(YM_REG_CH(FREQ_LSB, 3), (channel.frequency & 0xFF));
}

void initChannel4(Channel channel) {
	// Feedback & algorithm
	setRegPt2(YM_REG_CH(FB_ALG, 1), (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setRegPt2(YM_REG_CH(DET_MUL_OP1, 1), (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP2, 1), (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP3, 1), (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP4, 1), (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setRegPt2(YM_REG_CH(TL_OP1, 1), channel.ops[0].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP2, 1), channel.ops[1].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP3, 1), channel.ops[2].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP4, 1), channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setRegPt2(YM_REG_CH(RS_AR_OP1, 1), (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP2, 1), (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP3, 1), (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP4, 1), (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setRegPt2(YM_REG_CH(AM_DR_OP1, 1), (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP2, 1), (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP3, 1), (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP4, 1), (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setRegPt2(YM_REG_CH(DR2_OP1, 1), channel.ops[0].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP2, 1), channel.ops[1].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP3, 1), channel.ops[2].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP4, 1), channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setRegPt2(YM_REG_CH(SL_RR_OP1, 1), (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP2, 1), (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP3, 1), (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP4, 1), (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setRegPt2(YM_REG_CH(PROPR1, 1), 0x00);
	setRegPt2(YM_REG_CH(PROPR2, 1), 0x00);
	setRegPt2(YM_REG_CH(PROPR3, 1), 0x00);
	setRegPt2(YM_REG_CH(PROPR4, 1), 0x00);

	// Set frequency. Important: set MSB first
	setRegPt2(YM_REG_CH(FREQ_MSB, 1), ((channel.frequencyOctave << 3) | (channel.frequency >> 8)));
	setRegPt2(YM_REG_CH(FREQ_LSB, 1), (channel.frequency & 0xFF));
}

void initChannel5(Channel channel) {
	// Feedback & algorithm
	setRegPt2(YM_REG_CH(FB_ALG, 2), (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setRegPt2(YM_REG_CH(DET_MUL_OP1, 2), (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP2, 2), (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP3, 2), (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP4, 2), (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setRegPt2(YM_REG_CH(TL_OP1, 2), channel.ops[0].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP2, 2), channel.ops[1].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP3, 2), channel.ops[2].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP4, 2), channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setRegPt2(YM_REG_CH(RS_AR_OP1, 2), (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP2, 2), (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP3, 2), (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP4, 2), (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setRegPt2(YM_REG_CH(AM_DR_OP1, 2), (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP2, 2), (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP3, 2), (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP4, 2), (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setRegPt2(YM_REG_CH(DR2_OP1, 2), channel.ops[0].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP2, 2), channel.ops[1].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP3, 2), channel.ops[2].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP4, 2), channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setRegPt2(YM_REG_CH(SL_RR_OP1, 2), (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP2, 2), (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP3, 2), (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP4, 2), (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setRegPt2(YM_REG_CH(PROPR1, 2), 0x00);
	setRegPt2(YM_REG_CH(PROPR2, 2), 0x00);
	setRegPt2(YM_REG_CH(PROPR3, 2), 0x00);
	setRegPt2(YM_REG_CH(PROPR4, 2), 0x00);

	// Set frequency. Important: set MSB first
	setRegPt2(YM_REG_CH(FREQ_MSB, 2), ((channel.frequencyOctave << 3) | (channel.frequency >> 8)));
	setRegPt2(YM_REG_CH(FREQ_LSB, 2), (channel.frequency & 0xFF));
}

void initChannel6(Channel channel) {
	// Feedback & algorithm
	setRegPt2(YM_REG_CH(FB_ALG, 3), (channel.feedback << 3) | channel.algorithm);

	// Detune & multiply
	setRegPt2(YM_REG_CH(DET_MUL_OP1, 3), (channel.ops[0].detune << 4) | channel.ops[0].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP2, 3), (channel.ops[1].detune << 4) | channel.ops[1].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP3, 3), (channel.ops[2].detune << 4) | channel.ops[2].multiply);
	setRegPt2(YM_REG_CH(DET_MUL_OP4, 3), (channel.ops[3].detune << 4) | channel.ops[3].multiply);

	// Total level
	setRegPt2(YM_REG_CH(TL_OP1, 3), channel.ops[0].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP2, 3), channel.ops[1].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP3, 3), channel.ops[2].totalLevel);
	setRegPt2(YM_REG_CH(TL_OP4, 3), channel.ops[3].totalLevel);

	// Rate scaling & attack rate
	setRegPt2(YM_REG_CH(RS_AR_OP1, 3), (channel.ops[0].rateScaling << 6) | channel.ops[0].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP2, 3), (channel.ops[1].rateScaling << 6) | channel.ops[1].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP3, 3), (channel.ops[2].rateScaling << 6) | channel.ops[2].attackRate);
	setRegPt2(YM_REG_CH(RS_AR_OP4, 3), (channel.ops[3].rateScaling << 6) | channel.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setRegPt2(YM_REG_CH(AM_DR_OP1, 3), (channel.ops[0].amplitudeModulation << 7) | channel.ops[0].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP2, 3), (channel.ops[1].amplitudeModulation << 7) | channel.ops[1].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP3, 3), (channel.ops[2].amplitudeModulation << 7) | channel.ops[2].decayRate1);
	setRegPt2(YM_REG_CH(AM_DR_OP4, 3), (channel.ops[3].amplitudeModulation << 7) | channel.ops[3].decayRate1);

	// 2nd decay rate
	setRegPt2(YM_REG_CH(DR2_OP1, 3), channel.ops[0].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP2, 3), channel.ops[1].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP3, 3), channel.ops[2].decayRate2);
	setRegPt2(YM_REG_CH(DR2_OP4, 3), channel.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setRegPt2(YM_REG_CH(SL_RR_OP1, 3), (channel.ops[0].secondaryAmplitude << 4) | channel.ops[0].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP2, 3), (channel.ops[1].secondaryAmplitude << 4) | channel.ops[1].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP3, 3), (channel.ops[2].secondaryAmplitude << 4) | channel.ops[2].releaseRate);
	setRegPt2(YM_REG_CH(SL_RR_OP4, 3), (channel.ops[3].secondaryAmplitude << 4) | channel.ops[3].releaseRate);

	// Proprietary
	setRegPt2(YM_REG_CH(PROPR1, 3), 0x00);
	setRegPt2(YM_REG_CH(PROPR2, 3), 0x00);
	setRegPt2(YM_REG_CH(PROPR3, 3), 0x00);
	setRegPt2(YM_REG_CH(PROPR4, 3), 0x00);

	// Set frequency. Important: set MSB first
	setRegPt2(YM_REG_CH(FREQ_MSB, 3), ((channel.frequencyOctave << 3) | (channel.frequency >> 8)));
	setRegPt2(YM_REG_CH(FREQ_LSB, 3), (channel.frequency & 0xFF));
}
