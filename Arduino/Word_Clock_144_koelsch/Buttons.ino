void initButtons() {
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  lastButtons = PINC & 0x0f;;
}

boolean updateButtons() {
  uint8_t currentState = PINC & 0x0f;
  uint8_t pinChanges = currentState ^ lastButtons;

  boolean resetSeconds = false;
  
  // Always check if button was released.
  if (bitRead(pinChanges, 0) && bitRead(currentState, 0)) {
    resetSeconds = true;
    clock.setDateTime(timestamp.unixtime + 3600);
//    Serial.println("+ 1 hour");
  }
  if (bitRead(pinChanges, 1) && bitRead(currentState, 1)) {
    resetSeconds = true;
    clock.setDateTime(((timestamp.unixtime + 60) / 60) * 60);
//    Serial.println("+ 1 minute");
  }
  if (bitRead(pinChanges, 2) && bitRead(currentState, 2)) {
    resetSeconds = true;
    clock.setDateTime(((timestamp.unixtime - 60) / 60) * 60);
//    Serial.println("- 1 minute");
  }
  if (bitRead(pinChanges, 3) && bitRead(currentState, 3)) {
    resetSeconds = true;
    clock.setDateTime(timestamp.unixtime - 3600);
//    Serial.println("- 1 hour");
  }
  
  if (resetSeconds) {
    resetSecondsRTC();
  }
  lastButtons = currentState;
  return resetSeconds;
}

