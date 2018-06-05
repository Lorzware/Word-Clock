boolean updateLightsensor() {
  boolean change = true;
  uint8_t tempBrightness = analogRead(2) >> 2;
  if (tempBrightness > brightness) {
    ++brightness;
  } else if (tempBrightness < brightness && brightness > 15) {
    --brightness;
  } else {
    change = false;
  }
  Serial.println(brightness);
  return change;
}

