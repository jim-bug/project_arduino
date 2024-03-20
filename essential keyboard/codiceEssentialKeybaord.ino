#include <Keyboard.h>
#define NUMBER_KEY 9 
#define LOWER_CASE 14
#define DELETE_LAST_CHAR 15
#define DELETE_KEY 18
#define NEW_LINE_KEY 19
#define SPACE_KEY 20
struct Tasto{
  char caratteri[4];
  int count = 1;
};
struct TastoSpeciale{
  char valoreTastoEsadecimale;
};
int tasto;
int vecchioTasto;
int numeroCaratteriTasto = 4;
Tasto tastiTastiera[9];
TastoSpeciale tastiSpeciali[3];

void setup(){
  Serial.begin(9600);
  int inizioLettere = 65;
  int inizioNumeri = 48;
  pinMode(LOWER_CASE, INPUT);
  pinMode(DELETE_LAST_CHAR, INPUT);
  pinMode(DELETE_KEY, INPUT);
  pinMode(NEW_LINE_KEY, INPUT);
  pinMode(SPACE_KEY, INPUT);
  for(int i = 2;i <= (NUMBER_KEY+1);i++){   // sommo 1, perchè parto dal pin digitale 2, quindi i miei pulsanti sono dal 2 al 10
  	pinMode(i, INPUT);
  }
  for (int i = 0; i < NUMBER_KEY; i ++){
    for (int j = 0; j < 3; j++){
    	tastiTastiera[i].caratteri[j] = char(j+inizioLettere);
    }
    tastiTastiera[i].caratteri[3] = char(inizioNumeri);
    inizioNumeri ++;
    inizioLettere += 3;
  }
  // set tasti 
  tastiTastiera[8].caratteri[0] = 'Y';
  tastiTastiera[8].caratteri[1] = 'Z';
  tastiTastiera[8].caratteri[2] = '8';
  tastiTastiera[8].caratteri[3] = '9';
  // Set dei tasti speciali
  tastiSpeciali[0].valoreTastoEsadecimale = 0x8;
  tastiSpeciali[1].valoreTastoEsadecimale = 0xA;
  tastiSpeciali[2].valoreTastoEsadecimale = 0x20;
}

int tastoPremuto(){
  for (int i = 2;i <= NUMBER_KEY+1;i++){
    if (digitalRead(i)){
    	return i;
    }
    if (digitalRead(NEW_LINE_KEY)){
      return NEW_LINE_KEY;
    }
    if (digitalRead(SPACE_KEY)){
      return SPACE_KEY;
    }
    if (digitalRead(DELETE_KEY)){
      return DELETE_KEY;
    }
  }
  return 1;
}



int controlloClicchiTasto(int contatore, int tastoPremutoPrima, int tastoPremuto, int numeroCaratteriTasto){
      if(tastoPremutoPrima == tastoPremuto){
        if (contatore < numeroCaratteriTasto){
          contatore += 1;
        }
        else{
          contatore = 1;
        }
    }
    else{
        contatore = 1;
    }
    return contatore;
}

void loop(){
  tasto = tastoPremuto();
  Serial.println(digitalRead(NEW_LINE_KEY));
  /*
  backspace: 0x8
  space: 0x20
  a capo: 0xA
  */     
  if(tasto >= 2){
    Keyboard.begin();
    if (tasto >= 18 && tasto <= 20){    // se clicco un tasto speciale
        Keyboard.write(tastiSpeciali[tasto-DELETE_KEY].valoreTastoEsadecimale);
        delay(300);
    }
    else{
        tastiTastiera[tasto-2].count = controlloClicchiTasto(tastiTastiera[tasto-2].count, vecchioTasto, tasto, numeroCaratteriTasto);
        if (digitalRead(LOWER_CASE)){
          if(digitalRead(DELETE_LAST_CHAR)){
            Keyboard.write(0x8);
          }
          if ((int)tastiTastiera[tasto-2].caratteri[tastiTastiera[tasto-2].count-1] >= 48 && (int)tastiTastiera[tasto-2].caratteri[tastiTastiera[tasto-2].count-1] <=57){
            Keyboard.print(tastiTastiera[tasto-2].caratteri[tastiTastiera[tasto-2].count-1]);
            delay(300);
          }
          else{
              char carattereLowerCase = char(int(tastiTastiera[tasto-2].caratteri[tastiTastiera[tasto-2].count-1]+32));
              Keyboard.print(carattereLowerCase);
              delay(300);
          }

        }
        else{
          if(digitalRead(DELETE_LAST_CHAR)){
            Keyboard.write(0x8);
          }
          Keyboard.print(tastiTastiera[tasto-2].caratteri[tastiTastiera[tasto-2].count-1]);
          delay(300);
        }

        vecchioTasto = tasto;
      }
    Keyboard.end();
  }
}