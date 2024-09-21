#include <stdint.h>

// YM2612 registers
#define YM_REG_LFO (0x22)
#define YM_REG_TIMERS (0x27)
#define YM_REG_KEY_ON_OFF (0x28)
#define YM_REG_DAC (0x2B)

// Macro to generate full register names based on the register name and channel number
#define YM_REG_CH(reg, ch) reg##_CH##ch

#define DET_MUL_OP1_CH1 (0x30)
#define DET_MUL_OP1_CH2 (0x31)
#define DET_MUL_OP1_CH3 (0x32)
#define DET_MUL_OP1_CH4 (0x33)
#define DET_MUL_OP2_CH1 (0x34)
#define DET_MUL_OP2_CH2 (0x35)
#define DET_MUL_OP2_CH3 (0x36)
#define DET_MUL_OP2_CH4 (0x37)
#define DET_MUL_OP3_CH1 (0x38)
#define DET_MUL_OP3_CH2 (0x39)
#define DET_MUL_OP3_CH3 (0x3A)
#define DET_MUL_OP3_CH4 (0x3B)
#define DET_MUL_OP4_CH1 (0x3C)
#define DET_MUL_OP4_CH2 (0x3D)
#define DET_MUL_OP4_CH3 (0x3E)
#define DET_MUL_OP4_CH4 (0x3F)

#define TL_OP1_CH1 (0x40)
#define TL_OP1_CH2 (0x41)
#define TL_OP1_CH3 (0x42)
#define TL_OP1_CH4 (0x43)
#define TL_OP2_CH1 (0x44)
#define TL_OP2_CH2 (0x45)
#define TL_OP2_CH3 (0x46)
#define TL_OP2_CH4 (0x47)
#define TL_OP3_CH1 (0x48)
#define TL_OP3_CH2 (0x49)
#define TL_OP3_CH3 (0x4A)
#define TL_OP3_CH4 (0x4B)
#define TL_OP4_CH1 (0x4C)
#define TL_OP4_CH2 (0x4D)
#define TL_OP4_CH3 (0x4E)
#define TL_OP4_CH4 (0x4F)

#define RS_AR_OP1_CH1 (0x50)
#define RS_AR_OP1_CH2 (0x51)
#define RS_AR_OP1_CH3 (0x52)
#define RS_AR_OP1_CH4 (0x53)
#define RS_AR_OP2_CH1 (0x54)
#define RS_AR_OP2_CH2 (0x55)
#define RS_AR_OP2_CH3 (0x56)
#define RS_AR_OP2_CH4 (0x57)
#define RS_AR_OP3_CH1 (0x58)
#define RS_AR_OP3_CH2 (0x59)
#define RS_AR_OP3_CH3 (0x5A)
#define RS_AR_OP3_CH4 (0x5B)
#define RS_AR_OP4_CH1 (0x5C)
#define RS_AR_OP4_CH2 (0x5D)
#define RS_AR_OP4_CH3 (0x5E)
#define RS_AR_OP4_CH4 (0x5F)

#define AM_DR_OP1_CH1 (0x60)
#define AM_DR_OP1_CH2 (0x61)
#define AM_DR_OP1_CH3 (0x62)
#define AM_DR_OP1_CH4 (0x63)
#define AM_DR_OP2_CH1 (0x64)
#define AM_DR_OP2_CH2 (0x65)
#define AM_DR_OP2_CH3 (0x66)
#define AM_DR_OP2_CH4 (0x67)
#define AM_DR_OP3_CH1 (0x68)
#define AM_DR_OP3_CH2 (0x69)
#define AM_DR_OP3_CH3 (0x6A)
#define AM_DR_OP3_CH4 (0x6B)
#define AM_DR_OP4_CH1 (0x6C)
#define AM_DR_OP4_CH2 (0x6D)
#define AM_DR_OP4_CH3 (0x6E)
#define AM_DR_OP4_CH4 (0x6F)

