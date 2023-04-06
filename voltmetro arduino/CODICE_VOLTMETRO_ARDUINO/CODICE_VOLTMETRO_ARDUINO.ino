// BY IGNAZIO SPERANDEO
#include <LiquidCrystal.h>
#define VOLT_ARD 5.0
#define R1 10000.0
#define R2 2000.0

const float inverse = (R1+R2)/R2;
float analog_value;

void setup(){
  Serial.begin(9600);
		// lcd.begin(16, 2);
		// lcd.print("VOLTMETRO");
}
void loop(){
	analog_value = analogRead(A4);
	float vout = ((analog_value*VOLT_ARD)/1023.0) *	inverse;
	

	Serial.print(vout);
  Serial.print("\n");

	delay(200);

}