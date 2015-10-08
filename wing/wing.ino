#include <Servo.h>

#define XOUT A3
#define YOUT A2
#define ZOUT A1

Servo wingleft; 
Servo wingright;

void setup()
{
  Serial.begin(9600);
  wingright.attach(5);  
  wingleft.attach(3);
}

void loop() 
{  
  Serial.print(analogRead(XOUT));
  Serial.print("  ");
  Serial.print(analogRead(YOUT));
  Serial.print("  ");
  Serial.println(analogRead(ZOUT));

  wingleft.write(90);
  wingright.write(80);
  
  while(analogRead(YOUT) >= 375) {
    wingleft.write(160);
    delay(300);  
    wingleft.write(60); 
    delay(300); 
  }

  while(analogRead(YOUT) <= 335) {
    wingright.write(50);
    delay(300); 
    wingright.write(120);
    delay(300); 
  }

  while(analogRead(ZOUT) <= 260) {
    wingleft.write(160);
    wingright.write(20);
    delay(300);  
    wingleft.write(60); 
    wingright.write(120);
    delay(300); 
  }
} 

