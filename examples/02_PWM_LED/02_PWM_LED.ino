/*
  🌟 [점점 밝아지는 LED, 부드럽게 꺼지는 효과] 🌟

  📌 [프로그램 설명]
  - 버튼을 누르면 LED가 점점 밝아지고, 떼면 부드럽게 어두워지는 기능입니다.
  - analogWrite함수(PWM)를 사용하여 LED 밝기를 256단계로 조절합니다.
    - analogWrite(핀 번호, 0~255 출력);

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 (LED가 PWM 핀에 연결되어 있어야 함)
  - LED 연결 핀은 PWM이 가능한 핀을 사용해야 합니다.
  -  

  ✅ [사용 방법]
  1. 버튼을 누르고 있으면 LED가 점점 밝아집니다.
  2. 버튼을 떼면 LED가 서서히 어두워집니다.
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 스위치를 뗀 상태를 HIGH로 정의 (내장 풀업 저항 사용)

int brightness = 0;  // 현재 LED 밝기 (0~255)

// setup() 함수: 초기 설정을 수행
void setup() {  
  Serial.begin(115200);  // 시리얼 통신 속도를 115200bps로 설정 (시리얼 모니터용)

  pinMode(LED_BUILTIN, OUTPUT);       // 내장 LED 핀을 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치 핀을 입력 모드로 설정 (내부 풀업 저항 사용)

  Serial.print("🌟 Press and hold the button to increase LED brightness!\n"); // 초기 설정 완료 메시지 출력
}

// loop() 함수: 계속 반복 실행되며 스위치 상태를 확인하고 동작을 제어
void loop() {
  if (digitalRead(SW_BUILTIN) == sw_Pressed) { // 만약 내장 스위치가 눌렸다면
    // 버튼을 누르고 있으면 밝기 증가
    if (brightness < 255) { 
      brightness = (brightness + 1);  // 밝기 증가
      // 현재 밝기를 시리얼 모니터에 출력
      Serial.print("\nBrightness: ");
      Serial.print(brightness);
    }
    else {                // 최대 밝기(255) 도달 시
      brightness = 255;   // 최대 밝기 제한
    }
    delay(20);   // 밝아지는 단계별 시간 간격
  }
  else {  // if(digitalRead(SW_BUILTIN) == sw_Released)   // 만약 내장 스위치를 뗐다면
    // 버튼을 떼면 밝기 감소
    if (0 < brightness) {
      brightness = (brightness - 1);  // 밝기 감소
      Serial.print("\nBrightness: ");
      Serial.print(brightness);
    }
    else {                // 최소 밝기(0) 도달 시
      brightness = 0;   // 최소 밝기 제한
    }
    delay(5);    // 어두워지는 단계별 시간 간격
  }

  analogWrite(LED_BUILTIN, brightness); // PWM 값으로 LED 밝기 조절
}
