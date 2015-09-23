
#include <Servo.h>

Servo wingleft; 
Servo wingright;

void setup()
{
  wingleft.attach(3);  // attaches the servo on pin 9 to the servo object
  wingright.attach(5);
}

void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
} 

