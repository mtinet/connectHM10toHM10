# connectHM10toHM10

# HM-10모듈끼리 연결하기

## 작업순서
### 사전조치  
1. 아래 코드를 이용해 AT커맨드를 입력할 수 있는 상태를 만듬  
```
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() { 
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
```
2. 시리얼 모니터를 열어줌(윈도우에서는 아두이노IDE를 두개 열면 두개의 COM포트를 열수 있고, 따라서 두개의 시리얼 모니터를 확인할 수 있음)  
3. 마스터로 사용할 모듈의 시리얼 모니터에 다음의 AT커맨드를 날려 마스터 역할로 사용할 수 있도록 바꿔줌(ROLE1은 마스터, ROLE0은 슬레이브)  
```
AT+ROLE1
```
### 첫번째 방법  
1. 마스터에서 다음 커맨드로 슬레이브 모듈을 검색함(검색을 할 때 내부적으로 리스트를 구성함, 전원이 해제되면 리스트가 사라지므로 다시 아래 명령어를 통해 리스트를 만들어주고 연결해야함)  
```
AT+INQ
```
2. 연결하고 싶은 슬레이브 모듈의 리스트 번호를 확인함  
3. 아래 명령어를 통해 리스트에 해당하는 슬레이브 모듈과 연결함  
```
// 1번 리스트의 슬레이브 모듈과 연결하고 싶을 경우
AT+CONN1
// 2번 리스트의 슬레이브 모듈과 연결하고 싶을 경우
AT+CONN2
```

### 두번째 방법  
1. 슬레이브 MAC 주소 확인
- 슬레이브에서 다음 커맨드를 날려 슬레이브 모듈의 MAC주소를 확인한다.    
```
AT+ADDR
//결과
+ADDR=00:15:83:31:6A:68
```
- 또는, 아래 코드를 슬레이브 모듈로 사용할 아두이노에 업로드 한 다음 시리얼 모니터를 확인한다.  
```
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
String string = "";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) {
    ;
  }
  mySerial.println("AT+ADDR");
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
```
2. 마스터 
- 슬레이브의 MAC주소를 확인하고 마스터에서 다음과 같이 명령을 날리면 바로 연결된다. 
```
// AT+CONA + 0x + MAC 주소의 ':' 제거
AT+CONA0x001583316A68
```
- 아두이노 코드를 이용해 바로 연결하게 하는 방법(마스터 모듈)  
```
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) {
    ;
  }
  mySerial.println("AT+CONA0x001583316A68"); // 위의 두번째 방법에 해당하는 슬레이브 모듈의 주소를 따옴표 안에 있는 문구의 'x'뒤쪽에 바꿔 넣어준다.
  delay(100);
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
```

### 연결 해제  
1. 전원을 차단하여 연결을 해제함

(HC-06의 경우 마스터로 바꾸고 이름과 비밀번호를 똑같이 만들어주면 자동으로 연결되지만, HM-10에서는 연결되는 것과 이름은 상관이 없음)  

## 마스터 모듈의 도움말
********************************************************************
* Command             Description			           *
* ---------------------------------------------------------------- *
* AT                  Check if the command terminal work normally  *
* AT+RESET            Software reboot				   *
* AT+VERSION          Get firmware, bluetooth, HCI and LMP version *
* AT+HELP             List all the commands		           *
* AT+NAME             Get/Set local device name                    *
* AT+PIN              Get/Set pin code for pairing                 *
* AT+BAUD             Get/Set baud rate		                   *
* AT+LADDR            Get local bluetooth address		   *
* AT+ADDR             Get local bluetooth address		   *
* AT+DEFAULT          Restore factory default			   *
* AT+RENEW            Restore factory default			   *
* AT+STATE            Get current state				   *
* AT+PWRM             Get/Set power on mode(low power) 		   *
* AT+POWE             Get/Set RF transmit power 		   *
* AT+SLEEP            Sleep mode 		                   *
* AT+ROLE             Get/Set current role.	                   *
* AT+PARI             Get/Set UART parity bit.                     *
* AT+STOP             Get/Set UART stop bit.                       *
* AT+INQ              Search slave model                           *
* AT+SHOW             Show the searched slave model.               *
* AT+CONN             Connect the index slave model.               *
* AT+IMME             System wait for command when power on.	   *
* AT+START            System start working.			   *
* AT+UUID             Get/Set system SERVER_UUID .            	   *
* AT+CHAR             Get/Set system CHAR_UUID .            	   *
* -----------------------------------------------------------------*
* Note: (M) = The command support master mode only. 	           *
* Copyright@2013 www.bolutek.com. All rights reserved.		   *
********************************************************************


## 슬레이브 모듈의 도움말
⸮********************************************************************
* Command             Description			           *
* ---------------------------------------------------------------- *
* AT                  Check if the command terminal work normally  *
* AT+RESET            Software reboot				   *
* AT+VERSION          Get firmware, bluetooth, HCI and LMP version *
* AT+HELP             List all the commands		           *
* AT+NAME             Get/Set local device name                    *
* AT+PIN              Get/Set pin code for pairing                 *
* AT+PASS             Get/Set pin code for pairing                 *
* AT+BAUD             Get/Set baud rate		                   *
* AT+LADDR            Get local bluetooth address		   *
* AT+ADDR             Get local bluetooth address		   *
* AT+DEFAULT          Restore factory default			   *
* AT+RENEW            Restore factory default			   *
* AT+STATE            Get current state				   *
* AT+PWRM             Get/Set power on mode(low power) 		   *
* AT+POWE             Get/Set RF transmit power 		   *
* AT+SLEEP            Sleep mode 		                   *
* AT+ROLE             Get/Set current role.	                   *
* AT+PARI             Get/Set UART parity bit.                     *
* AT+STOP             Get/Set UART stop bit.                       *
* AT+START            System start working.			   *
* AT+IMME             System wait for command when power on.	   *
* AT+IBEA             Switch iBeacon mode.	                   *
* AT+IBE0             Set iBeacon UUID 0.            	           *
* AT+IBE1             Set iBeacon UUID 1.            	           *
* AT+IBE2             Set iBeacon UUID 2.            	           *
* AT+IBE3             Set iBeacon UUID 3.            	           *
* AT+MARJ             Set iBeacon MARJ .            	           *
* AT+MINO             Set iBeacon MINO .            	           *
* AT+MEA              Set iBeacon MEA .            	           *
* AT+NOTI             Notify connection event .                    *
* AT+UUID             Get/Set system SERVER_UUID .            	   *
* AT+CHAR             Get/Set system CHAR_UUID .            	   *
* -----------------------------------------------------------------*
* Note: (M) = The command support slave mode only. 		   *
* For more information, please visit http://www.bolutek.com        *
* Copyright@2013 www.bolutek.com. All rights reserved.		   *
********************************************************************