#define DR2_OP1_CH1 (0x70)
#define DR2_OP1_CH2 (0x71)
#define DR2_OP1_CH3 (0x72)
#define DR2_OP1_CH4 (0x73)
#define DR2_OP2_CH1 (0x74)
#define DR2_OP2_CH2 (0x75)
#define DR2_OP2_CH3 (0x76)
#define DR2_OP2_CH4 (0x77)
#define DR2_OP3_CH1 (0x78)
#define DR2_OP3_CH2 (0x79)
#define DR2_OP3_CH3 (0x7A)
#define DR2_OP3_CH4 (0x7B)
#define DR2_OP4_CH1 (0x7C)
#define DR2_OP4_CH2 (0x7D)
#define DR2_OP4_CH3 (0x7E)
#define DR2_OP4_CH4 (0x7F)

#define SL_RR_OP1_CH1 (0x80)
#define SL_RR_OP1_CH2 (0x81)
#define SL_RR_OP1_CH3 (0x82)
#define SL_RR_OP1_CH4 (0x83)
#define SL_RR_OP2_CH1 (0x84)
#define SL_RR_OP2_CH2 (0x85)
#define SL_RR_OP2_CH3 (0x86)
#define SL_RR_OP2_CH4 (0x87)
#define SL_RR_OP3_CH1 (0x88)
#define SL_RR_OP3_CH2 (0x89)
#define SL_RR_OP3_CH3 (0x8A)
#define SL_RR_OP3_CH4 (0x8B)
#define SL_RR_OP4_CH1 (0x8C)
#define SL_RR_OP4_CH2 (0x8D)
#define SL_RR_OP4_CH3 (0x8E)
#define SL_RR_OP4_CH4 (0x8F)

#define PROPR1_CH1 (0x90)
#define PROPR1_CH2 (0x91)
#define PROPR1_CH3 (0x92)
#define PROPR1_CH4 (0x93)
#define PROPR2_CH1 (0x94)
#define PROPR2_CH2 (0x95)
#define PROPR2_CH3 (0x96)
#define PROPR2_CH4 (0x97)
#define PROPR3_CH1 (0x98)
#define PROPR3_CH2 (0x99)
#define PROPR3_CH3 (0x9A)
#define PROPR3_CH4 (0x9B)
#define PROPR4_CH1 (0x9C)
#define PROPR4_CH2 (0x9D)
#define PROPR4_CH3 (0x9E)
#define PROPR4_CH4 (0x9F)

#define FREQ_LSB_CH1 (0xA0)
#define FREQ_LSB_CH2 (0xA1)
#define FREQ_LSB_CH3 (0xA2)
#define FREQ_LSB_CH4 (0xA3)
#define FREQ_MSB_CH1 (0xA4)
#define FREQ_MSB_CH2 (0xA5)
#define FREQ_MSB_CH3 (0xA6)
#define FREQ_MSB_CH4 (0xA7)

#define FB_ALG_CH1 (0xB0)
#define FB_ALG_CH2 (0xB1)
#define FB_ALG_CH3 (0xB2)
#define FB_ALG_CH4 (0xB3)

#define CH1_KEY_ON (0xF0)
#define CH2_KEY_ON (0xF1)
#define CH3_KEY_ON (0xF2)
#define CH4_KEY_ON (0xF4)
#define CH5_KEY_ON (0xF5)
#define CH6_KEY_ON (0xF6)
#define CH1_KEY_OFF (0x00)
#define CH2_KEY_OFF (0x01)
#define CH3_KEY_OFF (0x02)
#define CH4_KEY_OFF (0x04)
#define CH5_KEY_OFF (0x05)
#define CH6_KEY_OFF (0x06)

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
	uint16_t frequency;          // 11bit 0-2047
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

// Set register in YM2612 part 1, this is controlled with A0 and A1 pins
void setRegPt1(uint8_t reg, uint8_t data);
// Set register in YM2612 part 2
void setRegPt2(uint8_t reg, uint8_t data);

void initChannel1(Channel channel);
void initChannel2(Channel channel);
void initChannel3(Channel channel);
void initChannel4(Channel channel);
void initChannel5(Channel channel);
void initChannel6(Channel channel);
