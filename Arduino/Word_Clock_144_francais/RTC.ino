void initRTC() {
  clock.begin();
//  clock.setDateTime(__DATE__, __TIME__);
  updateRTC();
}


boolean updateRTC() {
  uint8_t oldSecond = timestamp.second;
  timestamp = clock.getDateTime();
  return (oldSecond != timestamp.second);
}

void resetSecondsRTC() {
  updateRTC();
  clock.setDateTime(timestamp.year,
                    timestamp.month,
                    timestamp.day,
                    timestamp.hour,
                    timestamp.minute,
                    0);
  updateRTC();
}

