#include <Servo.h>

// Создаём 4 объекта для управления сервомоторами
Servo servoosn;
Servo servopl1;
Servo servopl2;
Servo servozax;

// Текущие углы
int angles[4] = {90, 90, 90, 90};

void setup() {
  Serial.begin(9600);

  servoosn.attach(3);
  servopl1.attach(5);
  servopl2.attach(6);
  servozax.attach(9);

  // Начальное положение
  servoosn.write(90);
  servopl1.write(90);
  servopl2.write(90);
  servozax.write(90);

  Serial.println(F("=== Управление 4 сервомоторами ==="));
  Serial.println("1 сервомотор - основание");
  Serial.println("2 сервомотор - 2 плечо");
  Serial.println("3 сервомотор - 1 плечо");
  Serial.println("4 сервомотор - захват");
  Serial.println(F("Формат: <номер_мотора> <угол>"));
  Serial.println(F("Пример: 1 90"));
  Serial.println(F("Моторы: 1-4, Углы: 0-180"));
  Serial.println(F("==============================="));
}

void loop() {
  if (Serial.available() > 0) {
    int servoNum = Serial.parseInt();
    int angle = Serial.parseInt();

    if (servoNum >= 1 && servoNum <= 4 && angle >= 0 && angle <= 180) {
      switch (servoNum) {
        case 1: servoosn.write(angle); delay(500); break;
        case 2: servopl1.write(angle); delay(500); break;
        case 3: servopl2.write(angle); delay(500); break;
        case 4: servozax.write(angle); delay(500); break;
      }
      angles[servoNum - 1] = angle;

      Serial.print(F("✓ Мотор "));
      Serial.print(servoNum);
      Serial.print(F(" установлен на "));
      Serial.print(angle);
      Serial.println(F(" градусов"));
    } else {
      Serial.println(F("✕ Ошибка! Номер мотора: 1-4, угол: 0-180"));
    }

    // Очистка буфера
    while (Serial.available()) {
      Serial.read();
    }
  }
}
