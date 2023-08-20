#define BLYNK_PRINT Serial          //Enable Wifi module and Blynk fx
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "";     // You should get Auth Token in the Blynk App. Go to the Project Settings (nut icon).
char ssid[] = "";                            // Your WiFi credentials.  
char pass[] = "";                         // Set password to "" for open networks.

/*
 * Using phone hotspot
 */

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 4);      // RX, TX for the SPEEEduino

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);   //To initalise LCD-I2C

#define ESP8266_BAUD 9600           //Setting ESP module
ESP8266 wifi(&EspSerial);

BlynkTimer timer;                   //Initalise 'timer' FX

int SpeedPin = 9;                   //Speed control to Pin9 due to PWM
int A_Win = 6;                      //AWin to Pin6
int B_Win = 7;                      //BWin to Pin7
int Piezo = 11;                     //Piezo to Pin11 due to Gnd point


/*Could not get FX calls to work, hence stuff everything in a single FX*/
void VoltOut()                      //Seperate FX as void loop needs to be clear for Blynk to work
{
  int AnalogValsWind[50];             // Initialise array size of 50, for wind
  int AnalogPinWind= A1;              // Use A3 as windmill input
  int RawWind=0;                      //Value to store raw wind array output
  float TotalWind=0;                  //Value to store converted wind array output, float to allow for decimal points

  int AnalogValsSolar[50];            // Initialise array size of 50, for solar
  int AnalogPinSolar= A0;             // Use A2 as Solar input
  int RawSolar=0;                     //Value to store raw solar array output
  float TotalSolar=0;                 //Value to store converted solar array output

  for (int i=0; i<50; i++)            //Speed control using var 'SpeedValue'
  {
    for (int SpeedValue = 120 ; SpeedValue <= 255; SpeedValue == SpeedValue)
    {
     analogWrite(SpeedPin, SpeedValue);// Outputs for Speed control

      int Reading = digitalRead;//AWin, Bwin FX    
      Reading = digitalRead (B_Win); 
      Reading = digitalRead (A_Win);   
      
      
      if  (digitalRead(B_Win) == HIGH && digitalRead(A_Win) == LOW)// BWin =  2 fast bleeps  
        { 
          digitalWrite(Piezo, HIGH); 
          delay(100);
          digitalWrite(Piezo, LOW);
          delay(100);
          digitalWrite(Piezo, HIGH); 
          delay(100);
          digitalWrite(Piezo, LOW);
          delay(100);
        } 
      
      if (digitalRead(A_Win) == HIGH && digitalRead(B_Win) == LOW)// AWin = 1 long bleep
        {
          digitalWrite(Piezo, HIGH);
          delay(2000);
          digitalWrite(Piezo, LOW);
        }
       if (digitalRead(A_Win) == HIGH && digitalRead(B_Win) == HIGH) // Default = no sound
        {
          digitalWrite(Piezo, LOW);
        }
           
     AnalogValsWind[i] = analogRead(AnalogPinWind);  //Store input of A1 into array
     delay(1000);                                    //wait 1 Ssecond between recordings
     RawWind += AnalogValsWind[i];                    // Add all items in array together for wind
     TotalWind = RawWind*0.0049;                      //Convert to voltage
    
     AnalogValsSolar[i]= analogRead(AnalogPinSolar); //Store input of A2 into array
     delay(1000);                                    //wait 1 Ssecond between recordings
     RawSolar += AnalogValsSolar[i];                  // Add all items in array together for solar
     TotalSolar = RawSolar*0.0049;                    //Convert to voltage
  
     float TotalVolt=TotalWind+TotalSolar;            //Calculate total voltage for Blynk
    
     Blynk.virtualWrite(V0, TotalWind);               //Send info to Blynk
     Blynk.virtualWrite(V1, TotalSolar);
     Blynk.virtualWrite(V2, TotalVolt);
  
     lcd.setCursor(0, 0);         // move cursor to (0, 0), the top row
     lcd.print("Solar: ") ;       //For solar voltage output
     lcd.print(TotalSolar, 2);
     lcd.print(" w");
     lcd.setCursor(0, 1);         // move cursor to   (0, 1), the second row
     lcd.print("Wind : ") ;       //For wind voltage output
     lcd.print(TotalWind, 2);        
     lcd.print(" w");
    }
  }
}

void setup()
{
  Serial.begin(9600);                                 //Activate serial connection
  delay(10);
  EspSerial.begin(ESP8266_BAUD);                      // Set ESP8266 baud rate
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);                //Use credential to connect blynk

  lcd.begin(16, 2);                                   //Activates LCD
  lcd.backlight();

  pinMode(SpeedPin, OUTPUT);                          //Setting all pin modes
  pinMode(Piezo, OUTPUT);  
  
  pinMode(B_Win, INPUT);    
  pinMode(A_Win, INPUT);     

  timer.setInterval(0100, VoltOut);       //Call fx every 0.1 second
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer and runs
}
