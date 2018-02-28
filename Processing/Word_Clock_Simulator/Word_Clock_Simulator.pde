PFont f;
PFont fs;
int hour_disp = 0;
int minute_disp = 0;
String pattern = "MERXHANHATTEDEMNÄCHSEVVEBEINOHJERADEZWANZIGZEHNXVEEDELFÜNNEFNOHVÜRXHALVEEENDREIUHRXXZWEIVEERAACHSECHSIBBELFXZWÖLLEFÜNNEFZEHNÜNGINUHRXMEDDERNAACH";
public static int ON = 200;
boolean isManualTime = false;

void setup() {
  size(790, 840);
  f = createFont("Courier", 60, true);
  fs = createFont("Courier", 15, true);
}

void draw() {
  background(0);
  fill(200);
  textFont(f);
  int[] timeMask = getTimeMask();
  for (int i = 0; i < 144; ++i) {
    textFont(f);
    fill(timeMask[i]);
    text(pattern.charAt(i), 63*(i%12)+30, 63*(int(i/12)+1));
    fill(ON);
    String hour_s = nf(hour_disp, 2);
    String minute_s = nf(minute_disp, 2);
    text(hour_s + ":" + minute_s, 30,63*13);
    //fill(ON);
    //textFont(fs);
    //text(i, 63*(i%12 )+30, 63*(int(i/12)+1) - 40);
    
    
  }
}

int[] getTimeMask() {
  if (isManualTime) {
    return getTimeMask(hour_disp, minute_disp);
  } else {
    return getTimeMask(hour(), minute());
    //return getTimeMask(0, 0);
  }
}

