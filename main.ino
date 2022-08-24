// include part
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// NOTE 변수 지정
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


// Port Part
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ONBUTTON = 2; // ONOFF 스위치 포트 지정(2번)
const int MODEBUTTON = 3; // MODE 스위치 포트 지정(3번)
const int LED = 8; // LED 포트 지정(8번)
const int speakerPin = 7; // 피에조 부조 포트 지정(7번)
int greenled = 9; // 결과 led 포트 지정(녹)(9번)
int yellowled = 10; // 결과 led 포트 지정(노)(10번)
int redled = 11; // 결과 led 포트 지정(빨)(11번)
int mq3Pin = A3; // MQ-3 포트 지정(A3번)

// 변수 지정
int powerState = 0;
int modeState = 0;
int ledState = 0;
int iterup = 0; // 시작 문구 중복 방지
int iterdown = 0; // 종료 문구 중복 방지
int swStateA = 0; // 모드 변환 중 문구 초기 출력 방지(A)
int swStateB = 0; // 모드 변환 중 문구 초기 출력 방지(B)
#define aLOW 340
#define aHIGH 680

// 함수 지정
int bootmelody(int boot) {
  // 시작음
  if (boot == 1) {
    int snumTones = 6;
    int stones[] = {NOTE_E6, NOTE_G6, NOTE_E7, NOTE_C7, NOTE_D7, NOTE_G7};
    int stempo[] = {12, 12, 12, 12, 12, 12};
    for(int i=0;i < snumTones;i++) {
      int sduration = 1000 / stempo[i];
      tone(speakerPin, stones[i], sduration);
      int spause = sduration * 1.30;
      delay(spause);
    }
    noTone(speakerPin);
    delay(1000);
  }
  // 종료 음
  else {
    int dnumTones = 12;
    int dtones[] = 
    {NOTE_G5, NOTE_D6, 0, NOTE_D6, NOTE_D6, NOTE_C6,
    NOTE_B5, NOTE_G5, NOTE_E5, 0, NOTE_E5, NOTE_C5};
    int dtempo[] = {9,9,9,9,12,12,12,9,9,9,9,9};
    for(int j=0;j < dnumTones;j++) {
      int dduration = 1000 / dtempo[j];
      tone(speakerPin, dtones[j], dduration);
      int dpause = dduration * 1.30;
      delay(dpause);
    }
    noTone(speakerPin);
    delay(1000);
  }
  
}

int melody(int sel) {
  // mode A-3의 멜로디
  if (sel == 1) {
    int melody[] = {
      NOTE_E7, NOTE_E7, 0, NOTE_E7,
      0, NOTE_C7, NOTE_E7, 0,
      NOTE_G7, 0, 0,  0,
      NOTE_G6, 0, 0, 0,

      NOTE_C7, 0, 0, NOTE_G6,
      0, 0, NOTE_E6, 0,
      0, NOTE_A6, 0, NOTE_B6,
      0, NOTE_AS6, NOTE_A6, 0,
    
      NOTE_G6, NOTE_E7, NOTE_G7,
      NOTE_A7, 0, NOTE_F7, NOTE_G7,
      0, NOTE_E7, 0, NOTE_C7,
      NOTE_D7, NOTE_B6, 0, 0,
    
      NOTE_C7, 0, 0, NOTE_G6,
      0, 0, NOTE_E6, 0,
      0, NOTE_A6, 0, NOTE_B6,
      0, NOTE_AS6, NOTE_A6, 0,
    
      NOTE_G6, NOTE_E7, NOTE_G7,
      NOTE_A7, 0, NOTE_F7, NOTE_G7,
      0, NOTE_E7, 0, NOTE_C7,
      NOTE_D7, NOTE_B6, 0, 0
    };
    int tempo[] = {
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
    
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
    
      9, 9, 9,
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
    
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
    
      9, 9, 9,
      12, 12, 12, 12,
      12, 12, 12, 12,
      12, 12, 12, 12,
    };
    int size = sizeof(melody) / sizeof(int);
    for (int i = 0; i < size; i++) {
      int noteDuration = 1000 / tempo[i];
      tone(speakerPin, melody[i], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      tone(speakerPin, 0, noteDuration);
    }
  }
  // mode B의 멜로디
  else if(sel == 2) {
    int bmelody[] = {
      NOTE_GS3, NOTE_C6, NOTE_D6, NOTE_C6, NOTE_G6, NOTE_GS3, NOTE_GS3,
      NOTE_G6, NOTE_G6, NOTE_A6, NOTE_AS6, NOTE_F7, NOTE_E7, NOTE_D7,
      NOTE_C7, 0, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
      NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
      NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
      NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_GS5,
      NOTE_C6, 0, NOTE_B5, NOTE_D6, NOTE_C6,
      NOTE_G5, 0, NOTE_DS5, NOTE_E5, NOTE_G5,
      NOTE_G5, 0, NOTE_F5, NOTE_F5,
      NOTE_F5,
      NOTE_D6, 0, NOTE_CS6, NOTE_E6, NOTE_D6,
      NOTE_CS6, NOTE_B5, NOTE_GS5, NOTE_B5,
      NOTE_GS5, 0, NOTE_G5, NOTE_G5,
      NOTE_G5
    };
    int btempo[] = {
      3, 9, 9, 9, 4, 8, 10,
      6, 9, 9, 9, 6, 6, 6,
      9, 6, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 6,
      4, 9, 9, 9, 9,
      4, 9, 9, 9, 9,
      8, 9, 9, 4,
      1,
      4, 9, 9, 9, 9,
      7, 8, 8, 9,
      8, 9, 9, 4,
      3
      
      
    };
    int bsize = sizeof(bmelody) / sizeof(int);
    for (int j = 0; j < bsize; j++) {
      int bnduration = 1000 / btempo[j];
      tone(speakerPin, bmelody[j], bnduration);
      int bpause = bnduration * 1.30;
      delay(bpause);

      tone(speakerPin, 0, bnduration);
    }
  }
  // mode 전환 간 멜로디
  else if(sel == 3) {
    int switchmelody[] = {
      NOTE_E5, NOTE_GS5, 0, NOTE_GS5, NOTE_GS5, NOTE_F5, NOTE_A5,
      0, NOTE_A5, NOTE_A5, NOTE_FS5, NOTE_AS5, 0, NOTE_AS5,NOTE_AS5,
      NOTE_B5, NOTE_B5
    };
    int switchtempo[] = {
      15, 15, 15, 15, 12,
      15, 15, 15, 15, 12,
      15, 15, 15, 15, 12,
      12, 12
    };
    int switchsize = sizeof(switchmelody) / sizeof(int);
    for (int k = 0; k < switchsize; k++) {
      int swnduration = 1000 / switchtempo[k];
      tone(speakerPin, switchmelody[k], swnduration);
      int swpause = swnduration * 1.30;
      delay(swpause);

      tone(speakerPin, 0, swnduration);
    }
  }
  // mode A-1 melody
  else if(sel == 4) {
    int a1melody[] = {
      NOTE_C5, NOTE_E5, NOTE_G5,
      NOTE_C5, NOTE_E5, NOTE_G5,
      NOTE_C6
    };
    int a1tempo[] = {
      5, 5, 5, 5, 5, 5, 5
    };
    int a1size = sizeof(a1melody) / sizeof(int);
    for(int l = 0; l < a1size; l++) {
      int a1nduration = 1000 / a1tempo[l];
      tone(speakerPin, a1melody[l], a1nduration);
      int a1pause = a1nduration * 1.30;
      delay(a1pause);

      tone(speakerPin, 0, a1nduration);
    }
  }
  // mode A-2 melody
  else if(sel == 5) {
    int a2melody[] = {
      NOTE_B6, NOTE_E7
    };
    int a2tempo[] = {
      15, 9
    };
    int a2size = sizeof(a2melody) / sizeof(int);
    for(int m = 0; m < a2size; m++) {
      int a2nduration = 1000 / a2tempo[m];
      tone(speakerPin, a2melody[m], a2nduration);
      int a2pause = a2nduration * 1.30;
      delay(a2pause);

      tone(speakerPin, 0, a2nduration);
    }
  }
}

void switchMode() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Switching Mode");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Wait...");
  melody(3);
  delay(100);
}



