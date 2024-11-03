#include <Arduino.h>
#include <MIDI.h>
#include <stdint.h>

#include "ym2612.h"
#include "platform.h"
#include "sound.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);

uint8_t updateCounter = 0;
uint8_t tmpTLCH1 = 0;
uint8_t tmpTLCH2 = 0;
uint8_t tmpTLCH3 = 0;
uint8_t tmpTLCH4 = 0;
uint8_t tmpTLCH5 = 0;
uint8_t tmpTLCH6 = 0;
uint8_t tmpDecayCH1 = 0;
uint8_t tmpDecayCH2 = 0;
uint8_t tmpDecayCH3 = 0;
uint8_t tmpDecayCH4 = 0;
uint8_t tmpDecayCH5 = 0;
uint8_t tmpDecayCH6 = 0;
uint16_t tmpPitchCH1 = 0;
uint16_t tmpPitchCH2 = 0;
uint16_t tmpPitchCH3 = 0;
uint16_t tmpPitchCH4 = 0;

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

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity) {
	switch (inNote) {
		case 60:
			setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_ON);
			break;
		case 61:
			setRegPt1(YM_REG_KEY_ON_OFF, CH2_KEY_ON);
			break;
		case 62:
			setRegPt1(YM_REG_KEY_ON_OFF, CH3_KEY_ON);
			break;
		case 63:
			setRegPt1(YM_REG_KEY_ON_OFF, CH4_KEY_ON);
			break;
		case 64:
			setRegPt1(YM_REG_KEY_ON_OFF, CH5_KEY_ON);
			break;
		case 65:
			setRegPt1(YM_REG_KEY_ON_OFF, CH6_KEY_ON);
			break;
	}
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity) {
	switch (inNote) {
		case 60:
			setRegPt1(YM_REG_KEY_ON_OFF, CH1_KEY_OFF);
			break;
		case 61:
			setRegPt1(YM_REG_KEY_ON_OFF, CH2_KEY_OFF);
			break;
		case 62:
			setRegPt1(YM_REG_KEY_ON_OFF, CH3_KEY_OFF);
			break;
		case 63:
			setRegPt1(YM_REG_KEY_ON_OFF, CH4_KEY_OFF);
			break;
		case 64:
			setRegPt1(YM_REG_KEY_ON_OFF, CH5_KEY_OFF);
			break;
		case 65:
			setRegPt1(YM_REG_KEY_ON_OFF, CH6_KEY_OFF);
			break;
	}
}

