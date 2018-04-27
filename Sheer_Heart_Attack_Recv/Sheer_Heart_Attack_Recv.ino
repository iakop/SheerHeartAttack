#include <VirtualWire.h>

#define BUFLEN 3 //VW_MAX_MESSAGE_LEN

#define LFWD 2
#define LBCK 3
#define LEN 5

#define RFWD 4
#define RBCK 7
#define REN 6

#define LED1 A4
#define LED2 A5

uint8_t buf[BUFLEN]; //Buffer set to max lenght.
uint8_t xVal, yVal, flags;
uint8_t rightDrive, leftDrive;
int xPos, xNeg, yPos, yNeg;
bool dir = true;

void setup() {
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(12);
  vw_setup(4000); //bits pr. sec
  vw_rx_start();
  motorInit();
  ledInit();
  Serial.begin(9600);
}

/*
void loop(){
  digitalWrite(LFWD, HIGH);
  digitalWrite(LBCK, LOW);
  analogWrite(LEN, 255);
  digitalWrite(RFWD, HIGH);
  digitalWrite(RBCK, LOW);
  analogWrite(REN, 255);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}
*/


void loop() {
  if (vw_get_message(buf, (uint8_t*)BUFLEN)){
    xVal = buf[0];
    yVal = buf[1];
    flags = buf[2];
    Serial.print("xVal = "); Serial.print(xVal); Serial.print("yVal = "); Serial.println(yVal);
  }
  
  xPos = xVal-128;
  xNeg = 128-xVal;
  yPos = yVal-128;
  yNeg = 128-yVal;

  rightDrive, leftDrive = 0;
  
  if(yPos>yNeg){
    dir = true;
    rightDrive, leftDrive = yPos;
  }
  else{
    dir = false;
    rightDrive, leftDrive = yNeg;
  }

  //Maybe put two inside the above if-case?
  if(xPos>xNeg){
    leftDrive += xPos;
  }
  else{
    rightDrive += xNeg;
  }

  switch(dir){
    case true:
      digitalWrite(LBCK,LOW);
      digitalWrite(LFWD,HIGH);
      analogWrite(LEN, leftDrive);
      digitalWrite(RBCK,LOW);
      digitalWrite(RFWD,HIGH);
      analogWrite(REN, leftDrive);
      break;
    case false:
      digitalWrite(LFWD,LOW);
      digitalWrite(LBCK,HIGH);
      analogWrite(LEN, leftDrive);
      digitalWrite(RFWD,LOW);
      digitalWrite(RBCK,HIGH);
      analogWrite(REN, leftDrive);
      break;
  }
}


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


void ledInit(void){
  pinMode(LED1,OUTPUT);
  digitalWrite(LED1, HIGH);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED2, HIGH);
}
