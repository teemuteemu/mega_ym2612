#include <Arduino.h>

 // YM2612 Clock Pin (ATmega Port L)
#define YM_MCLOCK_DDR DDRB
#define YM_MCLOCK (5) // PB5 = OC1A (= pin 11 for Arduino Mega)

// YM2612 Control Pins (ATmega Port A) 
#define YM_CTRL_DDR DDRC
#define YM_CTRL_PORT PORTC
#define YM_A1 (0) // PC0 pin 37 for Arduino Mega
#define YM_A0 (1) // PC1 pin 36 for Arduino Mega
#define YM_RD (2) // PC2 pin 35 for Arduino Mega
#define YM_WR (3) // PC3 pin 34 for Arduino Mega
#define YM_CS (4) // PC4 pin 33 for Arduino Mega
#define YM_IC (5) // PC5 pin 32 for Arduino Mega

// YM2612 Data Pins (ATmega Port C)
#define YM_DATA_DDR DDRA
#define YM_DATA_PORT PORTA
#define YM_DATA_0 (0) // PA0 pin 22 for Arduino Mega
#define YM_DATA_1 (1) // PA1 pin 23 for Arduino Mega
#define YM_DATA_2 (2) // PA2 pin 24 for Arduino Mega
#define YM_DATA_3 (3) // PA3 pin 25 for Arduino Mega
#define YM_DATA_4 (4) // PA4 pin 26 for Arduino Mega
#define YM_DATA_5 (5) // PA5 pin 27 for Arduino Mega
#define YM_DATA_6 (6) // PA6 pin 28 for Arduino Mega
#define YM_DATA_7 (7) // PA7 pin 29 for Arduino Mega

typedef struct {
	uint8_t totalLevel;          // 7bit 0-127
	uint8_t detune;              // 3bit 0-7
	uint8_t multiply;            // 4bit 0-15
	uint8_t amplitudeModulation; // 1bit 0-1
	uint8_t secondaryAmplitude;  // 4bit 0-15
	uint8_t rateScaling;         // 2bit 0-3
	uint8_t attackRate;          // 5bit 0-31
	uint8_t decayRate1;          // 5bit 0-31
	uint8_t decayRate2;          // 5bit 0-31
	uint8_t releaseRate;         // 4bit 0-15
} Op;

typedef struct {
	uint8_t frequencyLSB;        // 8bit 0-255
	uint8_t frequencyMSB;        // 3bit 0-7
	uint8_t frequencyOctave;     // 3bit 0-7
	uint8_t feedback;            // 3bit 0-7
	uint8_t algorithm;           // 3bit 0-7
	uint8_t lfoEnabled;          // 1bit 0-1
	uint8_t lfoFrequency;        // 3bit 0-7
	Op ops[4];
} Channel;

Channel channel1 = {
	.frequencyLSB = 105,
	.frequencyMSB = 2,
	.frequencyOctave = 4,
	.feedback = 6,
	.algorithm = 2,
	.lfoEnabled = 0,
	.lfoFrequency = 0,
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
	}
};

static void write_ym(uint8_t data) {
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


static void setreg(uint8_t reg, uint8_t data) {
	// specify registers (timers + channels 1-3) to write
	YM_CTRL_PORT &= ~_BV(YM_A0); // A0 LOW (select register)
	write_ym(reg);
	// write the data to those registers
	YM_CTRL_PORT |= _BV(YM_A0);  // A0 HIGH (write register)
	write_ym(data);
}

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
	setreg(0x22, (channel1.lfoEnabled << 3) | channel1.lfoFrequency);

	setreg(0x27, 0x00); // Note off (channel 0)
	setreg(0x28, 0x01); // Note off (channel 1)
	setreg(0x28, 0x02); // Note off (channel 2)
	setreg(0x28, 0x04); // Note off (channel 3)
	setreg(0x28, 0x05); // Note off (channel 4)
	setreg(0x28, 0x06); // Note off (channel 5)

	// DAC off
	setreg(0x2B, 0x00);

	// Feedback & algorithm
	setreg(0xB0, (channel1.feedback << 3) | channel1.algorithm);

	// Detune & multiply
	setreg(0x30, (channel1.ops[0].detune << 4) | channel1.ops[0].multiply);
	setreg(0x34, (channel1.ops[1].detune << 4) | channel1.ops[1].multiply);
	setreg(0x38, (channel1.ops[2].detune << 4) | channel1.ops[2].multiply);
	setreg(0x3C, (channel1.ops[3].detune << 4) | channel1.ops[3].multiply);


	// Total level
	setreg(0x40, channel1.ops[0].totalLevel);
	setreg(0x44, channel1.ops[1].totalLevel);
	setreg(0x48, channel1.ops[2].totalLevel);
	setreg(0x4C, channel1.ops[3].totalLevel);


	// Rate scaling & attack rate
	setreg(0x50, (channel1.ops[0].rateScaling << 6) | channel1.ops[0].attackRate);
	setreg(0x54, (channel1.ops[1].rateScaling << 6) | channel1.ops[1].attackRate);
	setreg(0x58, (channel1.ops[2].rateScaling << 6) | channel1.ops[2].attackRate);
	setreg(0x5C, (channel1.ops[3].rateScaling << 6) | channel1.ops[3].attackRate);

	// Amplitude modulation & 1st decay rate
	setreg(0x60, (channel1.ops[0].amplitudeModulation << 7) | channel1.ops[0].decayRate1);
	setreg(0x64, (channel1.ops[1].amplitudeModulation << 7) | channel1.ops[1].decayRate1);
	setreg(0x68, (channel1.ops[2].amplitudeModulation << 7) | channel1.ops[2].decayRate1);
	setreg(0x6C, (channel1.ops[3].amplitudeModulation << 7) | channel1.ops[3].decayRate1);

	// 2nd decay rate
	setreg(0x70, channel1.ops[0].decayRate2);
	setreg(0x74, channel1.ops[1].decayRate2);
	setreg(0x78, channel1.ops[2].decayRate2);
	setreg(0x7C, channel1.ops[3].decayRate2);

	// Secondary amplitude & release rate
	setreg(0x80, (channel1.ops[0].secondaryAmplitude << 4) | channel1.ops[0].releaseRate);
	setreg(0x84, (channel1.ops[1].secondaryAmplitude << 4) | channel1.ops[1].releaseRate);
	setreg(0x88, (channel1.ops[2].secondaryAmplitude << 4) | channel1.ops[2].releaseRate);
	setreg(0x8C, (channel1.ops[3].secondaryAmplitude << 4) | channel1.ops[3].releaseRate);

	// Proprietary
	setreg(0x90, 0x00);
	setreg(0x94, 0x00);
	setreg(0x98, 0x00);
	setreg(0x9C, 0x00);

	// Both speakers on
	setreg(0xB4, 0xC0);

	// Key off
	setreg(0x28, 0x00);

	// Set frequency
	setreg(0xA4, (channel1.frequencyOctave << 3) | channel1.frequencyMSB);
	setreg(0xA0, channel1.frequencyLSB);

	while (true) {
		// cycle tone on/off
		_delay_ms(200);
		setreg(0x28, 0xF0); // Key on
		_delay_ms(1000);
		setreg(0x28, 0x00); // Key off
	}
}

