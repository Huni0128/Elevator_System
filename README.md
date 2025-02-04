# Elevator_System
아래 표는 엘리베이터 시스템의 주요 기능을 기능별로 분류하여 정리한 것입니다.

| **기능 분류**              | **상세 설명**                                                                                                                                                                                                                                                                                          |
|-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **호출 기능**             | ● 각 층의 엘리베이터 호출 버튼을 누르면 엘리베이터가 해당 층으로 이동한다.<br>● 각 층의 엘리베이터 호출 버튼은 동시에 누를 수 있다.                                                                                                                                                                  |
| **호출 취소 기능**         | ● 호출 이후, 한 번 더 호출 버튼을 누르면 호출이 취소된다.                                                                                                                                                                                                                                           |
| **호출상태 표시 기능**      | ● 각 층의 엘리베이터 호출 버튼을 누르면 호출상태 LED가 켜진다.<br>● 엘리베이터가 도착하거나 호출이 취소되면 호출상태 LED는 꺼진다.                                                                                                                                                           |
| **엘리베이터 이동**        | ● 엘리베이터는 1층에서 시작한다.<br>● 대기 중 호출이 발생하면 해당 층으로 이동한다.<br>● 이동 중 다른 호출이 발생하면 다음 규칙에 따라 처리한다:<br>&nbsp;&nbsp;&nbsp;● 먼저 호출된 층으로 가는 길에 있는 경우, 경유지로 설정하고 이동한다. 1 > 3, 3 > 1 이동시 2층 버튼을 누르면 표현이 확실하지않아 목적지경로 취소 후 2층에 정지<br>&nbsp;&nbsp;&nbsp;● 먼저 호출된 층으로 가는 길에 없는 경우, 최종 목적지로 설정하고 이동한다.<br>● 호출이 없는 경우, 현재 층에서 대기한다.<br>● 엘리베이터는 각 층 사이에 대기할 수 없다. |
| **엘리베이터 위치 표시 기능** | ● 엘리베이터의 현재 위치에 해당하는 LED가 켜진다.<br>● 엘리베이터가 이동한 뒤, 이전 LED는 꺼진다.<br>● 엘리베이터의 이동속도는 적절히 조정된다.                                                                                                                             |
---

## Flow Chart
<img src="https://private-user-images.githubusercontent.com/192555666/409504105-cf194982-a22f-4291-84d6-aa1082a49973.svg?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Mzg2NjQxODcsIm5iZiI6MTczODY2Mzg4NywicGF0aCI6Ii8xOTI1NTU2NjYvNDA5NTA0MTA1LWNmMTk0OTgyLWEyMmYtNDI5MS04NGQ2LWFhMTA4MmE0OTk3My5zdmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMjA0JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDIwNFQxMDExMjdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1hYmM5MDNjN2ZjNDZiYjZmZTQ3NzI0M2ViZDc1ZGQxZjM4MjEzZWU5YTczMzc3MjNlODUyYTg1YWM2MWQwZmUyJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.ukUgEUx5Oo5q2x3c48K718C7QYNK8zqfox0dnNmHHzg" alt="순서도" width="800" />

## Source Code
[Elevator System Source Code 보러가기](./elevator_system.ino)
---

