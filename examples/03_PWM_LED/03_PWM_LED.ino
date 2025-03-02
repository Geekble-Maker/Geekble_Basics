/*
  🌟 [점점 밝아지는 LED, 부드럽게 꺼지는 효과] 🌟

  📌 [프로그램 설명]
  - 버튼을 누르면 LED가 점점 밝아지고, 떼면 부드럽게 어두워지는 기능입니다.
  - PWM(Pulse Width Modulation)을 사용하여 LED 밝기를 조절합니다.

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 (LED가 PWM 핀에 연결되어 있어야 함)
  - LED 연결 핀은 PWM이 가능한 핀을 사용해야 합니다.

  ✅ [사용 방법]
  1. 버튼을 누르고 있으면 LED가 점점 밝아집니다.
  2. 버튼을 떼면 LED가 서서히 어두워집니다.
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define LED_PIN LED_BUILTIN  // LED 핀 (PWM 가능 핀 사용 필요)

int brightness = 0;  // 현재 LED 밝기 (0~255)
bool buttonPressed = false;

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  pinMode(LED_PIN, OUTPUT);  // LED 출력 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 스위치 입력 (풀업 저항 사용)

  Serial.println("🌟 Press and hold the button to increase LED brightness!");
}

void loop() {
  if (digitalRead(SW_BUILTIN) == sw_Pressed) {
    // 버튼을 누르고 있으면 밝기 증가
    if (brightness < 255) {
      brightness += 1;  // 밝기 증가 속도 조절
      if (brightness > 255) brightness = 255; // 최대 밝기 제한
    }
    buttonPressed = true;
  } else {
    // 버튼을 떼면 밝기 감소
    if (brightness > 0) {
      brightness -= 5;  // 부드럽게 어두워지는 속도 조절
      if (brightness < 0) brightness = 0; // 최소 밝기 제한
    }
    buttonPressed = false;
  }

  analogWrite(LED_PIN, brightness); // PWM 값으로 LED 밝기 조절
  Serial.print("Brightness: ");
  Serial.println(brightness);
  delay(10); // 부드러운 조절을 위한 작은 지연
}
