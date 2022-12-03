/*
  Author: Advait Thale
  *******************************************************************
  *                  Flight Controller Read Test                    *    
  *******************************************************************

  The flight controller is designed to work around drone(quadcopter) transceiving data 
  via NRF24L01 radio module. Before implementing to drone, I wrote this test code to 
  ensure sensors, dual-axis potentiometer, MCU and both displays are working correctly.
  LCD shows up arrow (^), when data is sent and down arrow(v), when data is received.
  For now, only OLED, LCD and Dual-axis pots are tested.
  -----------------------------------------------------------------------------------
  +++ : Forward Thrust                                     Pitch(^) : Downward Pitch
  --- : Backward Thrust                                    Pitch(v) : Upward Pitch
  <<< : Strafe Left                                        Roll (<) : Roll Left 
  >>> : Strafe Right                                       Roll (>) : Roll Right 
  -----------------------------------------------------------------------------------
  
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <LiquidCrystal.h>
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
LiquidCrystal lcd(12, 11, 10, 6 , 7, 8, 9); //(RS,R/W,EN,D4,D5,D6,D7)

unsigned char Character1[8] = { 0x04, 0x0E, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04 };// UP Arrow
unsigned char Character2[8] = { 0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x0E, 0x04 };// DOWN Arrow

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.createChar(0, Character1);
  lcd.createChar(1, Character2);
  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
  display.display();
  display.clearDisplay();
}

void loop() {
  int X = analogRead(0);
  int Y = analogRead(1);
  int P = analogRead(2);
  int R = analogRead(3);
  int THROTTLE = map(Y, 0, 1024, 500, -512);
  int YAW = map(X, 0, 1024, 500, -512);
  int PITCH = map(P, 0, 1024, 471, -512);
  int ROLL = map(R, 0, 1024, 499, -513);
  delay(100);
  //Serial
  Serial.print("Throttle: ");
  Serial.print(THROTTLE);
  Serial.print("\t");
  Serial.print("Yaw: ");
  Serial.print(YAW);
  Serial.print("\t");
  Serial.print("Pitch: ");
  Serial.print(PITCH);
  Serial.print("\t");
  Serial.print("Roll: ");
  Serial.println(ROLL);

  //LCD
  lcd.setCursor(0, 0);
  lcd.print("DSM v6.05");
  lcd.setCursor(0, 1);
  lcd.print("Connected");
  if (PITCH > 10 || PITCH < -10 || ROLL < 0 || ROLL > 10 || THROTTLE > 10 || THROTTLE < 0 || YAW < 0 || YAW > 10) {
    lcd.setCursor(13, 0);
    lcd.write(byte(0));
    delay(200);
    lcd.setCursor(13, 0);
    lcd.print(" ");
  }

  //lcd.clear();

  //OLED
  display.setTextSize(1); //setTextSize(2)
  display.setTextColor(SH110X_WHITE);
  if (THROTTLE > 10) {
    display.setCursor(15, 0);
    display.print("+++");
  }
  else if (THROTTLE < 0) {
    display.setCursor(15, 20);
    display.print("---");
  }
  if (YAW < 0) {
    display.setCursor(0, 10);
    display.print("<<");
  }
  else if (YAW > 10) {
    display.setCursor(40, 10);
    display.print(">>");
  }

  //Joystick 2
  if (PITCH > 10) {
    display.setCursor(70, 0);
    display.print("Pitch");
  }
  else if (PITCH < -10) {
    display.setCursor(70, 20);
    display.print("Pitch");
  }
  if (ROLL < 0 ) {
    display.setCursor(50, 10);
    display.print("Roll");
  }
  else if (ROLL > 10) {
    display.setCursor(100, 10);
    display.print("Roll");
  }
  display.display();
  delayMicroseconds(2);
  display.clearDisplay();
}
