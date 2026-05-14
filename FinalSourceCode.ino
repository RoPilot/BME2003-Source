// GYRO ACCELEROMETER
#include<Wire.h>
#include<MPU9250.h>

// TEMPERATURE SENSOR
#define B 3900

// HEARTBEAT SENSOR
#define samp_siz 4
#define rise_threshold 4

// LCD DISPLAY
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcdMessage(String line1, String line2) {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(line1);

  lcd.setCursor(0, 1);
  lcd.print(line2);
}

//
const int MPU_addr1 = 0x68;
float xa, ya, za, roll, pitch;

void setup() {

  // ACCELEROMETER GYRO SETUP
  Wire.begin();
  Wire.beginTransmission(MPU_addr1);                 
  Wire.write(0x6B);                                  
  Wire.write(0);
  Wire.endTransmission(true);    
                      
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcdMessage("Starting..", "");
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

  lcdMessage("Roll: " + String(roll, 1),
           "Pitch: " + String(pitch, 1));

  delay(400);

}