## Thinkercad 회로
[Thinkercad 보러가기](https://www.tinkercad.com/things/bocGA5UaAkd-surprising-elzing-borwo?sharecode=SsPkLf7Fkf3UwdpTAjQigbn5cZSbVa4m2_InsnSYL7M)
<img src="https://private-user-images.githubusercontent.com/192555666/409511873-a1444777-4a27-4ae1-8c5e-9347ff447af7.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Mzg2NjU0MjcsIm5iZiI6MTczODY2NTEyNywicGF0aCI6Ii8xOTI1NTU2NjYvNDA5NTExODczLWExNDQ0Nzc3LTRhMjctNGFlMS04YzVlLTkzNDdmZjQ0N2FmNy5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMjA0JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDIwNFQxMDMyMDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0yNzk5NWQyYWZkOTkxMmVlZjVhMWIyZjI4ZDRlZjFjOGM3NmY2YjJhNGI4ZTViNDA5NjhjNmExZTE0OGEzMWY5JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.rsSmNz64FMJq5dLmVK7QmMmEzgua-ioIoS6hiPq_cOs" alt="아두이노 회로" width="800" />
---

## Debugging & Troubleshooting

### 1. delay() 함수 사용으로 인한 문제점

- **문제점:**  
  - **블로킹(Blocking) 이슈:**  
    `delay()` 함수는 호출 시 지정한 시간 동안 프로그램의 실행을 멈추므로 그 동안 다른 작업(예: 버튼 입력 처리, LED 업데이트 등)이 지연됩니다.  
    - 예시: 버튼 디바운스 처리 시 `delay(debounceDelay)`를 사용하면 매우 짧은 시간에도 불필요한 대기(delay)가 발생하여 버튼 이벤트를 놓치거나, 연속 입력이 원활하게 처리되지 않을 수 있음.
  - **타이밍 불일치:**  
    LED 점등 전환 및 이동 단계 처리에 `delay()`를 사용하면, 여러 동작이 동시에 일어나야 할 때(예: 버튼 입력과 LED 상태 업데이트) 타이밍이 어긋날 수 있음.

### 2. 해결 방법 및 개선 방안

- **millis()를 활용한 논블로킹 타이밍 구현:**  
  - `millis()` 함수를 사용하면, 프로그램의 흐름을 멈추지 않고 경과 시간을 체크할 수 있으므로, 버튼 입력이나 LED 업데이트 등 다른 작업들을 동시에 처리할 수 있음.  
  - 위 코드에서는 `processMovement()` 함수 내에서 이동 단계별 타이밍을 `millis()`를 통해 처리하여, delay() 없이도 시간 간격을 유지할 수 있도록 구현함.

- **디바운스 처리 개선:**  
  - 초기에는 `delay(debounceDelay)`를 사용하여 버튼 입력의 노이즈를 줄였지만, 이로 인해 응답성이 떨어지는 문제가 발생함.  
  - 해결 방법:  
    - 디바운스 시간(대략 30~50ms)을 조절하며 최적의 값을 찾음.  
    - 더 나아가, 논블로킹 디바운스 로직(예: 최근 시간 체크 후 이벤트 처리)을 도입하면 delay() 없이도 안정적인 입력 처리가 가능함.

- **메인 루프 내의 최소 delay 사용:**  
  - 메인 `loop()`에서는 CPU 사용률을 낮추기 위해 `delay(1)` 정도의 최소한의 delay만을 사용하여, 다른 작업들의 실행을 방해하지 않도록 함.

### 3. 디버깅 팁

- **Serial 디버깅 활용:**  
  - 각 버튼 입력, 이동 단계 전환, LED 상태 변경 시 `Serial.print()` 문을 삽입하여, 내부 상태와 타이밍을 로그로 확인함.  
  - 예시:
    ```cpp
    Serial.print("Current Floor: ");
    Serial.println(currentFloorNum);
    Serial.print("Movement Phase: ");
    Serial.println(movementPhase);
    ```
  - 이를 통해 어느 부분에서 타이밍 문제나 블로킹 현상이 발생하는지 쉽게 파악할 수 있음.

- **부분별 테스트:**  
  - 전체 시스템을 한 번에 테스트하기보다는,  
    1. 버튼 입력과 디바운스 로직,
    2. LED 점등 및 이동 단계 처리,
    3. 전체 이동 로직  
    등 각 부분별로 단위 테스트를 진행하여 문제가 발생하는 구간을 명확하게 구분함.

- **실시간 모니터링:**  
  - Arduino IDE의 Serial Monitor를 사용해 시스템의 상태 변화를 실시간으로 관찰하여 문제를 조기에 발견하고 수정함.

---

**요약:**  
delay() 함수 사용 시 발생하는 블로킹 문제와 타이밍 불일치 문제는, millis()를 이용한 논블로킹 타이밍 구현과 적절한 디바운스 로직 조정으로 개선할 수 있었습니다.  
Serial 디버깅 및 부분별 테스트를 통해 각 단계의 문제를 명확하게 파악하고 수정하는 것이 중요합니다.
