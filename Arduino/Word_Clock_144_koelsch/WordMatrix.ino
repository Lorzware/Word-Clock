// Color construction for standard white-ish color
static const float white_hue = 0.075;
static const float white_lightness = 0.18;
static const float white_saturation = 0.24;
static uint32_t    whiteColor = matrix.Color(115, 90, 70, 100);

// Color construction for 'elf uhr elf' and 'alaaf'
static const float elf_hue = 0.036;
static const float elf_lightness = 0.225;
static const float elf_saturation = 1;
static uint32_t    elfColor   = matrix.Color(230, 50, 0, 100);

// Color construction for time prefixes 'demnächs', 'beinoh', 'jerade' and 'evve'
static const float hue_min = 0.03;
static const float hue_step = 0.0049;
static const float lightness = 0.1;
static const float saturation = 0.7;

void initWordMatrix() {
  matrix.begin();
  matrix.show();
    clearLEDsTemporary();
  // Set ALAAF
  setLettersColor( 66, 1, elfColor); // A
  setLettersColor( 78, 1, elfColor); // L
  setLettersColor( 90, 1, elfColor); // A
  setLettersColor(102, 1, elfColor); // A
  setLettersColor(114, 1, elfColor); // F
  matrix.show();
  delay(2000);
  updateWordMatrix();
}

void updateWordMatrix() {
  uint8_t minute = timestamp.minute;
  uint8_t hour = timestamp.hour;
  
  whiteColor = hsl2Rgb(white_hue, white_saturation, white_lightness);
  elfColor   = hsl2Rgb(elf_hue, elf_saturation, elf_lightness);
  
  updateTimeMask(hour, minute);
  matrix.show();
}

void updateTimeMask(uint8_t hour, uint8_t minute) {
  uint8_t dist; // time distance in seconds to next anchor time, i.e. minute % 5 == 0

  clearLEDsTemporary();
  setLetters(0, 3);      // MER
  
  // There are two special cases that have to be taken care of.
  // In all other cases the standard procedure can be used.
  // Some special cases regarding midnight will be processed further down
  // This is a special case 11:11
  if (hour % 12 == 11 && minute == 11) {
    setLetters(4, 3);                   // HAN 
    setLettersColor(52, 3, elfColor);   // ELF
    setLettersColor(93, 3, elfColor);   // UHR
    setLettersColor(112, 3, elfColor);  // ELF
  } else if (hour % 12 == 11 && minute == 12) {
    // Special case 11:12 (HATTE JERADE ELF UHR ELF)
    setLetters(7, 5);    // HATTE
    setLetters(30, 6);   // JERADE
    setLetters(52, 3);   // ELF
    setLetters(93, 3);   // UHR
    setLetters(112, 3);  // ELF
  } else if (hour == 23 && minute == 58) {
    setLetters(4, 3);                   // HAN
    setLettersColor(12, 8, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // DEMNÄCHS
    setLetters(133, 11);  // MEDDERNAACH
  } else if (hour == 23 && minute == 59) {
    setLetters(4, 3);                   // HAN
    setLettersColor(24, 6, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // BEINOH
    setLetters(133, 11);  // MEDDERNAACH
  } else if (hour == 0 && minute == 1) {
    setLetters(7, 5);   // HATTE
    setLettersColor(30, 6, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // JERADE
    setLetters(133, 11);  // MEDDERNAACH
  } else if (hour == 0 && minute == 2) {
    setLetters(7, 5);   // HATTE
    setLettersColor(20, 4, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // EVVE
    setLetters(133, 11);  // MEDDERNAACH
  }
  
  
  else {
    switch (minute % 5) {
    case 0:
      setLetters(4, 3);   // HAN
      break;
    case 1:
      dist = timestamp.second;
      setLetters(7, 5);   // HATTE
      setLettersColor(30, 6, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // JERADE
      break;
    case 2:
      dist = 60 + timestamp.second;
      setLetters(7, 5);   // HATTE
      setLettersColor(20, 4, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // EVVE
      break;
    case 3:
      dist = 120 - timestamp.second;
      setLetters(4, 3);   // HAN
      setLettersColor(12, 8, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // DEMNÄCHS
      break;
    case 4:
      dist = 60 - timestamp.second;
      setLetters(4, 3);   // HAN
      setLettersColor(24, 6, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // BEINOH
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
      setLetters(44, 4);   // ZEHN
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
      setLetters(44, 4);   // ZEHN
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
          setLetters(75, 5);    // ZWÖLF
        }
        
      } else {
        // Otherwise it is simply 'ZWÖLLEF'
        setLetters(75, 5);   // ZWÖLF
      }
      break;
    case 1:
      setLetters(72, 3);   // EEN
      break;
    case 2:
      setLetters(84, 4);   // ZWEI
      break;
    case 3:
      setLetters(80, 4);   // DREI
      break;
    case 4:
      setLetters(103, 4);  // VEER
      break;
    case 5:
      setLetters(96, 6);   // FÜNNEF
      break;
    case 6:
      setLetters(115, 5);  // SECHS
      break;
    case 7:
      setLetters(108, 5);  // SIBBE
      break;
    case 8:
      setLetters(89, 4);   // AACH
      break;
    case 9:
      setLetters(123, 4);  // NÜNG
      break;
    case 10:
      setLetters(120, 4);  // ZEHN
      break;
    case 11:
      setLetters(112, 3);  // ELF
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
  setLettersColor(start, duration, whiteColor);
}

void setLettersColor(uint8_t start, uint8_t duration, uint32_t color) {
  for (uint8_t i = start; i < start + duration; ++i) {
    uint8_t line = i/12;
    if (line % 2 == 0) {
      matrix.setPixelColor(line * 12 + 11-(i % 12), color);
    } else {
      matrix.setPixelColor(line * 12 + (i % 12), color);
    }
  }
}



float hue2rgb(float p, float q, float t) {
  if(t < 0) t += 1;
  if(t > 1) t -= 1;
  if(t < 0.1666667) return p + (q - p) * 6 * t;
  if(t < 0.5) return q;
  if(t < 0.6666667) return p + (q - p) * (0.6666667 - t) * 6;
  return p;
}

/**
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   {number}  h       The hue
 * @param   {number}  s       The saturation
 * @param   {number}  l       The lightness
 * @return  {Array}           The RGB representation
 */
uint32_t hsl2Rgb(float h, float s, float l) {
  float r, g, b;
  
  l = l * (1 - 0.6 * cos((float)(timestamp.hour % 24)/12.0*PI));
  l = min(l, 1); // safety check
  l = max(l, 0); // safety check
  if(s == 0){
    r = g = b = l; // achromatic
  } else {
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    r = hue2rgb(p, q, h + 0.333333);
    g = hue2rgb(p, q, h);
    b = hue2rgb(p, q, h - 0.333333);
  }
  return matrix.Color(r * 255, g * 255, b * 255, 100);
}