void modeA() {
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MODE A");
  lcd.setCursor(0,1);
  lcd.print("Alcohol ");
  // MQ-3 센서 출력값을 시리얼 모니터로 출력
  unsigned long val = analogRead(mq3Pin);
  Serial.println(val);
  delay(1000);
  if (val <= aLOW) {
    digitalWrite(greenled, HIGH);
    digitalWrite(yellowled, LOW);
    digitalWrite(redled, LOW);
    melody(4);
  }
  else if (val <= aHIGH) {
    digitalWrite(greenled, LOW);
    digitalWrite(yellowled, HIGH);
    digitalWrite(redled, LOW);
    melody(5);
  }
  else {
    digitalWrite(greenled, LOW);
    digitalWrite(yellowled, LOW);
    digitalWrite(redled, HIGH);
    melody(1);
  }
  lcd.print(val);
  delay(500);
  /////////////
}

void modeB() {
  digitalWrite(greenled, LOW);
  digitalWrite(yellowled, LOW);
  digitalWrite(redled, LOW);
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MODE B");
  lcd.setCursor(0,1);
  lcd.print("Gusty Garden");
  melody(2);
}

void shuttingdown() {
  digitalWrite(greenled, LOW);
  digitalWrite(yellowled, LOW);
  digitalWrite(redled, LOW);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Shutting Down");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Wait...");
  bootmelody(0);
  delay(5000);
  lcd.clear();
  lcd.noBacklight();
}

void poweron() {
  lcd.backlight(); // LCD 초기 설정
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alcoholic");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initializing...");
  bootmelody(1);
  lcd.setCursor(0,1);
  lcd.print("Wait a second");
  delay(3500);
}

void setup() {
  Serial.begin(9600); // 아두이노 보드와 PC간의 통신속도 설정
  lcd.init(); // LCD 초기 설정
  pinMode(ONBUTTON, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(redled, OUTPUT);https://i.imgur.com/uvGrlhl.png
  poweron();
}



void loop() {
  powerState = digitalRead(ONBUTTON);
  modeState = digitalRead(MODEBUTTON);

  if (powerState == HIGH) {
    ledState = 1;
    iterdown = 0;
    if (iterup == 0) {
      poweron();
      iterup = 1;
    }
    if (modeState == HIGH) {
      if (swStateA == 1) {
        switchMode();
        swStateA = 0;
      }
      else {
        swStateB = 1;
      }
      modeA();
    }
    else {
      if (swStateB == 1) {
        switchMode();
        swStateB = 0;
      }
      else {
        swStateA = 1;
      }
      modeB();
    }
  }
  else {
    if (iterdown == 0) {
      shuttingdown();
      iterdown = 1;
    }
    ledState = 0;
    iterup = 0;
    
  } 
  digitalWrite(LED, ledState);
  
}
