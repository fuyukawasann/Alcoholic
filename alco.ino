//int buttonPin = 3;
int mq3Pin = A5;   // MQ-3 센서핀을 아두이노 보드의 A5 핀으로 설정

void setup(){
  Serial.begin(9600);          // 아두이노 보드와 PC간의 통신속도 설정
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


//수정 테스트 1 - 준서
