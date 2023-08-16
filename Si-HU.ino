#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
Servo Myservo;
int pos;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd (0x27, 16, 2);
#define echoPin 2
#define trigPin 3
long duration;
int distance;
float suhu;
bool state = 0;
bool laststate = 0;
void buka(){
for(pos=0;pos<=110;pos++){
Myservo.write(pos);
delay(15);
}
}
void tutup(){
for(pos=90;pos>=0;pos--){
Myservo.write(pos);
delay(15);
}
}
void setup() {
mlx.begin();
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Myservo.attach(4);
Myservo.write(0);
lcd.init();
lcd.backlight();
}
void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
if(distance <= 10){
state = 1;
}
else{
state = 0;
}
lcd.clear();
lcd.setCursor(0,1);
lcd.print("Suhu: ");
if (state == 1 && laststate != state){
suhu = mlx.readObjectTempC();
Serial.print("Suhu: ");
Serial.print(suhu);
Serial.println(" C");
if(suhu < 37){
lcd.setCursor(0,0);
lcd.print("SUHU NORMAL");
lcd.setCursor(6,1);
lcd.print(suhu);
lcd.print(" C");
buka();
delay(1500);
tutup();
}
else{
lcd.setCursor(0,0);
lcd.print("SUHU PANAS");
lcd.setCursor(6,1);
lcd.print(suhu);
lcd.print(" C");
}
}
else{
lcd.setCursor(0,0);
lcd.print("Dekatkan Tangan Anda");
}
laststate = state;
delay(1000);
}