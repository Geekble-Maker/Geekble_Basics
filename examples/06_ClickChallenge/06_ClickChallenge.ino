/*
  🚀 [LED 클릭 챌린지] 🚀

  📌 [프로그램 설명]
  - 버튼을 10초 동안 최대한 많이 눌러 점수를 획득하는 게임입니다.
  - LED는 게임 진행 상태를 표시하며, 시리얼 모니터에 점수를 출력합니다.
  - 최고 점수를 기록하여 도전할 수 있습니다.

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 등의 개발 보드 (내장 버튼 및 LED 포함)
  - 시리얼 모니터(115200 baud) 사용 가능

  ✅ [사용 방법]
  1. `"🚀 Press the button to start!"` 메시지가 나타나면 버튼을 눌러 게임을 시작하세요.
  2. `"🔄 Get Ready... 3...2...1...GO!"` 메시지가 출력되면 버튼을 최대한 빠르게 눌러 점수를 올리세요.
  3. LED가 깜빡이며 게임이 진행됩니다.
  4. **10초 후 자동으로 게임 종료** 후 점수가 출력됩니다.
  5. 최고 점수와 비교하여 새로운 기록을 세울 수 있습니다.
  6. 버튼을 눌러 다시 도전할 수 있습니다.
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 스위치를 뗀 상태를 HIGH로 정의 (내장 풀업 저항 사용)

int clickCount = 0;      // 현재 클릭 횟수 저장
int highScore = 0;       // 최고 기록 저장
unsigned long startTime; // 게임 시작 시간을 저장 (millis() 사용)

// ==============================
// 🔧 초기 설정 (setup) 함수
// ==============================
void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  pinMode(LED_BUILTIN, OUTPUT);       // 내장 LED를 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치를 입력 모드로 설정 (풀업 저항 사용)

  Serial.print("🚀 Welcome to the LED Click Challenge! 🚀\n");
  Serial.print("Press the button to start!\n");
}

// ==============================
// 🎮 메인 게임 루프 (loop) 함수
// ==============================
void loop() {
  // 🎮 게임 시작 전, 사용자가 버튼을 누를 때까지 대기
  Serial.print("\n🎮 Press the button to start the game...\n");
  while (digitalRead(SW_BUILTIN) != sw_Pressed) {  // 버튼이 눌릴 때까지 대기
    ;
  }
  delay(50);  // 디바운싱 방지 (잘못된 중복 입력을 막기 위해 잠시 대기)

  // ==============================
  // ⏳ 게임 시작 전 카운트다운
  // ==============================
  Serial.print("\n🔄 Get Ready... 3\n");
  delay(1000);
  Serial.print("🔄 2...\n");
  delay(1000);
  Serial.print("🔄 1...\n");
  delay(1000);
  Serial.print("⚡ GO! Click as fast as you can!\n");

  // ==============================
  // 🕹️ 게임 시작: 클릭 카운트 측정
  // ==============================
  clickCount = 0;  // 클릭 횟수 초기화
  startTime = millis();  // 현재 시간을 기록 (10초 타이머 시작)

  // 게임이 10초 동안 진행됨
  while (millis() - startTime < 10000) {  
    checkButtonPress();  // 사용자의 버튼 입력 감지
  }

  // ==============================
  // 🎯 결과 출력
  // ==============================
  Serial.print("⏱️ Time's up! Your Score: ");
  Serial.print(clickCount);
  Serial.print("\n");

  // 📌 최고 점수 업데이트
  if (clickCount > highScore) {
    highScore = clickCount;
    Serial.print("🏆 New High Score!\n");
  } else {
    Serial.print("🏅 Best Score: ");
    Serial.print(highScore);
    Serial.print("\n");
  }

  Serial.print("🔁 Press the button to play again!\n");

  // 🕹️ 사용자가 다시 버튼을 누를 때까지 대기
  while (digitalRead(SW_BUILTIN) == sw_Released) {
    ;
  }
  delay(500);  // 버튼이 눌린 후 잘못된 중복 입력 방지를 위한 짧은 대기
}

// ==============================
// 🎯 버튼 클릭 감지 (checkButtonPress) 함수
// ==============================
/*
  📌 [checkButtonPress() 함수 설명]
  - 게임이 진행 중일 때 사용자의 버튼 입력을 감지하여 클릭 횟수를 증가시킵니다.
  - LED를 짧게 점멸시켜 버튼 입력을 피드백으로 표시합니다.
  - **디바운싱 처리**를 통해 버튼이 한 번만 카운트되도록 합니다.

  📌 [디바운싱 (Debouncing) 이란?]
  - 기계식 버튼은 눌릴 때 신호가 여러 번 튀는 현상이 발생할 수 있음.
  - `delay(50)`을 추가하여 버튼이 확실히 눌렸다가 떼어진 후에만 카운트되도록 조정.
*/
void checkButtonPress() {
  if (digitalRead(SW_BUILTIN) == sw_Pressed) {  // 버튼이 눌렸는지 확인
    clickCount = (clickCount + 1);              // 클릭 횟수 증가

    // 점수 출력
    Serial.print("👍 Click! Total: ");
    Serial.print(clickCount);
    Serial.print("\n");

    // LED 깜빡임 (사용자가 입력했음을 피드백으로 제공)
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);

    // 버튼이 떼어질 때까지 대기 (디바운싱 처리)
    while (digitalRead(SW_BUILTIN) == sw_Pressed) {
      ;
    }
    delay(50);  // 불필요한 추가 입력 방지
  }
}