void setup() {
	Serial.begin(9600);
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

	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);
	MIDI.begin(10);
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
		Serial.println(updateCounter);
		if (++updateCounter >= 100) {
			Serial.println("update");

			tmpPitchCH1 = map(analogRead(A0), 0, 1023, 200, 1024);
			tmpDecayCH1 = map(analogRead(A1), 0, 1023, 20, 0);
			tmpTLCH1 = map(analogRead(A2), 0, 1023, 32, 0);
			tmpPitchCH2 = map(analogRead(A3), 0, 1023, 100, 2047);
			tmpDecayCH2 = map(analogRead(A4), 0, 1023, 20, 0);
			tmpTLCH2 = map(analogRead(A5), 0, 1023, 64, 0);
			tmpPitchCH3 = map(analogRead(A6), 0, 1023, 100, 2047);
			tmpDecayCH3 = map(analogRead(A7), 0, 1023, 15, 0);
			tmpTLCH3 = map(analogRead(A8), 0, 1023, 64, 0);
			tmpPitchCH4 = map(analogRead(A9), 0, 1023, 100, 2047);
			tmpDecayCH4 = map(analogRead(A10), 0, 1023, 20, 8);
			tmpTLCH4 = map(analogRead(A11), 0, 1023, 32, 0);
			tmpDecayCH5 = map(analogRead(A12), 0, 1023, 31, 8);
			tmpTLCH5 = map(analogRead(A13), 0, 1023, 64, 0);
			tmpDecayCH6 = map(analogRead(A14), 0, 1023, 31, 8);
			tmpTLCH6 = map(analogRead(A15), 0, 1023, 32, 0);

			// Total levels
			if (ym2612.channels[0].ops[3].totalLevel != tmpTLCH1) {
				// Serial.println("update tl 1");
				ym2612.channels[0].ops[3].totalLevel = tmpTLCH1;
				setRegPt1(YM_REG_CH(TL_OP4, 1), ym2612.channels[0].ops[3].totalLevel);
			}
			if (ym2612.channels[1].ops[3].totalLevel != tmpTLCH2) {
				// Serial.println("update tl 2");
				ym2612.channels[1].ops[3].totalLevel = tmpTLCH2;
				setRegPt1(YM_REG_CH(TL_OP4, 2), ym2612.channels[1].ops[3].totalLevel);
			}
			if (ym2612.channels[2].ops[3].totalLevel != tmpTLCH3) {
				// Serial.println("update tl 3");
				ym2612.channels[2].ops[3].totalLevel = tmpTLCH3;
				setRegPt1(YM_REG_CH(TL_OP4, 3), ym2612.channels[2].ops[3].totalLevel);
			}
			if (ym2612.channels[3].ops[3].totalLevel != tmpTLCH4) {
				// Serial.println("update tl 4");
				ym2612.channels[3].ops[3].totalLevel = tmpTLCH4;
				setRegPt2(YM_REG_CH(TL_OP4, 1), ym2612.channels[3].ops[3].totalLevel);
			}
			if (ym2612.channels[4].ops[3].totalLevel != tmpTLCH5) {
				// Serial.println("update tl 5");
				ym2612.channels[4].ops[3].totalLevel = tmpTLCH5;
				setRegPt2(YM_REG_CH(TL_OP4, 2), ym2612.channels[4].ops[3].totalLevel);
			}
			if (ym2612.channels[5].ops[3].totalLevel != tmpTLCH6) {
				// Serial.println("update tl 6");
				ym2612.channels[5].ops[3].totalLevel = tmpTLCH6;
				setRegPt2(YM_REG_CH(TL_OP4, 3), ym2612.channels[5].ops[3].totalLevel);
			}

			// Decays
			if (ym2612.channels[0].ops[3].decayRate1 != tmpDecayCH1) {
				// Serial.println("update dc 1");
				ym2612.channels[0].ops[3].decayRate1 = tmpDecayCH1;
				setRegPt1(YM_REG_CH(AM_DR_OP4, 1), (ym2612.channels[0].ops[3].amplitudeModulation << 7) | ym2612.channels[0].ops[3].decayRate1);
			}
			if (ym2612.channels[1].ops[3].decayRate1 != tmpDecayCH2) {
				// Serial.println("update dc 2");
				ym2612.channels[1].ops[3].decayRate1 = tmpDecayCH2;
				setRegPt1(YM_REG_CH(AM_DR_OP4, 2), (ym2612.channels[1].ops[3].amplitudeModulation << 7) | ym2612.channels[1].ops[3].decayRate1);
			}
			if (ym2612.channels[2].ops[3].releaseRate != tmpDecayCH3) {
				// Serial.println("update dc 3");
				ym2612.channels[2].ops[3].releaseRate = tmpDecayCH3;
				setRegPt1(YM_REG_CH(SL_RR_OP4, 3), (ym2612.channels[2].ops[3].sustain << 4) | ym2612.channels[2].ops[3].releaseRate);
			}
			if (ym2612.channels[3].ops[3].decayRate1 != tmpDecayCH4) {
				// Serial.println("update dc 4");
				ym2612.channels[3].ops[3].decayRate1 = tmpDecayCH4;
				setRegPt2(YM_REG_CH(AM_DR_OP4, 1), (ym2612.channels[3].ops[3].amplitudeModulation << 7) | ym2612.channels[3].ops[3].decayRate1);
			}
			if (ym2612.channels[4].ops[3].decayRate1 != tmpDecayCH5) {
				// Serial.println("update dc 5");
				ym2612.channels[4].ops[3].decayRate1 = tmpDecayCH5;
				setRegPt2(YM_REG_CH(AM_DR_OP4, 2), (ym2612.channels[4].ops[3].amplitudeModulation << 7) | ym2612.channels[4].ops[3].decayRate1);
			}
			if (ym2612.channels[5].ops[3].decayRate1 != tmpDecayCH6) {
				// Serial.println("update dc 6");
				ym2612.channels[5].ops[3].decayRate1 = tmpDecayCH6;
				setRegPt2(YM_REG_CH(AM_DR_OP4, 3), (ym2612.channels[5].ops[3].amplitudeModulation << 7) | ym2612.channels[5].ops[3].decayRate1);
			}

			// Pitch
			if (ym2612.channels[0].frequency != tmpPitchCH1) {
				// Serial.println("update p 1");
				ym2612.channels[0].frequency = tmpPitchCH1;
				setRegPt1(YM_REG_CH(FREQ_MSB, 1), ((ym2612.channels[0].frequencyOctave << 3) | (ym2612.channels[0].frequency >> 8)));
				setRegPt1(YM_REG_CH(FREQ_LSB, 1), (ym2612.channels[0].frequency & 0xFF));
			}
			if (ym2612.channels[1].frequency != tmpPitchCH2) {
				// Serial.println("update p 2");
				ym2612.channels[1].frequency = tmpPitchCH2;
				setRegPt1(YM_REG_CH(FREQ_MSB, 2), ((ym2612.channels[1].frequencyOctave << 3) | (ym2612.channels[1].frequency >> 8)));
				setRegPt1(YM_REG_CH(FREQ_LSB, 2), (ym2612.channels[1].frequency & 0xFF));
			}
			if (ym2612.channels[2].frequency != tmpPitchCH3) {
				// Serial.println("update p 3");
				ym2612.channels[2].frequency = tmpPitchCH3;
				setRegPt1(YM_REG_CH(FREQ_MSB, 3), ((ym2612.channels[2].frequencyOctave << 3) | (ym2612.channels[2].frequency >> 8)));
				setRegPt1(YM_REG_CH(FREQ_LSB, 3), (ym2612.channels[2].frequency & 0xFF));
			}
			if (ym2612.channels[3].frequency != tmpPitchCH4) {
				// Serial.println("update p 4");
				ym2612.channels[3].frequency = tmpPitchCH4;
				setRegPt2(YM_REG_CH(FREQ_MSB, 1), ((ym2612.channels[3].frequencyOctave << 3) | (ym2612.channels[3].frequency >> 8)));
				setRegPt2(YM_REG_CH(FREQ_LSB, 1), (ym2612.channels[3].frequency & 0xFF));
			}

			updateCounter = 0;
		}

		MIDI.read();
	}
}

