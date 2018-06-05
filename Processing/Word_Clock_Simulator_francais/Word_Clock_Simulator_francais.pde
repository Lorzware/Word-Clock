PFont f;
PFont fs;
int hour_disp = 0;
int minute_disp = 0;
String pattern = "ILSESTÉTAITUJUSTEPRESQUEHUITONZESEPTSIXUNEUFDEUXYTROISMINUITCINQUATRENTEMIDIXLHEURESMOINSULETDIXAVINGTDEMIERICINQUARTODELCAPRÈS-MIDIDURMATINSOIR";
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
    
    fill(ON);
    textFont(fs);
    text(i, 63*(i%12 )+30, 63*(int(i/12)+1) - 40);
    
    
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
    timeMask[i] = ON/4;
  }
  
  setLetters(timeMask, 0, 2);      // IL
  
    switch (minute % 5) {
    case 0:
      setLetters(timeMask, 3, 3);   // EST
      break;
    case 1:
    case 2:
      setLetters(timeMask, 6, 5);   // ÉTAIT
      setLetters(timeMask, 12, 5);  // JUSTE
      break;
    case 3:
    case 4:
      setLetters(timeMask, 3, 3);   // EST
      setLetters(timeMask, 17, 7);  // PRESQUE
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
      setLetters(timeMask, 109, 4);  // CINQ
      break;
    case 2: // 10 nach
      setLetters(timeMask, 93, 3);   // DIX
      break;
    case 3: // 15 nach
      setLetters(timeMask, 91, 2);   // ET
      setLetters(timeMask, 112, 5);  // QUART
      break;
    case 4: // 20 nach
      setLetters(timeMask, 97, 5);   // VINGT
      break;
    case 5: // 25 nach
      setLetters(timeMask, 97, 5);   // VINGT
      setLetters(timeMask, 109, 4);  // CINQ
      break;
    case 6: // halb
      setLetters(timeMask, 91, 2);   // ET
      if (hour%12 == 0)
        setLetters(timeMask, 102, 4);  // DEMI
      else
        setLetters(timeMask, 102, 5);  // DEMIE
      break;
    case 7: // 25 vor
      setLetters(timeMask, 84, 5);   // MOINS
      setLetters(timeMask, 97, 5);   // VINGT
      setLetters(timeMask, 109, 4);  // CINQ
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 8: // 20 vor
      setLetters(timeMask, 84, 5);   // MOINS
      setLetters(timeMask, 97, 5);   // VINGT
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 9: // 15 vor
      setLetters(timeMask, 84, 5);   // MOINS
      setLetters(timeMask, 90, 2);   // LE
      setLetters(timeMask, 112, 5);  // QUART
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 10: // 10 vor
      setLetters(timeMask, 84, 5);   // MOINS
      setLetters(timeMask, 93, 3);   // DIX
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    case 11: // 5 vor
      setLetters(timeMask, 84, 5);   // MOINS
      setLetters(timeMask, 109, 4);  // CINQ
      ++hour;   // increase displayed hour since it is before a certain time.
      break;
    }
    
    // Process the current hour
    switch (hour % 12) {
    case 0:
      if (hour % 24 == 0) {
        setLetters(timeMask, 54, 6);  // MINUIT
      } else {
        setLetters(timeMask, 72, 4);   // MIDI
      }
      break;
    case 1:
      setLetters(timeMask, 39, 3);   // UNE
      break;
    case 2:
      setLetters(timeMask, 44, 4);   // DEUX
      break;
    case 3:
      setLetters(timeMask, 49, 5);   // TROIS
      break;
    case 4:
      setLetters(timeMask, 63, 6);   // QUATRE
      break;
    case 5:
      setLetters(timeMask, 60, 4);  // CINQ
      break;
    case 6:
      setLetters(timeMask, 36, 3);   // SIX
      break;
    case 7:
      setLetters(timeMask, 32, 4);  // SEPT
      break;
    case 8:
      setLetters(timeMask, 24, 4);   // HUIT
      break;
    case 9:
      setLetters(timeMask, 40, 4);  // NEUF
      break;
    case 10:
      setLetters(timeMask, 74, 3);  // DIX
      break;
    case 11:
      setLetters(timeMask, 28, 4);  // ONZE
      break;
    }
    
    // 'HEURE(S)' is shown only if it is not around minuit or midi
    if (hour%12 == 0) {
        ;
    } else if (hour == 1 || hour == 13 ) {
      setLetters(timeMask, 78, 5); // HEURE
    } else {
      setLetters(timeMask, 78, 6); // HEURES
    }
    
  // Vormittags/Nachmittags
  if (round(minute/5.0) % 6 == 0) {
    if (0 < hour && hour < 12) {
      setLetters(timeMask, 132, 2); // DU
      setLetters(timeMask, 135, 5); // MATIN
    } else if (12 < hour && hour < 18) {
      setLetters(timeMask, 118, 3); // DE L'
      setLetters(timeMask, 122, 10); // APRÈS-MIDI
    } else if (18 <= hour && hour < 24) {
      setLetters(timeMask, 132, 2); // DU
      setLetters(timeMask, 140, 4); // SOIR
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
    if (keyCode == UP && isManualTime) {
      ++hour_disp;
      if (hour_disp >= 24) {
        hour_disp %= 24;
      }
    }
    if (keyCode == DOWN && isManualTime) {
      --hour_disp;
      if (hour_disp < 0) {
        hour_disp = (hour_disp + 24) % 24;
      }
    }
  }
}
