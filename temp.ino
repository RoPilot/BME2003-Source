#define B 3900

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  float temperature_calc;
  float RT;

val = analogRead(1);
RT = 1023./val - 1;
temperature_calc = (1.0 / (((log((10000/RT)/10000))/B)+1.0/(25+273.15)))-273.15;

Serial.println(temperature_calc);
delay(100);
}
