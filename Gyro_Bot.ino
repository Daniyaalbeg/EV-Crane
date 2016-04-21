#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
int orientationx;
int orientationy;
int orientationz;

EVShield          evshield(0x34, 0x36);
Servo myservo;
#define BNO055_SAMPLERATE_DELAY_MS (100)

; Adafruit_BNO055 bno = Adafruit_BNO055();

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  char str[256];
  Serial.begin(115200);

  evshield.init( SH_HardwareI2C );

  Serial.println ("------------------");
  Serial.println ("Starting Program");
  Serial.println ("----------------");

  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();
  myservo.writeMicroseconds(2060);
  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  myservo.attach(8);
  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/

long  count = 1;


void loop(void)
{
  char aa[80];
  int a;
  char str[256];

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
  Serial.print("\t\t");
  orientationx = euler.x();
  orientationy = euler.y();
  orientationz = euler.z();



  while (count < 2)
  {
    count = 1;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    orientationx = euler.x();
    orientationy = euler.y();
    orientationz = euler.z();

    while (orientationy > 10 && orientationy < 20)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        SH_Speed_Slow
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        SH_Speed_Slow
                                       );
      orientationy = euler.y();

    }
    evshield.bank_b.motorReset();

    while (orientationy > 20 && orientationy < 30)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        SH_Speed_Medium
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        SH_Speed_Medium
                                       );
      orientationy = euler.y();

    }
    evshield.bank_b.motorReset();

    while (orientationy > 30 && orientationy < 40)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        SH_Speed_Full
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        SH_Speed_Full
                                       );
      orientationy = euler.y();

    }
    evshield.bank_b.motorReset();


    while (orientationy < -10 && orientationy > -20)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        SH_Speed_Slow
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        SH_Speed_Slow
                                       );
      orientationy = euler.y();

    }
    evshield.bank_b.motorReset();

    while (orientationy < -20 && orientationy > -30)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        SH_Speed_Medium
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        SH_Speed_Medium
                                       );
      orientationy = euler.y();

    }
    evshield.bank_b.motorReset();
    while (orientationy < -30 && orientationy > -50)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        SH_Speed_Full
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        SH_Speed_Full
                                       );
      orientationy = euler.y();

    }
    evshield.bank_b.motorReset();




    while (orientationz < -10 && orientationz > -20)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Reverse,
                                        SH_Speed_Slow
                                       );
      orientationz = euler.z();
    }
    evshield.bank_b.motorReset();


    while (orientationz < -20 && orientationz > -30)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Reverse,
                                        SH_Speed_Medium
                                       );
      orientationz = euler.z();
    }
    evshield.bank_b.motorReset();


    while (orientationz < -30 && orientationz > -50)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Reverse,
                                        SH_Speed_Full
                                       );
      orientationz = euler.z();
    }
    evshield.bank_b.motorReset();





    while (orientationz > 10 && orientationz < 20)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Forward,
                                        SH_Speed_Slow
                                       );
      orientationz = euler.z();
    }

    evshield.bank_b.motorReset();

    while (orientationz > 20 && orientationz < 30)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Forward,
                                        SH_Speed_Medium
                                       );
      orientationz = euler.z();
    }

    evshield.bank_b.motorReset();

    while (orientationz > 30 && orientationz < 50)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Forward,
                                        SH_Speed_Full
                                       );
      orientationz = euler.z();
    }

    evshield.bank_b.motorReset();

    if ( evshield.getButtonState(BTN_LEFT) == true )
    {
      Serial.println("LEFT button pressed");
      count = count + 1;
    }
        if (evshield.getButtonState(BTN_GO) == true )
    {
      Serial.println("GO button pressed");
      myservo.writeMicroseconds(1590);

    }

    if (evshield.getButtonState(BTN_RIGHT) == true )
    {
      Serial.println("RIGHT button pressed");
      myservo.writeMicroseconds(2060);

    }
  }












  while (count > 1)
  {
    count = 2;
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    orientationx = euler.x();
    orientationy = euler.y();
    orientationz = euler.z();

    while (orientationz > 20 && orientationz < 100)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        SH_Speed_Medium
                                       );
      orientationz = euler.z();
    }

    evshield.bank_a.motorReset();


    while (orientationz < -20 && orientationz > -100)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_a.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Forward,
                                        SH_Speed_Medium
                                       );
      orientationz = euler.z();
    }

    evshield.bank_a.motorReset();


    while (orientationy > 20 && orientationy < 100)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Reverse,
                                        SH_Speed_Medium
                                       );
      orientationy = euler.y();
    }

    evshield.bank_a.motorReset();


    while (orientationy < -20 && orientationy > -100)
    {
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
      evshield.bank_a.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        SH_Speed_Medium
                                       );
      orientationy = euler.y();
    }

    evshield.bank_a.motorReset();

    if (evshield.getButtonState(BTN_LEFT) == true )
    {
      Serial.println("LEFT button SECOND pressed");
      count = count - 1;
    }
        if (evshield.getButtonState(BTN_GO) == true )
    {
      Serial.println("GO button pressed");
      myservo.writeMicroseconds(1590);

    }

    if (evshield.getButtonState(BTN_RIGHT) == true )
    {
      Serial.println("RIGHT button pressed");
      myservo.writeMicroseconds(2060);

    }
  }






  delay(BNO055_SAMPLERATE_DELAY_MS);
}

