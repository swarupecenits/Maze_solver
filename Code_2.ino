#include <NewPing.h>

#define TRIGGER_PIN_1  A0   // For Front Sensor.
#define ECHO_PIN_1     A1   
#define TRIGGER_PIN_2  A2   // For Left Sensor.
#define ECHO_PIN_2     A3
#define TRIGGER_PIN_3  A4  // For Right Sensor.
#define ECHO_PIN_3     A5
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing fSensor(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing lSensor(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing rSensor(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);

int motor_lA = 7;
int motor_lB = 6;
int motor_enableA = 9;
int lspeed = 80;

int motor_rA = 4;
int motor_rB = 5;
int motor_enableB = 3;
int rspeed = 79;

void setup() {
  int front_distance = fSensor.ping_cm();
  int left_distance = lSensor.ping_cm();
  int right_distance = rSensor.ping_cm();
  pinMode(motor_lA,OUTPUT);   //left motors forward
  pinMode(motor_lB,OUTPUT);   //left motors reverse
  pinMode(motor_enableA, OUTPUT);

  pinMode(motor_rA,OUTPUT);   //right motors forward
  pinMode(motor_rB,OUTPUT);   //rignt motors reverse
  pinMode(motor_enableB, OUTPUT);

  analogWrite(motor_enableA, 0);
  analogWrite(motor_enableB, 0);
  Serial.begin(9600);
}
  void MoveFront(){
  digitalWrite(motor_lA,1);
  digitalWrite(motor_lB,0);
  digitalWrite(motor_rA,1);
  digitalWrite(motor_rB,0);
  analogWrite(motor_enableA, lspeed);
  analogWrite(motor_enableB, rspeed);
  // delay(300);
}

void MoveRight(){
  digitalWrite(motor_lA,1);
  digitalWrite(motor_lB,0);
  digitalWrite(motor_rA,0);
  digitalWrite(motor_rB,1);
  analogWrite(motor_enableA, (lspeed));
  analogWrite(motor_enableB, (rspeed));
  // delay(300);
}

void MoveLeft(){
  digitalWrite(motor_lA,0);
  digitalWrite(motor_lB,1);
  digitalWrite(motor_rA,1);
  digitalWrite(motor_rB,0);
  analogWrite(motor_enableA, (lspeed));
  analogWrite(motor_enableB, (rspeed));
//  delay(300);
}

void Stop(){
  digitalWrite(motor_lA,0);
  digitalWrite(motor_lB,0);
  digitalWrite(motor_rA,0);
  digitalWrite(motor_rB,0);
  analogWrite(motor_enableA, 0);
  analogWrite(motor_enableB, 0);
//  delay(300);
}

void loop() {
  MoveFront();
    int front_distance = fSensor.ping_cm();
  int left_distance = lSensor.ping_cm();
  int right_distance = rSensor.ping_cm();
  Serial.print("front = ");
  Serial.println(front_distance);
  Serial.print("Left = ");
  Serial.println(left_distance);
  Serial.print("Right = ");
  Serial.println(right_distance);  
  delay(50);

  if(front_distance > 20){
    MoveFront();
  }
    else{
      delay(150);
      Stop();
      if(right_distance >left_distance){
      MoveRight();
    }
    else if(left_distance > right_distance){
      MoveLeft();
    }
    }
    
  delay(250);

}
