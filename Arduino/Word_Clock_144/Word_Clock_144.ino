#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <Wire.h>
#include <DS3231.h>

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(144, 17, NEO_GRB + NEO_KHZ800);

DS3231 clock;                 // The clock itself
RTCDateTime timestamp;        // The current timestamp

uint8_t wordMatrix[18];

void setup() {
  Serial.begin(115200);
  Wire.begin();

  initRTC();
  initWordMatrix();

  matrix.setBrightness(50);
  matrix.begin();
  matrix.show();
  updateWordMatrix();
  Serial.print(timestamp.hour);
  Serial.print(":");
  Serial.println(timestamp.minute);
//  colorWipe(matrix.Color(10, 0, 0), 50); // Red
}

void loop() {
  
  if (updateRTC()) {
    updateWordMatrix();
    Serial.print(timestamp.hour);
    Serial.print(":");
    Serial.println(timestamp.minute);
  }
  delay(1000);
}

// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
//  for(uint16_t i=0; i<matrix.numPixels(); i++) {
//    matrix.setPixelColor(i, c);
//    matrix.show();
//    delay(100);
//  }
//}
