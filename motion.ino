#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;
const int ledPin = 8;
const int buzzerPin = 9;
const float threshold = 20.0;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Connected!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(1000);
}
void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float roll = atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;
  float pitch = atan2(-a.acceleration.x,
                      sqrt(a.acceleration.y * a.acceleration.y +
                           a.acceleration.z * a.acceleration.z)) * 180 / PI;
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("  Pitch: ");
  Serial.println(pitch);
  if (abs(roll) > threshold || abs(pitch) > threshold) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  delay(100);
}