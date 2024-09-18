#include <stdint.h>

// YM2612 registers
#define YM_REG_LFO (0x22)
#define YM_REG_TIMERS (0x27)
#define YM_REG_KEY_ON_OFF (0x28)
#define YM_REG_DAC (0x2B)

// Channel 1 registers
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
#define YM_REG_CH1_PROPR1 (0x90)
#define YM_REG_CH1_PROPR2 (0x94)
#define YM_REG_CH1_PROPR3 (0x98)
#define YM_REG_CH1_PROPR4 (0x9C)
#define YM_REG_CH1_FREQ_LSB (0xA0)
#define YM_REG_CH1_FREQ_MSB (0xA4)
#define YM_REG_CH1_FB_ALG (0xB0)

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

void write_ym(uint8_t data);
void setreg(uint8_t reg, uint8_t data);
