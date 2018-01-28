


#include <DHT.h>
#include "src/Bluetooth/Bluetooth.h"
#include "src/com/com.h"
#include "src/supervisor/supervisor.h"
#include "src/supervisor/task.h"
#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD




#define RX 12 //tx blue
#define TX 11 //rx blue   
#define LED_GREEN 10
#define DHT11PIN 9
#define DHTTYPE DHT11

Bluetooth bluetooth(RX, TX, 500, LED_GREEN, LED_BUILTIN);
Com com(100);
DHT dht(DHT11PIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

Supervisor supervisor("super1");

void recived_msg();
void send_msg();
void callback1();
void callback2();
void callback3();
void callback4();
void callback5();
void callback6();
void get_messurment();


Task bT(&recived_msg);
Task sbT(&send_msg);;
Task t1(&callback1,true);
Task t2(&callback2,true);
Task t3(&callback3,true);
Task t4(&callback4,true);
Task t5(&callback5,true);
Task t6(&callback6,true);


Task gmT(&get_messurment);

void setup() {
  //leds
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  //comunications
  bluetooth.init();
  com.init();
  //initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("platformx!");

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  supervisor.addTask(bT);
  bT.setPriority(P_IMMORTAL);
  
  supervisor.addTask(t1);
  supervisor.addTask(t2);
  supervisor.addTask(t2);
  supervisor.addTask(t3);
  supervisor.addTask(t4);
  supervisor.addTask(gmT);
  supervisor.addTask(sbT);
  sbT.setPriority(P_IMMORTAL);
  supervisor.addTask(t5);
  supervisor.addTask(t6);


  
}


void loop() {
  //supervisor.run();
  supervisor.execute();
}



void recived_msg() {

  String recived_msg = bluetooth.recv();
  if (recived_msg != "") {
    if(recived_msg== String('1')){
      change_state(t1);
    }
    if(recived_msg== String('2')){
      change_state(t2);
    }
    if(recived_msg== String('3')){
      change_state(t3);
    }
    if(recived_msg== String('4')){
      change_state(t4);
    }
    if(recived_msg== String('5')){
      change_state(t5);
    }
    if(recived_msg== String('s')){
      supervisor.suspend();
    }
    if(recived_msg== String('r')){
      supervisor.resume();
    }




    
    com.send("bluetooth message was :" + recived_msg);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("bluetooth msg:");
    lcd.setCursor(0, 1);
    lcd.print(recived_msg);
  }else{
    com.send("bluetooth nothing recv");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("bluetooth msg:");
    lcd.setCursor(0, 1);
    lcd.print("nothing");
  }
}



void send_msg() {
  int iRandom = random(1, 1000000000);
  String sRandom = String(iRandom, HEX);
  bluetooth.send("Sending msg id:" + sRandom);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending msg id:");
  lcd.setCursor(0, 1);
  lcd.print(sRandom );
}

void get_messurment() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  com.send("temp :" + String(t) + " *C");
  com.send("hum :" + String(h) + " %");
  com.send("get_messurment executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temp :" + String(t) + " *C");
  lcd.setCursor(0, 1);
  lcd.print("hum :" + String(h) + " %");
}



void callback1() {

  com.send("task 1 executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 1");
  lcd.setCursor(0, 1);
  lcd.print("executed");
}

void callback2() {

  com.send("task  2 executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 2");
  lcd.setCursor(0, 1);
  lcd.print("executed");
}


void callback3() {

  com.send("task 3 executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 3");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  //t2.suspend();
}

void callback4() {
  com.send("task 4 executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 4");
  lcd.setCursor(0, 1);
  lcd.print("executed");
}


void callback5() {
  com.send("task 5 executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 5");
  lcd.setCursor(0, 1);
  lcd.print("chain executed");
}



void callback6() {
  com.send("task 6 executed");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 6");
  lcd.setCursor(0, 1);
  lcd.print("chain executed");
}






void change_state(Task &task){
  if(task.isRunning()){
    task.suspend();
  }else{
    task.resume();
  }
}



