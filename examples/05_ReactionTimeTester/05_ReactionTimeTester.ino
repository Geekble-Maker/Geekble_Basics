/*
  🏆 [빠른 반응 속도 테스트] 🏆

  📌 [프로그램 설명]
  - LED가 랜덤한 시간 후 켜지며, 사용자는 최대한 빠르게 버튼을 눌러야 합니다.
  - 반응 속도를 측정하여 시리얼 모니터에 출력합니다.
  - 너무 빠르게 누르면 "False Start!" 메시지가 출력됩니다.

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 등의 개발 보드 (내장 버튼 및 LED 포함)
  - 시리얼 모니터(115200 baud) 사용 가능

  ✅ [사용 방법]
  1. `"Get Ready..."` 메시지가 출력되면 대기합니다.
  2. LED가 랜덤한 시간 후 켜지면, 최대한 빨리 버튼을 누릅니다.
  3. 반응 속도가 시리얼 모니터에 출력됩니다.
  4. 너무 빠르게 누르면 `"False Start!"` 메시지가 표시됩니다.
  5. 다시 도전 가능!
*/

#define sw_Pressed  LOW  // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)

unsigned long startTime;  // LED가 켜진 시간을 저장
bool waitingForResponse = false;  // 사용자가 반응해야 하는 상태인지 확인

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작
  pinMode(LED_BUILTIN, OUTPUT);  // LED 출력 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 스위치 입력 (풀업 저항 사용)

  Serial.println("🏆 Welcome to the Reaction Time Tester! 🏆");
  Serial.println("Press the button when the LED turns ON.");
}

void loop() {
  Serial.println("\n🔄 Get Ready...");
  delay(random(1000, 5000));  // 1~5초 랜덤 대기 (사용자가 예측할 수 없도록)

  // LED 켜짐 (사용자 반응 대기)
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("⚡ NOW! Press the button as fast as you can!");
  startTime = millis();  // 현재 시간을 저장
  waitingForResponse = true;

  // 사용자가 반응할 때까지 대기
  while (waitingForResponse) {
    if (digitalRead(SW_BUILTIN) == sw_Pressed) {
      unsigned long reactionTime = millis() - startTime;  // 반응 속도 계산
      Serial.print("⏱️ Your reaction time: ");
      Serial.print(reactionTime);
      Serial.println(" ms!");

      // LED 끄기 및 재시작 준비
      digitalWrite(LED_BUILTIN, LOW);
      waitingForResponse = false;
      delay(2000);  // 잠시 대기 후 다음 라운드 시작
    }
  }

  // 너무 빨리 버튼을 누른 경우 (반응 대기 전에)
  if (digitalRead(SW_BUILTIN) == sw_Pressed) {
    Serial.println("🚨 False Start! Wait for the LED to turn ON!");
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);
  }
}
