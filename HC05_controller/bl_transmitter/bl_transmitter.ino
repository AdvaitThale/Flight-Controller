/*
  Author: Advait Thale
  *******************************************************************
  *                        HC-05 Transmitter                        *    
  *******************************************************************

  The 4WD is controlled by self made handheld direction control console via dual-axis 
  potentiometer also having HC-05 and Arduino Nano as MCU. As D-A pot is moved the 
  4WD moves. The implemented direction movements on Dual-axis pot. are:
  -----------------------------------------------------------------------------------
                                     Forward 
                               
                           Turn Left         Turn Right     
                                            
                                     Backward                                               
  -----------------------------------------------------------------------------------
*/

#include<SoftwareSerial.h>
SoftwareSerial bt(2, 3);
byte start = 0xE7; //start byte for x axis
byte starty = 0xE5; //start byte for y axis
byte dip = 0xE6;
int SW = 5;
int NRx = A0;
int NRy = A1;
int x, y, state, state1, state2;
int s1 = 30;
int s2 = 31;
int s3 = 32;
int s4 = 33;
int s5 = 34;
int s6 = 35;
int s7 = 36;
int s8 = 37;
bool flag;

void setup() 
{
  pinMode(SW, INPUT_PULLUP);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  Serial.begin(38400);
  bt.begin(38400);
  Serial.println("Init");
}
void loop()
{
  NRx = analogRead(A0);
  NRy = analogRead(A1);
  state = digitalRead(SW); 
  state1 = digitalRead(s1);
  state2 = digitalRead(s2);


  byte xh = ((NRx & 0b1110000000) >> 3);
  delay(70);
  byte xl = NRx & 0x7F;
  byte yh = ((NRy & 0b1110000000) >> 3);
  delay(70);
  byte yl = NRy & 0x7F;

  bt.write(start);
  delay(100);
  bt.write(xh);
  delay(100);
  bt.write(xl);
  delay(100);
  bt.write(state);
  delay(100);
  bt.write(yh);
  delay(100);
  bt.write(yl);
  delay(100);
  bt.write(state1);
  delay(100);
  bt.write(state2);
  //  Serial.print("\tstart: ");
  //  //  Serial.print(state/);
  //  Serial.print("\txh: ");
  //  Serial.print(state1);
  //  Serial.print("\txl: ");
  //  Serial.println(xl);
  bt.flush();

  
  byte switchState = 0x00;
  if (digitalRead(s1 == LOW))
  {
    byte s1 = 0b00000001;
    byte switchState = switchState | s1;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  }
   if (digitalRead(s2 == LOW))
  {
    byte s2 = 0b00000010;
    byte switchState = switchState | s2;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  } 
  if (digitalRead(s3 == LOW))
  {
    byte s3 = 0b00000100;
    byte switchState = switchState | s3;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  } 
  if (digitalRead(s4 == LOW))
  {
    byte s4 = 0b00001000;
    byte switchState = switchState | s4;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  }
    if (digitalRead(s5 == LOW))
  {
    byte s5 = 0b00010000;
    byte switchState = switchState | s5;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  }
   if (digitalRead(s6 == LOW))
  {
    byte s6 = 0b00100000;
    byte switchState = switchState | s6;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  } 
  if (digitalRead(s7 == LOW))
  {
    byte s7 = 0b01000000;
    byte switchState = switchState | s7;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  } 
  if (digitalRead(s8 == LOW))
  {
    byte s8 = 0b10000000;
    byte switchState = switchState | s8;
    bt.write(switchState);
  }
  else
  {
    byte switchState = switchState & 0x00;
    bt.write(switchState);
  }

  //    delay(10);
  //      Serial.print("\nrx: ");
  //      Serial.print(NRx);
  //    Serial.print("\tstart: ");
  //    Serial.print(start);
  //    Serial.print("\txh: ");
  //    Serial.print(xh);
  //    Serial.print("\txl: ");
  //    Serial.println(xl);
}
