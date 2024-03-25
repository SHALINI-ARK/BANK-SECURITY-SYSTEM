#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 20, 4);

#define in 4
#define out 3
int count = 0;

int vib = 5;
int buzzer = 13;

const int trigPin = 7;
const int echoPin = 6;
long duration;
int distance;

void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO OUR ");
  lcd.setCursor(0, 1);
  lcd.print("    BANK PROJECT");
  delay(2000);
  lcd.clear();
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  //pinMode(vib, INPUT);
  //pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  lcd.clear();
}

void loop()

{ IR();
  VS();
  hcSR1();
}
void IR()
{
  int in_value = digitalRead(in);
  int out_value = digitalRead(out);
  if (in_value == LOW)
  {
    count++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Person In Bank:");
    lcd.setCursor(16, 0);
    lcd.print(count);
    delay(200);
  }
  if (out_value == LOW)
  {
    count--;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Person In Bank:");
    lcd.setCursor(16, 0);
    lcd.print(count);
    delay(200);
  }
  if (count == 0)
  {
    lcd.clear();
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Person In Bank:");
    lcd.setCursor(15, 0);
    lcd.print("No");
    //delay(200);
  }

  else
  {
    lcd.clear();
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Person In Bank:");
    lcd.setCursor(16, 0);
    lcd.print(count);
    delay(1000);
  }
}

void VS()
{
  if (digitalRead(vib) == LOW)
  {
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Bank Locker   :");
    lcd.setCursor(15, 1);
    lcd.print("Danger");
    delay(5000);
  }
  else
  {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Bank Locker   :");
    lcd.setCursor(15, 1);
    lcd.print("safe");
   // delay(200);
  }
}

void hcSR1() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  lcd.setCursor(0, 2);
  lcd.print("Person Near Bank:");
  lcd.setCursor(17, 2);
  lcd.print(distance);
//  lcd.setCursor(18, 2);
//  lcd.print(" MM");
  Serial.print("Distance from the Bank = ");
  Serial.print(distance);
  Serial.println(" MM");
  delay(1000);
}
