#include <TinyGPS.h>
#include <SoftwareSerial.h>
#define vibr_pin 3
SoftwareSerial SIM900(7, 8);

TinyGPS gps;  //Creates a new instance of the TinyGPS object

int enA=12;
int ln1=11;
int ln2=10;

int enB=4;
int ln3=6;
int ln4=5;
int val;
void setup()
{
  Serial.begin(9600);
  SIM900.begin(9600);  
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(ln1,OUTPUT);
  pinMode(ln2,OUTPUT);
  pinMode(ln3,OUTPUT);
  pinMode(ln4,OUTPUT);
 
}


  


void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
 val=digitalRead(vibr_pin);
  motor1();

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }

  if (newData &&  val==1 )      //If newData is true
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    SIM900.print("Accident detected\r"); 
    //delay(400);
    SIM900.println("message sent to \"+918008772677\"");// recipient's mobile number with country code
    //delay(300);
    SIM900.print("Latitude = ");
    SIM900.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    SIM900.print(" Longitude = ");
    SIM900.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
   // delay(200);
    SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
    //delay(200);
    SIM900.println();
    

  }else
  {SIM900.println("Accident is not detected");
  }
 
  Serial.println(failed);
 // if (chars == 0)
   // Serial.println("** No characters received from GPS: check wiring **");
}
void motor1()
{
  digitalWrite(enA,HIGH);
  digitalWrite(ln1,LOW);
  digitalWrite(ln2,HIGH);
  delay(500);
}
