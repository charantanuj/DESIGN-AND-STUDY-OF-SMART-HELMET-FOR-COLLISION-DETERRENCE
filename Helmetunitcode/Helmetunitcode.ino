#include <LiquidCrystal.h>
#define gas_Pin 7
#define touch_Pin 5
#define trigPin 3
#define echoPin 2

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
int pos = 0; 
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int touch_value;
int gas_value;
void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(32, 2); 
  pinMode(6,OUTPUT);
}
void loop()
{   long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  gas_value = digitalRead(gas_Pin);
  touch_value=digitalRead(touch_Pin);
  if(gas_value==1 && touch_value==1 )
  {
   
   lcd.setCursor (0, 1);
   lcd.print("NOT TRANSMITTED");
   
      if(distance <30)
      {
        digitalWrite(6,HIGH);
      }
   lcd.display();
   }
   else if(gas_value==0 && touch_value==1 )
   {
   lcd.setCursor (0, 1);
    lcd.print("SIGNAL IS TRANSMITTED ");
     
      if(distance <100)
      {
        digitalWrite(6,HIGH);
    }
    
    lcd.display();
   }
   else if(gas_value==0 && touch_value==0)
   {
    digitalWrite(6,LOW);
    lcd.setCursor (0, 1);
    lcd.print("NOT TRANSMITTED ");
    lcd.display();
   }
    else 
   {
    digitalWrite(6,LOW);
    lcd.setCursor (0, 1);
    lcd.print("NOT TRANSMITTED ");
    lcd.display();
   }
   {
    lcd.setCursor(1, 0);
  lcd.print("Distance= ");
 
  lcd.print(distance);
  lcd.print("cm");
  
    Serial.print(distance);
    Serial.println(" cm");
   delay(500);
   
} 
}
