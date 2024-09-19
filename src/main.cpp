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
	setReg(YM_REG_LFO, (ym2612.lfoEnabled << 3) | ym2612.lfoFrequency);

	// DAC off
	setReg(YM_REG_DAC, 0x00);

	setReg(YM_REG_TIMERS, 0x00); // Software timers
	setReg(YM_REG_KEY_ON_OFF, 0x00); // Note off (channel 0)
	setReg(YM_REG_KEY_ON_OFF, 0x01); // Note off (channel 1)
	setReg(YM_REG_KEY_ON_OFF, 0x02); // Note off (channel 2)
	setReg(YM_REG_KEY_ON_OFF, 0x04); // Note off (channel 3)
	setReg(YM_REG_KEY_ON_OFF, 0x05); // Note off (channel 4)
	setReg(YM_REG_KEY_ON_OFF, 0x06); // Note off (channel 5)

	initChannel(ym2612.channels[0]);

	// Both speakers on
	setReg(0xB4, 0xC0);

	// Key off
	setReg(YM_REG_KEY_ON_OFF, 0x00);
	setReg(YM_REG_KEY_ON_OFF, 0x01);

	while (true) {
		// cycle tone on/off
		_delay_ms(200);
		setReg(YM_REG_KEY_ON_OFF, 0xF1); // Key on
		_delay_ms(200);
		setReg(YM_REG_KEY_ON_OFF, 0xF0); // Key on
		_delay_ms(1000);
		setReg(YM_REG_KEY_ON_OFF, 0x01); // Key off
		setReg(YM_REG_KEY_ON_OFF, 0x00); // Key off
	}
}

