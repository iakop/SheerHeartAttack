#include <VirtualWire.h>

//#define SERIAL_DEBUG

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
uint8_t rightDrive = 0, leftDrive = 0;
int xGlobal = 0, yGlobal = 0;
bool dir = true;

void setup() {
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(12);
  vw_setup(4000); //bits pr. sec
  vw_rx_start();
  motorInit();
  ledInit();
  #ifdef SERIAL_DEBUG
    Serial.begin(9600);
  #endif
}

void loop() {
  mesgUpdate();

  // Since 
  xGlobal = xVal-128;
  yGlobal = yVal-128;

  // Left motor = K x (Front_Back + Left_Right)
  // Right motor = K x (Front_Back - Left_Right)
  // Use these Formulae, and map them to the motorSpeeds API:
  leftDrive = map((yGlobal + xGlobal), -128, 128, -255, 255);
  rightDrive = map((yGlobal- xGlobal), -128, 128, -255, 255);

  // Set the motor Speeds using the motorSpeeds function:
  motorSpeeds(leftDrive, rightDrive);
}
