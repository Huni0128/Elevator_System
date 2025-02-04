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

## 순서도
<img src="https://private-user-images.githubusercontent.com/192555666/409504105-cf194982-a22f-4291-84d6-aa1082a49973.svg?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Mzg2NjQxODcsIm5iZiI6MTczODY2Mzg4NywicGF0aCI6Ii8xOTI1NTU2NjYvNDA5NTA0MTA1LWNmMTk0OTgyLWEyMmYtNDI5MS04NGQ2LWFhMTA4MmE0OTk3My5zdmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMjA0JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDIwNFQxMDExMjdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1hYmM5MDNjN2ZjNDZiYjZmZTQ3NzI0M2ViZDc1ZGQxZjM4MjEzZWU5YTczMzc3MjNlODUyYTg1YWM2MWQwZmUyJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.ukUgEUx5Oo5q2x3c48K718C7QYNK8zqfox0dnNmHHzg" alt="순서도" width="800" />
---

## 소스코드
[Elevator System 소스코드 보러가기](./elevator_system.ino)
---

## Thinkercad 회로
[Thinkercad 보러가기](https://www.tinkercad.com/things/bocGA5UaAkd-surprising-elzing-borwo?sharecode=SsPkLf7Fkf3UwdpTAjQigbn5cZSbVa4m2_InsnSYL7M)
<img src="https://private-user-images.githubusercontent.com/192555666/409511873-a1444777-4a27-4ae1-8c5e-9347ff447af7.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Mzg2NjU0MjcsIm5iZiI6MTczODY2NTEyNywicGF0aCI6Ii8xOTI1NTU2NjYvNDA5NTExODczLWExNDQ0Nzc3LTRhMjctNGFlMS04YzVlLTkzNDdmZjQ0N2FmNy5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMjA0JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDIwNFQxMDMyMDdaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0yNzk5NWQyYWZkOTkxMmVlZjVhMWIyZjI4ZDRlZjFjOGM3NmY2YjJhNGI4ZTViNDA5NjhjNmExZTE0OGEzMWY5JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.rsSmNz64FMJq5dLmVK7QmMmEzgua-ioIoS6hiPq_cOs" alt="아두이노 회로" width="800" />
---
