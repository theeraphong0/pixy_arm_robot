#include <Arduino_FreeRTOS.h>
#include <Servo.h>
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

#include <Pixy2.h>
Pixy2 pixy;

void setup() {
  servo0.attach(3);
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(9);
  Serial.begin(9600);
  Serial.setTimeout(100);
  xTaskCreate(Servo0, "Servo0", 100, NULL, 1, NULL);
  delay(3000);
  pixy.init();
}


void loop() {
  int i;
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i = 0; i < pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      if (pixy.ccc.blocks[i].m_x < 150)
      {
        delay(1000);
        signatureOnLeft();
      }
      else
      {
        delay(1000);
        
        signatureOnRight();
      }
    }
  }
  else
  {
    gotozero();
  }

  if (Serial.available() > 0)
  {
    String text = Serial.readStringUntil("\n");
    Serial.println(text);
    int ch = text.substring(0, 1).toInt();
    int value = text.substring(1, text.length()).toInt();
    switch (ch) {
      case 0:
        servo0.write(value);
        break;
      case 1:
        servo1.write(value);
        break;
      case 2:
        servo2.write(value);
        break;
      case 3:
        servo3.write(value);
        break;
      default:
        break;
    }
  }
}
void signatureOnRight()
{
  servo0.write(0);
  delay(100);
  servo0.write(65);
  delay(500);
  servo1.write(65);
  delay(500);
  servo3.write(80);
  delay(500);
  servo2.write(135);
  delay(500);
  servo3.write(45);
  delay(500);
  servo2.write(100);
  delay(500);
  servo0.write(0);
  delay(500);
  servo3.write(80);
  delay(500);
}

void signatureOnLeft()
{
  servo0.write(0);
  delay(500);
  servo0.write(90);
  delay(500);
  servo1.write(65);
  delay(500);
  servo3.write(80);
  delay(500);
  servo2.write(135);
  delay(500);
  servo3.write(45);
  delay(500);
  servo2.write(100);
  delay(500);
  servo0.write(30);
  delay(500);
  servo3.write(80);
  delay(500);
}

void Servo0(void *pvParameters)
{
  servo0.write(0);
  servo1.write(90);
  servo2.write(90);
  servo3.write(80);
  vTaskDelete(NULL);
}

void gotozero()
{
  servo0.write(0);
  servo1.write(90);
  servo2.write(90);
  servo3.write(80);
}
