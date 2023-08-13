#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define VOLT 10
#define OHM 9
#define LEN 3
byte omega[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b01110,
	0b01010,
	0b11011
};
void setup() {
  analogReadResolution(14);     // setto al DAC 14 bit.
  pinMode(VOLT, INPUT);
  pinMode(OHM, INPUT);
  lcd.createChar(0, omega);
  lcd.begin(16, 2);
  lcd.clear();         
  lcd.print("By jim_bug :)");
  delay(500);
  lcd.clear();
  lcd.print("Scegli");
  lcd.setCursor(0, 1);
  lcd.print("la funzione: ");
  delay(1000);
  lcd.clear();
  lcd.print("Volt & Ohm");
}

void voltmetro(){
  float r1 = 10000.0;
  float r2 = 2000.0;
  float vout = (analogRead(A0)*5.0)/16383.0;
  float vin = (vout*(r1+r2))/r2;
  lcd.print("Volt: ");
  lcd.print(vin);
  lcd.print("V");
  delay(250);

}
void ohmetro() {
  double r2 = 1000.0;
  double rx;
  double vin = 5.0;
  double vout = (analogRead(A1)*vin)/16383.0;
  rx = ((r2 * vin)/vout)-r2;
  lcd.print("R: ");
  delay(500);
  if (rx > 1000){
      lcd.print(rx);
      lcd.print("K");
      lcd.write(byte(0));
  }
  else{
      lcd.print(rx);
      lcd.write(byte(0)); 
  }
  delay(250);
}

void loop(){
  
  if (digitalRead(VOLT)){
    lcd.clear();
    while (!(digitalRead(OHM))){
      lcd.setCursor(0, 0);
      voltmetro();
    }
    
  }
  if (digitalRead(OHM)){
    lcd.clear();
    while (!(digitalRead(VOLT))){
      lcd.setCursor(0, 0);
      ohmetro();
      lcd.clear();
    }
  }
}

