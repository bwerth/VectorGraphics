/*=================================
This code demostrates 4-Wire Touch screen 
interfacing with Arduino

blog.circuits4you.com
www.circuits4you.com

4- Wire Touchscreen Connections
A0=====X+
A1=====X-
A2=====Y+
A3=====Y-
=================================*/
//Define your Touch screen connections
const byte Y1 = A0;
const byte X1 = A1;
const byte Y2 = A2;
const byte X2 = A3;
const byte TOUCH = A5;
int Ymax = 185;
int Xmax = 450;
Servo panservo;
Servo tiltservo;
//Define your screen resolution as per your Touch screen (Max: 1024)
#define Xresolution 1024 //128
#define Yresolution 512 //64

void setup()
{
   panservo.attach(10);
   tiltservo.attach(11);
   Serial.begin(9600);
   while(!Serial){
    // wait for serial point to connect
  }
  Serial.println("BEGINNING");
  while (Serial.read()!='1'){
    //Wait for MATLAB to send a byte over serial to the Arduino
    //Allows us to hit Run on MATLAB and have the Arduino collect data again
  }
}

void loop(){
  if (isTouched()){
    delay(5);
    while (isTouched()){
      pinMode(TOUCH,INPUT);
      int X,Y; //Touch Coordinates are stored in X,Y variable
      pinMode(Y1,INPUT);
      pinMode(Y2,INPUT);  
      digitalWrite(Y2,LOW);
      pinMode(X1,OUTPUT);
      digitalWrite(X1,HIGH);
      pinMode(X2,OUTPUT);
      digitalWrite(X2,LOW);
      X = (analogRead(Y1))/(1024/Xresolution); //Reads X axis touch position
      X = (X/Xmax)*180;
      pinMode(X1,INPUT);
      pinMode(X2,INPUT);
      digitalWrite(X2,LOW);
      pinMode(Y1,OUTPUT);
      digitalWrite(Y1,HIGH);
      pinMode(Y2,OUTPUT);
      digitalWrite(Y2,LOW);
      Y = (analogRead(X1))/(1024/Yresolution); //Reads Y axis touch position
      Y = (Y/Ymax)*180;
      panservo.write(X);
      tiltservo.write(Y);
    }
  }
  delay(20);
}
boolean isTouched(){
  pinMode(Y1,INPUT);
  pinMode(X1,INPUT);
  pinMode(Y2,OUTPUT);
  digitalWrite(Y2,LOW);
  pinMode(X2,INPUT);
  pinMode(TOUCH,OUTPUT);
  digitalWrite(TOUCH,HIGH);
  int touch_reading = analogRead(X2);
//  Serial.println(touch_reading);
  if (touch_reading<1000){
    return true;
  }
  else{
    return false;
  }
}
