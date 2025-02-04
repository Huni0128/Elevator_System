// =====================================================
// 핀 설정
// =====================================================
const int callButtonPins[3] = {11, 12, 13};  // 호출 버튼
const int callIndicatorPins[3] = {8, 9, 10};  // 호출 요청 상태 LED
const int floorIndicatorPins[3] = {A0, 4, 7};  // 현재 층 표시 LED
const int corridorLED_1_2_phase1 = 2;  // 1층-2층 이동 LED
const int corridorLED_1_2_phase2 = 3;
const int corridorLED_2_3_phase1 = 5;  // 2층-3층 이동 LED
const int corridorLED_2_3_phase2 = 6;

// =====================================================
// 전역 변수
// =====================================================
bool callRequested[3] = { false, false, false };  // 호출 상태 배열
int prevButtonState[3] = { LOW, LOW, LOW };  // 이전 버튼 상태 배열
int currentFloorNum = 1;  // 현재 층, 초기값 1층
int destinationFloor = 1;  // 목표 층
int direction = 0;  // 이동 방향, +1은 위로, -1은 아래로
bool isMoving = false;  // 이동 중인지 여부
const unsigned long moveDelay = 1000;  // 층 간 이동 시간 (밀리초)
const unsigned long debounceDelay = 50;  // 버튼 디바운스 지연 시간 (밀리초)
int movementPhase = 0;  // 이동 단계
unsigned long phaseStartTime = 0;  // 이동 시작 시간
int nextFloorNum = 0;  // 다음 층

// =====================================================
// 설정: 초기화
// =====================================================
void setup() {
  // 호출 버튼, 호출 상태 LED, 층 표시 LED 초기화
  for (int i = 0; i < 3; i++) 
  {
    pinMode(callButtonPins[i], INPUT);  // 호출 버튼을 INPUT 모드로 설정
    pinMode(callIndicatorPins[i], OUTPUT);  // 호출 상태 LED를 OUTPUT 모드로 설정
    pinMode(floorIndicatorPins[i], OUTPUT);  // 층 표시 LED를 OUTPUT 모드로 설정
    digitalWrite(callIndicatorPins[i], LOW);  // 호출 상태 LED 초기화
    digitalWrite(floorIndicatorPins[i], LOW);  // 층 표시 LED 초기화
  }
  // 현재 층 표시 LED 켜기
  digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);

  // 복도 LED 핀 초기화
  pinMode(corridorLED_1_2_phase1, OUTPUT);
  pinMode(corridorLED_1_2_phase2, OUTPUT);
  pinMode(corridorLED_2_3_phase1, OUTPUT);
  pinMode(corridorLED_2_3_phase2, OUTPUT);
  // 복도 LED 초기화 (모두 끄기)
  digitalWrite(corridorLED_1_2_phase1, LOW);
  digitalWrite(corridorLED_1_2_phase2, LOW);
  digitalWrite(corridorLED_2_3_phase1, LOW);
  digitalWrite(corridorLED_2_3_phase2, LOW);
}

