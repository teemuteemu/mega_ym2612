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

// YM2612 registers
#define YM_REG_LFO (0x22)
#define YM_REG_DAC (0x2B)
#define YM_REG_KEY_ON_OFF (0x28)

// Channel 1 registers
#define YM_REG_CH1_FB_ALG (0xB0)
#define YM_REG_CH1_OP1_DET_MUL (0x30)
#define YM_REG_CH1_OP2_DET_MUL (0x34)
#define YM_REG_CH1_OP3_DET_MUL (0x38)
#define YM_REG_CH1_OP4_DET_MUL (0x3C)
#define YM_REG_CH1_OP1_TL (0x40)
#define YM_REG_CH1_OP2_TL (0x44)
#define YM_REG_CH1_OP3_TL (0x48)
#define YM_REG_CH1_OP4_TL (0x4C)
#define YM_REG_CH1_OP1_RS_AR (0x50)
#define YM_REG_CH1_OP2_RS_AR (0x54)
#define YM_REG_CH1_OP3_RS_AR (0x58)
#define YM_REG_CH1_OP4_RS_AR (0x5C)
#define YM_REG_CH1_OP1_AM_DR (0x60)
#define YM_REG_CH1_OP2_AM_DR (0x64)
#define YM_REG_CH1_OP3_AM_DR (0x68)
#define YM_REG_CH1_OP4_AM_DR (0x6C)
#define YM_REG_CH1_OP1_DR2 (0x70)
#define YM_REG_CH1_OP2_DR2 (0x74)
#define YM_REG_CH1_OP3_DR2 (0x78)
#define YM_REG_CH1_OP4_DR2 (0x7C)
#define YM_REG_CH1_OP1_SL_RR (0x80)
#define YM_REG_CH1_OP2_SL_RR (0x84)
#define YM_REG_CH1_OP3_SL_RR (0x88)
#define YM_REG_CH1_OP4_SL_RR (0x8C)

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
	Op ops[4];
} Channel;

typedef struct {
	uint8_t lfoEnabled;          // 1bit 0-1
	uint8_t lfoFrequency;        // 3bit 0-7
	Channel channels[6];
} YM2612;


YM2612 ym2612 = {
	.lfoEnabled = 0,
	.lfoFrequency = 0,
	.channels = {
		{
			.frequencyLSB = 105,
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
	},
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
	setreg(YM_REG_LFO, (ym2612.lfoEnabled << 3) | ym2612.lfoFrequency);

	// DAC off
	setreg(YM_REG_DAC, 0x00);

	setreg(0x27, 0x00); // Note off (channel 0)
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
	setreg(0x90, 0x00);
	setreg(0x94, 0x00);
	setreg(0x98, 0x00);
	setreg(0x9C, 0x00);

	// Both speakers on
	setreg(0xB4, 0xC0);

	// Key off
	setreg(YM_REG_KEY_ON_OFF, 0x00);

	// Set frequency
	setreg(0xA4, (ym2612.channels[0].frequencyOctave << 3) | ym2612.channels[0].frequencyMSB);
	setreg(0xA0, ym2612.channels[0].frequencyLSB);

	while (true) {
		// cycle tone on/off
		_delay_ms(200);
		setreg(YM_REG_KEY_ON_OFF, 0xF0); // Key on
		_delay_ms(1000);
		setreg(YM_REG_KEY_ON_OFF, 0x00); // Key off
	}
}

