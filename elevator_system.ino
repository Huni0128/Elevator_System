// ===== 핀 번호 설정 =====
// 각 층 호출 버튼 핀 (1층, 2층, 3층)
const int callButtonPins[3] = {11, 12, 13};

// 각 층 호출 상태를 표시하는 LED 핀
const int callIndicatorPins[3] = {8, 9, 10};

// 엘리베이터 위치(현재 층)를 표시하는 LED 핀
// 1층: A0, 2층: 디지털 4, 3층: 디지털 7
const int floorIndicatorPins[3] = {A0, 4, 7};

// 복도(층간) 이동 시 점등되는 LED 핀 (1층 ↔ 2층)
const int corridorLED_1_2_phase1 = 2;  // 첫 단계 LED
const int corridorLED_1_2_phase2 = 3;  // 두번째 단계 LED

// 복도(층간) 이동 시 점등되는 LED 핀 (2층 ↔ 3층)
const int corridorLED_2_3_phase1 = 5;  // 첫 단계 LED
const int corridorLED_2_3_phase2 = 6;  // 두번째 단계 LED

// ===== 전역 변수 =====
// 각 층의 호출 요청 상태 (true: 호출 요청 발생)
bool callRequested[3] = { false, false, false };

// 버튼은 풀다운 회로로 연결되었으므로 기본 상태는 LOW.
// 이전에 읽은 버튼 상태 (디바운스 처리를 위해)
int prevButtonState[3] = { LOW, LOW, LOW };

// 엘리베이터의 현재 층 (초기값: 1층)
int currentFloorNum = 1;
// 이동할 목적지 층 (호출된 층 번호)
int destinationFloor = 1;

// 이동 방향: +1이면 위로, -1이면 아래로
int direction = 0;

// 이동 중인지 여부를 나타내는 플래그
bool isMoving = false;

// 타이밍 상수
const unsigned long moveDelay = 1000;     // 층간 전체 이동 시간 (밀리초)
const unsigned long debounceDelay = 50;     // 버튼 디바운스 시간 (밀리초)

// 이동 상태(단계)를 나타내는 변수
// 0: 복도 LED 점등 전 단계 (아직 시작 전)
// 1: 복도 LED 첫 단계 (예: 첫 LED 점등)
// 2: 복도 LED 두번째 단계 (예: 두번째 LED 점등 후, 층에 도착)
int movementPhase = 0;

// 각 이동 단계 시작 시각
unsigned long phaseStartTime = 0;

// 현재 이동 중 다음에 도달할 인접 층 번호
int nextFloorNum = 0;

/////////////////////////////////////////////////////////////////////////////
// setup() 함수: 초기 설정
/////////////////////////////////////////////////////////////////////////////
void setup() {
  // 호출 버튼, 호출 LED, 위치 LED 핀을 초기화
  for (int i = 0; i < 3; i++) {
    // 호출 버튼은 풀다운 회로이므로 INPUT 모드 사용 (기본 LOW)
    pinMode(callButtonPins[i], INPUT);
    // 호출 상태 LED 출력 (초기 LOW)
    pinMode(callIndicatorPins[i], OUTPUT);
    digitalWrite(callIndicatorPins[i], LOW);
    // 위치(층) LED 출력 (초기 LOW)
    pinMode(floorIndicatorPins[i], OUTPUT);
    digitalWrite(floorIndicatorPins[i], LOW);
  }
  // 시작 시 엘리베이터는 1층에 있으므로 1층 LED(A0)를 켠다.
  digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);
  
  // 복도 LED 핀 출력 설정 (초기 LOW)
  pinMode(corridorLED_1_2_phase1, OUTPUT);
  pinMode(corridorLED_1_2_phase2, OUTPUT);
  pinMode(corridorLED_2_3_phase1, OUTPUT);
  pinMode(corridorLED_2_3_phase2, OUTPUT);
  digitalWrite(corridorLED_1_2_phase1, LOW);
  digitalWrite(corridorLED_1_2_phase2, LOW);
  digitalWrite(corridorLED_2_3_phase1, LOW);
  digitalWrite(corridorLED_2_3_phase2, LOW);
}

