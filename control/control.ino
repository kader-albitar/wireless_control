#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
// RS, E, D4, D5, D6, D7

const byte rows = 4, cols = 4;
char keys[rows][cols] = {{'1','2','3','A'},
                         {'4','5','6','B'},
                         {'7','8','9','C'},
                         {'*','0','#','D'}};
byte rowPins[rows] = {2, 3, 4, 5};
byte colPins[cols] = {6, 7, 8, 9};
Keypad control = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int buzz = 10, gled = 11, rled = 12;

char gett, key, alarm;

int temp, humidity, light, gas;

int f;

void setup() {
  Serial.begin(38400);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  pinMode(gled, OUTPUT);
  pinMode(rled, OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(gled, HIGH);
  digitalWrite(rled, LOW);
  digitalWrite(buzz, LOW);
  lcd.print("Initializing...");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Running fine!");
}

void loop() {
  if(Serial.available() > 0){
    f = Serial.read();
  }
  gett = control.getKey();
  readKeypad();
  sender();
}

void readKeypad(){
  switch(gett){
    case '1':
    key = '1';
    break;
    case '2':
    key = '2';
    break;
    case '3':
    key = '3';
    break;
    case '4':
    key = '4';
    break;
    case '5':
    key = '5';
    break;
    case '6':
    key = '6';
    break;
    case '7':
    key = '7';
    break;
    case '8':
    key = '8';
    break;
    case '9':
    key = '9';
    break;
    case '0':
    key = '0';
    break;
    case '*':
    key = '*';
    break;
    case '#':
    key = '#';
    break;
    case 'A':
    key = 'A';
    break;
    case 'B':
    key = 'B';
    break;
    case 'C':
    key = 'C';
    break;
    case 'D':
    key = 'D';
    break;
  }
}

void sender(){
  switch(key){
    case '1':
    Serial.write('1');
    if(Serial.available() > 0){
      gas = Serial.read();
    }
    if(gas == 'g'){
      digitalWrite(gled, LOW);
      digitalWrite(rled, HIGH);
      digitalWrite(buzz, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gas leakage");
      lcd.setCursor(0, 1);
      lcd.print("detected!");
    }
    else{
      digitalWrite(gled, HIGH);
      digitalWrite(rled, LOW);
      digitalWrite(buzz, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Running fine!");
    }
    delay(100);
    break;
    
    case '2':
    Serial.write('2');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LEDs turned ON!");
    delay(100);
    break;
    
    case '3':
    Serial.write('3');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan turned ON!");
    delay(100);
    break;
    
    case '4':
    Serial.write('4');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door opened!");
    delay(100);
    break;
    
    case '5':
    Serial.write('5');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door closed!");
    delay(100);
    break;
    
    case 'A': // read temperature
    Serial.write('A');
    if(Serial.available() > 0){
      temp = Serial.read();
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    lcd.print(" C");
    delay(100);
    break;
    
    case 'B': // read humidity
    Serial.write('B');
    if(Serial.available() > 0){
      humidity = Serial.read();
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity:");
    lcd.setCursor(0, 1);
    lcd.print(humidity);
    lcd.print(" %");
    delay(100);
    break;
    
    case 'C': // read light
    Serial.write('C');
    if(Serial.available() > 0){
      light = Serial.read();
    }
    if(light == 'D'){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dark");
    }
    else if(light == 'd'){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dim");
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bright");
    }
    delay(100);
    break;
    
    case 'D': // read gas
    Serial.write('D');
    if(Serial.available() > 0){
      gas = Serial.read();
    }
    if(gas == 'g'){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gas leakage");
      lcd.setCursor(0, 1);
      lcd.print("detected!");
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No gas detected!");
    }
    delay(100);
    break;
    
    case '0':
    digitalWrite(rled, LOW);
    digitalWrite(buzz, LOW);
    Serial.write('0');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Running fine!");
    digitalWrite(gled, HIGH);
    delay(100);
    break;
  }
}
