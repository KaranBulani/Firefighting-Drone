/*


*/

#include <LiquidCrystal.h>
const int trigPin1 = A0;
const int echoPin1 = A1;

const int trigPin2 = A2;
const int echoPin2 = A3;

const int trigPin3 = A4;
const int echoPin3= A5;

const int trigPin4 = 7;
const int echoPin4= 8;
int s;
const int trigPin5 = 9;
const int echoPin5= 10;
int mini;

long duration1,duration2,duration3,duration4,duration5,duration6;
long distance1,distance2,distance3,distance4,distance5,distance6;
int f1,f2,f3,f4,f5,f6;
int Contrast=150;
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  analogWrite(6,Contrast);

lcd.begin(16,2);

lcd.print("Done");
  // initialize digital pin 13 as an output.
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);
  
  
  lcd.begin(16,2);

  lcd.print("Ready!");
  
}

void loop() 
{
delay(3000);
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);


digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);

digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);


digitalWrite(trigPin4, LOW);
delayMicroseconds(2);
digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);
duration4 = pulseIn(echoPin4, HIGH);

digitalWrite(trigPin5, LOW);
delayMicroseconds(2);
digitalWrite(trigPin5, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin5, LOW);
duration5 = pulseIn(echoPin5, HIGH);



Serial.print(duration1);
Serial.print("\n");
distance1= duration1/58.2;
distance2= duration2/58.2;
distance3=duration3/58.2;
distance4=duration4/58.2;
distance5=duration5/58.2;
f1=0;
f2=0;
f3=0;
f4=0;
f5=0;
Serial.print("Distance1 is ");
Serial.print(distance1);
Serial.print("\n-----\n");
Serial.print("Distance2 is ");
Serial.print(distance2);
Serial.print("\n-----\n");
Serial.print("Distance3 is ");
Serial.print(distance3);
Serial.print("\n-----\n");
Serial.print("Distance4 is ");
Serial.print(distance4);
Serial.print("\n-----\n");
Serial.print("Distance5 is ");
Serial.print(distance5);
Serial.print("\n-----\n");

if(distance1<= 15)
{
  f1=1;
}

if(distance2<= 15)
{
    f2=1;
}

if(distance3<= 15)
{
    f3=1;
}

if(distance4<= 15)
{
  f4=1;
}

if(distance5<= 15)
{
   f5=1;
}
s=f1+f2+f3+f4+f5;
if(s>=2)
{
 mini=min(min(min(distance1,distance2),min(distance3,distance4)),distance5);
 if(distance1==mini){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Left!");
  delay(100);
  }
  else if(distance2==mini){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Back!");
  delay(100);
  }
  else if(distance3==mini){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Right!");
  delay(100);
  }
  else if(distance4==mini){
    lcd.setCursor(0,1);
  lcd.print("Hover UP!");
  delay(100);
  }
  else if(distance5==mini){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Ahead!");
  delay(100);
  } 
  
  }
else if(s==1){
  if(f1==1){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Left!");
  delay(100);
  }
  else if(f2==1){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Back!");
  delay(100);
  }
  else if(f3==1){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Right!");
  delay(100);
  }
  else if(f4==1){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Up!");
  delay(100);
  }
  else if(f5==1){
    lcd.setCursor(0,1);
    lcd.clear();
  lcd.print("Hover Ahead!");
  delay(100);
  }
  }
  else{
    lcd.clear();
  lcd.print("SAFE");
  
  delay(100);
    }

}
