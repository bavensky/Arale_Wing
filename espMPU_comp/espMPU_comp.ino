#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <Servo.h>

Servo L_wing;
Servo R_wing;

MPU6050 accelgyro;
#define OUTPUT_READABLE_ACCELGYRO
#define BT 0

int16_t modeCount = 0;
int16_t ax, ay, az;
int16_t gx, gy, gz;
unsigned long sum_x, sum_y;

int16_t ax_diff = -4040;
int16_t ay_diff = 25;
int16_t gx_diff = 15;
int16_t gy_diff = 15;
int16_t gz_diff = -3;

float p_angle, r_angle, rollAcc, pitchAcc, gyroXrate;
float P_CompCoeff = 0.95;

unsigned long time_prev = 0;
unsigned long previousMode1 = 0;
unsigned long previousMode2 = 0;
unsigned long previousMode3 = 0;
unsigned long L_angle = 90, R_angle = 90;

void readMPU();
void wing_swing();
void mode1();
void mode2();
void mode3();

void setup() {
  Wire.begin();
  Serial.begin(115200);

  accelgyro.initialize();
  pinMode(BT, INPUT);
  L_wing.attach(14);
  R_wing.attach(12);
  delay(1000);
}

void loop() {
  // moveing wing
  //  L_wing.write(90); //wing left center
  //  R_wing.write(90); //wing right center
  //  L_wing.write(110); //forward
  //  R_wing.write(70); //forward
  //  L_wing.write(70); //backward
  //  R_wing.write(110); //backward

  readMPU();
  if (p_angle < 10 && r_angle < 10 && r_angle > -10) {
    L_wing.write(90);
    R_wing.write(90);
  }

  mode2();

  //  if(modeCount == 1)  mode1();
  //  if(modeCount == 2)  mode2();
  //  if(modeCount == 3)  mode3();
  //  if(modeCount == 4)  modeCount = 0;


  //    while (p_angle < -20 || p_angle > -40 ) {
  //      readMPU();
  //      L_wing.write(180);
  //      R_wing.write(50);
  //      delay(10);
  //      L_wing.write(50);
  //      R_wing.write(130);
  //      delay(200);
  //    }

  //  while (p_angle > 20 && p_angle < 30 ) {
  //    readMPU();
  //    L_wing.write(130);
  //    R_wing.write(50);
  //    delay(200);
  //    L_wing.write(50);
  //    R_wing.write(130);
  //    delay(200);
  //  }
  //  while (r_angle > 100 && r_angle < 110) {
  //    readMPU();
  //    L_wing.write(130);
  //    R_wing.write(90);
  //    delay(200);
  //    L_wing.write(50);
  //    R_wing.write(90);
  //    delay(200);
  //  }
  //  while (r_angle > 40 && r_angle < 50) {
  //    readMPU();
  //    L_wing.write(90);
  //    R_wing.write(50);
  //    delay(200);
  //    L_wing.write(90);
  //    R_wing.write(130);
  //    delay(200);
  //  }
}

void readMPU()  {
  unsigned long time_now = millis();
  if (time_now - time_prev >= 20)
  {
    time_prev = time_now;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // EX. set zero point
    //    rawAccx_X -= ax_diff;
    //    rawAccx_Y -= ay_diff;
    //    rawGyrox_X -= gx_diff;
    //    rawGyrox_Y -= gy_diff;
    //    rawGyrox_Z -= gz_diff;

    //    ax -= ax_diff;
    //    ay -= ay_diff;
    //
    //    gx -= gx_diff;
    //    gy -= gy_diff;
    //    gz -= gz_diff;

    //    for(int i=0; i<=100; i++) {
    //      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //      sum_x += ax;
    //      delay(1);
    //      Serial.println(sum_x);
    //    }
    //    for(int i=0; i<=100; i++) {
    //      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //      sum_y += ay;
    //      delay(1);
    //    }
    //
    //    ax = sum_x/100;
    //    ay = sum_y/100;

    //    p_angle += (((float)gz / 16.4f)) * (-0.01f);
    //    p_angle += ((gz / 16.4f)) * (-0.01f);

    p_angle += ((gx / 32.8f)) * (0.01f);    // gz จุดที่เปลี่ยนตามแกนหมุน
    //(float)22/7; //RAD_TO_DEG แปลงเรเดียนเป็นองศา
    float pitchAcc = atan2(ay, az) * RAD_TO_DEG; // atan2(1, 2)  1 คือจุดหมุน, 2 คือจุดตาม
    p_angle = P_CompCoeff * p_angle + (1.0f - P_CompCoeff) * pitchAcc;

    r_angle += ((gy / 32.8f)) * (0.01f);
    float rollAcc = atan2(ax, az) * RAD_TO_DEG;
    r_angle = P_CompCoeff * r_angle + (1.0f - P_CompCoeff) * rollAcc;

    //    Serial.printf("Read IMU %d %d %d\n", ax, ay, gz);

    Serial.print(p_angle);
    Serial.print("\t");
        Serial.println(r_angle);

  }
}

void mode1()  {
  unsigned long timenow = millis();
  readMPU();

  if (p_angle >= 10 && p_angle <= 30)  {
    R_wing.write(70); L_wing.write(110);
    delay(250);
    R_wing.write(0); L_wing.write(0);
    delay(250);
    R_wing.write(70); L_wing.write(110);
    delay(250);
    R_wing.write(0); L_wing.write(0);
    delay(250);
    if (timenow - previousMode1 >= 3000) {
      previousMode1 = timenow;
    }
  }
}

void mode2()  {
  unsigned long timenow = millis();
  readMPU();
  
  if (p_angle >= 10 && p_angle <= 30 ) {
    R_wing.write(50);
    L_wing.write(130);
    if (timenow - previousMode2 >= 500) {
      R_wing.write(90);
      L_wing.write(90);
      delay(200);
      previousMode2 = timenow;
    }
  } else {
    previousMode2 = timenow;
  }
  if (r_angle <= -10 ) {
    R_wing.write(50);
  } 
  if (r_angle >= 10 ) {
    L_wing.write(130);
  } 
}

void mode3()  {
  readMPU();

  if (p_angle >= 10 && p_angle <= 30)  {

    if (L_angle <= 130 && R_angle >= 50)  {
      L_angle++; R_angle--;
    }

    if (L_angle >= 130 && R_angle <= 50)  {
      R_angle++;  L_angle--;
    }

    R_wing.write(R_angle);  L_wing.write(L_angle);
    delay(100);
  } else {
    L_angle = 90;
    R_angle = 90;
  }
}
