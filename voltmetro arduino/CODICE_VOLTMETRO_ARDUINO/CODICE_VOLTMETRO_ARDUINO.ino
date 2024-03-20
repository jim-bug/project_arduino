// BY IGNAZIO SPERANDEO
#include <LiquidCrystal.h>
#define VOLT_ARD 5.0
#define R1 10000.0
#define R2 2000.0
#define PIN_Y 6
#define PIN_X 7
#define RS 12
#define E 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
const float inverse = (R1+R2)/R2;
float analog_value;

void setup(){
  pinMode(PIN_X, OUTPUT);
  pinMode(PIN_Y, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("BY JIM-BUG");
  delay(780);
  lcd.clear();
  lcd.print("VOLTMETRO");
}
void loop(){
  lcd.setCursor(0, 1);
  digitalWrite(PIN_Y, HIGH);
	analog_value = analogRead(A0);
	float vout = ((analog_value*VOLT_ARD)/1023.0) *	inverse;
  lcd.print("VOLT: ");
	Serial.println(vout);
  lcd.print("V");
  if (vout >= 28){
    digitalWrite(PIN_X, HIGH);
    delay(500);
    digitalWrite(PIN_X, LOW);
  }

	delay(200);
}
