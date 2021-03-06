#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <Wire.h>
#include <DS3231.h>

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(144, 17, NEO_GRB + NEO_KHZ800);

DS3231 clock;                 // The clock itself
RTCDateTime timestamp;        // The current timestamp

uint8_t lastButtons = PIND & 0x0f;
uint8_t brightness = 50;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  initEEPROM();
  printPinout();
  initRTC();
  initWordMatrix();
  initButtons();


//  colorWipe(matrix.Color(255, 0, 0), 50); // Red
}

void loop() {

//  colorWipe(0x2222, 50);
  clearLEDsTemporary();
//  matrix.show();
//  delay(100);
  
  if (updateRTC()  || updateLightsensor()) {
    updateWordMatrix();
  }
  if (updateButtons()) {
    updateWordMatrix();
  }
  delay(5);
}

// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
//  for(uint16_t i=0; i<matrix.numPixels(); i++) {
//    matrix.setPixelColor(i, c);
//    matrix.show();
//    delay(wait);
//  }
//}
