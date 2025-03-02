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
  1. "Press the button to start!" 메시지가 나타나면 버튼을 눌러 게임을 시작하세요.
  2. "Ready? 3...2...1...GO!" 메시지가 출력되면 버튼을 최대한 빠르게 누르세요.
  3. LED가 깜빡이며 게임이 진행됩니다.
  4. 10초 후 게임이 자동 종료되며 점수가 출력됩니다.
  5. 최고 점수와 비교하여 새로운 기록을 세울 수 있습니다.
  6. 다시 도전 가능!
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)

int clickCount = 0;      // 현재 클릭 횟수
int highScore = 0;       // 최고 기록 저장
bool gameActive = false; // 게임 진행 상태
unsigned long startTime; // 게임 시작 시간

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  pinMode(LED_BUILTIN, OUTPUT);  // LED 출력 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 스위치 입력 (풀업 저항 사용)

  Serial.println("🚀 Welcome to the LED Click Challenge! 🚀");
  Serial.println("Press the button to start!");
}

void loop() {
  // 게임 시작 전, 버튼을 누를 때까지 대기
  while (digitalRead(SW_BUILTIN) != sw_Pressed) {
    // 사용자가 버튼을 누를 때까지 기다림
  }
  delay(50); // 디바운싱 방지

  // 3초 카운트다운
  Serial.println("\n🔄 Get Ready... 3");
  delay(1000);
  Serial.println("🔄 2...");
  delay(1000);
  Serial.println("🔄 1...");
  delay(1000);
  Serial.println("⚡ GO! Click as fast as you can!");

  // 게임 시작
  clickCount = 0;
  gameActive = true;
  startTime = millis(); // 현재 시간 저장

  // LED 깜빡이며 게임 진행 상태 표시
  while (millis() - startTime < 10000) { // 10초 동안 실행
    checkButtonPress();  // 버튼 입력 감지
  }

  gameActive = false; // 게임 종료

  // 결과 출력
  Serial.print("⏱️ Time's up! Your Score: ");
  Serial.println(clickCount);

  // 최고 점수 업데이트
  if (clickCount > highScore) {
    highScore = clickCount;
    Serial.println("🏆 New High Score!");
  } else {
    Serial.print("🏅 Best Score: ");
    Serial.println(highScore);
  }

  Serial.println("🔁 Press the button to play again!");
  delay(2000);
}

// 버튼이 눌렸을 때 클릭 횟수 증가
void checkButtonPress() {
  if (gameActive && digitalRead(SW_BUILTIN) == sw_Pressed) {
    clickCount++;  // 클릭 횟수 증가
    Serial.print("👍 Click! Total: ");
    Serial.println(clickCount);

    // LED 짧게 점멸하여 피드백 제공
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);

    // 버튼이 떼어질 때까지 대기 (디바운싱)
    while (digitalRead(SW_BUILTIN) == sw_Pressed);
    delay(50);
  }
}
