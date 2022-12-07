int SW = 8;
int VRx = A0;
int VRy = A1;
int x, y, x1, y1, NRx, NRy, ax, ay;
bool flag;

void setup()
{
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() 
{
  NRx = analogRead(A0);
  NRy = analogRead(A1);
  ax = NRx;
  ay = NRy;
  x1 = map(ax, 0, 1024, -512, 512);
  y1 = map(ay, 0, 1024, -512, 512);
  if (digitalRead(SW) == 0)
  {
    flag = 1;
    VRx = analogRead(A0);
    VRy = analogRead(A1);
    x1 = VRx;
    y1 = VRy;
    Serial.println("****Calibration Sequence Started****");
    Serial.println("****Keep Joystick in the centre position****");
    while (flag)
    {
      VRx = analogRead(A0);
      VRy = analogRead(A1);
      delay(100);
      x = VRx - x1;
      y = VRy - y1;
      Serial.println("Corrected Reading");
      Serial.print(" | ");
      Serial.print("X-axis: ");
      Serial.print(x);
      Serial.print(" | ");
      Serial.print("Y-axis: ");
      Serial.print(y);
      Serial.println(" | ");
      delay(200);
    }
  }
  Serial.println("Init Reading");
  Serial.print(" | ");
  Serial.print("X-axis: ");
  Serial.print(NRx);
  Serial.print(" | ");
  Serial.print("Y-axis: ");
  Serial.print(NRy);
  Serial.println(" | ");
  delay(200);
}
