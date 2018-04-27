void motorInit(void){
  pinMode(LFWD,OUTPUT);
  digitalWrite(LFWD, LOW);
  pinMode(LBCK,OUTPUT);
  digitalWrite(LBCK, LOW);
  pinMode(LEN,OUTPUT);
  analogWrite(LEN, 0);

  pinMode(RFWD,OUTPUT);
  digitalWrite(RFWD, LOW);
  pinMode(RBCK,OUTPUT);
  digitalWrite(RBCK, LOW);
  pinMode(REN,OUTPUT);
  analogWrite(REN, 0);
}

void motorSpeeds(int left, int right){
        switch(left >= 0){
                case true:
                        digitalWrite(LBCK, LOW);
                        digitalWrite(LFWD, HIGH);
                        break;
                case false:
                        left = left*(-1);
                        digitalWrite(LFWD, LOW);
                        digitalWrite(LBCK, HIGH);
                        break;
                default:
                        analogWrite(REN, 0);
                        analogWrite(LEN, 0);
                        break;
        }
        switch(right >= 0){
                case true:
                        digitalWrite(RBCK, LOW);
                        digitalWrite(RFWD, HIGH);
                        break;
                case false:
                        right = right*(-1);
                        digitalWrite(RFWD, LOW);
                        digitalWrite(RBCK, HIGH);
                        break;
                default:
                        analogWrite(REN, 0);
                        analogWrite(LEN, 0);
                        break;
        }
        analogWrite(REN, (uint8_t)right);
        analogWrite(LEN, (uint8_t)left);
}

void ledInit(void){
  pinMode(LED1,OUTPUT);
  digitalWrite(LED1, LOW);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED2, LOW);
}

void mesgUpdate(void){
  if (vw_get_message(buf, (uint8_t*)BUFLEN)){
    xVal = buf[0];
    yVal = buf[1];
    flags = buf[2];
    #ifdef SERIAL_DEBUG
      Serial.print("xVal = "); Serial.print(xVal); Serial.print("yVal = "); Serial.println(yVal);
    #endif
  }
}
