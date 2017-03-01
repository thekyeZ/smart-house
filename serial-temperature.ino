/*
 * Author: Przemysław Urbaniak (kyeZ)
 * Date: 01.03.2017
 * Version: 0.0.1
 * Decription: 
 * Script for arduino for garage control system (mini smart home system)
 */

#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS_1 3
#define DHTPIN 2
#define DHTTYPE DHT11

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire1(ONE_WIRE_BUS_1);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire1);
DHT dht(DHTPIN, DHTTYPE);



// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(7, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT_PULLUP);

  pinMode(12, INPUT_PULLUP); //alarm switch
  
  // Start up the library
  sensors.begin();
  dht.begin();

  //Alarm (temp setup for gsm commands to arm and disarm alarm)
  int alarmArmed = 0;
  
  while(!Serial);
}

// the loop function runs over and over again forever
void loop() {

  int alarmArmed = digitalRead(12); //GSM command here
  
  Serial.print("Alarm Indicator: ");
  Serial.println(digitalRead(12));

  if(alarmArmed == 1 and digitalRead(5) == 1) { //alarm
      Serial.println("ALARM!");
      delay(2000);
  }
  
  sensors.requestTemperatures(); // Send the command to get temperatures
  float t = dht.readTemperature();  // odczyt temperatury
  float h = dht.readHumidity();     // odczyt wilgotności powietrza

  //Dallas
  Serial.println(sensors.getTempCByIndex(0)); 

  //dht
  Serial.print("Wilgotnosc: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");

  Serial.println(digitalRead(4));
  Serial.println(digitalRead(5));
  
//  if(sensors.getTempCByIndex(0) > 28){
//    for(int i=8; i<12; i++){
//      digitalWrite(i, HIGH);
//      delay(200);
//      digitalWrite(i, LOW);
//    }
//  }

//  if(digitalRead(7) == LOW){
//    digitalWrite(8, LOW);
//    delay(500);
//    digitalWrite(8, HIGH);
//  }

    if(digitalRead(4) == HIGH){
      turnAllOn();
    }else{
      
      
      
      if(sensors.getTempCByIndex(0) >= 27){
        digitalWrite(8, HIGH);
      }else{
        digitalWrite(8, LOW);
      }
  
      if(t >= 25){
        digitalWrite(11, HIGH);
      }else{
        digitalWrite(11, LOW);
      }
   
    }  
  
  delay(500); //one minute
}

void turnAllOn() {
       for(int i=8; i<12; i++){
        digitalWrite(i, HIGH);
      }
}

void turnAllOff() {
      for(int i=8; i<12; i++){
        digitalWrite(i, LOW);
      }
}


