#include "Arduino.h"
#include "FastLED.h"
#include <math.h>
#include <inttypes.h>

#define RANDOM_MAX 255
//#define NUM_LEDS 208
#define NUM_LEDS 294
#define DATA_PIN 3
#define CLOCK_PIN 13

#define LED_CHIPSET WS2812B
#define LED_ORDER GRB
#define LED_COLOR_CORRECTION TypicalSMD5050

#define VOLTAGE 5
#define AMP_LIMIT 7125

#define BRIGHTNESS 255

#define SERIAL_SPEED 9600

#define SERIAL_DEFAULT 0
#define SERIAL_RIGHT 120
#define SERIAL_PEG 100
#define SERIAL_LEFT 110
#define SERIAL_CENTERED 140
#define SERIAL_GEAR_CLOSE 130
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

uint8_t incomingByte = SERIAL_DEFAULT;
uint8_t gHue = 0;
bool gReverseDirection = false;
boolean switcher = true;
uint8_t climbPatternPos = 0;
CRGB leds[NUM_LEDS];
CRGBPalette16 gPal;

void setup() {
  Serial.begin(SERIAL_SPEED);
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<LED_CHIPSET, DATA_PIN, LED_ORDER>(leds, NUM_LEDS).setCorrection(LED_COLOR_CORRECTION);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE, AMP_LIMIT);
  FastLED.setBrightness(BRIGHTNESS);

  gPal = CRGBPalette16(CRGB(255, 75, 0), CRGB::Red, CRGB(255, 75, 0));
}

