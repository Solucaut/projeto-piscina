/*
  DESENVOLVIDO POR: SOLUCAUT - Soluções em Controle Automação e Eletrônica
  * Programação quase completa
*/

// Configuração da ALexa
#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include "fauxmoESP.h"
#include <EEPROM.h> 
#include <RCSwitch.h>

#define Comando_1      "Iluminação"    
#define Comando_2      "Avanço da iluminação"
/*
#define Comando_3      "Retrocesso da iluminação"
#define Comando_4      "Ajuste intensidade luz"
#define Comando_5      "Filtro on/off"
#define Comando_6      "Saída 1 on/off"
#define Comando_7      "Saída 2 on/off" 
#define Comando_8      "Áudio"
*/
#define Comando_9      "Branco"
#define Comando_10     "Vermelho"
#define Comando_11     "Laranja"
#define Comando_12     "Amarelo"
#define Comando_13     "Azul"
#define Comando_14     "Verde"
#define Comando_15     "Ciano"
#define Comando_16     "Rosa"
#define Comando_17     "Roxo"
#define Comando_18     "Modo 1"
#define Comando_19     "Modo 2"
#define Comando_20     "Modo 3"
#define Comando_21     "Modo 4"
#define Comando_22     "Sequência"
#define Comando_23     "Estrobo"
#define Comando_24     "Padrão"

#define WIFI_SSID      "Celia_WIFI"    
#define WIFI_PASS      "celia1116"

// * Funcoes
uint8_t getEEPROMUInt8(byte offset);
void setEEPROMInt8(byte offset, uint8_t v);
void setupWiFi();
void alterar_cor();

// * Constantes
const byte OFFSET_ESTADO = 0;
const byte OFFSET_TOTAL = 1 + OFFSET_ESTADO;
const uint8_t INTERVALO_COR = 500; // ms
const char comandos[16][50] = {
  Comando_9 , Comando_10, Comando_11, Comando_12, Comando_13,
  Comando_14, Comando_15, Comando_16, Comando_17, Comando_18,
  Comando_19, Comando_20, Comando_21, Comando_22, Comando_23, Comando_24
};

// * Variaveis Globais
uint8_t estado;                 // a
uint8_t requerido;              // a
fauxmoESP fauxmo;               // a
RCSwitch mySwitch = RCSwitch(); // Biblioteca e inicialização para RF


void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("INICIADO!");

  EEPROM.begin(OFFSET_TOTAL);

  // Configuração para Transmissão do RF
  mySwitch.enableTransmit(4);
  mySwitch.setProtocol(6);
  mySwitch.setPulseLength(435);
  

  // Configuração da Alexa e Adicionar dispositivo na Alexa
  setupWiFi();
  fauxmo.createServer(true); 
  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.addDevice(Comando_1);
  fauxmo.addDevice(Comando_2);
  /*
  fauxmo.addDevice(Comando_3);
  fauxmo.addDevice(Comando_4);
  fauxmo.addDevice(Comando_5);
  fauxmo.addDevice(Comando_6);
  fauxmo.addDevice(Comando_7);
  fauxmo.addDevice(Comando_8);
  */
  fauxmo.addDevice(Comando_9);  // Branco   - 1
  fauxmo.addDevice(Comando_10); // Vermelho - 2
  fauxmo.addDevice(Comando_11); // Laranja  - 3
  fauxmo.addDevice(Comando_12); // Amarelo  - 4
  fauxmo.addDevice(Comando_13); // Azul     - 5
  fauxmo.addDevice(Comando_14); // Verde    - 6
  fauxmo.addDevice(Comando_15); // Ciano    - 7
  fauxmo.addDevice(Comando_16); // Rosa     - 8
  fauxmo.addDevice(Comando_17); // Roxo
  fauxmo.addDevice(Comando_18); // Azul, Ciano e Verde
  fauxmo.addDevice(Comando_19); // Verde, Amarelo, Laranja e Vermelho
  fauxmo.addDevice(Comando_20); // Azul, Magenta e Vermelho
  fauxmo.addDevice(Comando_21); // Amarelo, Verde, Ciano, Azul, Magenta e Vermelho
  fauxmo.addDevice(Comando_22); // Azul, Ciano, Verde, Laranja, vermelho e Magenta
  fauxmo.addDevice(Comando_23); // Estrobo
  fauxmo.addDevice(Comando_24); // Padrão (pro branco)                                - 16



  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("Dispositivo #%d (%s) estado: %s valor: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    
    if ((strcmp(device_name, Comando_1) == 0)) {
      //Código binário do comando 1 
      mySwitch.send("0101001110101010101100100101");
      Serial.printf("A Iluminação está %s\r\n", state? "ON":"OFF");  
      // pode ocorrer dessincronia depois se usar corrigir com o comando do estado 
    }

    if ((strcmp(device_name, Comando_2) == 0)) {
      //Código binário do comando 2 
      mySwitch.send("0101001110101010101101000101");
      Serial.printf("Avanço da Iluminação está %s\r\n", state? "ON":"OFF"); 
    }

    for (int i=0; i <= 15; i++) {
      if (strcmp(device_name, comandos[i]) == 0) {
        alterar_cor(i+1);
      }
    }

    if(strcmp(device_name, Comando_24) == 0) {
      fauxmo.setState(Comando_9, true, 255);
      estado = 1;
      setEEPROMInt8(OFFSET_ESTADO, estado);
      EEPROM.commit();
    } 
  }); // END fauxmo.onSetState
} // END void setup


void loop() {
  fauxmo.handle();
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  } // END if
} // END void loop

uint8_t getEEPROMUInt8(byte offset){
  return EEPROM.read(offset);
}

void setEEPROMInt8(byte offset, uint8_t v) {
  EEPROM.write(offset, v);
  EEPROM.commit();
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

void alterar_cor(short int alvo) {
  short int c1 = 0, c2 = 0, caminho = 0;
  estado = getEEPROMUInt8(OFFSET_ESTADO);

  if (alvo == 16) {
    setEEPROMInt8(OFFSET_ESTADO, 0); // Reseta estado para o branco
  } else if (alvo > 15 || alvo < 0) {
    Serial.printf("\t\nError 4005 Entrada Divergente:(\n\n\a\a\a\a");
  } else if (estado == alvo) {
    Serial.printf("\nSem alteracao de estado de cor.\n\n");
  } else if (estado > alvo) {
    c1 = 15 - estado + alvo;
    c2 = estado - alvo;
  } else if (estado < alvo) {
    c1 = alvo - estado;
    c2 = 15 - alvo + estado;
  } else {
    Serial.printf("\t\nError 4040 :(\n\n\a\a\a\a"); // se chegar aqui deu zika
  }
  
  // Decide qual o menor caminho, c1 ou c2 e troca de cores
  if (c1 <= c2) {
    // Avancar - caminho C1
    for(int i=0; i != c1; i++) {
      mySwitch.send("0101001110101010101101000101");
      delay(INTERVALO_COR);
    }
    estado += c1;
    Serial.printf("\nCaminho eh igual a (avanco): %d\n\n",c1);
  } else if (c2 < c1) {
    // Voltar - caminho C2
    for(int i=0; i != c2; i++) {
      mySwitch.send("0101001110101010101101100101");
      delay(INTERVALO_COR);
    }
    estado -= c2;
    Serial.printf("\nCaminho eh igual a (retrocesso): %d\n\n",c2);
  }

  // Salvar na Eprom
  setEEPROMInt8(OFFSET_ESTADO, estado);
}
