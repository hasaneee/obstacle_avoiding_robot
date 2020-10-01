/*
 * Project Name : Voice Control Obstacle Avoding Robot
 * Author: Mahamudul Hasan
 * MCU: Arduino Nano
 * IDE: Arduino IDE
 * Date: 24/9/2020
 */
 
 String voice;
 int i =0;
 
 int trigger = 9;
 int echo = 10;

 int leftMotorPin1 = 4;
 int leftMotorPin2 = 5;
 int rightMotorPin1 = 6;
 int rightMotorPin2 = 7;

long duration, distance;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
}

void loop() {
  
  if(Serial.available() && i==0){
    voice = "";
    i++;
    }
  while(Serial.available()){
    delay(10);
    
    char c = Serial.read();
    if(c == '#'){
      break;
    }
    voice += c;
  }

  if(voice.length() > 0){
    Serial.println(voice);
    delay(1000);
  }
  
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = 0.0340*duration/2;

  if(distance > 5){ //Robot Move Forward
      forward();
   }

   if(distance <= 5){
      stopCar();
      delay(500);
      backward();
      delay(500);
      stopCar();
      delay(100);
      left();
      delay(700);
      //forward();
   }

   if(distance > 5 && voice.length() > 0 && voice == "*forward"){
      forward();
      delay(500);
   }
   if(distance > 5 && voice.length() > 0 && voice == "*backward"){
       backward();
       delay(500);
   }
   if(distance > 5 && voice.length() > 0 && voice == "*left"){
      left();
      delay(700);
      voice = "";
   }
   if(distance > 5 && voice.length() > 0 && voice == "*right"){
     right();
     delay(700);
     voice = "";
   }
   if(distance > 5 && voice.length() > 0 && voice == "*stop"){
     stopCar();
   }

i = 0;

}

void forward(){  //Robot Move Forward
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void backward(){  //Robot Move Backward
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
 }
void stopCar(){  //Robot Stop
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}
void left(){ //Robot Move Left
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  }
void right(){ //Robot Move Right
   digitalWrite(leftMotorPin1, LOW);
   digitalWrite(leftMotorPin2, LOW);
   digitalWrite(rightMotorPin1, LOW);
   digitalWrite(rightMotorPin2, HIGH);
  }
  
