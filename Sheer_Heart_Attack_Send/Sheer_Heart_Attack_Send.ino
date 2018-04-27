#include <VirtualWire.h>

#define XIN A1
#define YIN A0
#define BTN 7

byte msg[3];
uint8_t xVal;
uint8_t yVal;
uint8_t flags;

void setup(){
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000);
  Serial.begin(9600);
}

void loop(){
  xVal = map(analogRead(XIN),0,1024,0,255);
  yVal = map(analogRead(YIN),0,1024,0,255);
  flags = B00000000;
  if(digitalRead(BTN) == HIGH){
    setFlag(&flags,1);
    Serial.println(flags);
  }
  msg[0] = xVal;
  msg[1] = yVal;
  msg[2] = flags;
  Serial.print("xVal = "); Serial.print(xVal); Serial.print("yVal = "); Serial.print(yVal); Serial.print("msg = "); Serial.println((char*)msg);
  vw_send(msg, 2);
  vw_wait_tx();
}

void setFlag(uint8_t * flagAddr,unsigned int flagNo){
  *flagAddr |= 1 << (flagNo-1);
}

