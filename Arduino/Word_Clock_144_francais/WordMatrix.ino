// Color construction for standard white-ish color
static const float white_hue = 0.075;
static const float white_lightness = 0.18;
static const float white_saturation = 0.24;
static uint32_t    whiteColor = matrix.Color(115, 90, 70, 100);

// Color construction for 'salut'
static const float welcome_hue = 0.32;
static const float welcome_lightness = 0.102;
static const float welcome_saturation = .923;
static uint32_t welcomeColor = hsl2Rgb(welcome_hue, welcome_saturation, welcome_lightness);

// Color construction for time prefixes 'juste', 'presque'
static const float hue_min = 0.03;
static const float hue_step = 0.0049;
static const float lightness = 0.1;
static const float saturation = 0.7;

void initWordMatrix() {
  matrix.begin();
  matrix.show();
    clearLEDsTemporary();
  // Set SALUT
  setLettersColor( 53, 1, welcomeColor); // S
  setLettersColor( 65, 1, welcomeColor); // A
  setLettersColor( 77, 1, welcomeColor); // L
  setLettersColor( 89, 1, welcomeColor); // U
  setLettersColor(101, 1, welcomeColor); // T
  matrix.show();
  delay(2000);
  updateWordMatrix();
}

void updateWordMatrix() {
  uint8_t minute = timestamp.minute;
  uint8_t hour = timestamp.hour;
  
  whiteColor = hsl2Rgb(white_hue, white_saturation, white_lightness);
  welcomeColor   = hsl2Rgb(welcome_hue, welcome_saturation, welcome_lightness);
  
  updateTimeMask(hour, minute);
  matrix.show();
}

void updateTimeMask(uint8_t hour, uint8_t minute) {
  uint8_t dist; // time distance in seconds to next anchor time, i.e. minute % 5 == 0

  clearLEDsTemporary();
  setLetters(0, 2);      // IL
  
  
  switch (minute % 5) {
  case 0:
    setLetters(3, 3);   // EST
    break;
  case 1:
    dist = timestamp.second;
    setLetters(6, 5);   // ÉTAIT
    setLettersColor(12, 5, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // JUSTE
    break;
  case 2:
    dist = 60 + timestamp.second;
    setLetters(6, 5);   // ÉTAIT
    setLettersColor(12, 5, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // JUSTE
    break;
  case 3:
    dist = 120 - timestamp.second;
    setLetters(3, 3);   // EST
    setLettersColor(17, 7, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // PRESQUE
    break;
  case 4:
    dist = 60 - timestamp.second;
    setLetters(3, 3);   // EST
    setLettersColor(17, 7, hsl2Rgb(hue_min + hue_step * dist, saturation, lightness));  // PRESQUE
    break;
  }

  switch (round(minute/5.0) % 12) {
    case 0:
      if ((minute % 5) >= 3) {
        // increase displayed hour in case it is shortly before a full hour.s
        ++hour;
      }
      break;
    case 1: // 5 nach
      setLetters(109, 4);  // CINQ
      break;
    case 2: // 10 nach
      setLetters(93, 3);   // DIX
      break;
    case 3: // 15 nach
      setLetters(91, 2);   // ET
      setLetters(112, 5);  // QUART
      break;
    case 4: // 20 nach
      setLetters(97, 5);   // VINGT
      break;
    case 5: // 25 nach
      setLetters(97, 5);   // VINGT
      setLetters(109, 4);  // CINQ
      break;
    case 6: // halb
      setLetters(91, 2);   // ET
      if (hour%12 == 0)
        setLetters(102, 4);  // DEMI
      else
        setLetters(102, 5);  // DEMIE
      break;
    case 7: // 25 vor
      setLetters(84, 5);   // MOINS
      setLetters(97, 5);   // VINGT
      setLetters(109, 4);  // CINQ
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 8: // 20 vor
      setLetters(84, 5);   // MOINS
      setLetters(97, 5);   // VINGT
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 9: // 15 vor
      setLetters(84, 5);   // MOINS
      setLetters(90, 2);   // LE
      setLetters(112, 5);  // QUART
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 10: // 10 vor
      setLetters(84, 5);   // MOINS
      setLetters(93, 3);   // DIX
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 11: // 5 vor
      setLetters(84, 5);   // MOINS
      setLetters(109, 4);  // CINQ
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    }
  
  // Process the current hour
  switch (hour % 12) {
    case 0:
      if (hour % 24 == 0) {
        setLetters(54, 6);  // MINUIT
      } else {
        setLetters(72, 4);   // MIDI
      }
      break;
    case 1:
      setLetters(39, 3);   // UNE
      break;
    case 2:
      setLetters(44, 4);   // DEUX
      break;
    case 3:
      setLetters(49, 5);   // TROIS
      break;
    case 4:
      setLetters(63, 6);   // QUATRE
      break;
    case 5:
      setLetters(60, 4);  // CINQ
      break;
    case 6:
      setLetters(36, 3);   // SIX
      break;
    case 7:
      setLetters(32, 4);  // SEPT
      break;
    case 8:
      setLetters(24, 4);   // HUIT
      break;
    case 9:
      setLetters(40, 4);  // NEUF
      break;
    case 10:
      setLetters(74, 3);  // DIX
      break;
    case 11:
      setLetters(28, 4);  // ONZE
      break;
    }

  // 'HEURE(S)' is shown only if it is not around minuit or midi
  if (hour%12 == 0) {
      ;
  } else if (hour == 1 || hour == 13 ) {
    setLetters(78, 5); // HEURE
  } else {
    setLetters(78, 6); // HEURES
  }
    
  // Vormittags/Nachmittags
  if (round(minute/5.0) % 6 == 0) {
    if (0 < hour && hour < 12) {
      setLetters(132, 2); // DU
      setLetters(135, 5); // MATIN
    } else if (12 < hour && hour < 18) {
      setLetters(118, 3); // DE L'
      setLetters(122, 10); // APRÈS-MIDI
    } else if (18 <= hour && hour < 24) {
      setLetters(132, 2); // DU
      setLetters(140, 4); // SOIR
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
    if (line % 2 == 1) {
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

  l = l * brightness/255.0;
//  l = l * (1 - 0.6 * cos((float)(timestamp.hour % 24)/12.0*PI));
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


