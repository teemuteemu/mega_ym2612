#include <Arduino.h>
#include <stdint.h>

#include "ym2612.h"
#include "platform.h"
#include "sound.h"

#define NOTE_C3 (623)

YM2612 ym2612 = {
	.lfoEnabled = 0,
	.lfoFrequency = 0,
	.channels = {
		// channel 1:
		{
			.frequency = CH1_FREQ,
			.frequencyOctave = CH1_OCTAVE,
			.feedback = CH1_FEEDBACK,
			.algorithm = CH1_ALGORITHM,
			.ops = {
				{
					.totalLevel = CH1_OP1_TL,
					.detune = CH1_OP1_DETUNE,
					.multiply = CH1_OP1_MUL,
					.amplitudeModulation = CH1_OP1_AM,
					.rateScaling = CH1_OP1_RS,
					.attackRate = CH1_OP1_AR,
					.decayRate1 = CH1_OP1_DR1,
					.sustain = CH1_OP1_SUSTAIN,
					.decayRate2 = CH1_OP1_DR2,
					.releaseRate = CH1_OP1_RR,
				},
				{
					.totalLevel = CH1_OP2_TL,
					.detune = CH1_OP2_DETUNE,
					.multiply = CH1_OP2_MUL,
					.amplitudeModulation = CH1_OP2_AM,
					.rateScaling = CH1_OP2_RS,
					.attackRate = CH1_OP2_AR,
					.decayRate1 = CH1_OP2_DR1,
					.sustain = CH1_OP2_SUSTAIN,
					.decayRate2 = CH1_OP2_DR2,
					.releaseRate = CH1_OP2_RR,
				},
				{
					.totalLevel = CH1_OP3_TL,
					.detune = CH1_OP3_DETUNE,
					.multiply = CH1_OP3_MUL,
					.amplitudeModulation = CH1_OP3_AM,
					.rateScaling = CH1_OP3_RS,
					.attackRate = CH1_OP3_AR,
					.decayRate1 = CH1_OP3_DR1,
					.sustain = CH1_OP3_SUSTAIN,
					.decayRate2 = CH1_OP3_DR2,
					.releaseRate = CH1_OP3_RR,
				},
				{
					.totalLevel = CH1_OP4_TL,
					.detune = CH1_OP4_DETUNE,
					.multiply = CH1_OP4_MUL,
					.amplitudeModulation = CH1_OP4_AM,
					.rateScaling = CH1_OP4_RS,
					.attackRate = CH1_OP4_AR,
					.decayRate1 = CH1_OP4_DR1,
					.sustain = CH1_OP4_SUSTAIN,
					.decayRate2 = CH1_OP4_DR2,
					.releaseRate = CH1_OP4_RR,
				},
			},
		},
		// channel 2:
		{
			.frequency = CH2_FREQ,
			.frequencyOctave = CH2_OCTAVE,
			.feedback = CH2_FEEDBACK,
			.algorithm = CH2_ALGORITHM,
			.ops = {
				{
					.totalLevel = CH2_OP1_TL,
					.detune = CH2_OP1_DETUNE,
					.multiply = CH2_OP1_MUL,
					.amplitudeModulation = CH2_OP1_AM,
					.rateScaling = CH2_OP1_RS,
					.attackRate = CH2_OP1_AR,
					.decayRate1 = CH2_OP1_DR1,
					.sustain = CH2_OP1_SUSTAIN,
					.decayRate2 = CH2_OP1_DR2,
					.releaseRate = CH2_OP1_RR,
				},
				{
					.totalLevel = CH2_OP2_TL,
					.detune = CH2_OP2_DETUNE,
					.multiply = CH2_OP2_MUL,
					.amplitudeModulation = CH2_OP2_AM,
					.rateScaling = CH2_OP2_RS,
					.attackRate = CH2_OP2_AR,
					.decayRate1 = CH2_OP2_DR1,
					.sustain = CH2_OP2_SUSTAIN,
					.decayRate2 = CH2_OP2_DR2,
					.releaseRate = CH2_OP2_RR,
				},
				{
					.totalLevel = CH2_OP3_TL,
					.detune = CH2_OP3_DETUNE,
					.multiply = CH2_OP3_MUL,
					.amplitudeModulation = CH2_OP3_AM,
					.rateScaling = CH2_OP3_RS,
					.attackRate = CH2_OP3_AR,
					.decayRate1 = CH2_OP3_DR1,
					.sustain = CH2_OP3_SUSTAIN,
					.decayRate2 = CH2_OP3_DR2,
					.releaseRate = CH2_OP3_RR,
				},
				{
					.totalLevel = CH2_OP4_TL,
					.detune = CH2_OP4_DETUNE,
					.multiply = CH2_OP4_MUL,
					.amplitudeModulation = CH2_OP4_AM,
					.rateScaling = CH2_OP4_RS,
					.attackRate = CH2_OP4_AR,
					.decayRate1 = CH2_OP4_DR1,
					.sustain = CH2_OP4_SUSTAIN,
					.decayRate2 = CH2_OP4_DR2,
					.releaseRate = CH2_OP4_RR,
				},
			},
		},
		// channel 3:
		{
			.frequency = CH3_FREQ,
			.frequencyOctave = CH3_OCTAVE,
			.feedback = CH3_FEEDBACK,
			.algorithm = CH3_ALGORITHM,
			.ops = {
				{
					.totalLevel = CH3_OP1_TL,
					.detune = CH3_OP1_DETUNE,
					.multiply = CH3_OP1_MUL,
					.amplitudeModulation = CH3_OP1_AM,
					.rateScaling = CH3_OP1_RS,
					.attackRate = CH3_OP1_AR,
					.decayRate1 = CH3_OP1_DR1,
					.sustain = CH3_OP1_SUSTAIN,
					.decayRate2 = CH3_OP1_DR2,
					.releaseRate = CH3_OP1_RR,
				},
				{
					.totalLevel = CH3_OP2_TL,
					.detune = CH3_OP2_DETUNE,
					.multiply = CH3_OP2_MUL,
					.amplitudeModulation = CH3_OP2_AM,
					.rateScaling = CH3_OP2_RS,
					.attackRate = CH3_OP2_AR,
					.decayRate1 = CH3_OP2_DR1,
					.sustain = CH3_OP2_SUSTAIN,
					.decayRate2 = CH3_OP2_DR2,
					.releaseRate = CH3_OP2_RR,
				},
				{
					.totalLevel = CH3_OP3_TL,
					.detune = CH3_OP3_DETUNE,
					.multiply = CH3_OP3_MUL,
					.amplitudeModulation = CH3_OP3_AM,
					.rateScaling = CH3_OP3_RS,
					.attackRate = CH3_OP3_AR,
					.decayRate1 = CH3_OP3_DR1,
					.sustain = CH3_OP3_SUSTAIN,
					.decayRate2 = CH3_OP3_DR2,
					.releaseRate = CH3_OP3_RR,
				},
				{
					.totalLevel = CH3_OP4_TL,
					.detune = CH3_OP4_DETUNE,
					.multiply = CH3_OP4_MUL,
					.amplitudeModulation = CH3_OP4_AM,
					.rateScaling = CH3_OP4_RS,
					.attackRate = CH3_OP4_AR,
					.decayRate1 = CH3_OP4_DR1,
					.sustain = CH3_OP4_SUSTAIN,
					.decayRate2 = CH3_OP4_DR2,
					.releaseRate = CH3_OP4_RR,
				},
			},
		},
		// channel 4:
		{
			.frequency = CH4_FREQ,
			.frequencyOctave = CH4_OCTAVE,
			.feedback = CH4_FEEDBACK,
			.algorithm = CH4_ALGORITHM,
			.ops = {
				{
					.totalLevel = CH4_OP1_TL,
					.detune = CH4_OP1_DETUNE,
					.multiply = CH4_OP1_MUL,
					.amplitudeModulation = CH4_OP1_AM,
					.rateScaling = CH4_OP1_RS,
					.attackRate = CH4_OP1_AR,
					.decayRate1 = CH4_OP1_DR1,
					.sustain = CH4_OP1_SUSTAIN,
					.decayRate2 = CH4_OP1_DR2,
					.releaseRate = CH4_OP1_RR,
				},
				{
					.totalLevel = CH4_OP2_TL,
					.detune = CH4_OP2_DETUNE,
					.multiply = CH4_OP2_MUL,
					.amplitudeModulation = CH4_OP2_AM,
					.rateScaling = CH4_OP2_RS,
					.attackRate = CH4_OP2_AR,
					.decayRate1 = CH4_OP2_DR1,
					.sustain = CH4_OP2_SUSTAIN,
					.decayRate2 = CH4_OP2_DR2,
					.releaseRate = CH4_OP2_RR,
				},
				{
					.totalLevel = CH4_OP3_TL,
					.detune = CH4_OP3_DETUNE,
					.multiply = CH4_OP3_MUL,
					.amplitudeModulation = CH4_OP3_AM,
					.rateScaling = CH4_OP3_RS,
					.attackRate = CH4_OP3_AR,
					.decayRate1 = CH4_OP3_DR1,
					.sustain = CH4_OP3_SUSTAIN,
					.decayRate2 = CH4_OP3_DR2,
					.releaseRate = CH4_OP3_RR,
				},
				{
					.totalLevel = CH4_OP4_TL,
					.detune = CH4_OP4_DETUNE,
					.multiply = CH4_OP4_MUL,
					.amplitudeModulation = CH4_OP4_AM,
					.rateScaling = CH4_OP4_RS,
					.attackRate = CH4_OP4_AR,
					.decayRate1 = CH4_OP4_DR1,
					.sustain = CH4_OP4_SUSTAIN,
					.decayRate2 = CH4_OP4_DR2,
					.releaseRate = CH4_OP4_RR,
				},
			},
		},
		// channel 5:
		{
			.frequency = CH5_FREQ,
			.frequencyOctave = CH5_OCTAVE,
			.feedback = CH5_FEEDBACK,
			.algorithm = CH5_ALGORITHM,
			.ops = {
				{
					.totalLevel = CH5_OP1_TL,
					.detune = CH5_OP1_DETUNE,
					.multiply = CH5_OP1_MUL,
					.amplitudeModulation = CH5_OP1_AM,
					.rateScaling = CH5_OP1_RS,
					.attackRate = CH5_OP1_AR,
					.decayRate1 = CH5_OP1_DR1,
					.sustain = CH5_OP1_SUSTAIN,
					.decayRate2 = CH5_OP1_DR2,
					.releaseRate = CH5_OP1_RR,
				},
				{
					.totalLevel = CH5_OP2_TL,
					.detune = CH5_OP2_DETUNE,
					.multiply = CH5_OP2_MUL,
					.amplitudeModulation = CH5_OP2_AM,
					.rateScaling = CH5_OP2_RS,
					.attackRate = CH5_OP2_AR,
					.decayRate1 = CH5_OP2_DR1,
					.sustain = CH5_OP2_SUSTAIN,
					.decayRate2 = CH5_OP2_DR2,
					.releaseRate = CH5_OP2_RR,
				},
				{
					.totalLevel = CH5_OP3_TL,
					.detune = CH5_OP3_DETUNE,
					.multiply = CH5_OP3_MUL,
					.amplitudeModulation = CH5_OP3_AM,
					.rateScaling = CH5_OP3_RS,
					.attackRate = CH5_OP3_AR,
					.decayRate1 = CH5_OP3_DR1,
					.sustain = CH5_OP3_SUSTAIN,
					.decayRate2 = CH5_OP3_DR2,
					.releaseRate = CH5_OP3_RR,
				},
				{
					.totalLevel = CH5_OP4_TL,
					.detune = CH5_OP4_DETUNE,
					.multiply = CH5_OP4_MUL,
					.amplitudeModulation = CH5_OP4_AM,
					.rateScaling = CH5_OP4_RS,
					.attackRate = CH5_OP4_AR,
					.decayRate1 = CH5_OP4_DR1,
					.sustain = CH5_OP4_SUSTAIN,
					.decayRate2 = CH5_OP4_DR2,
					.releaseRate = CH5_OP4_RR,
				},
			},
		},
		// channel 6:
		{
			.frequency = CH6_FREQ,
			.frequencyOctave = CH6_OCTAVE,
			.feedback = CH6_FEEDBACK,
			.algorithm = CH6_ALGORITHM,
			.ops = {
				{
					.totalLevel = CH6_OP1_TL,
					.detune = CH6_OP1_DETUNE,
					.multiply = CH6_OP1_MUL,
					.amplitudeModulation = CH6_OP1_AM,
					.rateScaling = CH6_OP1_RS,
					.attackRate = CH6_OP1_AR,
					.decayRate1 = CH6_OP1_DR1,
					.sustain = CH6_OP1_SUSTAIN,
					.decayRate2 = CH6_OP1_DR2,
					.releaseRate = CH6_OP1_RR,
				},
				{
					.totalLevel = CH6_OP2_TL,
					.detune = CH6_OP2_DETUNE,
					.multiply = CH6_OP2_MUL,
					.amplitudeModulation = CH6_OP2_AM,
					.rateScaling = CH6_OP2_RS,
					.attackRate = CH6_OP2_AR,
					.decayRate1 = CH6_OP2_DR1,
					.sustain = CH6_OP2_SUSTAIN,
					.decayRate2 = CH6_OP2_DR2,
					.releaseRate = CH6_OP2_RR,
				},
				{
					.totalLevel = CH6_OP3_TL,
					.detune = CH6_OP3_DETUNE,
					.multiply = CH6_OP3_MUL,
					.amplitudeModulation = CH6_OP3_AM,
					.rateScaling = CH6_OP3_RS,
					.attackRate = CH6_OP3_AR,
					.decayRate1 = CH6_OP3_DR1,
					.sustain = CH6_OP3_SUSTAIN,
					.decayRate2 = CH6_OP3_DR2,
					.releaseRate = CH6_OP3_RR,
				},
				{
					.totalLevel = CH6_OP4_TL,
					.detune = CH6_OP4_DETUNE,
					.multiply = CH6_OP4_MUL,
					.amplitudeModulation = CH6_OP4_AM,
					.rateScaling = CH6_OP4_RS,
					.attackRate = CH6_OP4_AR,
					.decayRate1 = CH6_OP4_DR1,
					.sustain = CH6_OP4_SUSTAIN,
					.decayRate2 = CH6_OP4_DR2,
					.releaseRate = CH6_OP4_RR,
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
		//setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_ON);
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

		_delay_ms(3000);
		setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH2_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH3_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH4_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH5_KEY_OFF);
		setRegPt1(YM_REG_KEY_ON_OFF, CH6_KEY_OFF);
	}
}

