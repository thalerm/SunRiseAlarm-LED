/*
 * Austin Tarango
 * Jan 10, 2017
 * Sunrise Alarm Code
 * 
 * Changes for Time Control by Markus Thaler
 * Aug 20, 2018
 */
#include <DS3231.h> //Include the clock library
#include <EEPROM.h> //Include EEPROM library for storage while shut off

// Initialization
int fadeTime = 30; // How long the light will fade to max
int uled = 9; // Set pinout with with PWM

//not necessary to change time here, change in matrix!!
int setHour = 6; // hours to wake (military time)
int setMin = 30; // minute to wake

byte light; //boolean nightlight on/off
byte changeMode; //boolean changemode on/off
byte newTime; //new time after changemode
//possible time settings --> index 0 = 1 LED-blink, 1 = 2 ... --> indicates time set
int timeMatrix[5][3] = {
  {0,  5, 30  },
  {1,  6, 0  },
  {2,  6, 30  },
  {3,  7, 0  },
  {4,  7, 30  },
};

// Set up Vars
DS3231  rtc(SDA, SCL);
Time t;
void start();
void showTime();
 
void setup()
{
  pinMode(uled, OUTPUT);
  Serial.begin(9600); // Match to serial monitor
  rtc.begin();

//read EEPROM (internal storage)
  light = EEPROM.read(0);
  changeMode = EEPROM.read(1);
  newTime = EEPROM.read(2);

//set to 0 at initial start, in case EEPROM is corrupted
   if (light != 0 && light != 1){
    EEPROM.write(0, 0);
    light = EEPROM.read(0);
   }
   if (changeMode != 0 && changeMode != 1){
    EEPROM.write(1, 0);
    changeMode = EEPROM.read(1);
   }
   if (newTime < 0 || newTime > sizeof(timeMatrix)){
    EEPROM.write(2, 0);
    newTime = EEPROM.read(2);
   }

//Light off --> show current Alarmtime
  if (!light && !changeMode){
    showTime();
  }

//Light on 
  if (light && !changeMode){
    analogWrite(uled, 200);
    EEPROM.write(0, 0);
  }
  
//Changemode --> turn off while blinking to change Time     
   if (changeMode){
    EEPROM.write(2, newTime + 1);
    int counter2=0;
    while(counter2<20){
      analogWrite(uled, 50);
      delay(100);
      analogWrite(uled, 0);
      delay(100);
      counter2=counter2+1;
    }
    EEPROM.write(2, newTime);
    delay(500);
    showTime();
   }
//set new Time 
  setHour = timeMatrix[newTime][1];
  setMin = timeMatrix[newTime][2];

//Activate Changemode  
  EEPROM.write(1, 1);
  delay(3000);
  EEPROM.write(1, 0);

/*Debug
Serial.print("Settings: ");
Serial.print(light);
Serial.print(changeMode);
Serial.print(newTime);
Serial.print(" Time: ");
Serial.print(setHour);
Serial.print(setMin);
*/
}

//show time with light
void showTime(){
    int counter=0;
    while (counter<=newTime){
      analogWrite(uled, 50);
      delay(300);
      analogWrite(uled, 0);
      delay(300);
      counter=counter+1;
    }   
    EEPROM.write(0, 1);
}

void loop()
{
  t = rtc.getTime(); // Make a time class called 't'


  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());

  // Send Start Time
  Serial.print(" -- Time Set: ");
  Serial.print(setHour);
  Serial.print(setMin);

  if (t.hour == setHour && t.min == setMin) // Check if it's time to wake up!
  {
    start();
  }
  
  // Wait one second before repeating
  delay (1000);
}

void start()
{
  // Fix for SB LED
  analogWrite(uled, 1);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 2);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 3);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 4);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 4);
  delay((fadeTime * 60000)/50);
  analogWrite(uled, 5);
  delay((fadeTime * 60000)/50);


  // Fade script
  for (int i = 6 ; i <= 255; i++)
  {
    analogWrite(uled, i);
    delay(((fadeTime * 60000)/306));
    Serial.print(" mil sec ");
    Serial.print(((fadeTime * 60000)/306));
    Serial.print(" PWM " );
    Serial.print(i);


  }
  
  delay(90000); // Stay Bright
  analogWrite(uled, 0); // Turn off
  
}

