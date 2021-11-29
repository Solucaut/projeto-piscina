/*
  Example for receiving
  
  https://github.com/sui77/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/

 
  PASSO 1 
  PARA CLONAGEM
  Programa para reconhecer um sinal do controle.
  Analisar o valores do monitor serial.

*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    output(mySwitch.getReceivedValue(), 
    mySwitch.getReceivedBitlength(), 
    mySwitch.getReceivedDelay(), 
    mySwitch.getReceivedRawdata(),
    
    mySwitch.getReceivedProtocol());

    
    mySwitch.resetAvailable();
  }
}
