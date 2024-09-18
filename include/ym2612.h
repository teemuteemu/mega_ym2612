#include <stdint.h>

// YM2612 registers
#define YM_REG_LFO (0x22)
#define YM_REG_TIMERS (0x27)
#define YM_REG_KEY_ON_OFF (0x28)
#define YM_REG_DAC (0x2B)

#define YM_REG_CH1_OP1_DET_MUL (0x30)
#define YM_REG_CH2_OP1_DET_MUL (0x31)
#define YM_REG_CH3_OP1_DET_MUL (0x32)
#define YM_REG_CH4_OP1_DET_MUL (0x33)
#define YM_REG_CH1_OP2_DET_MUL (0x34)
#define YM_REG_CH2_OP2_DET_MUL (0x35)
#define YM_REG_CH3_OP2_DET_MUL (0x36)
#define YM_REG_CH4_OP2_DET_MUL (0x37)
#define YM_REG_CH1_OP3_DET_MUL (0x38)
#define YM_REG_CH2_OP3_DET_MUL (0x39)
#define YM_REG_CH3_OP3_DET_MUL (0x3A)
#define YM_REG_CH4_OP3_DET_MUL (0x3B)
#define YM_REG_CH1_OP4_DET_MUL (0x3C)
#define YM_REG_CH2_OP4_DET_MUL (0x3D)
#define YM_REG_CH3_OP4_DET_MUL (0x3E)
#define YM_REG_CH4_OP4_DET_MUL (0x3F)

#define YM_REG_CH1_OP1_TL (0x40)
#define YM_REG_CH2_OP1_TL (0x41)
#define YM_REG_CH3_OP1_TL (0x42)
#define YM_REG_CH4_OP1_TL (0x43)
#define YM_REG_CH1_OP2_TL (0x44)
#define YM_REG_CH2_OP2_TL (0x45)
#define YM_REG_CH3_OP2_TL (0x46)
#define YM_REG_CH4_OP2_TL (0x47)
#define YM_REG_CH1_OP3_TL (0x48)
#define YM_REG_CH2_OP3_TL (0x49)
#define YM_REG_CH3_OP3_TL (0x4A)
#define YM_REG_CH4_OP3_TL (0x4B)
#define YM_REG_CH1_OP4_TL (0x4C)
#define YM_REG_CH2_OP4_TL (0x4D)
#define YM_REG_CH3_OP4_TL (0x4E)
#define YM_REG_CH4_OP4_TL (0x4F)

#define YM_REG_CH1_OP1_RS_AR (0x50)
#define YM_REG_CH2_OP1_RS_AR (0x51)
#define YM_REG_CH3_OP1_RS_AR (0x52)
#define YM_REG_CH4_OP1_RS_AR (0x53)
#define YM_REG_CH1_OP2_RS_AR (0x54)
#define YM_REG_CH2_OP2_RS_AR (0x55)
#define YM_REG_CH3_OP2_RS_AR (0x56)
#define YM_REG_CH4_OP2_RS_AR (0x57)
#define YM_REG_CH1_OP3_RS_AR (0x58)
#define YM_REG_CH2_OP3_RS_AR (0x59)
#define YM_REG_CH3_OP3_RS_AR (0x5A)
#define YM_REG_CH4_OP3_RS_AR (0x5B)
#define YM_REG_CH1_OP4_RS_AR (0x5C)
#define YM_REG_CH2_OP4_RS_AR (0x5D)
#define YM_REG_CH3_OP4_RS_AR (0x5E)
#define YM_REG_CH4_OP4_RS_AR (0x5F)

#define YM_REG_CH1_OP1_AM_DR (0x60)
#define YM_REG_CH2_OP1_AM_DR (0x61)
#define YM_REG_CH3_OP1_AM_DR (0x62)
#define YM_REG_CH4_OP1_AM_DR (0x63)
#define YM_REG_CH1_OP2_AM_DR (0x64)
#define YM_REG_CH2_OP2_AM_DR (0x65)
#define YM_REG_CH3_OP2_AM_DR (0x66)
#define YM_REG_CH4_OP2_AM_DR (0x67)
#define YM_REG_CH1_OP3_AM_DR (0x68)
#define YM_REG_CH2_OP3_AM_DR (0x69)
#define YM_REG_CH3_OP3_AM_DR (0x6A)
#define YM_REG_CH4_OP3_AM_DR (0x6B)
#define YM_REG_CH1_OP4_AM_DR (0x6C)
#define YM_REG_CH2_OP4_AM_DR (0x6D)
#define YM_REG_CH3_OP4_AM_DR (0x6E)
#define YM_REG_CH4_OP4_AM_DR (0x6F)