// =====================================================
// 이동 처리: 이동 단계별로 LED 및 층 변경
// =====================================================
void processMovement() 
{
  // 호출이 취소된 경우 이동 중지 및 복도 LED 끄기
  if (!callRequested[destinationFloor - 1]) 
  {
    digitalWrite(corridorLED_1_2_phase1, LOW);
    digitalWrite(corridorLED_1_2_phase2, LOW);
    digitalWrite(corridorLED_2_3_phase1, LOW);
    digitalWrite(corridorLED_2_3_phase2, LOW);
    isMoving = false;
    movementPhase = 0;
    digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);  // 현재 층 LED 켜기
    return;
  }

  // 이동 준비 단계: 현재 층 LED 끄고, 이동할 층 계산
  if (movementPhase == 0) 
  {
    nextFloorNum = currentFloorNum + direction;  // 다음 층 계산
    digitalWrite(floorIndicatorPins[currentFloorNum - 1], LOW);  // 현재 층 LED 끄기

    // 복도 LED 켜기 (이동 방향에 따라 다름)
    if ((currentFloorNum == 1 && nextFloorNum == 2) || (currentFloorNum == 2 && nextFloorNum == 1)) 
    {
      if (direction > 0)
        digitalWrite(corridorLED_1_2_phase1, HIGH);  // 위로 이동
      else
        digitalWrite(corridorLED_1_2_phase2, HIGH);  // 아래로 이동
    }
    else if ((currentFloorNum == 2 && nextFloorNum == 3) || (currentFloorNum == 3 && nextFloorNum == 2)) 
    {
      if (direction > 0)
        digitalWrite(corridorLED_2_3_phase1, HIGH);  // 위로 이동
      else
        digitalWrite(corridorLED_2_3_phase2, HIGH);  // 아래로 이동
    }
    movementPhase = 1;  // 이동 단계 1로 변경
    phaseStartTime = millis();  // 이동 시작 시간 기록
  } 
  // 이동 단계 1: 복도 LED 변경
  else if (movementPhase == 1) 
  {
    if (millis() - phaseStartTime >= moveDelay / 2) 
    {
      if ((currentFloorNum == 1 && nextFloorNum == 2) || (currentFloorNum == 2 && nextFloorNum == 1)) 
      {
        if (direction > 0) {
          digitalWrite(corridorLED_1_2_phase1, LOW);
          digitalWrite(corridorLED_1_2_phase2, HIGH);  // 위로 이동 중
        } 
        else 
        {
          digitalWrite(corridorLED_1_2_phase2, LOW);
          digitalWrite(corridorLED_1_2_phase1, HIGH);  // 아래로 이동 중
        }
      }
      else if ((currentFloorNum == 2 && nextFloorNum == 3) || (currentFloorNum == 3 && nextFloorNum == 2)) 
      {
        if (direction > 0) 
        {
          digitalWrite(corridorLED_2_3_phase1, LOW);
          digitalWrite(corridorLED_2_3_phase2, HIGH);  // 위로 이동 중
        } 
        else 
        {
          digitalWrite(corridorLED_2_3_phase2, LOW);
          digitalWrite(corridorLED_2_3_phase1, HIGH);  // 아래로 이동 중
        }
      }
      movementPhase = 2;  // 이동 단계 2로 변경
      phaseStartTime = millis();  // 이동 시작 시간 기록
    }
  } 
  // 이동 단계 2: 이동 완료
  else if (movementPhase == 2) 
  {
    if (millis() - phaseStartTime >= moveDelay / 2) 
    {
      // 이동 완료 후 복도 LED 끄기
      if ((currentFloorNum == 1 && nextFloorNum == 2) || (currentFloorNum == 2 && nextFloorNum == 1)) 
      {
        digitalWrite(corridorLED_1_2_phase1, LOW);
        digitalWrite(corridorLED_1_2_phase2, LOW);
      }
      else if ((currentFloorNum == 2 && nextFloorNum == 3) || (currentFloorNum == 3 && nextFloorNum == 2)) 
      {
        digitalWrite(corridorLED_2_3_phase1, LOW);
        digitalWrite(corridorLED_2_3_phase2, LOW);
      }
      currentFloorNum = nextFloorNum;  // 현재 층 변경
      digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);  // 새로운 층 표시 LED 켜기

      callRequested[currentFloorNum - 1] = false;  // 호출 요청 취소
      digitalWrite(callIndicatorPins[currentFloorNum - 1], LOW);  // 호출 LED 끄기
      prevButtonState[currentFloorNum - 1] = LOW;  // 이전 버튼 상태 초기화
      movementPhase = 0;  // 이동 단계 초기화

      // 목표 층에 도달하지 않았다면 이동을 계속 진행
      if (currentFloorNum != destinationFloor) 
      {
        isMoving = true;
        direction = (destinationFloor > currentFloorNum) ? 1 : -1;  // 이동 방향 설정
      } 
      else 
      {
        isMoving = false;  // 이동 완료
      }
    }
  }
}

// =====================================================
// 메인 루프: 버튼 입력 처리 및 이동 시작
// =====================================================
void loop() 
{
  // 호출 버튼 상태 처리
  for (int i = 0; i < 3; i++) 
  {
    // 현재 층 버튼은 무시하고, 다른 층 버튼 처리
    if ((i + 1) == currentFloorNum) 
    {
      callRequested[i] = false;
      digitalWrite(callIndicatorPins[i], LOW);
      prevButtonState[i] = LOW;
      continue;
    }
    
    int buttonReading = digitalRead(callButtonPins[i]);  // 버튼 상태 읽기
    if (buttonReading != prevButtonState[i]) 
    {
      delay(debounceDelay);  // 디바운스 처리
    }

    // 버튼 눌리면 호출 요청 상태 토글
    if (buttonReading == HIGH && prevButtonState[i] == LOW) 
    {
      callRequested[i] = !callRequested[i];
      digitalWrite(callIndicatorPins[i], callRequested[i] ? HIGH : LOW);  // 호출 상태 LED 업데이트
    }
    prevButtonState[i] = buttonReading;  // 버튼 상태 저장
  }
  
  // 이동 중이 아니면 호출이 있는지 확인하여 이동 시작
  if (!isMoving) 
  {
    for (int i = 0; i < 3; i++) 
    {
      if (callRequested[i] && (i + 1) != currentFloorNum) 
      {
        destinationFloor = i + 1;
        isMoving = true;
        direction = (destinationFloor > currentFloorNum) ? 1 : -1;  // 이동 방향 설정
        break;
      }
    }
  }

  // 이동 중일 때 처리
  if (isMoving) 
  {
    // 중간에 2층 호출이 들어오면 2층으로 강제로 변경
    if (callRequested[1] && (currentFloorNum != 2)) 
    { 
      destinationFloor = 2;
      direction = (2 > currentFloorNum) ? 1 : -1;
      callRequested[0] = false;
      digitalWrite(callIndicatorPins[0], LOW);
      callRequested[2] = false;
      digitalWrite(callIndicatorPins[2], LOW);
    }
    processMovement();  // 이동 처리
    if (!callRequested[destinationFloor - 1]) 
    {
      digitalWrite(corridorLED_1_2_phase1, LOW);
      digitalWrite(corridorLED_1_2_phase2, LOW);
      digitalWrite(corridorLED_2_3_phase1, LOW);
      digitalWrite(corridorLED_2_3_phase2, LOW);
      isMoving = false;
      movementPhase = 0;
      digitalWrite(floorIndicatorPins[currentFloorNum - 1], HIGH);
    }
  }
  
  delay(1);  // CPU 과부하 방지
}
