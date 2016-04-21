
#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_EV3Ultrasonic.h>
#include <Servo.h>
EVShield          evshield(0x34, 0x36);
EVs_EV3Ultrasonic myUS;
EVs_EV3Ultrasonic myUS2;
Servo myservo;
// 1250 is just touching table, 2070 is at resting place
int avgd;
int distance;
int objectd;

long rotationcar = 3;
long rotationcarback = 4;
long rotationwheel = 2;
long rotationwheel2 = 1;
long rotationwheel3 = 1;
char str[40];
int ledPin = 9;


void setup() {


  Serial.begin(115200);
  Serial.println ("Start...");
  evshield.init( SH_HardwareI2C );

  Serial.println ("------------------");
  Serial.println ("Starting Program");
  Serial.println ("----------------");

  Serial.println ("Press GO button to continue");
  evshield.waitForButtonPress(BTN_GO);
  evshield.bank_a.motorReset();
  evshield.bank_b.motorReset();
  myservo.attach(8);

  myUS.init( &evshield, SH_BAS1 );
  myUS2.init( &evshield, SH_BAS2 );
  myUS.setMode(MODE_Sonar_CM);
  myUS2.setMode(MODE_Sonar_CM);

  myservo.writeMicroseconds(2060);

}

void forward()
{
  Serial.println("Forward");
  distance = myUS.getDist()
             ; Serial.print("Distance in cm: "); Serial.println(distance);
  Serial.println(str);
  str[0] = '\0';


  evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                    SH_Direction_Reverse,
                                    SH_Speed_Full
                                    //rotationwheel,
                                    //SH_Completion_Dont_Wait
                                    //SH_Next_Action_BrakeHold
                                   );
  evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                    SH_Direction_Reverse,
                                    SH_Speed_Medium
                                    //rotationwheel,
                                    //SH_Completion_Dont_Wait
                                    //SH_Next_Action_BrakeHold
                                   );
  ; distance = myUS.getDist();
  ; objectd = myUS2.getDist();
}

