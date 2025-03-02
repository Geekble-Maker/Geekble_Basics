/*
  📌 [프로그램 설명]
  - 이 코드는 내장 스위치를 눌렀을 때 내장 LED가 켜지고, 스위치를 떼면 LED가 꺼지는 기능을 구현합니다.
  - 내장 스위치가 눌렸을 때 LED를 켜고, 떼면 LED가 꺼지도록 하며, 풀업 저항을 사용하여 스위치 상태를 확인합니다.

  📌 [핵심 개념]
  - **풀업 저항 (INPUT_PULLUP)**: 스위치가 눌리지 않으면 기본적으로 HIGH 상태가 유지되며, 눌리면 LOW 상태로 변합니다.
  - **LED 제어**: `digitalWrite()` 함수로 LED를 제어하고, 스위치 상태에 따라 LED를 ON 또는 OFF 상태로 변경합니다.

  📌 [사용 환경]
  - 아두이노 보드 (내장 LED 및 스위치 포함)

  ✅ [사용 방법]
  1. 스위치를 누르면 내장 LED가 켜집니다.
  2. 스위치를 떼면 내장 LED가 꺼집니다.
*/

#define sw_Pressed  LOW   // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 스위치를 뗀 상태를 HIGH로 정의 (내장 풀업 저항 사용)

// setup() 함수: 초기 설정을 수행
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);         // 내장 LED 핀을 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);    // 내장 스위치 핀을 입력(Pull-Up)으로 설정
}

// loop() 함수: 계속 반복 실행되며 스위치 상태를 확인하고 LED를 제어
void loop() 
{
  // 내장 스위치가 눌렸는지 확인
  if(digitalRead(SW_BUILTIN) == sw_Pressed) { // 만약 내장 스위치가 눌렸다면
    digitalWrite(LED_BUILTIN, HIGH);          // LED를 켜기 (HIGH 출력)
  }
  else {    // if(digitalRead(SW_BUILTIN) == sw_Released) // 만약 내장 스위치를 뗀 상태라면
    digitalWrite(LED_BUILTIN, LOW);                       // LED를 끄기 (LOW 출력)
  }
}
