#include<LiquidCrystal_I2C.h>          //라이브러리 다운로드 필요
#define aLOW 340
#define aHIGH 680
//int buttonPin = 3;

int mode = 12;                        // 토글 스위치에 따른 인풋. 0일 때 1번 모드, 1일때 2번 모드를 적용하도록 하자.
LiquidCrystal_I2C lcd(0x3F, 16, 2);   // lcd 객체선언 : 혹시 제대로 작동 안 한다면 lcd 주소값 0x3F를 0x27로 고치기
int mq3Pin = A3;                      // MQ-3 센서핀을 아두이노 보드의 A3 핀으로 설정

void setup(){
  Serial.begin(9600);                 // 아두이노 보드와 PC간의 통신속도 설정
  lcd.begin();
  pinMode(mode, INPUT_PULLUP);          
}


void loop(){
  unsigned long val = analogRead(mq3Pin);
  Serial.println(val);   // MQ-3 센서 출력값을 시리얼 모니터로 출력
  delay(1000);
  
  if(digitalRead(mode) == 0){
    lcd.setCursor(0,0);
    lcd.print("MODE 1");
    lcd.setCursor(0,1);
    lcd.print("Alcohol : ");
    lcd.print(val);
    lcd.clear();
  }
  
  else{
    lcd.setCursor(0,0);
    lcd.print("MODE 2");
    lcd.setCursor(0,1);
    lcd.print("Alcohol : ");
    lcd.print(val);
    lcd.clear();
  }
}
