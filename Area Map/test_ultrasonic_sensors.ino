/*const int trigPin1 = 5;
const int echoPin1 = 6;

const int trigPin2 = 7;
const int echoPin2= 8;

const int trigPin3 = 9;
const int echoPin3= 10;

const int trigPin4 = 11;
const int echoPin4 = 12;
*/
const int trigPin1 = 4; //D2
const int echoPin1 = 0; //Front D3

const int trigPin2 = 16; //D0
const int echoPin2= 5; //Right D1

const int trigPin3 = 12; //D6
const int echoPin3= 13; //Back D7

const int trigPin4 = 2; //D4
const int echoPin4 = 14; //Left D5
long duration1, duration2, duration3, duration4;
long distance1, distance2, distance3, distance4;
//int t=0;

void setup() {
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT); 

pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT); 

pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT); 

pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT); 

Serial.begin(9600); // connect serial 
Serial.println("Ultrasonic Started"); 

}

void loop() 
{
//delay(3000);
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1=duration1/58.2;


digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2=duration2/58.2;


digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);
distance3=duration3/58.2;

digitalWrite(trigPin4, LOW);
delayMicroseconds(2);
digitalWrite(trigPin4, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin4, LOW);
duration4 = pulseIn(echoPin4, HIGH);
distance4=duration4/58.2;

//Serial.print(t);
//Serial.print(",");
Serial.print(distance1);
Serial.print(",");
Serial.print(distance2);
Serial.print(",");
Serial.print(distance3);
Serial.print(",");
Serial.print(distance4);
Serial.print("\n");
//delay(1000);
//t=t+1;
}
