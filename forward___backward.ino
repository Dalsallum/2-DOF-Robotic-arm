
#include <Servo.h>

Servo servo1;
Servo servo2;

const float pi = 3.14159;
const float L1 = 6; // the length of the first arm in cm
const float L2 = 4; // the length of the second arm in cm
float x; // the first coordinate
float y; // the second coordinate
float q1; // the angle of the first motor in radian
float Q1; // the angle of the first motor in degree
float q2; // the angle of the second motor in radian
float Q2; // the angle of the second motor in degree
float q ; // the sum of q1+q2 in radian ( in inverse kinematic it's known )
float Q ; // the sum of Q1+Q2 in degree ( in inverse kinematic it's known )
const int button1pin = 6;
const int button2pin = 7;
int button1state = LOW; // first button is for forward kinematics
int button2state = LOW; // second button is for backward kinematics
float x1 ; // // to calculate x to the power of 2
float y1 ; // // to calculate y to the power of 2
float L1p ; // to calculate L1 to the power of 2
float L2p ; // to calculate L2 to the power of 2


void setup() {
  
servo1.attach(2);
servo2.attach(3);
pinMode (button1pin ,INPUT);
pinMode (button2pin ,INPUT);
Serial.begin(9600); 

}

void loop() {
  

button1state = digitalRead(button1pin);
button2state = digitalRead(button2pin);

if (button1state == HIGH) // if button 1 is pressed , assume forward kinematics , the known variables are : Q1,Q2 
{
  Q1 = 40; // assume first angle 40 degree
  Q2 = 60; // assume second anagle 60 degree , Q1 , Q2 values are assumptions now, later they will be inputted by the user
  Q = Q1 + Q2 ; // Q = 100
  q1 = Q1*pi/ 180 ;// to convert q1 to radian , q1 = 0.698 
  q2 = Q2*pi/ 180 ;// to convert q2 to radian , q2 = 1.047
  q = Q*pi/180 ; // Q = 100 degree , q = 1.745 
  x = L1*cos(q1) + L2*cos(q); // the expected value of x , x= 3.9
  y = L1*sin(q1) + L2*sin(q);  // the expected value of y , y=7.798
  servo1.write(Q1); 
  servo2.write(Q2);
  
}

if (button2state == HIGH) // if button 2 pressed assume inverse kinematics , the known variables are : X,Y,Q
{
  x = 5; 
  y = 5; // assumed values of x and y for the desired end effector position , later these values will be inputted by the user
  Q = 100; // assume Q which is the sum of Q1+Q2
  q = Q*pi/180 ;
  x1 = pow(x,2); //X^2
  y1 = pow(y,2); //y^2
  L1p = pow(L1,2); // L1^2
  L2p = pow(L2,2); //L2^2
  q1 = acos((x1+y1-(L1p+L2p))/(2*L1*L2)); // q1 in radian = 1.61
  q2 = q - q1 ; // q2 in radian = 0.135
  Q1 = q1*180/pi ; // Q1 in degree = 92.24
  Q2 = q2*180/pi; // Q2 in degree = 7.734
  servo1.write(Q1); 
  servo2.write(Q2); // the two servos will move with an angle of Q1,Q2 so the end effector will reach x,y
  
}
}