void floor()
{
  {
    ; Serial.println("Floor Detected");
    Serial.println(str);
    str[0] = '\0';
    delay(500);
    evshield.bank_b.motorRunRotations(SH_Motor_Both,
                                      SH_Direction_Forward,
                                      SH_Speed_Slow,
                                      rotationwheel2,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    str[0] = '\0';
    delay(500);
    evshield.bank_b.motorRunRotations(SH_Motor_1,
                                      SH_Direction_Forward,
                                      SH_Speed_Slow,
                                      rotationwheel,
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_BrakeHold
                                     );
    str[0] = '\0';
    delay(500);
    evshield.bank_b.motorRunRotations(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      SH_Speed_Slow,
                                      rotationwheel,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    evshield.bank_b.motorReset();
    loop();
  }
}

void floorObject()
{
  {
    ; Serial.println("Floor Detected");
    Serial.println(str);
    str[0] = '\0';
    delay(500);
    evshield.bank_b.motorRunRotations(SH_Motor_Both,
                                      SH_Direction_Forward,
                                      SH_Speed_Slow,
                                      rotationwheel2,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    str[0] = '\0';
    delay(500);
    evshield.bank_b.motorRunRotations(SH_Motor_1,
                                      SH_Direction_Forward,
                                      SH_Speed_Slow,
                                      rotationwheel,
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_BrakeHold
                                     );
    str[0] = '\0';
    delay(500);
    evshield.bank_b.motorRunRotations(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      SH_Speed_Slow,
                                      rotationwheel,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    evshield.bank_b.motorReset();
  }
}

void objectCheck()
{
  Serial.println("Object Check");
  evshield.bank_b.motorRunRotations(SH_Motor_1,
                                    SH_Direction_Reverse,
                                    SH_Speed_Slow,
                                    rotationwheel3,
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_BrakeHold
                                   );
  evshield.bank_b.motorRunRotations(SH_Motor_2,
                                    SH_Direction_Forward,
                                    SH_Speed_Slow,
                                    rotationwheel3,
                                    SH_Completion_Wait_For,
                                    SH_Next_Action_BrakeHold
                                   );
  objectd = myUS2.getDist();
  if (objectd < 30)
  {
    Serial.println("Not Object");
    floor();
    loop();
  }
  else if (objectd > 30)
  {
    Serial.println("Object Found");
    while (objectd > 30)
    {
      objectd = myUS2.getDist();
      Serial.println("Searching for Object");
      evshield.bank_b.motorRunUnlimited(SH_Motor_1,
                                        SH_Direction_Forward,
                                        SH_Speed_Slow
                                       );
      evshield.bank_b.motorRunUnlimited(SH_Motor_2,
                                        SH_Direction_Reverse,
                                        SH_Speed_Slow
                                       );
    }
    delay(1000);
    evshield.bank_b.motorReset();
    while (objectd > 7)
    {
      objectd = myUS2.getDist();
      Serial.println("Preparing to Hook");
      evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                        SH_Direction_Reverse,
                                        SH_Speed_Slow
                                       );
      objectd = myUS2.getDist();
    }
    evshield.bank_b.motorReset();
    lift();
  }

}

void objectDetected()
{
  objectd = myUS2.getDist();
  Serial.println("Object Detected");
  evshield.bank_b.motorRunUnlimited(SH_Motor_Both,
                                    SH_Direction_Reverse,
                                    SH_Speed_Medium
                                   );
  objectd = myUS2.getDist();
}

void lift()
{
  Serial.println("Lifting Object");
  myservo.writeMicroseconds(1590);
  digitalWrite(ledPin, HIGH);
  delay(3000);
  evshield.bank_a.motorRunRotations(SH_Motor_2,
                                    SH_Direction_Forward,
                                    SH_Speed_Medium,
                                    rotationcar,
                                    SH_Completion_Wait_For,
                                    SH_Next_Action_BrakeHold
                                   );
  myservo.writeMicroseconds(1750);
  delay(3000);
  evshield.bank_a.motorRunRotations(SH_Motor_1,
                                    SH_Direction_Forward,
                                    SH_Speed_Medium,
                                    rotationwheel,
                                    SH_Completion_Wait_For,
                                    SH_Next_Action_BrakeHold
                                   );
  delay(2000);

  objectd = myUS2.getDist();
  if (objectd > 30)
  {
    Serial.println(" Object on Hook");
    myservo.writeMicroseconds(2080);
    digitalWrite(ledPin, LOW);
    delay(3000);
    evshield.bank_a.motorRunRotations(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      SH_Speed_Medium,
                                      rotationwheel,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    objectd = myUS2.getDist();
    objectd = myUS2.getDist();
    while (objectd > 10)
    {
      Serial.println("Finding Drop point");
      objectd = myUS2.getDist();
      distance = myUS.getDist();
      objectd = myUS2.getDist();
      forward();
      if (objectd < 10)
      {
        evshield.bank_b.motorReset();
        evshield.bank_b.motorRunRotations(SH_Motor_Both,
                                          SH_Direction_Reverse,
                                          SH_Speed_Medium,
                                          rotationwheel2,
                                          SH_Completion_Wait_For,
                                          SH_Next_Action_BrakeHold
                                         );
        drop();
      }
    }

  }
  else if (objectd < 20)
  {
    Serial.println(" Object not on Hook");
    myservo.writeMicroseconds(2060);
    delay(3000);
    evshield.bank_a.motorRunRotations(SH_Motor_1,
                                      SH_Direction_Reverse,
                                      SH_Speed_Medium,
                                      rotationwheel,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    evshield.bank_a.motorRunRotations(SH_Motor_2,
                                      SH_Direction_Reverse,
                                      SH_Speed_Medium,
                                      rotationcarback,
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_BrakeHold
                                     );
    evshield.bank_b.motorRunRotations(SH_Motor_Both,
                                      SH_Direction_Forward,
                                      SH_Speed_Medium,
                                      rotationwheel,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_BrakeHold
                                     );
    loop();
  }
}

void drop()
{
  myservo.writeMicroseconds(1590);
  delay(3000);
  evshield.bank_a.motorRunRotations(SH_Motor_2,
                                    SH_Direction_Reverse,
                                    SH_Speed_Medium,
                                    rotationcarback,
                                    SH_Completion_Wait_For,
                                    SH_Next_Action_BrakeHold
                                   );
  myservo.writeMicroseconds(2060);
  delay(2000);
  floor();
}

void loop() {

  distance = myUS.getDist();
  objectd = myUS2.getDist();

  while (distance < 32 && distance > 28 )
  {
    forward();
  }

  evshield.bank_b.motorReset();

  if (distance > 34)
  {
    floor();
    ; Serial.println("Floor Detected");

  }

  if (objectd < 40)
  {
    distance = myUS.getDist();
    objectd = myUS2.getDist();
    while (objectd > 15)
    {
      distance = myUS.getDist();
      objectd = myUS2.getDist();
      objectDetected();
      if (distance > 34)
      {
        evshield.bank_b.motorReset();
        Serial.println("Floor Detected");
        floor();
      }
    }
    evshield.bank_b.motorReset();
    distance = myUS.getDist();
    objectd = myUS2.getDist();
    if (objectd < 18)// && distance < 30)
    {
      objectCheck();
    }
    objectd = myUS2.getDist();
    if (distance > 32)
    {
      floor();
    }
    else if (objectd > 40)
    {
      loop();
    }
  }

  evshield.bank_b.motorReset();

  if (distance > 34)
  {
    evshield.bank_b.motorReset();
    Serial.println("Floor Detected OOPS");
    floor();
    evshield.bank_b.motorReset();
  }




}




