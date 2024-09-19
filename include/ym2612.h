#include <stdint.h>

// YM2612 registers
#define YM_REG_LFO (0x22)
#define YM_REG_TIMERS (0x27)
#define YM_REG_KEY_ON_OFF (0x28)
#define YM_REG_DAC (0x2B)

#define YM_REG_DET_MUL_OP1_CH1 (0x30)
#define YM_REG_DET_MUL_OP1_CH2 (0x31)
#define YM_REG_DET_MUL_OP1_CH3 (0x32)
#define YM_REG_DET_MUL_OP1_CH4 (0x33)
#define YM_REG_DET_MUL_OP2_CH1 (0x34)
#define YM_REG_DET_MUL_OP2_CH2 (0x35)
#define YM_REG_DET_MUL_OP2_CH3 (0x36)
#define YM_REG_DET_MUL_OP2_CH4 (0x37)
#define YM_REG_DET_MUL_OP3_CH1 (0x38)
#define YM_REG_DET_MUL_OP3_CH2 (0x39)
#define YM_REG_DET_MUL_OP3_CH3 (0x3A)
#define YM_REG_DET_MUL_OP3_CH4 (0x3B)
#define YM_REG_DET_MUL_OP4_CH1 (0x3C)
#define YM_REG_DET_MUL_OP4_CH2 (0x3D)
#define YM_REG_DET_MUL_OP4_CH3 (0x3E)
#define YM_REG_DET_MUL_OP4_CH4 (0x3F)

#define YM_REG_TL_OP1_CH1 (0x40)
#define YM_REG_TL_OP1_CH2 (0x41)
#define YM_REG_TL_OP1_CH3 (0x42)
#define YM_REG_TL_OP1_CH4 (0x43)
#define YM_REG_TL_OP2_CH1 (0x44)
#define YM_REG_TL_OP2_CH2 (0x45)
#define YM_REG_TL_OP2_CH3 (0x46)
#define YM_REG_TL_OP2_CH4 (0x47)
#define YM_REG_TL_OP3_CH1 (0x48)
#define YM_REG_TL_OP3_CH2 (0x49)
#define YM_REG_TL_OP3_CH3 (0x4A)
#define YM_REG_TL_OP3_CH4 (0x4B)
#define YM_REG_TL_OP4_CH1 (0x4C)
#define YM_REG_TL_OP4_CH2 (0x4D)
#define YM_REG_TL_OP4_CH3 (0x4E)
#define YM_REG_TL_OP4_CH4 (0x4F)

#define YM_REG_RS_AR_OP1_CH1 (0x50)
#define YM_REG_RS_AR_OP1_CH2 (0x51)
#define YM_REG_RS_AR_OP1_CH3 (0x52)
#define YM_REG_RS_AR_OP1_CH4 (0x53)
#define YM_REG_RS_AR_OP2_CH1 (0x54)
#define YM_REG_RS_AR_OP2_CH2 (0x55)
#define YM_REG_RS_AR_OP2_CH3 (0x56)
#define YM_REG_RS_AR_OP2_CH4 (0x57)
#define YM_REG_RS_AR_OP3_CH1 (0x58)
#define YM_REG_RS_AR_OP3_CH2 (0x59)
#define YM_REG_RS_AR_OP3_CH3 (0x5A)
#define YM_REG_RS_AR_OP3_CH4 (0x5B)
#define YM_REG_RS_AR_OP4_CH1 (0x5C)
#define YM_REG_RS_AR_OP4_CH2 (0x5D)
#define YM_REG_RS_AR_OP4_CH3 (0x5E)
#define YM_REG_RS_AR_OP4_CH4 (0x5F)

#define YM_REG_AM_DR_OP1_CH1 (0x60)
#define YM_REG_AM_DR_OP1_CH2 (0x61)
#define YM_REG_AM_DR_OP1_CH3 (0x62)
#define YM_REG_AM_DR_OP1_CH4 (0x63)
#define YM_REG_AM_DR_OP2_CH1 (0x64)
#define YM_REG_AM_DR_OP2_CH2 (0x65)
#define YM_REG_AM_DR_OP2_CH3 (0x66)
#define YM_REG_AM_DR_OP2_CH4 (0x67)
#define YM_REG_AM_DR_OP3_CH1 (0x68)
#define YM_REG_AM_DR_OP3_CH2 (0x69)
#define YM_REG_AM_DR_OP3_CH3 (0x6A)
#define YM_REG_AM_DR_OP3_CH4 (0x6B)
#define YM_REG_AM_DR_OP4_CH1 (0x6C)
#define YM_REG_AM_DR_OP4_CH2 (0x6D)
#define YM_REG_AM_DR_OP4_CH3 (0x6E)
#define YM_REG_AM_DR_OP4_CH4 (0x6F)

