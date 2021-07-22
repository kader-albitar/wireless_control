#include <Servo.h>
#include <dht.h>
Servo door;
dht ht;
#define dht A0
int ldr = 2, led = 6,ledLevel, light;
int temp, fan = 5;
int humidity;
int gasSensor = 1, gas;
char order;

int f;

void setup() {
  Serial.begin(38400);
  door.attach(3);
  door.write(0);
  pinMode(led, OUTPUT);
  pinMode(fan, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    f = Serial.read();
  }
  // Read sensors
  light = analogRead(ldr);
  ht.read11(dht);
  temp = ht.temperature;
  humidity = ht.humidity;
  gas = analogRead(gasSensor);
  
  if(Serial.available() > 0){
    order = Serial.read();
  }
  reader();
}

void automate(){
  // Light
  light = constrain(light, 220, 650);
  ledLevel = map(light, 220, 650, 255, 0);
  analogWrite(led, ledLevel);
  // Temp
  if(temp > 30){
    digitalWrite(fan, HIGH);
  }
  else{
    digitalWrite(fan, LOW);
  }
  // Gas
  if(gas > 250){
    Serial.write('g');
  }
  else{
    Serial.write('n');
  }
}

void reader(){
  switch(order){
    case '1': // automate
    automate();
    break;
    
    case '2': // turn on LED
    digitalWrite(led, HIGH);
    break;
    
    case '3': // turn on fan
    digitalWrite(fan, HIGH);
    break;
    
    case '4': // open door
    door.write(100);
    delay(200);
    door.detach();
    break;
    
    case '5': // close door
    door.write(0);
    delay(200);
    door.detach();
    break;
    
    case 'A':
    Serial.write(temp);
    break;
    
    case 'B':
    Serial.write(humidity);
    break;
    
    case 'C':
    if(light < 300){
      Serial.write('D');
    }
    else if(light >= 300 && light < 550){
      Serial.write('d');
    }
    else{
      Serial.write('b');
    }
    break;
    
    case 'D':
    if(gas > 250){
      Serial.write('g');
    }
    else{
      Serial.write('n');
    }
    break;
    
    case '0': // reset
    digitalWrite(led, LOW);
    digitalWrite(fan, LOW);
    door.attach(3);
    break;
  }
}
