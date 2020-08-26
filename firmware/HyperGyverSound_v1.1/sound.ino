int getSoundLength() {
  int thisMax = 0;
  int thisSignal = 0;
  for (int i = 0; i < 300; i++) {
    thisSignal = analogRead(ADC_PIN);
    if (thisSignal > thisMax) thisMax = thisSignal;
  }

  static float filMax = 1000, filMin = 1000;
  static float filLength;
  static int maxMax = 0, minMin = 1023;
  static byte counter;

  counter++;
  if (counter == 50) {
    counter = 0;
    maxMax = 0;
    minMin = 1023;
  }
  if (thisMax > maxMax) maxMax = thisMax;
  if (thisMax < minMin) minMin = thisMax;

  filMax += (float)(maxMax - filMax) * 0.01;
  filMin += (float)(minMin - filMin) * 0.01;

  int thisLenght = map(thisMax - filMin, VOL_THR, filMax - filMin, 0, 100);
  thisLenght = constrain(thisLenght, 0, 100);

  filLength += (float)(thisLenght - filLength) * 0.2;
  if (thisMax > filMax) filLength = 100;
  
  if (filMax - filMin > VOL_THR) return filLength;
  else return 0;
}
