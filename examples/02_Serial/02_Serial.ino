/*
  🎨 [내장 버튼을 눌러 LED 제어] 🎨

  📌 [프로그램 설명]
  - 버튼을 누르면 LED가 켜지고, 버튼이 눌려있는 동안 시리얼 모니터에 `.` 문자가 출력됩니다.
  - 버튼을 떼면 LED가 꺼지고, `"Switch Released!"` 메시지가 출력됩니다.

  📌 [핵심 개념]
  - **풀업 저항 (INPUT_PULLUP)**: 버튼이 눌리지 않았을 때 HIGH 상태를 유지, 눌리면 LOW로 변함.
  - **디지털 입력 (digitalRead())**: 버튼이 눌렸는지 감지하여 LED를 켜거나 끌 수 있음.
  - **시리얼 모니터 디버깅**: `Serial.print()`를 이용해 버튼 상태를 실시간으로 확인.

  📌 [사용 환경]
  - 아두이노 보드 또는 ESP32 (내장 버튼 및 LED 포함)
  - 시리얼 모니터(115200 baud) 사용 가능

  ✅ [사용 방법]
  1. 아두이노 보드에 코드를 업로드하고 **시리얼 모니터**를 엽니다.
  2. **내장 스위치를 누르면**:
    - 시리얼 모니터에 `"Switch Pressed!"` 메시지가 출력됩니다.
    - LED가 켜집니다.
    - LED가 켜진 상태에서 시리얼 모니터에 `.` 문자가 100ms마다 출력됩니다.
  3. **내장 스위치를 떼면**:
    - 시리얼 모니터에 `"Switch Released!"` 메시지가 출력됩니다.
    - LED가 꺼집니다.
*/

#define sw_Pressed  LOW   // 버튼이 눌린 상태를 LOW로 정의 (내장 풀업 저항 사용)
#define sw_Released HIGH  // 버튼이 떼어진 상태를 HIGH로 정의 (내장 풀업 저항 사용)

// ==============================
// 🔧 초기 설정 (setup) 함수
// ==============================
void setup() 
{
  Serial.begin(115200);   // 시리얼 통신 시작 (115200bps)
  pinMode(LED_BUILTIN, OUTPUT);  // 내장 LED를 출력 모드로 설정
  pinMode(SW_BUILTIN, INPUT_PULLUP);  // 내장 스위치를 입력 모드로 설정 (내부 풀업 저항 사용)

  Serial.print("🎨 Ready! Press the button to toggle the LED.\n");
}

// ==============================
// 🔄 메인 루프 (loop) 함수
// ==============================
void loop() 
{
  if (digitalRead(SW_BUILTIN) == sw_Pressed)  
  {  
    Serial.print("Switch Pressed!\n");  // 버튼이 눌리면 메시지 출력
    digitalWrite(LED_BUILTIN, HIGH);  // LED를 켬 (HIGH 출력)

    // 버튼이 눌려 있는 동안 실행
    while (digitalRead(SW_BUILTIN) == sw_Pressed)  
    {
      Serial.print(".");  // 진행 상태 출력
      delay(100);  // 100ms 간격으로 상태 확인 (너무 빠른 출력 방지)
    }

    Serial.print("\nSwitch Released!\n");  // 버튼이 떼어졌을 때 메시지 출력
    digitalWrite(LED_BUILTIN, LOW);  // LED를 끔 (LOW 출력)
  }
}
