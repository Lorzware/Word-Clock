void initWordMatrix() {
  matrix.setBrightness(10);
  matrix.begin();
  matrix.show();
  updateWordMatrix();
}

void updateWordMatrix() {
  uint8_t minute = timestamp.minute;
  uint8_t hour = timestamp.hour;
  
  updateTimeMask(hour, minute);
  
//  for (uint8_t i = 0; i < 144; ++i) {
//    if (bitRead(wordMatrix[i/8], 7-(i%8))) {
//      Serial.print("#");
//    } else {
//      Serial.print(".");
//    }
//  }
//  Serial.println();
  updateWordMatrixLEDs();
}

void updateTimeMask(uint8_t hour, uint8_t minute) {

  clearLEDsTemporary();
  
//  for (uint8_t i = 0; i < 18; ++i) {
//    wordMatrix[i] = 0;
//  }

  setLetters(0, 3);      // MER
  
  // There are two special cases that have to be taken care of.
  // In all other cases the standard procedure can be used.
  // Some special cases regarding midnight will be processed further down
  // This is a special case 11:11
  if (hour % 12 == 11 && minute == 11) {
    setLetters(4, 3);    // HAN 
    setLetters(52, 3);   // ELF
    setLetters(79, 3);   // UHR
    setLetters(104, 3);  // ELF
  } else if (hour % 12 == 11 && minute == 12) {
    // Special case 11:12 (HATTE JERADE ELF UHR ELF)
    setLetters(7, 5);    // HATTE
    setLetters(30, 6);   // JERADE
    setLetters(52, 3);   // ELF
    setLetters(79, 3);   // UHR
    setLetters(104, 3);  // ELF
  } else {
    switch (minute % 5) {
    case 0:
      setLetters(4, 3);   // HAN
      break;
    case 1:
      setLetters(7, 5);   // HATTE
      setLetters(30, 6);  // JERADE
      break;
    case 2:
      setLetters(7, 5);   // HATTE
      setLetters(20, 4);  // EVVE
      break;
    case 3:
      setLetters(4, 3);   // HAN
      setLetters(12, 8);  // DEMNÄCHS
      break;
    case 4:
      setLetters(4, 3);   // HAN
      setLetters(24, 6);  // BEINOH
      break;
    }
    
    switch (round(minute/5.0) % 12) {
    case 0:
      // Special case:
      // 'UHR' is shown only if it is not around midnight and especially not for midnights
      if (hour == 0 || hour == 23 && minute >= 23 || hour % 24 == 0 && minute >= 23) {
          ;
      } else {
        setLetters(129, 3); // UHR
      }
      if ((minute % 5) >= 3) {
        // increase displayed hour in case it is shortly before a full hour.s
        ++hour;
      }
      break;
    case 1: // 5 nach
      setLetters(54, 6);   // FÜNNEF
      setLetters(60, 3);   // NOH
      break;
    case 2: // 10 nach
      setLetters(43, 4);   // ZEHN
      setLetters(60, 3);   // NOH
      break;
    case 3: // 15 nach
      setLetters(48, 6);   // VEEDEL
      setLetters(60, 3);   // NOH
      break;
    case 4: // 20 nach
      setLetters(36, 7);   // ZWANZIG
      setLetters(60, 3);   // NOH
      break;
    case 5: // 5 vor halb
      setLetters(54, 6);   // FÜNNEF
      setLetters(63, 3);   // VÜR
      setLetters(67, 5);   // HALVE
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 6: // halb
      setLetters(67, 5);   // HALVE
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 7: // 5 nach halb
      setLetters(54, 6);   // FÜNNEF
      setLetters(60, 3);   // NOH
      setLetters(67, 5);   // HALVE
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 8: // 20 vor
      setLetters(36, 7);   // ZWANZIG
      setLetters(63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 9: // 15 vor
      setLetters(48, 6);   // VEEDEL
      setLetters(63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 10: // 10 vor
      setLetters(43, 4);   // ZEHN
      setLetters(63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 11: // 5 vor
      setLetters(54, 6);   // FÜNNEF
      setLetters(63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    }
    
    // Process the current hour
    switch (hour % 12) {
    case 0:
      // This is a special case. At midnight 'MEDDERNAACH' is displayed.
      // Of it is 12 o'clock at night, the additional 'IN DE NAACH' is displayed.
      if (hour % 24 == 0) {
        if (minute == 0) {
          setLetters(133, 11);  // MEDDERNAACH
        } else  {
          setLetters(127, 2);   // IN 
          setLetters(136, 2);   // DE
          setLetters(139, 5);   // NAACH
          setLetters(108, 7);   // ZWÖLLEF
        }
        
      } else {
        // Otherwise it is simply 'ZWÖLLEF'
        setLetters(108, 7);   // ZWÖLLEF
      }
      break;
    case 1:
      setLetters(72, 3);   // EEN
      break;
    case 2:
      setLetters(84, 4);   // ZWEI
      break;
    case 3:
      setLetters(75, 4);   // DREI
      break;
    case 4:
      setLetters(84, 4);   // VEER
      break;
    case 5:
      setLetters(114, 6);  // FÜNNEF
      break;
    case 6:
      setLetters(96, 5);   // SECHS
      break;
    case 7:
      setLetters(100, 5);  // SIBBE
      break;
    case 8:
      setLetters(92, 4);   // AACH
      break;
    case 9:
      setLetters(123, 4);  // NÜNG
      break;
    case 10:
      setLetters(120, 4);  // ZEHN
      break;
    case 11:
      setLetters(104, 3);  // ELF
      break;
    }
  }
}

void clearLEDsTemporary() {
  for (uint8_t i = 0; i < 144; ++i) {
    matrix.setPixelColor(i, matrix.Color(0, 0, 0, 0));
  }
}

void setLetters(uint8_t start, uint8_t duration) {
  for (uint8_t i = start; i < start + duration; ++i) {
    uint8_t line = i/12;
    if (line % 2 == 0) {
      matrix.setPixelColor(line * 12 + 11-i, matrix.Color(55, 55, 50, 100));
    } else {
      matrix.setPixelColor(line * 12 + i, matrix.Color(55, 55, 50, 100));
    }
    bitSet(wordMatrix[i / 8], 7 -(i % 8));
  }
}

void updateWordMatrixLEDs() {
    
  for (uint8_t line = 0; line < 12; ++line) {
    
    for (uint8_t i = 0; i < 12; ++i) {
      if (line % 2 == 0) {
        if (bitRead(wordMatrix[(line*12 + i) / 8], (line*12 + i) % 8)) {
          matrix.setPixelColor(line * 12 + 11-i, matrix.Color(55, 55, 50, 100));
        } else {
          matrix.setPixelColor(line * 12 + 11-i, matrix.Color(0,0,0,0));
        }
      } else  if (line % 2 == 1) {
        if (bitRead(wordMatrix[(line*12 + i) / 8], (line*12 + i) % 8)) {
          matrix.setPixelColor(line * 12 + i, matrix.Color(55, 55, 50, 100));
        } else {
          matrix.setPixelColor(line * 12 + 11-i, matrix.Color(0,0,0,0));
        }
      }
    }
  }
  matrix.show();
}
