#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int flex1 = A1;
int flex2 = A2;
int flex3 = A3;
int flex4 = A4;
int flex5 = A5;
int servo1_angle = 180;
int servo2_angle = 0;
int servo3_angle = 0;
int servo4_angle = 180;
int servo5_angle = 0;
bool manualMode = false;
void setup() {
  Serial.begin(9600);
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
  servo5.attach(12);
  servo1.write(180);
  servo2.write(0);
  servo3.write(0);
  servo4.write(180);
  servo5.write(0);
  Serial.println("=== Управление антропоморфным схватом ===");
  Serial.println("Режим по умолчанию: перчатка (автоматический)");
  Serial.println("Команды:");
  Serial.println("  а - переключиться в автоматический режим (перчатка)");
  Serial.println("  м - переключиться в ручной режим (с клавиатуры)");
  Serial.println("В ручном режиме:");
  Serial.println("  1 - серво 1 (+) | q - серво 1 (-)");
  Serial.println("  2 - серво 2 (+) | w - серво 2 (-)");
  Serial.println("  3 - серво 3 (+) | e - серво 3 (-)");
  Serial.println("  4 - серво 4 (+) | r - серво 4 (-)");
  Serial.println("  5 - серво 5 (+) | t - серво 5 (-)");
  Serial.println("  0 - разжать все пальцы");
  Serial.println("  9 - сжать все пальцы в кулак");
  Serial.println("  p - вывод текущих углов");
  Serial.println("=========================================");
}
void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'f') {
      manualMode = false;
      Serial.println("Режим: АВТОМАТИЧЕСКИЙ");
    }
    else if (command == 'v') {
      manualMode = true;
      Serial.println("Режим: РУЧНОЙ");
    }
    else if (manualMode) {
      switch(command) {
        case '1':
          servo1_angle = max(servo1_angle - 5, 0);
          servo1.write(servo1_angle);
          Serial.print("Серво 1: ");
          Serial.println(servo1_angle);
          break;
        case 'q':
          servo1_angle = min(servo1_angle + 5, 180);
          servo1.write(servo1_angle);
          Serial.print("Серво 1: ");
          Serial.println(servo1_angle);
          break;
        case '2':
          servo2_angle = min(servo2_angle + 5, 180);
          servo2.write(servo2_angle);
          Serial.print("Серво 2: ");
          Serial.println(servo2_angle);
          break;
        case 'w':
          servo2_angle = max(servo2_angle - 5, 0);
          servo2.write(servo2_angle);
          Serial.print("Серво 2: ");
          Serial.println(servo2_angle);
          break;
        case '3':
          servo3_angle = min(servo3_angle + 5, 180);
          servo3.write(servo3_angle);
          Serial.print("Серво 3: ");
          Serial.println(servo3_angle);
          break;
        case 'e':
          servo3_angle = max(servo3_angle - 5, 0);
          servo3.write(servo3_angle);
          Serial.print("Серво 3: ");
          Serial.println(servo3_angle);
          break;
        case '4':
          servo4_angle = max(servo4_angle - 5, 0);
          servo4.write(servo4_angle);
          Serial.print("Серво 4: ");
          Serial.println(servo4_angle);
          break;
        case 'r':
          servo4_angle = min(servo4_angle + 5, 180);
          servo4.write(servo4_angle);
          Serial.print("Серво 4: ");
          Serial.println(servo4_angle);
          break;
        case '5':
          servo5_angle = min(servo5_angle + 5, 180);
          servo5.write(servo5_angle);
          Serial.print("Серво 5: ");
          Serial.println(servo5_angle);
          break;
        case 't':
          servo5_angle = max(servo5_angle - 5, 0);
          servo5.write(servo5_angle);
          Serial.print("Серво 5: ");
          Serial.println(servo5_angle);
          break;
        case '0':
          servo1_angle = 180;
          servo2_angle = 0;
          servo3_angle = 0;
          servo4_angle = 180;
          servo5_angle = 0;
          servo1.write(180);
          servo2.write(0);
          servo3.write(0);
          servo4.write(180);
          servo5.write(0);
          Serial.println("Все пальцы разжаты");
          break;
        case '9':
          servo1_angle = 0;
          servo2_angle = 180;
          servo3_angle = 180;
          servo4_angle = 0;
          servo5_angle = 180;
          servo1.write(0);
          servo2.write(180);
          servo3.write(180);
          servo4.write(0);
          servo5.write(180);
          Serial.println("Все пальцы сжаты в кулак");
          break;
        // Вывод текущих углов
        case 'p':
          Serial.print("Текущие углы: ");
          Serial.print(servo1_angle);
          Serial.print("--");
          Serial.print(servo2_angle);
          Serial.print("--");
          Serial.print(servo3_angle);
          Serial.print("--");
          Serial.print(servo4_angle);
          Serial.print("--");
          Serial.println(servo5_angle);
          break;
      }
    }
  }
  if (!manualMode) {
    int flex1_pos = analogRead(flex1);
    int flex2_pos = analogRead(flex2);
    int flex3_pos = analogRead(flex3);
    int flex4_pos = analogRead(flex4);
    int flex5_pos = analogRead(flex5);
    int servo1_pos = map(flex1_pos, 985, 453, 0, 180);
    int servo2_pos = map(flex2_pos, 439, 920, 0, 180);
    int servo3_pos = map(flex3_pos, 525, 1000, 0, 180);
    int servo4_pos = map(flex4_pos, 947, 349, 0, 180);
    int servo5_pos = map(flex5_pos, 257, 1002, 0, 180);
    servo1_pos = constrain(servo1_pos, 0, 180);
    servo2_pos = constrain(servo2_pos, 0, 180);
    servo3_pos = constrain(servo3_pos, 0, 180);
    servo4_pos = constrain(servo4_pos, 0, 180);
    servo5_pos = constrain(servo5_pos, 0, 180);
    servo1.write(servo1_pos);
    servo2.write(servo2_pos);
    servo3.write(servo3_pos);
    servo4.write(servo4_pos);
    servo5.write(servo5_pos);
    servo1_angle = servo1_pos;
    servo2_angle = servo2_pos;
    servo3_angle = servo3_pos;
    servo4_angle = servo4_pos;
    servo5_angle = servo5_pos;
  }
  delay(50);
}