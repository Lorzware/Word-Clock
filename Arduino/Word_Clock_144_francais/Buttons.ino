void initButtons() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  lastButtons = PIND & 0x3c;;
}

boolean updateButtons() {
  uint8_t currentState = PIND & 0x3c;
  uint8_t pinChanges = currentState ^ lastButtons;

  boolean resetSeconds = false;
  
  // Always check if button was released.
  if (bitRead(pinChanges, 4) && bitRead(currentState, 4)) {
    resetSeconds = true;
    clock.setDateTime(timestamp.unixtime + 3600);
//    Serial.println("+ 1 hour");
  }
  if (bitRead(pinChanges, 2) && bitRead(currentState, 2)) {
    resetSeconds = true;
    clock.setDateTime(((timestamp.unixtime + 60) / 60) * 60);
//    Serial.println("+ 1 minute");
  }
  if (bitRead(pinChanges, 3) && bitRead(currentState, 3)) {
    resetSeconds = true;
    clock.setDateTime(((timestamp.unixtime - 60) / 60) * 60);
//    Serial.println("- 1 minute");
  }
  if (bitRead(pinChanges, 5) && bitRead(currentState, 5)) {
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

