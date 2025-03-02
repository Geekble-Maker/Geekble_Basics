/*
  🏆 [빠른 반응 속도 테스트] 🏆

  📌 [프로그램 설명]
  - LED가 랜덤한 시간 후 켜지며, 사용자는 최대한 빠르게 버튼을 눌러야 합니다.
  - 반응 속도를 측정하여 시리얼 모니터에 출력합니다.
  - 너무 빠르게 누르면 "False Start!" 메시지가 출력됩니다.
  - 버튼을 눌러야 다음 라운드가 시작됩니다.

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 등의 개발 보드 (내장 버튼 및 LED 포함)
  - 시리얼 모니터(115200 baud) 사용 가능

  ✅ [사용 방법]
  1. `"🔄 Get Ready..."` 메시지가 출력되면 대기합니다.
  2. LED가 랜덤한 시간 후 켜지면, 최대한 빨리 버튼을 누릅니다.
  3. 반응 속도가 시리얼 모니터에 출력됩니다.
  4. 너무 빠르게 누르면 `"🚨 False Start!"` 메시지가 표시됩니다.
  5. 버튼을 눌러야 다음 라운드가 시작됩니다.
*/

#define sw_Pressed  LOW   // 스위치가 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 스위치를 뗀 상태를 HIGH로 정의 (내장 풀업 저항 사용)

unsigned long startTime;  // LED가 켜진 시간을 저장 (반응 시간 계산용)
bool waitingForResponse = false;  // 사용자가 반응해야 하는 상태인지 확인

void setup() {
  Serial.begin(115200);  // 시리얼 통신 시작 (115200 baud 속도)
  pinMode(LED_BUILTIN, OUTPUT);  // 내장 LED를 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치를 입력 모드로 설정 (풀업 저항 사용)

  Serial.println("🏆 Welcome to the Reaction Time Tester! 🏆");
  Serial.println("Press the button to start the game.");
}

/*
  📌 [millis() 함수란?]
  - millis()는 **아두이노가 실행된 이후 경과한 시간을 밀리초(ms) 단위로 반환**하는 함수입니다.
  - 1초 = 1000ms 이므로, millis()는 현재까지 흐른 시간을 알 수 있습니다.
  - 이 값을 저장해 두면 특정 이벤트(LED 켜짐, 버튼 눌림 등) 사이의 **시간 차이**를 계산할 수 있습니다.
*/

void loop() {
  // ==========================
  // 🎮 게임 시작 대기 (사용자가 버튼을 눌러야 시작)
  // ==========================
  Serial.println("\n🎮 Press the button to start the game...");
  while (digitalRead(SW_BUILTIN) == sw_Released);  // 버튼이 눌릴 때까지 대기
  delay(500);  // 버튼이 눌린 후 잠시 대기 (잘못된 입력 방지)

  Serial.println("\n🔄 Get Ready...");
  delay(random(1000, 5000));  // 1~5초 랜덤 대기 (사용자가 예측할 수 없도록)

  // ==========================
  // 🚨 False Start 체크
  // ==========================
  /*
    사용자가 LED가 켜지기 전에 버튼을 누르면 "False Start!"를 출력하고 초기화합니다.
    - LED가 켜지기 전(대기 중)에 버튼이 눌리면 잘못된 입력으로 간주됩니다.
  */
  if (digitalRead(SW_BUILTIN) == sw_Pressed) {
    Serial.println("🚨 False Start! Wait for the LED to turn ON!");
    delay(1000);  // 1초 대기 후 다시 게임 시작 대기 상태로 이동
    return;  // loop()를 처음부터 다시 실행
  }

  // ==========================
  // 🔥 LED 켜기 & 반응 시간 측정 시작
  // ==========================
  digitalWrite(LED_BUILTIN, HIGH);  // LED를 켜서 반응 시작 신호
  Serial.println("⚡ NOW! Press the button as fast as you can!");
  startTime = millis();  // 현재 시간을 저장 (LED가 켜진 순간의 시간 기록)
  waitingForResponse = true;  // 사용자의 반응을 기다리는 상태로 변경

  // ==========================
  // 🎯 사용자의 반응을 기다림
  // ==========================
  while (waitingForResponse) {
    if (digitalRead(SW_BUILTIN) == sw_Pressed) {  // 버튼이 눌렸는지 확인
      unsigned long reactionTime = millis() - startTime;  // 반응 속도 계산

      Serial.print("⏱️ Your reaction time: ");
      Serial.print(reactionTime);
      Serial.println(" ms!");

      // LED 끄기 및 게임 종료 후 다시 버튼 대기 상태로 이동
      digitalWrite(LED_BUILTIN, LOW);
      waitingForResponse = false;

      Serial.println("\n🔄 Press the button to play again...");
      while (digitalRead(SW_BUILTIN) == sw_Released);  // 다시 버튼을 누를 때까지 대기
      delay(500);  // 버튼을 눌린 후 잠시 대기 (잘못된 입력 방지)
    }
  }
}