/////////////////////////////////////////////////////////////////////////////
// processMovement() 함수: 엘리베이터 이동 상태머신 처리
/////////////////////////////////////////////////////////////////////////////
void processMovement() {
  // 만약 목적지 층의 호출이 취소되었다면 (즉, 목적지 호출 LED가 꺼졌다면)
  // 복도 LED를 모두 끄고 이동을 중단하며, 현재 층 LED를 켠다.
  if (!callRequested[destinationFloor - 1]) {
    digitalWrite(corridorLED_1_2_phase1, LOW);
    digitalWrite(corridorLED_1_2_phase2, LOW);
    digitalWrite(corridorLED_2_3_phase1, LOW);
    digitalWrite(corridorLED_2_3_phase2, LOW);
    isMoving = false;
    movementPhase = 0;
    digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);
    return;
  }
  
  // 이동 단계에 따른 LED 점등 및 층 업데이트 처리
  if (movementPhase == 0) {
    // [단계 0] : 인접 층으로 이동 준비
    nextFloorNum = currentFloorNum + direction;  // 다음에 갈 층 (인접 층)
    // 현재 층 위치 LED 끄기 (이동 시작)
    digitalWrite(floorIndicatorPins[currentFloorNum - 1], LOW);
    
    // 복도 LED 첫 단계 점등 (층간 이동의 시작을 표시)
    if ((currentFloorNum == 1 && nextFloorNum == 2) || (currentFloorNum == 2 && nextFloorNum == 1)) {
      if (direction > 0)
        digitalWrite(corridorLED_1_2_phase1, HIGH);
      else
        digitalWrite(corridorLED_1_2_phase2, HIGH);
    }
    else if ((currentFloorNum == 2 && nextFloorNum == 3) || (currentFloorNum == 3 && nextFloorNum == 2)) {
      if (direction > 0)
        digitalWrite(corridorLED_2_3_phase1, HIGH);
      else
        digitalWrite(corridorLED_2_3_phase2, HIGH);
    }
    movementPhase = 1;
    phaseStartTime = millis();
  }
  else if (movementPhase == 1) {
    // [단계 1] : 일정 시간(moveDelay/2) 후, 복도 LED 전환
    if (millis() - phaseStartTime >= moveDelay / 2) {
      if ((currentFloorNum == 1 && nextFloorNum == 2) || (currentFloorNum == 2 && nextFloorNum == 1)) {
        if (direction > 0) {
          digitalWrite(corridorLED_1_2_phase1, LOW);
          digitalWrite(corridorLED_1_2_phase2, HIGH);
        } else {
          digitalWrite(corridorLED_1_2_phase2, LOW);
          digitalWrite(corridorLED_1_2_phase1, HIGH);
        }
      }
      else if ((currentFloorNum == 2 && nextFloorNum == 3) || (currentFloorNum == 3 && nextFloorNum == 2)) {
        if (direction > 0) {
          digitalWrite(corridorLED_2_3_phase1, LOW);
          digitalWrite(corridorLED_2_3_phase2, HIGH);
        } else {
          digitalWrite(corridorLED_2_3_phase2, LOW);
          digitalWrite(corridorLED_2_3_phase1, HIGH);
        }
      }
      movementPhase = 2;
      phaseStartTime = millis();
    }
  }
  else if (movementPhase == 2) {
    // [단계 2] : 일정 시간(moveDelay/2) 후, 이동 완료 처리
    if (millis() - phaseStartTime >= moveDelay / 2) {
      // 복도 LED 모두 끄기
      if ((currentFloorNum == 1 && nextFloorNum == 2) || (currentFloorNum == 2 && nextFloorNum == 1)) {
        digitalWrite(corridorLED_1_2_phase1, LOW);
        digitalWrite(corridorLED_1_2_phase2, LOW);
      }
      else if ((currentFloorNum == 2 && nextFloorNum == 3) || (currentFloorNum == 3 && nextFloorNum == 2)) {
        digitalWrite(corridorLED_2_3_phase1, LOW);
        digitalWrite(corridorLED_2_3_phase2, LOW);
      }
      // 도착 처리: 다음 층에 도착하므로 현재 층을 업데이트
      currentFloorNum = nextFloorNum;
      // 도착한 층 위치 LED 켜기
      digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);
      // 도착 시 해당 층의 호출 요청 해제 (호출 LED 끄기, 버튼 상태 LOW 유지)
      callRequested[currentFloorNum - 1] = false;
      digitalWrite(callIndicatorPins[currentFloorNum - 1], LOW);
      prevButtonState[currentFloorNum - 1] = LOW;
      movementPhase = 0;
      // 만약 아직 목적지(destinationFloor)에 도착하지 않았다면, 계속 이동하도록 설정
      if (currentFloorNum != destinationFloor) {
        isMoving = true;
        direction = (destinationFloor > currentFloorNum) ? 1 : -1;
      } else {
        isMoving = false;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// loop() 함수: 메인 루프 (버튼 입력 처리 및 이동 상태 제어)
/////////////////////////////////////////////////////////////////////////////
void loop() {
  // ===== 호출 버튼 입력 처리 =====
  // 현재 층에 해당하는 버튼은 무시(현재 층 호출은 발생하지 않음)
  for (int i = 0; i < 3; i++) {
    if ((i + 1) == currentFloorNum) {
      callRequested[i] = false;
      digitalWrite(callIndicatorPins[i], LOW);
      prevButtonState[i] = LOW;
      continue;
    }
    
    // 각 호출 버튼 상태 읽기 (풀다운 회로: 기본 LOW, 눌리면 HIGH)
    int buttonReading = digitalRead(callButtonPins[i]);
    // 디바운스 처리: 이전 상태와 다르면 잠시 지연
    if (buttonReading != prevButtonState[i]) {
      delay(debounceDelay);
    }
    // 버튼이 새로 눌렸을 때 (이전: LOW, 현재: HIGH)
    if (buttonReading == HIGH && prevButtonState[i] == LOW) {
      // 호출 요청 상태를 토글 (버튼을 누를 때마다 호출/취소)
      callRequested[i] = !callRequested[i];
      digitalWrite(callIndicatorPins[i], callRequested[i] ? HIGH : LOW);
    }
    prevButtonState[i] = buttonReading;
  }
  
  // ===== 이동 시작 조건 확인 =====
  // 엘리베이터가 정지 중일 때, 현재 층이 아닌 호출이 있다면 이동 시작
  if (!isMoving) {
    for (int i = 0; i < 3; i++) {
      if (callRequested[i] && (i + 1) != currentFloorNum) {
        destinationFloor = i + 1;
        isMoving = true;
        direction = (destinationFloor > currentFloorNum) ? 1 : -1;
        break;
      }
    }
  }
  
  // ===== 중간 호출(2층) 처리 =====
  // 만약 엘리베이터가 1층 ↔ 3층 이동 중이라면,
  // 그리고 2층 호출 버튼(인덱스 1)이 눌렸다면, 
  // 다른 층의 호출은 취소하고 목적지를 무조건 2층으로 설정
  if (isMoving) {
    if (callRequested[1] && (currentFloorNum != 2)) { 
      destinationFloor = 2;  // 2층(LED 4)을 목적지로 설정
      direction = (2 > currentFloorNum) ? 1 : -1;
      // 1층(인덱스 0)과 3층(인덱스 2)의 호출은 취소
      callRequested[0] = false;
      digitalWrite(callIndicatorPins[0], LOW);
      callRequested[2] = false;
      digitalWrite(callIndicatorPins[2], LOW);
    }
    
    // ===== 이동 처리 =====
    processMovement();
    
    // 만약 이동 도중 목적지 호출이 취소되면,
    // 복도 LED를 모두 끄고 이동을 중단하며 현재 층 LED만 켠다.
    if (!callRequested[destinationFloor - 1]) {
      digitalWrite(corridorLED_1_2_phase1, LOW);
      digitalWrite(corridorLED_1_2_phase2, LOW);
      digitalWrite(corridorLED_2_3_phase1, LOW);
      digitalWrite(corridorLED_2_3_phase2, LOW);
      isMoving = false;
      movementPhase = 0;
      digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);
    }
  }
  
  delay(1); // 루프 간 짧은 딜레이
}