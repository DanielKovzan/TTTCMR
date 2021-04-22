/*
*#################################################
*The TTTCMR
*By Daniel Kovzan, Mark Dee, Clintano Perrins and Gatis Berzins
*Modified By Daniel Kovzan 01:49 19/04/2021
*#################################################
*/
#define BLYNK_PRINT Serial 
#include <Wire.h>
#include <RTClib.h>
#include <Bridge.h>
#include <BlynkSimpleYun.h>
RTC_DS1307 RTC;

// You should get Auth Token in the Blynk App.
char auth[] = "YourAuthToken";

static unsigned long lastTick = 0;
int curMin = 0,curHour = 0, userChoice = 0;
int seconds, minute, hour;

//Blynk Menu Setup, hope it works
//I think that you need to restart the program eahc time you wish to change timezone since i donty think the program ever returns to this piece of code
BLYNK_WRITE(V1) {
  switch (param.asInt())
  {
    case 1: // Ireland
      userChoice = 1;
      break;
    case 2: // Russia
      userChoice = 2;
      break;
    case 3: // USA
      userChoice = 3;
      break;
     case 4: // China
      userChoice = 4;
      break;
     case 5: // Germany
      userChoice = 5;
      break;
      
    default:
      Serial.println("Unknown item selected");
  }
}

//############################################################################
void setup() {
  // put your setup code here, to run once:
  for (int i=1; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
  Blynk.begin(auth);
  
  Wire.begin();
  RTC.begin();
 
  DateTime now = RTC.now();
  seconds = now.second();
  minute = now.minute();
  hour;
  //TimeZone is chosen by the menu form Blynk
  //This manually changes the time depedning on the difference from our local timezone
  //Eg. USA is GMT -4 and since we are GMT +1 then having the hours go -5 would make it American time
  if(userChoice = 1)//Ireland
    hour = now.hour();
  else if(userChoice = 2)//Russia
    hour = now.hour() + 2;
  else if(userChoice = 2)//USA
    hour = now.hour() - 5;
  else if(userChoice = 2)//China
    hour = now.hour() + 8;
  else if(userChoice = 2)//Germany
    hour = now.hour() + 1;
  else
    hour = now.hour();//If the menu fails, we go back to standart time
}



//##############################################################################
void loop()
{
  Blynk.run();
//Seconds
if(millis() -  lastTick >1000)
{
  lastTick = millis();
  seconds++;
}
//Minutes
if(seconds >= 60)
{
  minute++;
  seconds = 0;
}
//Hours
if(minute >= 60)
  {
    hour++;
    minute = 0;
  }

//When the hour goes becomes 24, it goes back to 0 since it cant get to 25
  if (hour >=24) {
hour=0;
minute = 0; 
}

curMin = minute % 10;//gets the right side of minutes
curHour = hour % 10;//gets the right side of the hours

//############################################################################
//Minutes Output

//Pin 1 Binary 1 min
if(curMin == 1 || curMin == 3 || curMin == 5 || curMin == 7 || curMin == 9)
  digitalWrite(1, HIGH);
else
  digitalWrite(1, LOW);
  
//pIN 2 bINARY 2 min
if(curMin == 2 || curMin == 3 || curMin == 6 || curMin == 7 )
  digitalWrite(2, HIGH);
else
  digitalWrite(2, LOW);
  
//pin 3 binary 4 min
if(curMin == 4 || curMin == 5 || curMin == 6 || curMin == 7)
  digitalWrite(3, HIGH);
else
  digitalWrite(3, LOW);
  
  //pin 4 binary 8 min
if(curMin == 8 || curMin == 9)
  digitalWrite(4, HIGH);
else
  digitalWrite(4, LOW);

//--------------------------------------------------------------------------------------
  
//Tens of Minutes

//Pin 5 10 mins
if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60)) {
   digitalWrite(5, HIGH);
} else {
   digitalWrite(5,LOW);
}

//Pin 6 20 mins
if(minute >= 20 && minute < 40) {
   digitalWrite(6, HIGH);
} else {
   digitalWrite(6,LOW);
}

//Pin 7 40 mins
if(minute >= 40 && minute < 60) {
   digitalWrite(7, HIGH);
} else {
   digitalWrite(7,LOW);
}

//#########################################################################################
//#########################################################################################
//#########################################################################################
//Hours Output

//Pin 8 Binary 1 hour
if(curHour == 1 || curHour == 3 || curHour == 5 || curHour == 7 || curHour == 9)
  digitalWrite(8, HIGH);
else
  digitalWrite(8, LOW);
  
//pIN 9 bINARY 2 hour
if(curHour == 2 || curHour == 3 || curHour == 6 || curHour == 7 )
  digitalWrite(9, HIGH);
else
  digitalWrite(9, LOW);
  
//pin 10 binary 4 hour
if(curMin == 4 || curMin == 5 || curMin == 6 || curMin == 7)
  digitalWrite(10, HIGH);
else
  digitalWrite(10, LOW);
  
  //pin 11 binary 8 hour
if(curMin == 8 || curMin == 9)
  digitalWrite(11, HIGH);
else
  digitalWrite(11, LOW);

//--------------------------------------------------------------------------------------
  
//Tens of Hours

//Pin 12 10 Hours
if(hour >= 10 && hour < 20) {
   digitalWrite(12, HIGH);
} else {
   digitalWrite(12,LOW);
}

//Pin 13 20 - 24 hours
if(hour >= 20 && hour < 24) {
   digitalWrite(13, HIGH);
} else {
   digitalWrite(13,LOW);
}
//#########################################################################################










  
  

}
