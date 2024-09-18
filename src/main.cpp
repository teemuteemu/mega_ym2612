#include <Arduino.h>
#include <stdint.h>

#include "ym2612.h"
#include "platform.h"

YM2612 ym2612 = {
	.lfoEnabled = 0,
	.lfoFrequency = 0,
	.channels = {
		{
			.frequencyLSB = 34,
			.frequencyMSB = 2,
			.frequencyOctave = 4,
			.feedback = 6,
			.algorithm = 2,
			.ops = {
				{
					.totalLevel = 35,
					.detune = 7,
					.multiply = 1,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 1,
					.rateScaling = 2,
					.attackRate = 31,
					.decayRate1 = 5,
					.decayRate2 = 2,
					.releaseRate = 1,
				},
				{
					.totalLevel = 45,
					.detune = 0,
					.multiply = 13,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 1,
					.rateScaling = 2,
					.attackRate = 25,
					.decayRate1 = 5,
					.decayRate2 = 2,
					.releaseRate = 1,
				},
				{
					.totalLevel = 38,
					.detune = 3,
					.multiply = 3,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 1,
					.rateScaling = 1,
					.attackRate = 31,
					.decayRate1 = 5,
					.decayRate2 = 2,
					.releaseRate = 1,
				},
				{
					.totalLevel = 0,
					.detune = 0,
					.multiply = 1,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 10,
					.rateScaling = 2,
					.attackRate = 20,
					.decayRate1 = 7,
					.decayRate2 = 2,
					.releaseRate = 6,
				},
			},
		},
		{
			.frequencyLSB = 34,
			.frequencyMSB = 2,
			.frequencyOctave = 4,
			.feedback = 1,
			.algorithm = 2,
			.ops = {
				{
					.totalLevel = 38,
					.detune = 2,
					.multiply = 1,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 0,
					.rateScaling = 0,
					.attackRate = 31,
					.decayRate1 = 31,
					.decayRate2 = 24,
					.releaseRate = 13,
				},
				{
					.totalLevel = 36,
					.detune = 0,
					.multiply = 2,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 15,
					.rateScaling = 0,
					.attackRate = 27,
					.decayRate1 = 26,
					.decayRate2 = 13,
					.releaseRate = 15,
				},
				{
					.totalLevel = 67,
					.detune = 1,
					.multiply = 1,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 15,
					.rateScaling = 0,
					.attackRate = 31,
					.decayRate1 = 23,
					.decayRate2 = 21,
					.releaseRate = 12,
				},
				{
					.totalLevel = 0,
					.detune = 0,
					.multiply = 0,
					.amplitudeModulation = 0,
					.secondaryAmplitude = 15,
					.rateScaling = 0,
					.attackRate = 31,
					.decayRate1 = 16,
					.decayRate2 = 0,
					.releaseRate = 15,
				},
			},
		},
	},
};

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	/* === Pins setup === */
	YM_MCLOCK_DDR |= _BV(YM_MCLOCK);

	YM_CTRL_DDR |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD) | _BV(YM_A0) | _BV(YM_A1); // sets as write pins
	YM_CTRL_PORT |= _BV(YM_IC) | _BV(YM_CS) | _BV(YM_WR) | _BV(YM_RD); // IC, CS, WR and RD HIGH by default
	YM_CTRL_PORT &= ~(_BV(YM_A0) | _BV(YM_A1)); // A0 and A1 LOW by default
	
	YM_DATA_DDR = 0xFF; // set all 8 pins on this port to write

	/* === F_CPU / 2 clock generation === */
	// See ATmega datasheet for register definitions
	TCCR1A = _BV(COM1A0);            // Toggle OC1A on compare match
	TCCR1B = _BV(WGM12) | _BV(CS10); // CTC mode with prescaler /1 
	TCCR1C = 0;                      // Flag reset 
	TCNT1 = 0;                       // Counter reset 
	OCR1A = 0;                       // Divide base clock by two

	/* === Reset YM2612 === */
	YM_CTRL_PORT &= ~_BV(YM_IC);
	_delay_ms(10);
	YM_CTRL_PORT |= _BV(YM_IC);
	_delay_ms(10);
}


