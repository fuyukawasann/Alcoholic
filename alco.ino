#include<LiquidCrystal_I2C.h>   //라이브러리 다운로드 필요
#define aLOW 340
#define aHIGH 680
//int buttonPin = 3;

LiquidCrystal_I2C lcd(0x3F, 16, 2);   // lcd 객체선언 : 혹시 제대로 작동 안 한다면 lcd 주소값 0x3F를 0x27로 고치기
int mq3Pin = A5;   // MQ-3 센서핀을 아두이노 보드의 A5 핀으로 설정

void setup(){
  Serial.begin(9600);          // 아두이노 보드와 PC간의 통신속도 설정
  lcd.begin();
//  pinMode(buttonPin, INPUT);
}


void loop(){
  unsigned long val = analogRead(mq3Pin);
  Serial.println(val);   // MQ-3 센서 출력값을 시리얼 모니터로 출력
  delay(1000);
//  if (digitalRead(buttonPin) == HIGH) {
//    
//  }
//  else {
//    Serial.println("Disread");
//  }
}
