// VS Code / PlatformIO Arduino Code
// 4 IR Sensor Line Follower Robot
// Added delay + hold time for sharp turns

#include <Arduino.h>

//  IR Sensors 
#define IR_SENSOR_RIGHT_OUTER 11
#define IR_SENSOR_RIGHT_INNER 12
#define IR_SENSOR_LEFT_INNER 13
#define IR_SENSOR_LEFT_OUTER A0

//  Motor Speed 
#define MOTOR_SPEED 170
#define TURN_SPEED 180

//  Delay 
#define SHARP_TURN_DELAY 210   // increase if missing sharp turn
#define SLIGHT_TURN_DELAY 50

// Right Motor 
const int enableRightMotor = 6;
const int rightMotorPin1 = 7;
const int rightMotorPin2 = 8;

//  Left Motor 
const int enableLeftMotor = 5;
const int leftMotorPin1 = 9;
const int leftMotorPin2 = 10;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed);


void setup()
{
    // PWM frequency tweak for pins 5 & 6
    TCCR0B = TCCR0B & B11111000 | B00000010;

    // Motor Pins
    pinMode(enableRightMotor, OUTPUT);
    pinMode(rightMotorPin1, OUTPUT);
    pinMode(rightMotorPin2, OUTPUT);

    pinMode(enableLeftMotor, OUTPUT);
    pinMode(leftMotorPin1, OUTPUT);
    pinMode(leftMotorPin2, OUTPUT);

    // Sensor Pins
    pinMode(IR_SENSOR_RIGHT_OUTER, INPUT);
    pinMode(IR_SENSOR_RIGHT_INNER, INPUT);
    pinMode(IR_SENSOR_LEFT_INNER, INPUT);
    pinMode(IR_SENSOR_LEFT_OUTER, INPUT);

    rotateMotor(0, 0);
}


void loop()
{
    int RO = digitalRead(IR_SENSOR_RIGHT_OUTER);
    int RI = digitalRead(IR_SENSOR_RIGHT_INNER);
    int LI = digitalRead(IR_SENSOR_LEFT_INNER);
    int LO = digitalRead(IR_SENSOR_LEFT_OUTER);

    // Stop (all sensors on black)
    if (RO == HIGH && RI == HIGH && LI == HIGH && LO == HIGH)
    {
        rotateMotor(0, 0);
    }

    // Straight
    else if (RO == LOW && RI == LOW && LI == LOW && LO == LOW)
    {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }

    // Sharp Right
    else if (RO == HIGH)
    {
        rotateMotor(TURN_SPEED, -TURN_SPEED);
        delay(SHARP_TURN_DELAY);
    }

    // Slight Right
    else if (RI == HIGH)
    {
        rotateMotor( MOTOR_SPEED, 140);
        delay(SLIGHT_TURN_DELAY);
    }

    // Sharp Left
    else if (LO == HIGH)
    {
        rotateMotor(-TURN_SPEED, TURN_SPEED);
        delay(SHARP_TURN_DELAY);
    }

    // Slight Left
    else if (LI == HIGH)
    {
        rotateMotor(140,MOTOR_SPEED);
        delay(SLIGHT_TURN_DELAY);
    }

    else
    {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
    // Right Motor
    if (rightMotorSpeed < 0)
    {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
    }
    else if (rightMotorSpeed > 0)
    {
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
    }
    else
    {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, LOW);
    }

    // Left Motor
    if (leftMotorSpeed < 0)
    {
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
    }
    else if (leftMotorSpeed > 0)
    {
        digitalWrite(leftMotorPin1, HIGH);
        digitalWrite(leftMotorPin2, LOW);
    }
    else
    {
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, LOW);
    }

    analogWrite(enableRightMotor, abs(rightMotorSpeed));
    analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}