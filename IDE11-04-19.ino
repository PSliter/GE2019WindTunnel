/*
IDE for wind tunnel desing based on 2 force sensitive resistors fcr1 and fcr2
fcr1 measures the drag
fcr2 measures the lift
lift is calculated by finding the weight of the objcet before any wind is applied and then subtracting the weight of the object during the trial any change in observed weight is assumed to be caused by lift
*/
const int newB=7;
//Threshhold values for determining whether the test experiences low, medium, or high lift/drag
const int lowDrag=20;
const int highDrag=50;
const int lowLift=20;
const int highLift=50;

int fcr1 = 0;              //this variable will hold a value based on the force applied to the sensor downstream of the object
int fcr2=0;               // This variable will hold a value based on the force applied to the bottom sensor
int newV=0;
int defW=0;
int deltaW=0;
//double drag=0;                     // Float for the calculated drag value
#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

void setup()
{
  Serial.begin(9600);               //start a serial connection with the computer
  
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display

  pinMode(newB,INPUT);
}

void loop()
{
  newV=digitalRead(newB);
  fcr1 = analogRead(A0);   //set sensor to a number between 0 and 1023 based on the force for this sensor
  fcr2 = analogRead(A1);    // set sensor to a number between 0 and 1023 based on force for this sensor
  Serial.print(fcr1);    //print the value of sensor in the serial monitor on the computer
  Serial.print("\t");
  Serial.print(fcr2);   //print value of sensor in serial mon.
  Serial.print("\t");
  Serial.print(digitalRead(newB));   //print value of sensor in serial mon.
  
  Serial.print("\t");
  Serial.print(defW);
  
  //On button press set a new default weight of object
  if (newV==1){
    defW=fcr2;
  }
  
  deltaW = defW - fcr2;
  Serial.print("\t");
  Serial.println(deltaW);   //print value of sensor in serial mon.
  //String fcr1cnst= String(fcr1);
  //String fcr2cnst= String(deltaW);
  //if the photoresistor value is below the threshold turn the light on, otherwise turn it off
  lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
  lcd.print("Drag:");
  lcd.setCursor(7,0);
  //lcd.print(fcr1cnst.substring(0,3));      
  if (fcr1<lowDrag){
    lcd.print("LOW");
  }
  else if(fcr1>highDrag){
    lcd.print("HIGH");
  }
  else{
    lcd.print("MED.");
  }

  lcd.setCursor(0,1);               //move the cursor to the first space of the bottom row
  lcd.print("Lift:");
  lcd.setCursor(7,1);
  
  if (deltaW<lowLift){
    lcd.print("LOW");
  }
  else if(deltaW>highLift){
    lcd.print("HIGH");
  }
  else{
    lcd.print("MED.");
  }
  //lcd.print(fcr2cnst.substring(0,3));         
  delay(50);                       //short delay to make the printout easier to read
}
