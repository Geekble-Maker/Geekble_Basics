/*
  🌟 [점점 밝아지는 LED, 부드럽게 꺼지는 효과] 🌟

  📌 [프로그램 설명]
  - 버튼을 누르면 LED가 점점 밝아지고, 떼면 부드럽게 어두워지는 기능입니다.
  - `analogWrite()` 함수를 사용하여 LED 밝기를 256단계(0~255)로 조절합니다.
    - `analogWrite(핀 번호, 0~255 출력);`

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 (LED가 PWM 핀에 연결되어 있어야 함)
  - LED 연결 핀은 PWM이 가능한 핀을 사용해야 합니다.

  ✅ [사용 방법]
  1. 버튼을 누르고 있으면 LED가 점점 밝아집니다.
  2. 버튼을 떼면 LED가 서서히 어두워집니다.
  3. 현재 밝기는 시리얼 모니터에서 확인할 수 있습니다.
*/

#define sw_Pressed  LOW   // 버튼이 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 버튼이 떼어진 상태를 HIGH로 정의 (내장 풀업 저항 사용)

int brightness = 0;  // 현재 LED 밝기 (0~255)

// ==============================
// 🔧 초기 설정 (setup) 함수
// ==============================
void setup() {  
  Serial.begin(115200);   // 시리얼 통신 시작 (115200bps)
  pinMode(LED_BUILTIN, OUTPUT);       // 내장 LED를 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치를 입력 모드로 설정 (내부 풀업 저항 사용)

  Serial.print("🌟 Press and hold the button to increase LED brightness!\n"); 
}

// ==============================
// 🔄 메인 루프 (loop) 함수
// ==============================
void loop() 
{
  // ==========================
  // 🔼 버튼을 누르면 LED 밝기 증가
  // ==========================
  if (digitalRead(SW_BUILTIN) == sw_Pressed) 
  {  
    if (brightness < 255) 
    {  
      brightness = (brightness + 1);  // 밝기 증가
      Serial.print("Brightness: ");
      Serial.print(brightness);
      Serial.print("\n");
    }
    delay(20);  // 밝아지는 속도 조절
  }

  // ==========================
  // 🔽 버튼을 떼면 LED 밝기 감소
  // ==========================
  else 
  {  
    if (brightness > 0) 
    {  
      brightness = (brightness - 1);  // 밝기 감소
      Serial.print("Brightness: ");
      Serial.print(brightness);
      Serial.print("\n");
    }
    delay(5);  // 어두워지는 속도 조절
  }

  // PWM 값으로 LED 밝기 조절
  analogWrite(LED_BUILTIN, brightness);  
}
