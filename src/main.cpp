#include <Arduino.h>
#include "web_porton.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define PORT_RELAY_WD1  13 // PORT IS D7 
#define SSID_IAR_LOCAL ""
#define PASS_SSID_LOCAL ""



void IRAM_ATTR relayManagement(); 
void connect_iar_local()  ; 
bool isConnect() ; 
void indexHTML() ; 
void abirPorton() ; 
void enableTimer1() ; 
ESP8266WebServer server_porton_iar(80);    // puerto HTTP 


enum state_relay {ON,OFF} ; 
bool isr_enabled = false ; 
state_relay st_relay = OFF ;  

void setup() {
  Serial.begin(9600) ; 
  pinMode(PORT_RELAY_WD1,OUTPUT) ; 
  connect_iar_local() ; 
  server_porton_iar.on("/", indexHTML);
  server_porton_iar.on("/open",HTTP_GET ,abirPorton);
  server_porton_iar.begin();
  
}

void loop() {
  server_porton_iar.handleClient() ; 
  
}



void connect_iar_local(){
  IPAddress ip_porton_iar(,,,)  ; 
  IPAddress gateway_local_iar(,,,)  ; 
  IPAddress subnet_local_iar(,,,)  ; 
  
  WiFi.mode(WIFI_STA) ; 
  WiFi.config(ip_porton_iar,gateway_local_iar,subnet_local_iar ) ; 
  WiFi.begin(SSID_IAR_LOCAL,PASS_SSID_LOCAL);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200); 
    Serial.print('.');
  }
  Serial.println("Wifi: ") ; 
  Serial.println(WiFi.localIP() );  




}


void indexHTML(){
  String s = INDEX_PAGE; //Read HTML contents
  server_porton_iar.send(200, "text/html", s); //Send web page
}

void abirPorton(){
  //prender relay durante 2 segundos 

  String s = "ok" ; 
  server_porton_iar.send(200,"text/html",s ) ; 
  if (isr_enabled == false){
    Serial.println("starting isr") ; 
    st_relay = ON ; 
    relayManagement() ; 
    enableTimer1()  ; 
    isr_enabled = true ; 
  }else{ 
    Serial.println("isr running") ; 
  }
} 



void IRAM_ATTR relayManagement(){
  Serial.println("end isr") ; 
  //prender o apagar rele 
  if( st_relay == ON){
    digitalWrite(PORT_RELAY_WD1,HIGH) ; 
    Serial.println("on") ; 
    st_relay = OFF ; 
  }else if(st_relay == OFF){
    digitalWrite(PORT_RELAY_WD1,LOW) ; 
    Serial.println("off") ; 
    st_relay = OFF ; 
    isr_enabled = false  ; 


  }

}  



void enableTimer1(){
  timer1_enable(TIM_DIV256,TIM_EDGE,TIM_SINGLE) ; 
  timer1_write(170000) ; //cantidad de ticks .. 23 bits sabe dios cuanto es !   
  //timer1_attachInterrupt(relayManagement()) ; //cantidad de ticks 
  timer1_attachInterrupt(relayManagement) ; //cantidad de ticks 
}
