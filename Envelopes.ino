/*  uint8_t startPoint = 11;
  uint8_t paramWindow = 28;
  uint8_t envCeiling = 23;
  uint8_t envFloor = 38;

  uint8_t atkParam = (sigValue[0] / 5) + startPoint;
  uint8_t decayParam = (sigValue[1] / 5) + atkParam;
  uint8_t susParam =  (-sigValue [2] / 8) + envFloor;
  uint8_t rlsParam = (sigValue[3] / 5) + paramWindow + decayParam;

  uint8_t atkAmt = (-sigValue [4] / 8) + envFloor;
  uint8_t decayAmt = (-sigValue [5] / 8) + envFloor;
  uint8_t susAmt = (-sigValue [6] / 8) + envFloor;
  uint8_t rlsAmt = (-sigValue [7] / 8) + envFloor;

  display.drawLine(startPoint, envFloor, atkParam, atkAmt, WHITE);
  display.drawLine(atkParam, atkAmt, decayParam, decayAmt, WHITE);
  display.drawLine(decayParam, decayAmt, paramWindow + decayParam, susAmt, WHITE);
  display.drawLine(paramWindow + decayParam, susParam, rlsParam, envFloor, WHITE);


 * 
 *Standard ADSR Envelope:
 *
  display.drawLine(startPoint, envFloor, atkParam, envCeiling, WHITE);
  display.drawLine(atkParam, envCeiling, decayParam, susParam, WHITE);
  display.drawLine(decayParam, susParam, paramWindow + decayParam, susParam, WHITE);
  display.drawLine(paramWindow + decayParam, susParam, rlsParam, envFloor, WHITE);//*/
