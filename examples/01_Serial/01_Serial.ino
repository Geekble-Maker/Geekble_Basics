/*
  [프로그램 설명]
  이 코드는 내장 스위치를 사용하여 내장 LED를 제어하는 간단한 예제입니다.
  - 스위치를 누르면 LED가 켜지고, "Switch Pressed!" 메시지가 시리얼 모니터에 출력됩니다.
  - 스위치를 계속 누르고 있으면 '.' 문자가 일정 간격(100ms)으로 출력됩니다.
  - 스위치를 떼면 "Switch Released!" 메시지가 출력되며 LED가 꺼집니다.

  [핵심 개념]
  - 내장 풀업 저항 (INPUT_PULLUP): 스위치가 눌리지 않았을 때 기본적으로 HIGH(1) 상태를 유지하고, 눌리면 LOW(0) 상태가 됩니다.
  - 시리얼 모니터를 활용한 디버깅: Serial.println()을 이용해 버튼 상태를 실시간으로 확인할 수 있습니다.

  [사용 환경]
  - 아두이노 보드 또는 ESP32 등의 내장 버튼 및 LED가 있는 개발 보드
  - 시리얼 모니터(115200 baud) 사용 가능
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)

// setup() 함수: 초기 설정을 수행
void setup() 
{
  Serial.begin(115200);  // 시리얼 통신 속도를 115200bps로 설정 (디버깅용)

  pinMode(LED_BUILTIN, OUTPUT);       // 내장 LED 핀을 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치 핀을 입력 모드로 설정 (내부 풀업 저항 사용)

  Serial.println("Arduino Setup Complete!");  // 초기 설정 완료 메시지 출력
}

// loop() 함수: 계속 반복 실행되며 스위치 상태를 확인하고 LED를 제어
void loop() 
{
  // 내장 스위치가 눌렸는지 확인
  if(digitalRead(SW_BUILTIN) == sw_Pressed) {
    Serial.println("Switch Pressed!"); // 스위치가 눌리면 메시지 출력
    digitalWrite(LED_BUILTIN, HIGH);   // LED를 켜기 (HIGH 출력)

    // 사용자가 버튼을 계속 누르고 있는 동안 반복 실행
    while(digitalRead(SW_BUILTIN) == sw_Pressed) {  
      Serial.print(".");  // 버튼이 눌린 상태에서 '.'을 출력하여 상태 표시
      delay(100);         // 100ms 간격으로 상태 확인 (너무 빠른 출력 방지)
    }

    Serial.print("\nSwitch Released!\n\n"); // 스위치가 떼어졌을 때 메시지 출력
    digitalWrite(LED_BUILTIN, LOW);  // LED를 끄기 (LOW 출력)
  }
}