#define YM_REG_DR2_OP1_CH1 (0x70)
#define YM_REG_DR2_OP1_CH2 (0x71)
#define YM_REG_DR2_OP1_CH3 (0x72)
#define YM_REG_DR2_OP1_CH4 (0x73)
#define YM_REG_DR2_OP2_CH1 (0x74)
#define YM_REG_DR2_OP2_CH2 (0x75)
#define YM_REG_DR2_OP2_CH3 (0x76)
#define YM_REG_DR2_OP2_CH4 (0x77)
#define YM_REG_DR2_OP3_CH1 (0x78)
#define YM_REG_DR2_OP3_CH2 (0x79)
#define YM_REG_DR2_OP3_CH3 (0x7A)
#define YM_REG_DR2_OP3_CH4 (0x7B)
#define YM_REG_DR2_OP4_CH1 (0x7C)
#define YM_REG_DR2_OP4_CH2 (0x7D)
#define YM_REG_DR2_OP4_CH3 (0x7E)
#define YM_REG_DR2_OP4_CH4 (0x7F)

#define YM_REG_SL_RR_OP1_CH1 (0x80)
#define YM_REG_SL_RR_OP1_CH2 (0x81)
#define YM_REG_SL_RR_OP1_CH3 (0x82)
#define YM_REG_SL_RR_OP1_CH4 (0x83)
#define YM_REG_SL_RR_OP2_CH1 (0x84)
#define YM_REG_SL_RR_OP2_CH2 (0x85)
#define YM_REG_SL_RR_OP2_CH3 (0x86)
#define YM_REG_SL_RR_OP2_CH4 (0x87)
#define YM_REG_SL_RR_OP3_CH1 (0x88)
#define YM_REG_SL_RR_OP3_CH2 (0x89)
#define YM_REG_SL_RR_OP3_CH3 (0x8A)
#define YM_REG_SL_RR_OP3_CH4 (0x8B)
#define YM_REG_SL_RR_OP4_CH1 (0x8C)
#define YM_REG_SL_RR_OP4_CH2 (0x8D)
#define YM_REG_SL_RR_OP4_CH3 (0x8E)
#define YM_REG_SL_RR_OP4_CH4 (0x8F)

#define YM_REG_PROPR1_CH1 (0x90)
#define YM_REG_PROPR1_CH2 (0x91)
#define YM_REG_PROPR1_CH3 (0x92)
#define YM_REG_PROPR1_CH4 (0x93)
#define YM_REG_PROPR2_CH1 (0x94)
#define YM_REG_PROPR2_CH2 (0x95)
#define YM_REG_PROPR2_CH3 (0x96)
#define YM_REG_PROPR2_CH4 (0x97)
#define YM_REG_PROPR3_CH1 (0x98)
#define YM_REG_PROPR3_CH2 (0x99)
#define YM_REG_PROPR3_CH3 (0x9A)
#define YM_REG_PROPR3_CH4 (0x9B)
#define YM_REG_PROPR4_CH1 (0x9C)
#define YM_REG_PROPR4_CH2 (0x9D)
#define YM_REG_PROPR4_CH3 (0x9E)
#define YM_REG_PROPR4_CH4 (0x9F)

#define YM_REG_FREQ_LSB_CH1 (0xA0)
#define YM_REG_FREQ_LSB_CH2 (0xA1)
#define YM_REG_FREQ_LSB_CH3 (0xA2)
#define YM_REG_FREQ_LSB_CH4 (0xA3)
#define YM_REG_FREQ_MSB_CH1 (0xA4)
#define YM_REG_FREQ_MSB_CH2 (0xA5)
#define YM_REG_FREQ_MSB_CH3 (0xA6)
#define YM_REG_FREQ_MSB_CH4 (0xA7)

#define YM_REG_FB_ALG_CH1 (0xB0)
#define YM_REG_FB_ALG_CH2 (0xB1)
#define YM_REG_FB_ALG_CH3 (0xB2)
#define YM_REG_FB_ALG_CH4 (0xB3)

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

void setReg(uint8_t reg, uint8_t data);
void initChannel(Channel channel);
