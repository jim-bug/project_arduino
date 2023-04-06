// BY IGNAZIO SPERANDEO
#include <LiquidCrystal.h>
#define VOLT_ARD 5.0
#define R1 10000.0
#define R2 2000.0
#define PIN_Y 6
#define PIN_X 7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const float inverse = (R1+R2)/R2;
float analog_value;

void setup(){
  pinMode(PIN_X, OUTPUT);
  pinMode(PIN_Y, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("BY JIM-BUG");
  delay(300);
  lcd.clear();
  lcd.print("VOLTMETRO");
}
void loop(){
  lcd.setCursor(0, 1);
  digitalWrite(PIN_Y, HIGH);
	analog_value = analogRead(A4);
	float vout = ((analog_value*VOLT_ARD)/1023.0) *	inverse;
  lcd.print("VOLT: ");
	lcd.print(vout);
  lcd.print("V");
  if (vout >= 28){
    digitalWrite(PIN_X, HIGH);
    delay(500);
    digitalWrite(PIN_X, LOW);
  }

	delay(200);
}