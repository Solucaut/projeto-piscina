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
#include <ESP8266WebServer.h>
#include <DNSServer.h> //Local DNS Server used for redirecting all requests to the configuration portal ( https://github.com/zhouhan0126/DNSServer---esp32 )
#include <WiFiManager.h>  
#include "fauxmoESP.h"

const int PIN_AP = 33; //pino que ligara o botão 

void setupWiFi();
fauxmoESP fauxmo;

#define WIFI_SSID      "Coloque_Aqui_o_nome_do_seu_WiFi"    
#define WIFI_PASS      "A_Senha_do_seu_WiFi"

#define Comando_1      "Iluminação"    
#define Comando_2      "Avanço da iluminação"
#define Comando_3      "Retrocesso da iluminação"
#define Comando_4      "Ajuste intensidade luz"
#define Comando_5      "Filtro on/off"
#define Comando_6      "Saída 1 on/off"
#define Comando_7      "Saída 2 on/off" 
#define Comando_8      "Áudio"


//       Biblioteca e inicialização para RF
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();


void setup()
{ pinMode(PIN_AP, INPUT);
  //declaração do objeto wifiManager
  WiFiManager wifiManager;

  //utilizando esse comando, as configurações são apagadas da memória
  //caso tiver salvo alguma rede para conectar automaticamente, ela é apagada.
  //  wifiManager.resetSettings();

  //callback para quando entra em modo de configuração AP
  wifiManager.setAPCallback(configModeCallback); 
  //callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação
  wifiManager.setSaveConfigCallback(saveConfigCallback); 

 //cria uma rede de nome ESP_AP com senha 12345678
  wifiManager.autoConnect("ESP_AP", "12345678"); 

  Serial.begin(9600);
  delay(500);
  Serial.println("INICIADO!");


 //   Configuração para Transmissão do RF
  mySwitch.enableTransmit(4);
  mySwitch.setProtocol(6);
  mySwitch.setPulseLength(435);
  

 //       Configuração da Alexa e Adicionar dispositivo na Alexa
  fauxmo.createServer(true); 
  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.addDevice(Comando_1);
  fauxmo.addDevice(Comando_2);
  fauxmo.addDevice(Comando_3);
  fauxmo.addDevice(Comando_4);
  fauxmo.addDevice(Comando_5);
  fauxmo.addDevice(Comando_6);
  fauxmo.addDevice(Comando_7);
  fauxmo.addDevice(Comando_8);
 
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

   if ( (strcmp(device_name, Comando_3) == 0) ) {
      
      //Código binário do comando 3 
      mySwitch.send("0101001110101010101101100101");
      Serial.printf("Retrocesso da Iluminação está %s\r\n", state? "ON":"OFF"); 
    
   }

   if ( (strcmp(device_name, Comando_4) == 0) ) {
      
      //Código binário do comando 4 
      mySwitch.send("0101001110101010101110000101");
      Serial.printf("Ajuste intensidade luz está %s\r\n", state? "ON":"OFF"); 
    
   }

   if ( (strcmp(device_name, Comando_5) == 0) ) {
      
      //Código binário do comando 5 
      mySwitch.send("0101001110101010101100010101");
      Serial.printf("Filtro on/off está %s\r\n", state? "ON":"OFF"); 
    
   }

   if ( (strcmp(device_name, Comando_6) == 0) ) {
      
      //Código binário do comando 6 
      mySwitch.send("0101001110101010101110010101");
      Serial.printf("Saída 1 on/off está %s\r\n", state? "ON":"OFF"); 
    
   }

   if ( (strcmp(device_name, Comando_7) == 0) ) {
      
      //Código binário do comando 7 
      mySwitch.send("0101001110101010101110100101");
      Serial.printf("Saída 2 on/off está %s\r\n", state? "ON":"OFF"); 
    
   }

   if ( (strcmp(device_name, Comando_8) == 0) ) {
      
      //Código binário do comando 8 
      mySwitch.send("0101001110101010101101010101");
      Serial.printf("Áudio está %s\r\n", state? "ON":"OFF"); 
    
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
  
  if ( digitalRead(PIN_AP) == HIGH ) 
   {
      WiFiManager wifiManager;
      if(!wifiManager.startConfigPortal("ESP_AP", "12345678") )
      {
        Serial.println("Falha ao conectar");
        delay(2000);
        ESP.restart();
      }
   }
}

//callback que indica que o ESP entrou no modo AP
void configModeCallback (WiFiManager *myWiFiManager) {  
//  Serial.println("Entered config mode");
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede

}

//callback que indica que salvamos uma nova rede para se conectar (modo estação)
void saveConfigCallback () {
  Serial.println("Configuração salva");
}