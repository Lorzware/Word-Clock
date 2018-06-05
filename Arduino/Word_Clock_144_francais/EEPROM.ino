void initEEPROM() {
//  writeEEPROM();
}

void writeEEPROM() {
  EEPROM.write(0, 17); // RGB LED Strip
  EEPROM.write(1, 2); // Light sensor
  EEPROM.write(2, 2); // Button 1
  EEPROM.write(3, 3); // Button 2
  EEPROM.write(4, 4); // Button 3
  EEPROM.write(5, 5); // Button 4
}

void printPinout() {
  Serial.println("\nWelcome to the Word-Clock in French!");
  Serial.println("Pin-Layout:");
  Serial.print(EEPROM.read(0));
  Serial.println(": RGB LED Strip");
  Serial.print(EEPROM.read(1));
  Serial.println(": Light sensor (analog)");
  Serial.print(EEPROM.read(2));
  Serial.println(": Button 1");
  Serial.print(EEPROM.read(3));
  Serial.println(": Button 2");
  Serial.print(EEPROM.read(4));
  Serial.println(": Button 3");
  Serial.print(EEPROM.read(5));
  Serial.println(": Button 4");
}

