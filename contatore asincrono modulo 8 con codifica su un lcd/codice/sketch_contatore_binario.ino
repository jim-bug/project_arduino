#include <LiquidCrystal.h>
#define Q3 10
#define Q2 9
#define Q1 8

int q1;
int q2;
int q3;
int temp_result;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
  lcd.begin(16, 2);
  pinMode(Q1, OUTPUT);
  pinMode(Q2, OUTPUT);
  pinMode(Q3, OUTPUT);
}

void loop(){
  lcd.clear();
  q1 = digitalRead(Q1);
  q2 = digitalRead(Q2);
  q3 = digitalRead(Q3);
  temp_result = (pow(2, 0)*q1)+(pow(2, 1)*q2)+(pow(2, 2)*q3);
  if (temp_result > 0){
    lcd.print(temp_result);
    delay(1000);
    
  }
}
