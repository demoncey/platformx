


#include <DHT.h>
#include "src/Bluetooth/Bluetooth.h"
#include "src/com/com.h"
#include "src/supervisor/supervisor.h"
#include "src/supervisor/task.h"
#include "src/utils/smart.h"

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
void callback_temporary();
//void get_messurment();


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
  bT.setPriority(P_HIGH);
  
  supervisor.addTask(t1);
  supervisor.addTask(t2);
  supervisor.addTask(t2);
  supervisor.addTask(t3);
  supervisor.addTask(t4);
  supervisor.addTask(t5);
  supervisor.addTask(t6);
  supervisor.addTask(gmT);
  supervisor.addTask(sbT);
  sbT.setPriority(P_HIGH);
}


void loop() {
  smart_ptr<TestPtr> test(new TestPtr("Smart pointer 1"));
  supervisor.execute();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("smart_ptr name:");
  lcd.setCursor(0, 1);
  lcd.print(test->name);
  delay(2000);
  
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
    if(recived_msg== String('6')){
      Task txxx(&callback1);
      supervisor.addTask(txxx);
    }

    if(recived_msg== String('t')){
      Task *temp=new Task(&callback_temporary);
      temp->setMode(MODE_ONCE);
      supervisor.addTask(*temp);
    }

    
    if(recived_msg== String('s')){
      supervisor.suspendAll();
    }
    if(recived_msg== String('r')){
      supervisor.resumeAll();
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
  com.send("send_msg executed");
}

void get_messurment() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temp :" + String(t) + " *C");
  lcd.setCursor(0, 1);
  lcd.print("hum :" + String(h) + " %");
  com.send("get_messurment executed");
}



void callback1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 1");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("task 1 executed");
}

void callback2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 2");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("task  2 executed");
}


void callback3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 3");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("task 3 executed");
}

void callback4() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 4");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("task 4 executed");
}


void callback5() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 5");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("task 5 executed");
}



void callback6() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("task 6");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("task 6 executed");
}


void callback_temporary() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temporary task");
  lcd.setCursor(0, 1);
  lcd.print("executed");
  com.send("temporary task executed");
  delay(5000);
}






void change_state(Task &task){
  if(task.isRunning()){
    task.suspend();
  }else{
    task.resume();
  }
}




