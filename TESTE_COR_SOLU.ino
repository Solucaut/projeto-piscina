/* DESENVOLVIDO POR: SOLUCAUT
 * Programação completa
 * 
 * Programa para receber sinal da Alexa e enviar comando.
 * Pegar os valores binários e aplicar aqui.
 * Preparado para 2 comandos
 */


//          Configuração da ALexa
#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include "fauxmoESP.h"

//CONTADOR DA COR
int stts = 1;


void setupWiFi();
fauxmoESP fauxmo;

#define WIFI_SSID      "Celia_WIFI"    
#define WIFI_PASS      "celia1116"

#define Comando_1      "Iluminação"    
#define Comando_2      "Avanço da iluminação"
/*#define Comando_3      "Retrocesso da iluminação"
#define Comando_4      "Ajuste intensidade luz"
#define Comando_5      "Filtro on/off"
#define Comando_6      "Saída 1 on/off"
#define Comando_7      "Saída 2 on/off" 
#define Comando_8      "Áudio" */
#define Comando_9      "Branco"
#define Comando_10     "Vermelho"
#define Comando_11     "Laranja"
#define Comando_12     "Amarelo"
#define Comando_13     "Azul"


//       Biblioteca e inicialização para RF
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();


void setup()
{
  Serial.begin(9600);
  delay(500);
  Serial.println("INICIADO!");


//   Configuração para Transmissão do RF
  mySwitch.enableTransmit(4);
  mySwitch.setProtocol(6);
  mySwitch.setPulseLength(435);
  

//       Configuração da Alexa e Adicionar dispositivo na Alexa
  setupWiFi();
  fauxmo.createServer(true); 
  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.addDevice(Comando_1);
  fauxmo.addDevice(Comando_2);
 /* fauxmo.addDevice(Comando_3);
  fauxmo.addDevice(Comando_4);
  fauxmo.addDevice(Comando_5);
  fauxmo.addDevice(Comando_6);
  fauxmo.addDevice(Comando_7);
  fauxmo.addDevice(Comando_8);*/
  fauxmo.addDevice(Comando_9);
  fauxmo.addDevice(Comando_10);
  fauxmo.addDevice(Comando_11);
  fauxmo.addDevice(Comando_12);
  fauxmo.addDevice(Comando_13);
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
   
    Serial.printf("Dispositivo #%d (%s) estado: %s valor: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    
    if ( (strcmp(device_name, Comando_1) == 0) ) {

      //Código binário do comando 1 
      mySwitch.send("0101001110101010101100100101");
      Serial.printf("A Iluminação está %s\r\n", state? "ON":"OFF");  
   }

    if ( (strcmp(device_name, Comando_2) == 0) ) {
      
      //Código binário do comando 2 
      mySwitch.send("0101001110101010101101000101");
      Serial.printf("Avanço da Iluminação está %s\r\n", state? "ON":"OFF"); 

   }
      // bRANCO 
     if ( (strcmp(device_name, Comando_9) == 0) ) {
        Serial.println(stts);
          if(stts > 1){
          Serial.println(stts);
          stts = stts - 1;
          mySwitch.send("0101001110101010101101100101");
          delay(500);
          mySwitch.send("");;
          delay(500);
         }
          else if(stts < 1){
          Serial.println(stts);
          stts = stts + 1;
          mySwitch.send(" 0101001110101010101101000101");
          delay(500);
          mySwitch.send("");;
          delay(500);
            }
          else{
          Serial.println("ssts = fun");}
          }

        //VERMELHO
     if ( (strcmp(device_name, Comando_10) == 0) ) {
        Serial.println(stts);
          if(stts > 2){
          Serial.println(stts);
          stts = stts - 1;
          mySwitch.send("0101001110101010101101100101");
          delay(500);
          mySwitch.send("");;
          delay(500);
         }
          else if(stts < 2){
          Serial.println(stts);
          stts = stts + 1;
          mySwitch.send(" 0101001110101010101101000101");
          delay(500);
          mySwitch.send("");;
          delay(500);
            }
          else{
          Serial.println("ssts = fun");}
          }
          
       //LARANJA
       if ( (strcmp(device_name, Comando_11) == 0) ) {
        Serial.println(stts);
          if(stts > 3){
          Serial.println(stts);
          stts = stts - 1;
          mySwitch.send("0101001110101010101101100101");
          delay(500);
          mySwitch.send("");;
          delay(500);
         }
          else if(stts < 3){
          Serial.println(stts);
          stts = stts + 1;
          mySwitch.send(" 0101001110101010101101000101");
          delay(500);
          mySwitch.send("");;
          delay(500);
            }
          else{
          Serial.println("ssts = fun");}
          }   

       //AMARELO
       if ( (strcmp(device_name, Comando_12) == 0) ) {
        Serial.println(stts);
          if(stts > 4){
          Serial.println(stts);
          stts = stts - 1;
          mySwitch.send("0101001110101010101101100101");
          delay(500);
          mySwitch.send("");;
          delay(500);
         }
          else if(stts < 4){
          Serial.println(stts);
          stts = stts + 1;
          mySwitch.send(" 0101001110101010101101000101");
          delay(500);
          mySwitch.send("");;
          delay(500);
            }
          else{
          Serial.println("ssts = fun");}
          }   

       //AZUL
       if ( (strcmp(device_name, Comando_13) == 0) ) {
        Serial.println(stts);
          if(stts > 5){
          Serial.println(stts);
          stts = stts - 1;
          mySwitch.send("0101001110101010101101100101");
          delay(500);
          mySwitch.send("");;
          delay(500);
         }
          else if(stts < 5){
          Serial.println(stts);
          stts = stts + 1;
          mySwitch.send(" 0101001110101010101101000101");
          delay(500);
          mySwitch.send("");;
          delay(500);
            }
          else{
          Serial.println("ssts = fun");}
          }   

  });
     // FECHA VOID SETUP!!
}


void loop() {
  
  fauxmo.handle();

  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  } 
}

// Setup das conexões Wifi
void setupWiFi() {
  WiFi.mode(WIFI_STA);
  Serial.printf("\r\n[Wifi]: Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(300);
  }
  Serial.printf("Conectado!\r\n[WiFi]: Endereço de IP e %s\r\n", WiFi.localIP().toString().c_str());
}
