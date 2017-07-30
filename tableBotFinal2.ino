#include <Servo.h> //imports the servo library


//initialize servo objects
Servo rightMotor;
Servo leftMotor;

//initialize distance sensor variables
int triggerPin = 8;
int echoPin    = 9;
int limit = 6;
int duration;
int distance;

//initialize timing loop variables
int previousMillis;
int interval;


//setup only runs once
void setup() {
  Serial.begin(9600);           //begin serial communication

  //tells the arduino whether the pins should output or receive input
  pinMode(triggerPin, OUTPUT);  
  pinMode(echoPin, INPUT);

  //tells the arduino what pins will control which servos
  rightMotor.attach(13);
  leftMotor.attach(12);
  
}

//The loop repeats until the arduino is shut down
void loop() { 
  if(millis() - previousMillis >= interval){
    distance = sensorValue();   //sets the distance variable as the returned output from the sensorValue function
    stateMachine(distance);     //evaluates whether to turn left or continue forward
    previousMillis = millis();  
  }
}

int sensorValue(){
  //sends an ultrasonic pulse 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);        // must keep the trig pin high for at least 10us
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); //measures the time taken for the pulse to return
  distance = (duration/2)/29;   //calculates distance by the speed of sound
  Serial.println(distance);
  return distance;
}

//this function decides whether to turn the robot
void stateMachine(int distance){
  //move forward
  if(distance > limit){
    rightMotor.write(180);
    leftMotor.write(0);  
  }
  //turn left
  else{
    unsigned long timeToTurnLeft = 1100; // it takes around 1.1 seconds to turn 90 degrees
    unsigned long turnStartTime = millis(); // save the time that we started turning

    while((millis()-turnStartTime) < timeToTurnLeft){// stay in this loop until timeToTurnLeft (1.1 seconds) has elapsed
      rightMotor.write(180);
      leftMotor.write(180);
    }
  }
}

