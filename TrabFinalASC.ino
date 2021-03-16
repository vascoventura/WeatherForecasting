// --- Biblioteca ---
#include <dht.h>   //biblioteca do sensor de humidade e temperatura (DHT11)
// ===============================================================================
// --- Mapeamento de Hardware ---

#define    dht_pin    A0   //pino de sinal do dht11 ligado no digital 5
int interruptPin = 2;
int ledPin = 10;


// ===============================================================================
// --- Declaração de Objetos ---
dht   my_dht;   //objeto para o sensor

// ===============================================================================
// --- Variáveis Globais ---
int    temperatura = 0,   //armazena a temperatura em inteiro
       humidade     = 0,   //armazena a umidade em inteiro
       somaTemperatura = 0,
       somaHumidade = 0,       
       temperaturaFinal = 0,
       humidadeFinal = 0;

boolean button = false;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
long period = 5000;  //the value is a number of milliseconds


// ===============================================================================
void setup(){
  
   Serial.begin(9600);   //serial em 9600 baud rate
  
   pinMode(interruptPin,INPUT);
   attachInterrupt(digitalPinToInterrupt(interruptPin), botao, RISING);

  startMillis = millis();  //initial start time
  
}


// ===============================================================================



void loop() {
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if ((currentMillis - startMillis) == period){
    period = 3600000;//test whether the period has elapsed
    ler(); //if so, change the state of the LED.  Uses a neat trick to change the state
    startMillis = currentMillis;
  }
  
  if(button == 0){
    if(temperatura >= 20){
      alerta();
    }else{
      apagaLed();
    }
  }else{
    apagaLed();
  }
}

void ler(){
  
   my_dht.read11(dht_pin);

   temperatura = my_dht.temperature;
   humidade     = my_dht.humidity;


  somaTemperatura = 0;
  somaHumidade = 0;
  
  for(int i = 0; i < 5; i++){
    my_dht.read11(dht_pin);

   temperatura = my_dht.temperature;
   humidade     = my_dht.humidity;


   somaTemperatura = somaTemperatura + temperatura;
   somaHumidade = somaHumidade + humidade;
   
   temperaturaFinal = somaTemperatura / 5;
   humidadeFinal = somaHumidade / 5;
   }
   
   
   Serial.print(temperaturaFinal);
   Serial.print(" ");
   Serial.print(humidadeFinal);
   Serial.print("\n");

}

void apagaLed(){
  digitalWrite(ledPin, LOW);
}
void alerta(){
  digitalWrite(ledPin, HIGH);
}

void botao(){
  if(button){
    button = false;
  }else{
    button=true;
   
  }
}
