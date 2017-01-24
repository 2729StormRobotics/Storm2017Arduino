#include "Arduino.h"
#include "FastLED.h"
#include <math.h>

#define NUM_LEDS 33
#define DATA_PIN 8
#define CLOCK_PIN 13

int incomingByte = 0;
boolean switcher = true;
CRGB leds[NUM_LEDS];

void setup() {

	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
	Serial.begin(9600);

}

void loop() {

	if (Serial.available() > 0) {
		incomingByte = Serial.read();
	}

	//autonomous basic
	if (incomingByte == 175) {
		if (switcher) {
			for (int i = 0; i <= 32; i++) {
				if (i % 2 == 0) {
					leds[i].setRGB(255, 0, 0);
				} else {
					leds[i].setRGB(255, 45, 0);
				}
			}
			switcher = !switcher;
			FastLED.show();
			delay(100);
		} else {
			for (int i = 0; i <= 32; i++) {
				if (i % 2 == 0) {
					leds[i].setRGB(255, 45, 0);
				} else {
					leds[i].setRGB(255, 0, 0);
				}
			}
			switcher = !switcher;
			FastLED.show();
			delay(100);
		}
	}

	//autonomous drive failure
	if (incomingByte == 200) {
		for (int i = 0; i <= 32; i++) {
			leds[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(300);
		for (int i = 0; i <= 32; i++) {
			leds[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(300);
	}

}
