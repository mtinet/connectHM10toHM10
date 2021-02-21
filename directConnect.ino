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
