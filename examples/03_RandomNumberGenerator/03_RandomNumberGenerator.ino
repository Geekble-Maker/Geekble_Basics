/*
  🎲 [랜덤 숫자 생성기 - 행운의 번호 뽑기] 🎲

  📌 [프로그램 설명]
  - 스위치를 누르면 LED가 빠르게 깜빡이며 랜덤 숫자를 변경합니다.
  - 스위치를 떼는 순간 현재의 랜덤 숫자가 확정됩니다.
  - 시리얼 모니터에 "Your Lucky Number: X" 형식으로 출력됩니다.
  - 확정된 숫자만큼 LED가 깜빡이며 결과를 시각적으로 표시합니다.

  📌 [핵심 개념]
  - **스위치 입력 (INPUT_PULLUP)**: 내장 풀업 저항을 사용하여 스위치가 눌리면 LOW, 떼면 HIGH가 됩니다.
  - **랜덤 숫자 생성 (`random(1, 10)`)**: 스위치를 누르고 있는 동안 1~9 사이의 숫자가 계속 변경됩니다.
  - **시리얼 모니터 출력 (`Serial.print()`)**: 숫자가 확정되면 시리얼 모니터에 결과를 출력합니다.
  - **LED 피드백**: 확정된 숫자만큼 LED가 깜빡이며 시각적 효과를 줍니다.

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 등의 개발 보드 (내장 버튼 및 LED 포함)
  - 시리얼 모니터(115200 baud) 사용 가능
  - LED_BUILTIN 및 SW_BUILTIN 핀을 활용

  ✅ [사용 방법]
  1. 버튼을 누르면 LED가 빠르게 깜빡이며 랜덤 숫자가 계속 변경됩니다.
  2. 버튼을 떼면 현재 숫자가 확정되고, 시리얼 모니터에 표시됩니다.
  3. 확정된 숫자만큼 LED가 깜빡입니다.
  4. 다시 버튼을 누르면 새로운 숫자를 뽑을 수 있습니다.
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 스위치를 뗀 상태를 HIGH로 정의 (내장 풀업 저항 사용)

int luckyNumber = 0;  // 생성된 랜덤 숫자 저장 변수

// setup() 함수: 초기 설정을 수행
void setup() {
  Serial.begin(115200);  // 시리얼 통신 속도를 115200bps로 설정 (시리얼 모니터용)

  pinMode(LED_BUILTIN, OUTPUT);       // 내장 LED 핀을 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치 핀을 입력 모드로 설정 (내부 풀업 저항 사용)

  Serial.println("Press the button to get your lucky number!");  // 시작 메시지 출력
}

void loop() {
  // 스위치를 눌렀을 때 랜덤 숫자 생성 시작
  if (digitalRead(SW_BUILTIN) == sw_Pressed) {
    Serial.print("Generating your lucky number");

    // 사용자가 버튼을 계속 누르고 있는 동안 반복 실행
    while (digitalRead(SW_BUILTIN) == sw_Pressed) {
      luckyNumber = random(1, 10);  // 1~9 사이의 랜덤 숫자 생성

      Serial.print(".");
      // LED가 50mSec마다 켜지고 꺼짐
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }

    // 버튼을 뗀 순간 확정된 랜덤 숫자 출력
    Serial.print("\nYour Lucky Number: ");
    Serial.println(luckyNumber);

    // LED가 당첨된 숫자의 횟수만큼 깜빡임
    for (int i = 0; i < luckyNumber; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(300);
      digitalWrite(LED_BUILTIN, LOW);
      delay(300);
    }

    Serial.print("Try again if you want a new lucky number!\n\n");
  }
}
