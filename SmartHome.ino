#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(2, 3); // RX, TX
const int light1 = 13;
const int light2 = 12;
volatile String mode = "auto";
const int pirPin = 7;
int motion = 0;
bool pirState = LOW;
String value;

void setup() {

pinMode(light1, OUTPUT);
pinMode(light2, OUTPUT);
pinMode(pirPin, INPUT);
Serial.begin(9600);
Bluetooth.begin(9600);
Serial.println("Waiting for data...");

}


void loop() {

if(Bluetooth.available() > 0) {

  value = Bluetooth.readString();
   
   if(value == "auto" || value == "controlled"){

    mode = value;

   }
  Serial.println(value);

  }

  if(mode == "controlled"){

//send birghtness value as text on bluetooth to the app
int ldr = analogRead(A0);
   Bluetooth.print(String(ldr));
    delay(10);
   


       if(value == "0"){
      digitalWrite(light1, LOW);
     }
    else if (value == "1") {
      digitalWrite(light1, HIGH);
     }
     else if (value == "2") {
      digitalWrite(light2, LOW);
     }
     else if (value == "3") {
      digitalWrite(light2, HIGH);

     }
   
  }

 if (mode == "auto") {
 
//read data from photolight sensor and determine if 0 ir 1 or 2 lights should be on
int ldr = analogRead(A0);

//read data from PIR motion sensor if no motion occurs in 15 mintutes turn lights off
motion = digitalRead(pirPin); // Read the PIR sensor output

if (ldr < 100 && motion == HIGH) {
  digitalWrite (light1, HIGH);
  digitalWrite(light2, LOW);
}

else if (ldr > 500 && motion == HIGH){
    digitalWrite (light1, HIGH);
  digitalWrite(light2, HIGH);
}

else if (motion == LOW) {
   digitalWrite (light1, LOW);
  digitalWrite(light2, LOW);
}


//display motion status
  if (motion == HIGH && pirState == LOW) {
    Serial.println("Motion detected!");
    pirState = HIGH;
  }
  else if (motion == LOW && pirState == HIGH) {
    Serial.println("No motion.");
    pirState = LOW;
  }
 

//send birghtness value as text on bluetooth to the app
      Bluetooth.print(ldr);
delay(100);

     }

}
