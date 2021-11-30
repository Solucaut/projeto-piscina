Repositório criado para atualizações da programação do Projeto Piscina.

A programação "Clonar_controle" servirá para decodificar sinais de controles remotos RF. 
Faça o upload, abra o monitor serial, segure o controle remoto próximo ao módulo receptor e pressione um botão. O microcontrolador irá imprimir os resultados no monitor serial.

O código "Final_Teste" foi baseado em dois exemplos da biblioteca Rc_switch e      fauxmoESP.
Servirá para se conectar com a Alexa e, ao pedir algo para mesma, irá enviar um comando para o dispositivo realizar a função desejada. Não precisa do controle remoto novamente.
Após ter os dados da programação anterior, faça o upload desta e faça as modificações necessárias para funcionamento do Wifi.

O código "Final_Teste_WifiManager" é um teste da programação final porém incluso o WiFiManager a fim de facilitar a conexão do Wifi no dispositivo final. Ela utilizada da biblioteca WiFiManager.h a fim de transformar o ESP em um Access Point , onde conectaremos nosso celular/notebook e faremos a conexão efetiva com a rede Wifi que provem a internet. Para conectar na rede de internet, apos conectarmos o celular na rede "ESP_AP" digitaremos em um navegador o endereço de ip "192.168.4.1" e faremos a conexão com a rede Wifi do cliente. Apos isso o ESP deixa de ser um access point. 