void loop() {
  static uint8_t startIndex = 0;
  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (incomingByte == SERIAL_CENTERED) {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
  }

  if (incomingByte == SERIAL_PEG){
    rainbowDanceParty();
  }

  if (incomingByte == SERIAL_GEAR_CLOSE) {
    fill_solid(leds, NUM_LEDS, CRGB::Aqua);
    FastLED.show();
  }

  if (incomingByte == SERIAL_RIGHT) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (int i = 0; i <= 104; i++) {
      leds[i].setRGB(255, 255, 255);
    }

    FastLED.show();
  }

  if (incomingByte == SERIAL_LEFT) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (int i = 104; i <= 208; i++) {
      leds[i].setRGB(255, 255, 255);
    }

    FastLED.show();
  }

  if (incomingByte == SERIAL_DEFAULT) {
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    //      if(switcher){
    //        for(int i = 0; i <= NUM_LEDS/2; i++){
    //          leds[i].setRGB(255, 0, 0);
    //          leds[NUM_LEDS - i].setRGB(255, 0, 0);
    //          FastLED.show();
    //          delay(10);
    //        }
    //      }
    //      else{
    //        for(int i = 0; i <= NUM_LEDS/2; i++){
    //          leds[i].setRGB(255, 45, 0);
    //          leds[NUM_LEDS - i].setRGB(255, 45, 0);
    //          FastLED.show();
    //          delay(10);
    //        }
    //      }
    //      switcher = !switcher;
  }

  //autonomous basic
  //  if (incomingByte == SERIAL_AUTONOMOUS) {
  //    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Red, CRGB::Orange,
  //        CRGB::Red, CRGB::Orange);
  //  }

  //off
  //  if (incomingByte == SERIAL_DEFAULT)  {
  //    fill_solid(leds, NUM_LEDS, CRGB::Black);
  //    FastLED.show();
  //  }

  //autonomous drive failure
  //  if (incomingByte == SERIAL_AUTONOMOUS_FAIL) {
  //    fill_solid(leds, NUM_LEDS, CRGB::Red);
  //    FastLED.show();
  //    delay(300);
  //    fill_solid(leds, NUM_LEDS, CRGB::Black);
  //    FastLED.show();
  //    delay(300);
  //  }

  //shooting
  //  if (incomingByte == SERIAL_SHOOTING) {
  //    for (int i = 0; i <= NUM_LEDS / 2; i++) {
  //      leds[i].setRGB(255, 45, 0);
  //      leds[207 - i].setRGB(255, 45, 0);
  //    }
  //    FastLED.show();
  //    for (int j = 1; j <= NUM_LEDS / 2; j++) {
  //      leds[j - 1].setRGB(255, 45, 0);
  //      leds[j].setRGB(255, 0, 0);
  //      leds[j + 1].setRGB(255, 0, 0);
  //      leds[j + 2].setRGB(255, 0, 0);
  //      leds[j + 3].setRGB(255, 0, 0);
  //      leds[j + 4].setRGB(255, 0, 0);
  //      leds[j + 5].setRGB(255, 0, 0);
  //      leds[j + 6].setRGB(255, 0, 0);
  //      leds[j + 7].setRGB(255, 0, 0);
  //
  //      FastLED.show();
  //      delay(10);
  //    }
  //  }

  //connection failure
  //  if (incomingByte == SERIAL_CONNECTION_FAIL) {
  //    /*
  //    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  //    FastLED.show();
  //    delay(300);
  //    fill_solid(leds, NUM_LEDS, CRGB::Black);
  //    FastLED.show();
  //    delay(300);
  //    */
  //    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Red, CRGB::Orange,
  //        CRGB::Red, CRGB::Orange);
  //  }

  //encoder failure
  //  if (incomingByte == SERIAL_ENCODER_FAIL) {
  //    fill_solid(leds, NUM_LEDS, CRGB::Green);
  //    FastLED.show();
  //    delay(300);
  //    fill_solid(leds, NUM_LEDS, CRGB::Black);
  //    FastLED.show();
  //    delay(300);
  //  }

  //teleop basic
  //  if (incomingByte == SERIAL_TELEOPERATED) {
  //    fill_gradient_RGB(leds, NUM_LEDS, CRGB::Red, CRGB::Orange,
  //        CRGB::Red, CRGB::Orange);
  //    /*
  //     if (switcher) {
  //     for (int i = 0; i <= NUM_LEDS / 2; i++) {
  //     leds[i].setRGB(255, 0, 0);
  //     leds[207 - i].setRGB(255, 0, 0);
  //     FastLED.show();
  //     delay(50);
  //     }
  //     } else {
  //     for (int i = 0; i <= NUM_LEDS / 2; i++) {
  //     leds[i].setRGB(255, 45, 0);
  //     leds[207 - i].setRGB(255, 45, 0);
  //     FastLED.show();
  //     delay(50);
  //     }
  //     }
  //     switcher = !switcher;
  //     */
  //  }

  //hanging failure
  if (incomingByte == SERIAL_HANGING_FAIL) {
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(300);
  }

  //shooting failure
  if (incomingByte == SERIAL_SHOOTING_FAIL) {
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
    FastLED.show();
    delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(300);
  }

  //gear failure
  if (incomingByte == SERIAL_GEAR_FAIL) {
    fill_solid(leds, NUM_LEDS, CRGB(100, 255, 240));
    FastLED.show();
    delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(300);
  }

  //intake failure
  if (incomingByte == SERIAL_INTAKE_FAIL) {
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
    delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(300);
  }

  //rainbow dance party
  if (incomingByte == SERIAL_RAINBOW) {
    rainbowBackToFront();
  }
}

void blinkColor(CRGB color) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(300);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(300);
}

void rainbowDanceParty() {
  fill_rainbow(leds, NUM_LEDS, gHue, 16);
  addGlitter(127);
  gHue++;
  FastLED.show();
}

void rainbowFrontToBack() {
  fadeToBlackBy(leds, NUM_LEDS, 10);
  leds[climbPatternPos] = CHSV(gHue, 255, 255);
  leds[NUM_LEDS - climbPatternPos] = CHSV(gHue, 255, 255);
  gHue += 8;
  climbPatternPos++;
  climbPatternPos = climbPatternPos % (NUM_LEDS / 2);
  FastLED.show();
}

void rainbowBackToFront() {
  fadeToBlackBy(leds, NUM_LEDS, 10);
  leds[climbPatternPos] = CHSV(gHue, 255, 255);
  leds[NUM_LEDS - climbPatternPos] = CHSV(gHue, 255, 255);
  gHue += 8;
  climbPatternPos--;
  if (climbPatternPos == 255) {
    climbPatternPos = NUM_LEDS / 2;
  }
  FastLED.show();
}

void addGlitter(fract8 chanceOfGlitter) {
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy(random());
  if (random8() < chanceOfGlitter) {
    leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(gPal, colorIndex, BRIGHTNESS, LINEARBLEND);
        colorIndex += 1;
    }
}

// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation,
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120


void Fire2012WithPalette()
{
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
}
