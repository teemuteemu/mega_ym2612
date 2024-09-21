#include <Arduino.h>
#include <stdint.h>

#include "ym2612.h"
#include "platform.h"

YM2612 ym2612 = {
	.lfoEnabled = 0,
	.lfoFrequency = 0,
	.channels = {
		// channel 1:
		{
			.frequency = 546, // => LSB = 546 & 0xFF = 0x22, MSB = 546 >> 8 = 0x02
			.frequencyOctave = 1,
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
		// channel 2:
		{
			.frequency = 546,
			.frequencyOctave = 2,
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
		// channel 3:
		{
			.frequency = 546,
			.frequencyOctave = 3,
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
		// channel 4:
		{
			.frequency = 546,
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
		// channel 5:
		{
			.frequency = 546,
			.frequencyOctave = 5,
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
		// channel 6:
		{
			.frequency = 546,
			.frequencyOctave = 6,
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
	// LFO
	setRegPt1(YM_REG_LFO, (ym2612.lfoEnabled << 3) | ym2612.lfoFrequency);

	// DAC off
	setRegPt1(YM_REG_DAC, 0x00);

	// Software timers
	setRegPt1(YM_REG_TIMERS, 0x00);

	// All channels off
	setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_OFF);
	setRegPt1(YM_REG_KEY_ON_OFF, CH2_KEY_OFF);
	setRegPt1(YM_REG_KEY_ON_OFF, CH3_KEY_OFF);
	setRegPt1(YM_REG_KEY_ON_OFF, CH4_KEY_OFF);
	setRegPt1(YM_REG_KEY_ON_OFF, CH5_KEY_OFF);
	setRegPt1(YM_REG_KEY_ON_OFF, CH6_KEY_OFF);

	initChannel1(ym2612.channels[0]);
	initChannel2(ym2612.channels[1]);
	initChannel3(ym2612.channels[2]);
	initChannel4(ym2612.channels[3]);
	initChannel5(ym2612.channels[4]);
	initChannel6(ym2612.channels[5]);

	// Both speakers on
	setRegPt1(0xB4, 0xC0);

	while (true) {
		// cycle tone on/off
		_delay_ms(200);
		setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_ON);
		_delay_ms(200);
		setRegPt1(YM_REG_KEY_ON_OFF, CH2_KEY_ON);
		_delay_ms(200);
		setRegPt1(YM_REG_KEY_ON_OFF, CH3_KEY_ON);
		_delay_ms(200);
		setRegPt1(YM_REG_KEY_ON_OFF, CH4_KEY_ON);
		_delay_ms(200);
		setRegPt1(YM_REG_KEY_ON_OFF, CH5_KEY_ON);
		_delay_ms(200);
		setRegPt1(YM_REG_KEY_ON_OFF, CH6_KEY_ON);

		_delay_ms(1000);
		setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH2_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH3_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH4_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH5_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH6_KEY_OFF);
	}
}

