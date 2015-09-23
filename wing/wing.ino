
#include <Servo.h>

Servo wingleft; 
Servo wingright;
int pos;

void setup()
{
  wingright.attach(3);  
  wingleft.attach(5);
}

void loop() 
{  
  wingleft.write(160);  
  wingright.write(20);
  delay(300);
  wingleft.write(60);  
  wingright.write(120);
  delay(300);
  
} 

