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
