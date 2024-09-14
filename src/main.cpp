#include <Arduino.h>

// YM2612 pins
#define D0 32
#define D1 32
#define D2 33
#define D3 34
#define D4 35
#define D5 36
#define D6 37
#define D7 38
#define IC 40
#define OM 41
#define CS 44
#define WR 45
#define RD 46
#define A0 47
#define A1 48


void setup() {
	Serial.begin(9600);
	pinMode(OM, OUTPUT);
}

void loop() {
	digitalWrite(OM, HIGH);
	Serial.println("LED ON");
	delay(100);
	digitalWrite(OM, LOW);
	Serial.println("LED OFF");
	delay(50);
}
