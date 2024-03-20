/*
 * Autore: Ignazio Leonardo Calogero Sperandeo
 * Data: 27/12/2023
 * Progetto: Particular Power Strip(PPS)
 * by jim_bug :)
 * 
 * Comandi da CLI dal device:
 * 0: accende/spegne la presa 1
 * 1: accende/spegne la presa 2
 * 2: accende/spegne la presa 3
 * 3: accende/spegne la presa 4
 * N: mappa stato delle prese
*/

#include <SoftwareSerial.h>
#define LEN 4
#define START_PIN 12
#define END_PIN 9
SoftwareSerial btserial(2, 3);  // rx tx pin
int pinPrese[LEN];
int statusPrese[LEN];  // logica inversa, 0=true 1=false

void setup(){
  Serial.begin(9600);
  btserial.begin(9600);
  // Serial.println("Particolar Power Strip by jim_bug :)");
  for(int i = START_PIN;i >= END_PIN; i--){
    pinPrese[START_PIN-i] = i;
    statusPrese[START_PIN-i] = 1; // salvo i stati di tutte le prese a 1 ossia spente
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); // diseccitto tutti i relè, quindi tutte le prese sono a stato 1
  }
}

void loop(){
  if(btserial.available()){ // se arduino riceve qualcosa
    int presa = btserial.read()-48;  // ricevo il dato grezzo, sottraendolo a 48(codice ascii di 0), ottengo l'indice inviato dal device
    Serial.println(presa);
    if(presa >= 0 && presa <= (LEN-1)){
      if(statusPrese[presa] == 1){  // se la presa è spenta
        digitalWrite(pinPrese[presa], LOW);   // eccito il relè
        statusPrese[presa] = 0; // mi salvo lo stato della presa
      }
      else{
        digitalWrite(pinPrese[presa], HIGH);
        statusPrese[presa] = 1;
      }
    }
    else if(presa == 30){
      for(int i = 0;i < LEN; i++){
          if(statusPrese[i] == 1){
              Serial.print(i+1);
              Serial.println(") Stato Presa: DISATTIVO");
          }
          else{
              Serial.print(i+1);
              Serial.println(") Stato Presa: ATTIVO");
          }
      }
    }
  }
}
