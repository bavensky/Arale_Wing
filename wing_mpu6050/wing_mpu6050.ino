#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Servo.h>

Servo wingleft;
Servo wingright;

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int valx , valy , valz;
char rd;
int prevVal;
int led = 13 ;
int pin11 = 11 , pin10 = 10 ;
int val1 , val2 ;
int valgy1 = 0 , valgy2 = 0;
void setup()
{
  Serial.begin(9600);
  wingright.attach(3);
  wingleft.attach(5);
  mpu.initialize();
}

void loop()
{
  read_6050();

  wingleft.write(90);
  wingright.write(90);

  while (valy <= 55) {
    read_6050();
    wingleft.write(160);
    delay(300);
    wingleft.write(20);
    delay(300);
  }

  while (valy >= 100) {
    read_6050();
    wingright.write(20);
    delay(300);
    wingright.write(155);
    delay(300);
  }

  while (valx >= 15) {
    read_6050();
    wingleft.write(160);
    wingright.write(20);
    delay(300);
    wingleft.write(60);
    wingright.write(120);
    delay(300);
  }
}

void read_6050()  {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  valx = map(ax, -17000, 17000, 0, 179);
  valy = map(ay, -17000, 17000, 0, 179);
  valz = map(az, -17000, 17000, 0, 179);

  Serial.print("axis x = ") ;
  Serial.print(valx) ;
  Serial.print(" axis y = ") ;
  Serial.print(valy) ;
  Serial.print(" axis z = ") ;
  Serial.println(valz) ;

}


