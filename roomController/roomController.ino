#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

char auth[] = "QYGtwYnSKbdmRWejSz8SbyvRUPvyGLIs";

#define W5100_CS  10
#define SDCARD_CS 4

#define ONPIN 4 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
BlynkTimer timer;
int r, g, b;
int FADESPEED =  5;
int Status = 0;

void setup(){
  Serial.begin(9600);
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
  pinMode(ONPIN, INPUT);

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  Blynk.begin(auth);
  timer.setInterval(3, controller);
  Blynk.virtualWrite(V0,FADESPEED);
}
void loop(){
  Blynk.run();
  timer.run();
}
BLYNK_WRITE(V0){//SPEED
  FADESPEED = param.asInt();
}
BLYNK_WRITE(V2){//ZEBRA
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  Status = 2;
}
BLYNK_WRITE(V1){//FADE
  Status = param.asInt();
}
void off(){//APAGAR
  Status = 0;
}
void controller(){
  if(Status == 0){
    analogWrite(REDPIN,0);
    analogWrite(GREENPIN,0);
    analogWrite(BLUEPIN,0);
  }
  else if(Status == 2){
    analogWrite(REDPIN,r);
    analogWrite(GREENPIN,g);
    analogWrite(BLUEPIN,b);
    Blynk.virtualWrite(V1,LOW);
  }else if(Status == 1){  
    fade();
  }
}
void fade(){
    for (r = 0; r < 256; r++) { // fade from blue to violet
      analogWrite(REDPIN, r);
      delay(FADESPEED);
    } 
    for (b = 255; b > 0; b--) { // fade from violet to red
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    } 
    for (g = 0; g < 256; g++) {  // fade from red to yellow
      analogWrite(GREENPIN, g);
      delay(FADESPEED);
    } 
    for (r = 255; r > 0; r--) { // fade from yellow to green
      analogWrite(REDPIN, r);
      delay(FADESPEED);
    } 
    for (b = 0; b < 256; b++) {  // fade from green to teal
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    } 
    for (g = 255; g > 0; g--) { // fade from teal to blue
      analogWrite(GREENPIN, g);
      delay(FADESPEED);
    }
}
