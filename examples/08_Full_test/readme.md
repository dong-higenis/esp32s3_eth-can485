08_Full_test
===
전체 테스트 코드
---
1. LED + Button: 버튼을 누르면 LED가 빠르게 깜박이고 떼면 천천히 깜박임
2. RS232(Serail2): 시리얼모니터(Serial)에 입력하면 그대로 송신, 반대로 수신되면 시리얼모니터로 출력
3. RS485(Serial1): 시리얼모니터(Serial)에 입력하면 그대로 송신, 반대로 수신되면 시리얼모니터로 출력
4. CAN: 500Kbps로 주기적으로 송신, 수신데이터가 있으면 시리얼모니터에 출력
5. ETH(W5500, HSPI): UDP(Port:1234) listener로 동작, 함께 제공되는 udp_client.py로 테스트 가능
6. EEPROM: 시스템 리셋시 쓰고 / 읽어 비교 (부팅시 1회 동작)
7. SPI FALSH(FSPI): 시스템 리셋시 쓰고 / 읽고 비교 (부팅시 1회 동작)

---

##### ETH UDP 사용시 아래의 내용 참고하시기 바랍니다.
```
예제코드는 UDP 서버이며 컴파일 & 업로드 후 모니터 프로그램에 잡히는 IP로 함께 제공되는 python 코드를 실행해 테스트 가능합니다.

1. 라이브러리 설치
library에 있는 ETHClass.zip 을 아두이노 라이브러리 설치를 통해 설치합니다.

2. 오류 수정 

ETH Started
ETH Connected
ETH MAC: 34:85:18:8F:40:25, IPv4: 192.168.8.44, FULL_DUPLEX, 100Mbps
Starting UDP listener on port 6454
Guru Meditation Error: Core  0 panic'ed (LoadProhibited). Exception was unhandled.

Core  0 register dump:
PC      : 0x4005544b  PS      : 0x00060730  A0      : 0x8201760b  A1      : 0x3fcf6fc0
A2      : 0x00000000  A3      : 0x3fceee00  A4      : 0x803803b9  A5      : 0x3fced490
A6      : 0x00060023  A7      : 0x00000003  A8      : 0x82017440  A9      : 0x3fcf6f70  
A10     : 0x00000001  A11     : 0x3fcf199c  A12     : 0x3fcf1950  A13     : 0x00000000
A14     : 0x3fcf199c  A15     : 0x00000000  SAR     : 0x00000000  EXCCAUSE: 0x0000001c  
EXCVADDR: 0x00000000  LBEG    : 0x40055499  LEND    : 0x400554a9  LCOUNT  : 0xfffffffb

Backtrace: 0x40055448:0x3fcf6fc0 |<-CORRUPTED

  #0  0x40055448:0x3fcf6fc0 in ?? ??:0


위와 같은 에러가 발생한다면 아래의 내용을 참고하세요.

https://github.com/Xinyuan-LilyGO/LilyGO-T-ETH-Series/issues/49

..\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.14\libraries\AsyncUDP\src\AsyncUDP.cpp 코드 수정 필요
```