void loop() {
	/* === YM2612 Test code === */ 
	// LFO
	setreg(YM_REG_LFO, (ym2612.lfoEnabled << 3) | ym2612.lfoFrequency);

	// DAC off
	setreg(YM_REG_DAC, 0x00);

	setreg(YM_REG_TIMERS, 0x00); // Software timers
	setreg(YM_REG_KEY_ON_OFF, 0x00); // Note off (channel 0)
	setreg(YM_REG_KEY_ON_OFF, 0x01); // Note off (channel 1)
	setreg(YM_REG_KEY_ON_OFF, 0x02); // Note off (channel 2)
	setreg(YM_REG_KEY_ON_OFF, 0x04); // Note off (channel 3)
	setreg(YM_REG_KEY_ON_OFF, 0x05); // Note off (channel 4)
	setreg(YM_REG_KEY_ON_OFF, 0x06); // Note off (channel 5)

	// Feedback & algorithm
	setreg(YM_REG_CH1_FB_ALG, (ym2612.channels[0].feedback << 3) | ym2612.channels[0].algorithm);

	// Detune & multiply
	setreg(YM_REG_CH1_OP1_DET_MUL, (ym2612.channels[0].ops[0].detune << 4) | ym2612.channels[0].ops[0].multiply);
	setreg(YM_REG_CH1_OP2_DET_MUL, (ym2612.channels[0].ops[1].detune << 4) | ym2612.channels[0].ops[1].multiply);
	setreg(YM_REG_CH1_OP3_DET_MUL, (ym2612.channels[0].ops[2].detune << 4) | ym2612.channels[0].ops[2].multiply);
	setreg(YM_REG_CH1_OP4_DET_MUL, (ym2612.channels[0].ops[3].detune << 4) | ym2612.channels[0].ops[3].multiply);

	// Total level
	setreg(YM_REG_CH1_OP1_TL, ym2612.channels[0].ops[0].totalLevel);
	setreg(YM_REG_CH1_OP2_TL, ym2612.channels[0].ops[1].totalLevel);
	setreg(YM_REG_CH1_OP3_TL, ym2612.channels[0].ops[2].totalLevel);
	setreg(YM_REG_CH1_OP4_TL, ym2612.channels[0].ops[3].totalLevel);

	// Rate scaling & attack rate
	setreg(YM_REG_CH1_OP1_RS_AR, (ym2612.channels[0].ops[0].rateScaling << 6) | ym2612.channels[0].ops[0].attackRate);
	setreg(YM_REG_CH1_OP2_RS_AR, (ym2612.channels[0].ops[1].rateScaling << 6) | ym2612.channels[0].ops[1].attackRate);
	setreg(YM_REG_CH1_OP3_RS_AR, (ym2612.channels[0].ops[2].rateScaling << 6) | ym2612.channels[0].ops[2].attackRate);
	setreg(YM_REG_CH1_OP4_RS_AR, (ym2612.channels[0].ops[3].rateScaling << 6) | ym2612.channels[0].ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setreg(YM_REG_CH1_OP1_AM_DR, (ym2612.channels[0].ops[0].amplitudeModulation << 7) | ym2612.channels[0].ops[0].decayRate1);
	setreg(YM_REG_CH1_OP2_AM_DR, (ym2612.channels[0].ops[1].amplitudeModulation << 7) | ym2612.channels[0].ops[1].decayRate1);
	setreg(YM_REG_CH1_OP3_AM_DR, (ym2612.channels[0].ops[2].amplitudeModulation << 7) | ym2612.channels[0].ops[2].decayRate1);
	setreg(YM_REG_CH1_OP4_AM_DR, (ym2612.channels[0].ops[3].amplitudeModulation << 7) | ym2612.channels[0].ops[3].decayRate1);

	// 2nd decay rate
	setreg(YM_REG_CH1_OP1_DR2, ym2612.channels[0].ops[0].decayRate2);
	setreg(YM_REG_CH1_OP2_DR2, ym2612.channels[0].ops[1].decayRate2);
	setreg(YM_REG_CH1_OP3_DR2, ym2612.channels[0].ops[2].decayRate2);
	setreg(YM_REG_CH1_OP4_DR2, ym2612.channels[0].ops[3].decayRate2);

	// Secondary amplitude & release rate
	setreg(YM_REG_CH1_OP1_SL_RR, (ym2612.channels[0].ops[0].secondaryAmplitude << 4) | ym2612.channels[0].ops[0].releaseRate);
	setreg(YM_REG_CH1_OP2_SL_RR, (ym2612.channels[0].ops[1].secondaryAmplitude << 4) | ym2612.channels[0].ops[1].releaseRate);
	setreg(YM_REG_CH1_OP3_SL_RR, (ym2612.channels[0].ops[2].secondaryAmplitude << 4) | ym2612.channels[0].ops[2].releaseRate);
	setreg(YM_REG_CH1_OP4_SL_RR, (ym2612.channels[0].ops[3].secondaryAmplitude << 4) | ym2612.channels[0].ops[3].releaseRate);

	// Proprietary
	setreg(YM_REG_CH1_PROPR1, 0x00);
	setreg(YM_REG_CH1_PROPR2, 0x00);
	setreg(YM_REG_CH1_PROPR3, 0x00);
	setreg(YM_REG_CH1_PROPR4, 0x00);

	// Set frequency
	setreg(YM_REG_CH1_FREQ_MSB, (ym2612.channels[0].frequencyOctave << 3) | ym2612.channels[0].frequencyMSB);
	setreg(YM_REG_CH1_FREQ_LSB, ym2612.channels[0].frequencyLSB);

	// Feedback & algorithm
	setreg(YM_REG_CH2_FB_ALG, (ym2612.channels[1].feedback << 3) | ym2612.channels[1].algorithm);

	// Detune & multiply
	setreg(YM_REG_CH2_OP1_DET_MUL, (ym2612.channels[1].ops[0].detune << 4) | ym2612.channels[1].ops[0].multiply);
	setreg(YM_REG_CH2_OP2_DET_MUL, (ym2612.channels[1].ops[1].detune << 4) | ym2612.channels[1].ops[1].multiply);
	setreg(YM_REG_CH2_OP3_DET_MUL, (ym2612.channels[1].ops[2].detune << 4) | ym2612.channels[1].ops[2].multiply);
	setreg(YM_REG_CH2_OP4_DET_MUL, (ym2612.channels[1].ops[3].detune << 4) | ym2612.channels[1].ops[3].multiply);

	// Total level
	setreg(YM_REG_CH2_OP1_TL, ym2612.channels[1].ops[0].totalLevel);
	setreg(YM_REG_CH2_OP2_TL, ym2612.channels[1].ops[1].totalLevel);
	setreg(YM_REG_CH2_OP3_TL, ym2612.channels[1].ops[2].totalLevel);
	setreg(YM_REG_CH2_OP4_TL, ym2612.channels[1].ops[3].totalLevel);

	// Rate scaling & attack rate
	setreg(YM_REG_CH2_OP1_RS_AR, (ym2612.channels[1].ops[0].rateScaling << 6) | ym2612.channels[1].ops[0].attackRate);
	setreg(YM_REG_CH2_OP2_RS_AR, (ym2612.channels[1].ops[1].rateScaling << 6) | ym2612.channels[1].ops[1].attackRate);
	setreg(YM_REG_CH2_OP3_RS_AR, (ym2612.channels[1].ops[2].rateScaling << 6) | ym2612.channels[1].ops[2].attackRate);
	setreg(YM_REG_CH2_OP4_RS_AR, (ym2612.channels[1].ops[3].rateScaling << 6) | ym2612.channels[1].ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setreg(YM_REG_CH2_OP1_AM_DR, (ym2612.channels[1].ops[0].amplitudeModulation << 7) | ym2612.channels[1].ops[0].decayRate1);
	setreg(YM_REG_CH2_OP2_AM_DR, (ym2612.channels[1].ops[1].amplitudeModulation << 7) | ym2612.channels[1].ops[1].decayRate1);
	setreg(YM_REG_CH2_OP3_AM_DR, (ym2612.channels[1].ops[2].amplitudeModulation << 7) | ym2612.channels[1].ops[2].decayRate1);
	setreg(YM_REG_CH2_OP4_AM_DR, (ym2612.channels[1].ops[3].amplitudeModulation << 7) | ym2612.channels[1].ops[3].decayRate1);

	// 2nd decay rate
	setreg(YM_REG_CH2_OP1_DR2, ym2612.channels[1].ops[0].decayRate2);
	setreg(YM_REG_CH2_OP2_DR2, ym2612.channels[1].ops[1].decayRate2);
	setreg(YM_REG_CH2_OP3_DR2, ym2612.channels[1].ops[2].decayRate2);
	setreg(YM_REG_CH2_OP4_DR2, ym2612.channels[1].ops[3].decayRate2);

	// Secondary amplitude & release rate
	setreg(YM_REG_CH2_OP1_SL_RR, (ym2612.channels[1].ops[0].secondaryAmplitude << 4) | ym2612.channels[1].ops[0].releaseRate);
	setreg(YM_REG_CH2_OP2_SL_RR, (ym2612.channels[1].ops[1].secondaryAmplitude << 4) | ym2612.channels[1].ops[1].releaseRate);
	setreg(YM_REG_CH2_OP3_SL_RR, (ym2612.channels[1].ops[2].secondaryAmplitude << 4) | ym2612.channels[1].ops[2].releaseRate);
	setreg(YM_REG_CH2_OP4_SL_RR, (ym2612.channels[1].ops[3].secondaryAmplitude << 4) | ym2612.channels[1].ops[3].releaseRate);

	// Proprietary
	setreg(YM_REG_CH2_PROPR1, 0x00);
	setreg(YM_REG_CH2_PROPR2, 0x00);
	setreg(YM_REG_CH2_PROPR3, 0x00);
	setreg(YM_REG_CH2_PROPR4, 0x00);

	// Set frequency
	setreg(YM_REG_CH2_FREQ_MSB, (ym2612.channels[1].frequencyOctave << 3) | ym2612.channels[1].frequencyMSB);
	setreg(YM_REG_CH2_FREQ_LSB, ym2612.channels[1].frequencyLSB);

	// Both speakers on
	setreg(0xB4, 0xC0);

	// Key off
	setreg(YM_REG_KEY_ON_OFF, 0x00);
	setreg(YM_REG_KEY_ON_OFF, 0x01);

	while (true) {
		// cycle tone on/off
		_delay_ms(200);
		setreg(YM_REG_KEY_ON_OFF, 0xF1); // Key on
		_delay_ms(200);
		setreg(YM_REG_KEY_ON_OFF, 0xF0); // Key on
		_delay_ms(1000);
		setreg(YM_REG_KEY_ON_OFF, 0x01); // Key off
		setreg(YM_REG_KEY_ON_OFF, 0x00); // Key off
	}
}

