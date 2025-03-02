// 내장 스위치가 눌렸을 때 LED가 켜지고, 떼면 꺼지는 기능을 구현

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)

// setup() 함수: 초기 설정을 수행
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);       // 내장 LED 핀을 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치 핀을 입력 모드로 설정 (내부 풀업 저항 사용)
}

// loop() 함수: 계속 반복 실행되며 스위치 상태를 확인하고 LED를 제어
void loop() 
{
  // 내장 스위치가 눌렸는지 확인
  if(digitalRead(SW_BUILTIN) == sw_Pressed) { 
    digitalWrite(LED_BUILTIN, HIGH);  // LED를 켜기 (HIGH 출력)
  }
  else { 
    digitalWrite(LED_BUILTIN, LOW);  // LED를 끄기 (LOW 출력)
  }
}
