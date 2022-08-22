#include<LiquidCrystal_I2C.h>          //라이브러리 다운로드 필요

#define aLOW 340
#define aHIGH 680
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
//int buttonPin = 3;
//Mario main theme melody
int melodySize = 75;
int melody[ ] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, 
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, 
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, 
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[ ] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};


int mode = 12;                        // 토글 스위치에 따른 인풋. 0일 때 1번 모드, 1일때 2번 모드를 적용하도록 하자.
LiquidCrystal_I2C lcd(0x27, 16, 2);   // lcd 객체선언 : 혹시 제대로 작동 안 한다면 lcd 주소값 0x3F를 0x27로 고치기
int mq3Pin = A3;                      // MQ-3 센서핀을 아두이노 보드의 A3 핀으로 설정
int green = 9;
int yellow = 8;
int red = 7;

void setup(){
  Serial.begin(9600);                 // 아두이노 보드와 PC간의 통신속도 설정
  lcd.begin();
  lcd.backlight();
  pinMode(mode, INPUT_PULLUP);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);          
}


void loop(){
  unsigned long val = analogRead(mq3Pin);
  Serial.println(val);   // MQ-3 센서 출력값을 시리얼 모니터로 출력
  if(digitalRead(mode) == 0){
    if(flag == 0){
      flag = 1;
      toggle_state = !toggle_state;
      }
    }
  else{
    flag = 0;
  }//토글 스위치 모드

  delay(1000);
  
  if(digitalRead(mode) == 0){
    //lcd.backlight();
    if(val<= aLOW){
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);

      tone(3, melody, tempo);//핀번호,주파수,지속시간   마리오 주제가      
         
      }
    else if(val <= aHIGH){
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);

      tone(3, 349, 2000);     
      delay(2000);            
    
      }
    else{
      digitalWrite(green, LOW);
      digitalWrite(yellow,LOW);
      digitalWrite(red, HIGH);

      tone(3, 494, 2000);     
      delay(2000);             
  
      }
    lcd.setCursor(0,0);
    lcd.print("MODE 1");
    lcd.setCursor(0,1);
    lcd.print("Alcohol ");
    lcd.print(val);
    delay(1000);
    lcd.clear(); 
  }
  
  else{
    //lcd.backlight();
       if(val*8<= aLOW){
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);

      tone(3, 272, 2000);     
      delay(2000);             
      
      }
    else if(val*8 <= aHIGH){
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
      
      tone(3, 349, 2000);     
      delay(2000);               
      
      }
    else{
      digitalWrite(green, LOW);
      digitalWrite(yellow,LOW);
      digitalWrite(red, HIGH);

      tone(3, melody, tempo);//마리오 템
      delay(2000);             
      
      }
    lcd.setCursor(0,0);
    lcd.print("MODE 2");
    lcd.setCursor(0,1);
    lcd.print("Alcohol ");
    lcd.print(val*4);
    delay(1000);
    lcd.clear();
  }
}