#define YM_REG_CH1_OP1_DR2 (0x70)
#define YM_REG_CH2_OP1_DR2 (0x71)
#define YM_REG_CH3_OP1_DR2 (0x72)
#define YM_REG_CH4_OP1_DR2 (0x73)
#define YM_REG_CH1_OP2_DR2 (0x74)
#define YM_REG_CH2_OP2_DR2 (0x75)
#define YM_REG_CH3_OP2_DR2 (0x76)
#define YM_REG_CH4_OP2_DR2 (0x77)
#define YM_REG_CH1_OP3_DR2 (0x78)
#define YM_REG_CH2_OP3_DR2 (0x79)
#define YM_REG_CH3_OP3_DR2 (0x7A)
#define YM_REG_CH4_OP3_DR2 (0x7B)
#define YM_REG_CH1_OP4_DR2 (0x7C)
#define YM_REG_CH2_OP4_DR2 (0x7D)
#define YM_REG_CH3_OP4_DR2 (0x7E)
#define YM_REG_CH4_OP4_DR2 (0x7F)

#define YM_REG_CH1_OP1_SL_RR (0x80)
#define YM_REG_CH2_OP1_SL_RR (0x81)
#define YM_REG_CH3_OP1_SL_RR (0x82)
#define YM_REG_CH4_OP1_SL_RR (0x83)
#define YM_REG_CH1_OP2_SL_RR (0x84)
#define YM_REG_CH2_OP2_SL_RR (0x85)
#define YM_REG_CH3_OP2_SL_RR (0x86)
#define YM_REG_CH4_OP2_SL_RR (0x87)
#define YM_REG_CH1_OP3_SL_RR (0x88)
#define YM_REG_CH2_OP3_SL_RR (0x89)
#define YM_REG_CH3_OP3_SL_RR (0x8A)
#define YM_REG_CH4_OP3_SL_RR (0x8B)
#define YM_REG_CH1_OP4_SL_RR (0x8C)
#define YM_REG_CH2_OP4_SL_RR (0x8D)
#define YM_REG_CH3_OP4_SL_RR (0x8E)
#define YM_REG_CH4_OP4_SL_RR (0x8F)

#define YM_REG_CH1_PROPR1 (0x90)
#define YM_REG_CH2_PROPR1 (0x91)
#define YM_REG_CH3_PROPR1 (0x92)
#define YM_REG_CH4_PROPR1 (0x93)
#define YM_REG_CH1_PROPR2 (0x94)
#define YM_REG_CH2_PROPR2 (0x95)
#define YM_REG_CH3_PROPR2 (0x96)
#define YM_REG_CH4_PROPR2 (0x97)
#define YM_REG_CH1_PROPR3 (0x98)
#define YM_REG_CH2_PROPR3 (0x99)
#define YM_REG_CH3_PROPR3 (0x9A)
#define YM_REG_CH4_PROPR3 (0x9B)
#define YM_REG_CH1_PROPR4 (0x9C)
#define YM_REG_CH2_PROPR4 (0x9D)
#define YM_REG_CH3_PROPR4 (0x9E)
#define YM_REG_CH4_PROPR4 (0x9F)

#define YM_REG_CH1_FREQ_LSB (0xA0)
#define YM_REG_CH2_FREQ_LSB (0xA1)
#define YM_REG_CH3_FREQ_LSB (0xA2)
#define YM_REG_CH4_FREQ_LSB (0xA3)
#define YM_REG_CH1_FREQ_MSB (0xA4)
#define YM_REG_CH2_FREQ_MSB (0xA5)
#define YM_REG_CH3_FREQ_MSB (0xA6)
#define YM_REG_CH4_FREQ_MSB (0xA7)
#define YM_REG_CH1_FB_ALG (0xB0)
#define YM_REG_CH2_FB_ALG (0xB1)
#define YM_REG_CH3_FB_ALG (0xB2)
#define YM_REG_CH4_FB_ALG (0xB3)

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
