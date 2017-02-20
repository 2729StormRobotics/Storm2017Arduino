#include "Arduino.h"
#include "FastLED.h"
#include <math.h>

#define RAND_MAX 255
#define NUM_LEDS 208
#define DATA_PIN 8
#define CLOCK_PIN 13

#define LED_CHIPSET WS2812B
#define LED_ORDER GRB
#define LED_COLOR_CORRECTION TypicalSMD5050

#define VOLTAGE 5
#define AMP_LIMIT 7125

#define BRIGHTNESS 255

#define SERIAL_SPEED 9600

#define SERIAL_DEFAULT 0
#define SERIAL_OFF 150
#define SERIAL_AUTONOMOUS 160
#define SERIAL_AUTONOMOUS_FAIL 170
#define SERIAL_SHOOTING 180
#define SERIAL_CONNECTION_FAIL 190
#define SERIAL_ENCODER_FAIL 200
#define SERIAL_TELEOPERATED 210
#define SERIAL_HANGING_FAIL 220
#define SERIAL_SHOOTING_FAIL 230
#define SERIAL_GEAR_FAIL 240
#define SERIAL_INTAKE_FAIL 250
#define SERIAL_RAINBOW 255

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

int incomingByte = SERIAL_DEFAULT;
boolean switcher = true;
CRGB leds[NUM_LEDS];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<LED_CHIPSET, DATA_PIN, LED_ORDER>(leds, NUM_LEDS).setCorrection( LED_COLOR_CORRECTION );
  Serial.begin(SERIAL_SPEED);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, AMP_LIMIT);
  FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
//  EVERY_N_MILLISECONDS( 1 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  gHue++;
  random16_add_entropy( random() );
  
//  if(incomingByte == SERIAL_DEFAULT){
//    if(switcher){
//      for(int i = 0; i <= NUM_LEDS/2; i++){
//        leds[i].setRGB(255, 0, 0);
//        leds[NUM_LEDS - i].setRGB(255, 0, 0);
//        FastLED.show();
//      }
//    }
//    else{
//      for(int i = 0; i <= NUM_LEDS/2; i++){
//        leds[i].setRGB(255, 45, 0);
//        leds[NUM_LEDS - i].setRGB(255, 45, 0);
//        FastLED.show();
//      }
//    }
//    switcher = !switcher;
//  }


  //autonomous basic
  if (incomingByte == SERIAL_AUTONOMOUS) {
    if (switcher) {
      for (int i = 0; i <= NUM_LEDS; i++) {
        if (i % 2 == 0) {
          leds[i].setRGB(255, 0, 0);
        } else {
          leds[i].setRGB(255, 45, 0);
        }
      }
      FastLED.show();
      delay(100);
    } else {
      for (int i = 0; i <= NUM_LEDS; i++) {
        if (i % 2 == 0) {
          leds[i].setRGB(255, 45, 0);
        } else {
          leds[i].setRGB(255, 0, 0);
        }
      }
      FastLED.show();
      delay(100);
    }
    switcher = !switcher;
  }

  //off
  if (incomingByte == SERIAL_OFF) {
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
  }

  //autonomous drive failure
  if (incomingByte == SERIAL_AUTONOMOUS_FAIL) {
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(255, 0, 0);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //shooting
  if (incomingByte == SERIAL_SHOOTING) {
    for (int i = 0; i <= NUM_LEDS/2; i++) {
      leds[i].setRGB(255, 45, 0);
      leds[207 - i].setRGB(255, 45, 0);
    }
    FastLED.show();
    for (int j = 1; j <= NUM_LEDS/2; j++) {
      leds[j - 1].setRGB(255, 45, 0);
      leds[j].setRGB(255, 0, 0);
      leds[j + 1].setRGB(255, 0, 0);
      leds[j + 2].setRGB(255, 0, 0);
      leds[j + 3].setRGB(255, 0, 0);
      leds[j + 4].setRGB(255, 0, 0);
      leds[j + 5].setRGB(255, 0, 0);
      leds[j + 6].setRGB(255, 0, 0);
      leds[j + 7].setRGB(255, 0, 0);

      FastLED.show();
      delay(10);
    }
  }

  //connection failure
  if (incomingByte == SERIAL_CONNECTION_FAIL) {
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 255);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //encoder failure
  if(incomingByte == SERIAL_ENCODER_FAIL){
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 255, 0);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //teleop basic
  if(incomingByte == SERIAL_TELEOPERATED){
    if(switcher){
      for(int i = 0; i <= NUM_LEDS/2; i++){
        leds[i].setRGB(255, 0, 0);
        leds[207 - i].setRGB(255, 0, 0);
        FastLED.show();
        delay(50);
      }
    }
    else{
      for(int i = 0; i <= NUM_LEDS/2; i++){
        leds[i].setRGB(255, 45, 0);
        leds[207 - i].setRGB(255, 45, 0);
        FastLED.show();
        delay(50);
      }
    }
    switcher = !switcher;
  }

  //hanging failure
  if(incomingByte == SERIAL_HANGING_FAIL){
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(150, 0 , 255);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //shooting failure
  if(incomingByte == SERIAL_SHOOTING_FAIL){
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(255, 255, 0);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //gear failure
  if(incomingByte == SERIAL_GEAR_FAIL){
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(100, 255, 240);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //intake failure
  if(incomingByte == SERIAL_INTAKE_FAIL){
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(255, 255, 255);
    }
    FastLED.show();
    delay(300);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //rainbow dance party
  if (incomingByte == SERIAL_DEFAULT) {
    //for (int i = 0; i <= NUM_LEDS; i++) {
    //  leds[i].setRGB(random8(), random8(), random8());
    //}
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();
    FastLED.show();
  }
}

if (incomingByte == SERIAL_RAINBOW) {
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
}


