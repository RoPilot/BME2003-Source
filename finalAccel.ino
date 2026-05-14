#include<Wire.h>

#include<MPU9250.h>

 

const int MPU_addr1 = 0x68;

float xa, ya, za, roll, pitch;

 

void setup() {

  Wire.begin();

  Wire.beginTransmission(MPU_addr1);                 

  Wire.write(0x6B);                                  

  Wire.write(0);

  Wire.endTransmission(true);                        

  Serial.begin(9600);

}

 

void loop() {

 

  Wire.beginTransmission(MPU_addr1);

  Wire.write(0x3B);  

  Wire.endTransmission(false); 

  Wire.requestFrom(MPU_addr1, 6); 

  int t = Wire.read();

  xa = (t << 8) | Wire.read();

  t = Wire.read();

  ya = (t << 8) | Wire.read();

  t = Wire.read();

  za = (t << 8) | Wire.read();

 

  roll = atan2(ya , za) * 180.0 / PI;

  pitch = atan2(-xa , sqrt(ya * ya + za * za)) * 180.0 / PI; 

 

  Serial.print("roll = ");

  Serial.println(roll,1);

  Serial.print("pitch = ");

  Serial.println(pitch,1);
  Serial.println("--------------");

  delay(400);

}
