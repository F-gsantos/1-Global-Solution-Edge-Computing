#include <LiquidCrystal.h>
#include <math.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
}
sensors_event_t event;

void ldrConversion() {
  //transforma o valor do ldr e o converte para lux
  int analogValue = analogRead(A0);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  // Print no valor convertido
  lcd.print("Lux: ");
  lcd.print(round(lux));
  delay(2000);
  lcd.clear();
}
void ntcConversion() {
  //transforma o valor do ntc e o converte para celsius
  const float BETA = 3950; 
  int analogValue = analogRead(A1);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  // Print no valor convertido
  lcd.print("Celsius: ");
  lcd.print(round(celsius));
  delay(2000);
  lcd.clear();
}
void mpuConversion(){
  // Print aceleração horizontal
  lcd.print("X: ");
  lcd.print(round(event.acceleration.x));
  lcd.print("m/s^2");
  delay(2000);
  lcd.clear();
  // Print aceleração vertical
  lcd.print("Y: ");
  lcd.print(round(event.acceleration.y));
  lcd.print("m/s^2");
  delay(2000);
  lcd.clear();
  // Print aceleração no eixo Z
  lcd.print("Z: ");
  lcd.print(round(event.acceleration.z));
  lcd.print("m/s^2");
  delay(2000);
  lcd.clear();
}
void loop() {
  mpu.getAccelerometerSensor()->getEvent(&event);
  ldrConversion();
  ntcConversion();
  mpuConversion();
}
