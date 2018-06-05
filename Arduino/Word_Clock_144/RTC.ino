void initRTC() {
  clock.begin();
//  clock.setDateTime(__DATE__, __TIME__);
  updateRTC();
}


boolean updateRTC() {
  boolean isNew = false;
  uint8_t oldMinute = timestamp.minute;
  timestamp = clock.getDateTime();
  if (oldMinute != timestamp.minute) {
    isNew = true;
  } 
  return isNew;
}