int[] getTimeMask(int hour, int minute) {
  hour_disp = hour;
  minute_disp = minute;
  int[] timeMask = new int[144];
  boolean isNight = false;
  for (int i = 0; i < 144; ++i) {
    timeMask[i] = ON/16;
  }
  
  setLetters(timeMask, 0, 3);      // MER
  
  // There are two special cases that have to be taken care of.
  // In all other cases the standard procedure can be used.
  // Some special cases regarding midnight will be processed further down
  // This is a special case 11:11
  if (hour % 12 == 11 && minute == 11) {
    setLetters(timeMask, 4, 3);    // HAN 
    setLetters(timeMask, 52, 3);   // ELF
    setLetters(timeMask, 79, 3);   // UHR
    setLetters(timeMask, 104, 3);  // ELF
  } else if (hour % 12 == 11 && minute == 12) {
    // Special case 11:12 (HATTE JERADE ELF UHR ELF)
    setLetters(timeMask, 7, 5);    // HATTE
    setLetters(timeMask, 30, 6);   // JERADE
    setLetters(timeMask, 52, 3);   // ELF
    setLetters(timeMask, 79, 3);   // UHR
    setLetters(timeMask, 104, 3);  // ELF
  } else {
    switch (minute % 5) {
    case 0:
      setLetters(timeMask, 4, 3);   // HAN
      break;
    case 1:
      setLetters(timeMask, 7, 5);   // HATTE
      setLetters(timeMask, 30, 6);  // JERADE
      break;
    case 2:
      setLetters(timeMask, 7, 5);   // HATTE
      setLetters(timeMask, 20, 4);  // EVVE
      break;
    case 3:
      setLetters(timeMask, 4, 3);   // HAN
      setLetters(timeMask, 12, 8);  // DEMNÄCHS
      break;
    case 4:
      setLetters(timeMask, 4, 3);   // HAN
      setLetters(timeMask, 24, 6);  // BEINOH
      break;
    }
    
    switch (round(minute/5.0) % 12) {
    case 0:
      // Special case:
      // 'UHR' is shown only if it is not around midnight and especially not for midnights
      if (hour == 0 || hour == 23 && minute >= 23 || hour % 24 == 0 && minute >= 23) {
          ;
      } else {
        setLetters(timeMask, 129, 3); // UHR
      }
      if ((minute % 5) >= 3) {
        // increase displayed hour in case it is shortly before a full hour.s
        ++hour;
      }
      break;
    case 1: // 5 nach
      setLetters(timeMask, 54, 6);   // FÜNNEF
      setLetters(timeMask, 60, 3);   // NOH
      break;
    case 2: // 10 nach
      setLetters(timeMask, 43, 4);   // ZEHN
      setLetters(timeMask, 60, 3);   // NOH
      break;
    case 3: // 15 nach
      setLetters(timeMask, 48, 6);   // VEEDEL
      setLetters(timeMask, 60, 3);   // NOH
      break;
    case 4: // 20 nach
      setLetters(timeMask, 36, 7);   // ZWANZIG
      setLetters(timeMask, 60, 3);   // NOH
      break;
    case 5: // 5 vor halb
      setLetters(timeMask, 54, 6);   // FÜNNEF
      setLetters(timeMask, 63, 3);   // VÜR
      setLetters(timeMask, 67, 5);   // HALVE
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 6: // halb
      setLetters(timeMask, 67, 5);   // HALVE
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 7: // 5 nach halb
      setLetters(timeMask, 54, 6);   // FÜNNEF
      setLetters(timeMask, 60, 3);   // NOH
      setLetters(timeMask, 67, 5);   // HALVE
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 8: // 20 vor
      setLetters(timeMask, 36, 7);   // ZWANZIG
      setLetters(timeMask, 63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 9: // 15 vor
      setLetters(timeMask, 48, 6);   // VEEDEL
      setLetters(timeMask, 63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 10: // 10 vor
      setLetters(timeMask, 43, 4);   // ZEHN
      setLetters(timeMask, 63, 3);   // VÜR
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 11: // 5 vor
      setLetters(timeMask, 54, 6);   // FÜNNEF
      setLetters(timeMask, 63, 3);   // VÜR
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
          setLetters(timeMask, 133, 11);  // MEDDERNAACH
        } else  {
          setLetters(timeMask, 127, 2);   // IN 
          setLetters(timeMask, 136, 2);   // DE
          setLetters(timeMask, 139, 5);   // NAACH
          setLetters(timeMask, 108, 7);   // ZWÖLLEF
        }
        
      } else {
        // Otherwise it is simply 'ZWÖLLEF'
        setLetters(timeMask, 108, 7);   // ZWÖLLEF
      }
      break;
    case 1:
      setLetters(timeMask, 72, 3);   // EEN
      break;
    case 2:
      setLetters(timeMask, 84, 4);   // ZWEI
      break;
    case 3:
      setLetters(timeMask, 75, 4);   // DREI
      break;
    case 4:
      setLetters(timeMask, 84, 4);   // VEER
      break;
    case 5:
      setLetters(timeMask, 114, 6);  // FÜNNEF
      break;
    case 6:
      setLetters(timeMask, 96, 5);   // SECHS
      break;
    case 7:
      setLetters(timeMask, 100, 5);  // SIBBE
      break;
    case 8:
      setLetters(timeMask, 92, 4);   // AACH
      break;
    case 9:
      setLetters(timeMask, 123, 4);  // NÜNG
      break;
    case 10:
      setLetters(timeMask, 120, 4);  // ZEHN
      break;
    case 11:
      setLetters(timeMask, 104, 3);  // ELF
      break;
    }
  }
  return timeMask;
}

int[] setLetters(int[] mask, int begin, int length) {
  for (int i = begin; i < begin + length; ++i) {
    mask[i] = ON;
  }
  return mask;
}


void keyReleased() {
  switch (key) {
  case 'r':
  case 'R':
    isManualTime = !isManualTime;
    break;
  case CODED:
    if (keyCode == RIGHT && isManualTime) {
      ++minute_disp;
      if (minute_disp >= 60) {
        minute_disp %= 60;
        hour_disp = (hour_disp + 1) % 24;
      }
    }
    if (keyCode == LEFT && isManualTime) {
      --minute_disp;
      if (minute_disp < 0) {
        minute_disp = (minute_disp + 60) % 60;
        hour_disp = (hour_disp -1 + 24) % 24;
      }
    }
  }
}